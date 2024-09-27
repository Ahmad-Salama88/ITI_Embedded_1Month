
#include "TWI_EEPROM.h"

volatile char PASS[] = "    ";

void TWI_INIT(void)
{
	TWSR = 0x00;	/* PS 1 */
	TWBR = 0X20; /* BAUD = 20 --eq(8MHz)--> f_scl = 400 KHz */
	TWCR = (1<<TWEN);	/* Enabel TWI */
}

void TWI_START (void)
{
	/* Start communication -- Enable TWI -- Clear TWINT flag */
	TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
}

void TWI_STOP (void)
{
	TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT);
	while(TWCR & (1<<TWSTO)); /* Wait until it is 0 */
	//_delay_ms(10);	/* Or you can delay this time */
}

void TWI_WRITE(char data)
{
	/* THIS FUNCTION USED TO SEND ADDRESS & DATA through TWDR */

	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));	/* wait until data transferred */
}

char TWI_READACK (void)
{
	/* ENABLE ACK */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);  /* Clear it after send address and enable TWI */

	while(!(TWCR & (1<<TWINT)));	/* He sends there then awaits, I here await then get it */
	return TWDR;
}

char TWI_READNACK (void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);  /* Clear it after send address and enable TWI */

	while(!(TWCR & (1<<TWINT)));	/* He sends there then awaits, I here await then get it */
	return TWDR;
}

char TWI_GETSTATUS (void)
{
	return TWSR & 0xF8;
}

/* YOU ,THE MASTER * READ EEPROM as RX */
void READ_EEPROM(char Address, char*str)
{
	char byte = 0;

	TWI_START();

	/* Select EEPROM as a slave (sending WRITE as DATA SHEET said */
	TWI_WRITE(EEPROM_Write_Addess);

	/* Select the word address to be accessed */
	TWI_WRITE(Address);

	/* Send start bit again as data sheet says */
	TWI_START();

	/* Send EEPROM slave address and READ */
	TWI_WRITE(EEPROM_Read_Addess);

	//for (char byte = 0; byte < strlen(str); byte++)
	while(str[byte] != 0)
	{
		PASS[byte] = TWI_READACK();
		byte++;
	}

	TWI_STOP();



}

/* YOU ,THE MASTER* WRITE ON EEPROM as TX */
void WRITE_EEPROM(char Address,char*str)
{
	char byte = 0;

	TWI_START();

	/* Select EEPROM as a slave and WRITE */
	TWI_WRITE(EEPROM_Write_Addess);

	/* Send Address of word to wirte on it */
	TWI_WRITE(Address);

	/* Write byte by byte -- Write the array data */
	//for (char byte = 0; byte<strlen(str); byte++)
	while(str[byte] != 0)
	{
		TWI_WRITE(str[byte]);
		byte++;
	}

	TWI_STOP();
	_delay_ms(10);
}
