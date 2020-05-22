#include "io.h"
#include "nios2.h"
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "sys/alt_cache.h"
#include "altera_avalon_mailbox_simple.h"
#include "sys/alt_timestamp.h"

#define USE_CUSTOM_INSTRUCTION 1
#define REPETITIONS 50

#define CUSTOM_INSTR_MAC 1
#define CUSTOM_INSTR_MAC_RESULT 2
#define custom_instr_mac(a,b) __builtin_custom_inii (CUSTOM_INSTR_MAC, a, b)
#define custom_instr_mac_ret() __builtin_custom_inii (CUSTOM_INSTR_MAC_RESULT, 0, 0)

#define MATRIX_SIZE (32)
#define LENGTH (MATRIX_SIZE / CORE_COUNT)
#define OFFSET (CORE_ID * LENGTH)

#define MAIN_CORE_ID 0
#define INFINITE_TIMEOUT 0

typedef int matrix_t[MATRIX_SIZE][MATRIX_SIZE];

__attribute__((section(".shared")))
matrix_t a, b, c;

void create_identity_matrix(matrix_t m, int matrix_size)
{
    for(int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            m[i][j] = (i == j ? 1 : 0);
}

void create_increasing_matrix(matrix_t m, int matrix_size)
{
    for(int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            m[i][j] = (i * matrix_size + j) % 0x10;
}

altera_avalon_mailbox_dev* mailbox_open(int cpu_id, char* msg_direction)
{
    char name[28];
    sprintf(name, "/dev/core_%d_avalon_mailbox_%s", cpu_id, msg_direction);
    return altera_avalon_mailbox_open(name, NULL, NULL);
}

void open_all_mailboxes(altera_avalon_mailbox_dev** in, altera_avalon_mailbox_dev** out)
{
    for(int i = 0; i < CORE_COUNT; i++)
    {
        if (i == MAIN_CORE_ID) continue;

        in[i] = mailbox_open(i, "in");
        out[i] = mailbox_open(i, "out");

        if(in[i] && out[i])
            printf("Successful mailbox open for core %d\n", i);
        else
            printf("Failed mailbox open for core %d\n", i);
    }
}

int main()
{
    alt_u32 message[2];

#if (CORE_ID == MAIN_CORE_ID)
    alt_u32 time_start, time_end, total_time;
    altera_avalon_mailbox_dev* mailbox_in_list[CORE_COUNT];
    altera_avalon_mailbox_dev* mailbox_out_list[CORE_COUNT];

    alt_timestamp_start();

    create_increasing_matrix(a, MATRIX_SIZE);
    create_identity_matrix(b, MATRIX_SIZE);

    alt_dcache_flush_all();

    open_all_mailboxes(mailbox_in_list, mailbox_out_list);

    for(int r = 0; r < REPETITIONS; r++)
    {
    printf("Repetition %d\n", r);

    time_start = alt_timestamp(); // START MEASURING TIME

    // Notify each slave core to start
    for(int i = 0; i < CORE_COUNT; i++)
    {
        altera_avalon_mailbox_send(mailbox_in_list[i], message, INFINITE_TIMEOUT, POLL);
    }
#endif

#if (CORE_ID != MAIN_CORE_ID)
    altera_avalon_mailbox_dev* mailbox_out = mailbox_open(CORE_ID, "out");
    altera_avalon_mailbox_dev* mailbox_in = mailbox_open(CORE_ID, "in");

    // Wait for signal from main core
    altera_avalon_mailbox_retrieve_poll(mailbox_in, message, INFINITE_TIMEOUT);
#endif

#if (USE_CUSTOM_INSTRUCTION)
    for (int i = OFFSET; i < OFFSET + LENGTH; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                custom_instr_mac(a[i][k], b[k][j]);
            }
            c[i][j] = custom_instr_mac_ret();
        }
    }
#else
    for (int i = OFFSET; i < OFFSET + LENGTH; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
#endif

#if (CORE_ID != MAIN_CORE_ID)
    alt_dcache_flush_all();

    // Notify main core that processing is completed
    altera_avalon_mailbox_send(mailbox_out, message, INFINITE_TIMEOUT, POLL);
#endif


#if (CORE_ID == MAIN_CORE_ID)

    for(int i = 0; i < CORE_COUNT; i++)
    {
        if (i == MAIN_CORE_ID) continue;

        // Wait for each slave core to complete
        altera_avalon_mailbox_retrieve_poll(mailbox_out_list[i], message, INFINITE_TIMEOUT);
    }

    time_end = alt_timestamp(); // STOP TIME MEASUREMENT
    total_time += time_end-time_start;
    }

    for(int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
           printf("%x  ", c[i][j]);
        }
        printf("\n");
    }

    printf("\nExecution time for %d cores is %d clock cycles\n", CORE_COUNT, total_time/REPETITIONS);
#endif

    while(1);
}
