#include <system.h>
#include <stdio.h>
#include "sys/alt_timestamp.h"

#define MAT_SIZE 32
#define CUSTOM_INSTR_MAC 1
#define CUSTOM_INSTR_MAC_RESULT 2
#define custom_instr_mac(a,b) __builtin_custom_inii (CUSTOM_INSTR_MAC, a, b)
#define custom_instr_mac_ret() __builtin_custom_inii (CUSTOM_INSTR_MAC_RESULT, 0, 0)

int main()
{
	alt_u32 time_start, time_end;
	alt_timestamp_start();

	if(alt_timestamp_start() < 0)
	{
		printf("Timer not available\n");
	}
	printf("Timer Frequency %u\n", (alt_u32) alt_timestamp_freq());

	typedef int matrix_t[MAT_SIZE][MAT_SIZE];
	matrix_t a, b, c;

	// Init matrix A (increasing numbers modulo 16)
	for(int i = 0; i < MAT_SIZE; i++)
		for (int j = 0; j < MAT_SIZE; j++)
			a[i][j] = (i * MAT_SIZE + j) % 0x10;

	// Init matrix B (identity matrix)
	for(int i = 0; i < MAT_SIZE; i++)
		for (int j = 0; j < MAT_SIZE; j++)
			b[i][j] = (i == j ? 1 : 0);

	// Standard multiplication
	time_start = alt_timestamp();
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < MAT_SIZE; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
	time_end = alt_timestamp();
	printf("Ticks   : %d\n", time_end-time_start);

    // Print the resulting matrix
    for(int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
           printf("%x  ", c[i][j]);

        printf("\n");
    }

	// Multiplication using custom MAC instructions
	time_start = alt_timestamp();
	for (int i = 0; i < MAT_SIZE; i++)
	{
		for (int j = 0; j < MAT_SIZE; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < MAT_SIZE; k++)
			{
				custom_instr_mac(a[i][k], b[k][j]);
			}
			c[i][j] = custom_instr_mac_ret();
		}
	}
	time_end = alt_timestamp();
	printf("Ticks CI : %d\n", time_end-time_start);

    // Print the resulting matrix
    for(int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
           printf("%x  ", c[i][j]);

        printf("\n");
    }

	return 0;
}
