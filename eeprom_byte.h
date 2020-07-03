//
// Created by milky on 21.06.2020.
//

#ifndef EV3_API_EEPROM_BYTE_H
#define EV3_API_EEPROM_BYTE_H
#include <avr/io.h>
#define __EEGET	(	 	var,
addr
)		   (var) = eeprom_read_byte ((const uint8_t *)(addr))

void eeprom_read_block(void)
{
    w = eeprom_read_word(0x01);
}

#endif //EV3_API_EEPROM_BYTE_H


