#include <EEPROM.h>
#include "save.h" 

void save_config()
{
    EEPROM.begin(1024);
    uint8_t *p = (uint8_t *)(&Keyboard_Config);
    for (int i = 0; i < sizeof(Keyboard_Config); i++)
    {
        EEPROM.write(i, *(p + i));
    }
    EEPROM.end();
}

void load_config()
{
    EEPROM.begin(1024);
    uint8_t *p = (uint8_t *)(&Keyboard_Config);
    for (int i = 0; i < sizeof(Keyboard_Config); i++)
    {
        *(p + i) = EEPROM.read(i);
    }
    EEPROM.end();

    if (Keyboard_Config.Version_KBD != KEYBOARD_VER)
    {
        Serial.println("initing");
        Keyboard_Config.BOOT_MODE = DEFAULT_BOOT_MODE ; 
        Keyboard_Config.Version_KBD = KEYBOARD_VER;
        save_config();
    }
}

