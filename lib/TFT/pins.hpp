#ifndef PINS_H
#define PINS_H
#define BIT_ORDER           LSBFIRST

#define PUSH_BUTTON         0           // Encoder pushbutton
#define ENCODER_LEFT        5           // FIXME: These maybe backwards, need to test
#define ENDCODE_RIGHT       4           // ^^ 
#define DATA_PIN            13          // MTCK - maybe the engineers have it backwards, or maybe I do! Logic analyzer will tell
#define CLOCK_PIN           14          // MTMS - Master Transmit Master Select - this is normally the data output
#define MTDO                15          // Normally SPI Data Out -> this is connected to LCD pin 12
#define MTDI                12          // Normally SPI Data IN  -> this is conencted to LCD pin 14

#endif