#include <system.h>
#include <stdio.h>
#include "sys/alt_timestamp.h"

#define CUSTOM_INSTR_OPCODE 0
#define custom_instr(a,b) __builtin_custom_inii (CUSTOM_INSTR_OPCODE, a, b)

int main()
{
	alt_u32 time_start, time_end;
	alt_timestamp_start();

	if(alt_timestamp_start() < 0)
	{
		printf("Timer not available\n");
	}
	printf("Timer Frequency %u\n", (alt_u32) alt_timestamp_freq());

	int a = 1;
	int b = 2;

	time_start = alt_timestamp();
	time_end = alt_timestamp();
	printf("Ticks base %d\n", time_end-time_start);


	time_start = alt_timestamp();
	int result = custom_instr(a,b);
	time_end = alt_timestamp();

	printf("Result %d\n", result);
	printf("Ticks %d\n", time_end-time_start);

	return 0;
}
