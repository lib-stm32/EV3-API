//
// Created by milky on 21.06.2020.
//

#include "eeprom_byte.h"
void EEPROM_write_string(int address, int lenght, char *data)
{
    while(lenght)
    { while(EECR & (1<<1));
        EEAR=address;
        address=address+1;
        EEDR= *data;
        data=data+1;
        EECR|=(1<<2);
        EECR|=(1<<1);
        lenght=lenght-1;
    }
}
void EEPROM_read_string(int address, int lenght, char *data)
{
    while(EECR & (1<<1));
    while(lenght--)
    {
        EEAR=address++;
        EEAR|=(1<<0);
        *data=EEDR;
        data++;
    }
}
int main(void)
{
    static char St_from_RAM_to_EEPROM[15] = "work with EEPROM";
    EEPROM_write_string(0x00,15,&St_from_RAM_to_EEPROM[0]);
    static char st_from_eeprom_to_ram[15];
    EEPROM_read_string(0x00, 15, &st_from_eeprom_to_ram[0]);
}