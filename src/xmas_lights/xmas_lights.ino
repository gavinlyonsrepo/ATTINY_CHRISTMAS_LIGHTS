

//********************** HEADER ***********************
/*
  Name  :ATTINY_CHRISTMAS_LIGHT
  Author: Gavin Lyons
  URL: https://github.com/gavinlyonsrepo/ATTINY_CHRISTMAS_LIGHT
*/

//******************** LIBRARIES ******************
// Include TinySnore Library needs small mod to lib , see URL , for attiny85 sleep
#include "tinysnore.h"

//******************** DEFINES ********************
#define RedYellowPin  PB0
#define BlueGreenPin PB1

//******************** GLOBALS ********************

// loop takes 120 seconds = 2:00 minutes
// for six hours 180 loops 120 X 180 = 21600 S
const uint8_t LOOPTIME = 180;
const uint32_t SLEEPTIME = 64800000 ; //   // 64,800,000  mS = 18 hours

enum LED_TYPE_e
{
  LED_RED_YELLOW = 1,
  LED_BLUE_GREEN = 2,
  LED_BOTH = 3
};


// *************** FUNCTION PROTOTYPES *************
void All_LEDS_off(uint16_t);
void LEDS_on(LED_TYPE_e, uint16_t);
void PWM_LEDS(uint8_t , bool , uint16_t );

void Display_Steady(uint16_t);
void Display_Flash(LED_TYPE_e, uint16_t);
void Display_PWM(LED_TYPE_e, uint16_t);

void Setup_pins(bool);

//******************** SETUP ************************
void setup() {
  Setup_pins(true);
  delay(2000);
}

//******************* MAIN LOOP *****************
void loop() {

  for (uint8_t LoopNumber  = 0; LoopNumber < LOOPTIME; LoopNumber ++)
  {
 
    // Display Steady on test
    Display_Steady(2100);

    // Flash patterns  
    Display_Flash(LED_RED_YELLOW, 100);
    Display_Flash(LED_BLUE_GREEN, 100);       
    Display_Flash(LED_BOTH , 500);
    Display_Flash(LED_BOTH , 700);


    // PWm patterns fade in and out LEDs
    Display_PWM(LED_RED_YELLOW , 50);
    delay(2000);
    Display_PWM(LED_BLUE_GREEN , 50);

    Display_Steady(1000);

    
  } // for loop

  // SLEEP 
  Setup_pins(false);
  snore(SLEEPTIME); // Deep sleeps
  Setup_pins(true);
 

} //END OF MAIN


// ********************* FUNCTIONS SPACE ************


void PWM_LEDS(uint8_t LEDS_ON, bool FadeUpDown, uint16_t delayTime )
{
  uint8_t  brightness = 0;
  if (FadeUpDown == true)
  {
    for (brightness = 0; brightness < 254; brightness++)
    {
      analogWrite(LEDS_ON, brightness);
      delay(delayTime);
    }
  } else
  {
    for (brightness = 254; brightness > 0; brightness--)
    {
      analogWrite(LEDS_ON, brightness);
      delay(delayTime);
    }
  }
  All_LEDS_off(20);
}

void Display_PWM( LED_TYPE_e   LEDS_ON ,  uint16_t delayTime)
{

  All_LEDS_off(20);

  switch (LEDS_ON) {
    case 1:
      PWM_LEDS(RedYellowPin , true, delayTime ); // fade in
      PWM_LEDS(RedYellowPin , false, delayTime );
      break;
    case 2:
      PWM_LEDS(BlueGreenPin, true, delayTime ); // fade in
      PWM_LEDS(BlueGreenPin, false, delayTime );
      break;
    case 3:
      // both
      PWM_LEDS(RedYellowPin, true, delayTime ); // fade in
      PWM_LEDS(BlueGreenPin, true, delayTime ); // fade in
      PWM_LEDS(RedYellowPin, false, delayTime ); // fade out
      PWM_LEDS(BlueGreenPin, false, delayTime ); // fade out

      break;
    default:
      // statements
      All_LEDS_off(delayTime);
      break;
  }

}
void Display_Flash( LED_TYPE_e  LEDS_ON ,  uint16_t delayTime)
{
  for (uint8_t flashloop = 1 ; flashloop <= 10 ; flashloop ++)
  {
    switch (LEDS_ON) {
      case 1:
        // red yellow flash
        LEDS_on(LED_RED_YELLOW, delayTime);
        All_LEDS_off(delayTime);
        break;
      case 2:
        // blue green flash
        LEDS_on(LED_BLUE_GREEN, delayTime);
        All_LEDS_off(delayTime);
        break;
      case 3:
        // both
        LEDS_on(LED_RED_YELLOW, delayTime);
        LEDS_on(LED_BLUE_GREEN, delayTime);
        break;
      default:
        // statements
        All_LEDS_off(delayTime);
        break;
    }
  }
  All_LEDS_off(5000);
}


void Display_Steady(uint16_t delayTime)
{
  LEDS_on(LED_RED_YELLOW, delayTime);
  LEDS_on(LED_BLUE_GREEN, delayTime);
  All_LEDS_off((delayTime*3) + 200);
}

void  All_LEDS_off(uint16_t delayTime)
{
  digitalWrite(BlueGreenPin, LOW);
  digitalWrite(RedYellowPin, LOW);
  delay(delayTime);
}

void Setup_pins(bool output)
{
  if (output == true)
  {
    pinMode(RedYellowPin, OUTPUT);
    pinMode(BlueGreenPin, OUTPUT);
    digitalWrite(RedYellowPin, LOW);
    digitalWrite(BlueGreenPin, LOW);
  }
  else {
    pinMode(RedYellowPin, INPUT);
    pinMode(BlueGreenPin, INPUT);
  }

}

void LEDS_on(LED_TYPE_e RY_LEDS_ON, uint16_t delayTime)
{
  if (RY_LEDS_ON == 1)
  {
    digitalWrite(BlueGreenPin, LOW);
    delay(50);
    digitalWrite(RedYellowPin, HIGH);
  } else if (RY_LEDS_ON == 2)
  {
    digitalWrite(RedYellowPin, LOW);
    delay(50);
    digitalWrite(BlueGreenPin, HIGH);
  } else
  {
    All_LEDS_off(5);
  }
  delay(delayTime);
}
