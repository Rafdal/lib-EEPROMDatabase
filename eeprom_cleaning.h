#include <EEPROM.h>

#if defined( ESP_H ) || defined( _HELTEC_H_ )
#define EESIZE 512
#else
#define EESIZE (int)EEPROM.length()
#endif

void Make_Sure_EEPROM_is_Clear(uint8_t BYTE0, uint8_t BYTE1)
{
	int length = EESIZE;
	if (EEPROM.read(length-2) != BYTE0 || EEPROM.read(length-1) != BYTE1)
	{
		DEBUG("EEPROM Error, cleaning...")
		for (int i = 0 ; i < length; i++) {
			#if defined( ESP_H ) || defined( _HELTEC_H_ )
			if (EEPROM.read(i) != 0)
            {
                EEPROM.write(i, 0);
                EEPROM.commit();
            }
			#else
    		EEPROM.update(i, 0);
			#endif
  		}
		DEBUG("EEPROM cleared")
		#if defined( ESP_H ) || defined( _HELTEC_H_ )
		EEPROM.write(length-2, BYTE0);
		EEPROM.commit();
		EEPROM.write(length-1, BYTE1);
		EEPROM.commit();

		delay(100);
		ESP.restart();
		#else
		EEPROM.update(length-2,BYTE0);
		EEPROM.update(length-1,BYTE1);

 		delay(100);
		asm("jmp 0x0000");
		#endif
	}
	else
	{
		DEBUG("EEPROM is ok")
	}
}