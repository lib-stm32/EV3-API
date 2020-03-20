#ifdef __cplusplus
extern "C" {
#endif

#ifndef ev3_h
#define ev3_h

#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "ev3_constants.h"
#include "ev3_command.h"
#include "ev3_output.h"
#include "ev3_sensor.h"
#include "ev3_button.h"
#include "ev3_lcd.h"
#include "ev3_sound.h"
#include "ev3_bluetooth.h"
#include "iput-output via serial port Keil.h"
#include "keil_in.h"

#define EV3_CONSTRUCTOR_PRIORITY 201
#define EV3_DESTRUCTOR_PRIORITY 201

int InitEV3(void);
int FreeEV3(void);
bool EV3IsInitialized(void);
#define ExitEV3() FreeEV3()
#ifndef EV3_NO_CONSTRUCTORS
static int __attribute__((used,deprecated)) (* volatile __reference_InitEV3)(void) = InitEV3;
static int __attribute__((used,deprecated)) (* volatile __reference_FreeEV3)(void) = FreeEV3;
#endif
typedef struct 
{
    /* data */
    const char *LCD_EV3
    const char *message_4_EV3;
    #define bool EV3_TO_MESSAGE 0xFF
    bool Message_ARRAY [25] ;
    getchar();
} message_to_ev3;
 bool Message_EV3()
 {
     char value_message[15];
     while(&value_message, info == 5)
     {
         if ( started)
         {
             #ifdef /*define*/test_message_ev3
             scanf("%f,%25", info == 1)
                /* code */
             #endif ///*define*/
             
         }
     }
 }

#endif // ev3_h

#ifdef __cplusplus
}
#endif