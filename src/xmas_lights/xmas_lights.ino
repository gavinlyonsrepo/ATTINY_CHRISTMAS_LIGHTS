//********************** HEADER ***********************
/*
  Name  :ATTINY_CHRISTMAS_LIGHT
  Author: Gavin Lyons
  URL: https://github.com/gavinlyonsrepo/ATTINY_CHRISTMAS_LIGHT
*/

//******************** LIBRARIES ******************

#include "tinysnore.h" // Include TinySnore Library

//******************** DEFINES ********************
#define RedYellowPin  PB0 
#define BlueGreenPin  PB1 

// loop takes 147 seconds = 2:43 minutes
// for six hours ~= 150 loops
#define LOOPTIME 150


//******************** GLOBALS ********************

enum LED_TYPE_t
{
  LED_RED_YELLOW = 1,
  LED_BLUE_GREEN = 2,
  LED_BOTH = 3
};


// *************** FUNCTION PROTOTYPES *************
void All_LEDS_off(uint16_t);
void LEDS_on(LED_TYPE_t, uint16_t);
void PWM_LEDS(uint8_t , bool , uint16_t );

void Display_Steady(void);
void Display_Flash(LED_TYPE_t, uint16_t);
void Display_PWM(LED_TYPE_t, uint16_t);


//******************** SETUP ************************
void setup() {
  pinMode(RedYellowPin, OUTPUT);
  pinMode(BlueGreenPin, OUTPUT);
  digitalWrite(RedYellowPin, LOW);
  digitalWrite(BlueGreenPin, LOW);
  delay(2000);
}

//******************* MAIN LOOP *****************
void loop() {

  for (uint8_t LoopNumber  = 0; LoopNumber < LOOPTIME; LoopNumber ++)
  {

    // Display Steady on test
    Display_Steady();

    // flash red + yellow only
    Display_Flash(LED_RED_YELLOW, 100);
    //  flash blue + green only
    Display_Flash(LED_BLUE_GREEN, 100);
    // flash both fast
    Display_Flash(LED_BOTH , 500);
    // flash both slow
    Display_Flash(LED_BOTH , 1000);

    // PWM fade in and out red + yellow
    Display_PWM(LED_RED_YELLOW , 50);
    // PWM fade in and out blue + green
    Display_PWM(LED_BLUE_GREEN , 50);
    // PWM fade in and out both fast
    Display_PWM(LED_BOTH , 5);
    // PWM fade in and out both slow
    Display_PWM(LED_BOTH , 25);

    delay(2000);
  } // for loop
  // SLEEP
  pinMode(RedYellowPin, INPUT);
  pinMode(BlueGreenPin, INPUT);
 for (int i = 0; i < 12960; i++) // (18*60*60)/5 = 64800 /5 
  {
   snore(5000); // Deep sleeps for 5 seconds, (low power) then resumes from here
  }
  pinMode(RedYellowPin, OUTPUT);
  pinMode(BlueGreenPin, OUTPUT);



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
  All_LEDS_off(1);
}

void Display_PWM( LED_TYPE_t   LEDS_ON ,  uint16_t delayTime)
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
void Display_Flash( LED_TYPE_t  LEDS_ON ,  uint16_t delayTime)
{
  for (uint8_t flashloop = 1 ; flashloop < 10 ; flashloop ++)
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


void Display_Steady(void)
{
  // red on five seconds
  LEDS_on(LED_RED_YELLOW, 2500);
  // blue on five seocnds
  LEDS_on(LED_BLUE_GREEN, 2500);
  // all off five seconds
  All_LEDS_off(5000);
}
void  All_LEDS_off(uint16_t delayTime)
{
  digitalWrite(BlueGreenPin, LOW);
  digitalWrite(RedYellowPin, LOW);
  delay(delayTime);
}


void LEDS_on(LED_TYPE_t RY_LEDS_ON, uint16_t delayTime)
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
