#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

/* Author: Carson Williams */

union RawFloat
{
	unsigned raw;
	float f;
};

int main()
{
    /* array to store register results */
	uint16_t tab_reg[2*sizeof(uint16_t)];
	memset(tab_reg, 0, 2*sizeof(uint16_t));

	/* open connection to the sensor */
    modbus_t *mb;
	mb = modbus_new_tcp("10.0.0.2", 1502);
	modbus_connect(mb);

	/* read temperature from register addresses 0x0004 and 0x0005 */
	if(modbus_read_input_registers(mb, 0x0004, 2, tab_reg) == -1)
		printf("Reading Temperature Failed\n");

    /* data is IEEE-754 float, but in network byte order so swap for little endian. */
	tab_reg[0] = ((tab_reg[0] << 8) + (tab_reg[0] >> 8));
	tab_reg[1] = ((tab_reg[1] << 8) + (tab_reg[1] >> 8));

    /* register 4 is the least significant word, and register 5 is the most significant word,
       so add the translated values together in reverse order to create a float */
	RawFloat temp;
	temp.raw = ((tab_reg[1] << 16) + tab_reg[0]);

	printf("Temperature: %f C\n", temp.f);

    /* Close Sensor Connection */
	modbus_close(mb);
	modbus_free(mb);
	return 0;
}