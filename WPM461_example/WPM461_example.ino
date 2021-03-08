/*
  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@

  
  Whadda WPM461 chip key display module example

  This example shows how you can drive the LEDs and 7-segment displays of the display module in various ways.

  Library dependancies:
    -TM1638plus library (Installation instructions: https://www.ardu-badge.com/TM1638plus/ide)

  For more information about the Whadda WPM461 chip key display module, check the manual available at https://whadda.com

  Based on TM1638plus_HELLOWORLD_TEST_Model1.ino example from TM1638plus library
  Author: Gavin Lyons.
  Created: feb 2020
  URL: https://github.com/gavinlyonsrepo/TM1638plus

  Altered by: Midas Gossye (Whadda/Velleman)
  Date: 08/03/2021
  URL: https://github.com/WhaddaMakers/WPM461
*/

#include <TM1638plus.h> //include the library

// GPIO I/O pins on the Arduino connected to strobe, clock, data,
//pick on any I/O you want.
#define  STROBE_TM 4 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 6  // clock = GPIO connected to clock line of module
#define  DIO_TM 7 // data = GPIO connected to data line of module
bool high_freq = false; //default false, If using a high freq CPU > ~100 MHZ set to true. 
 
// Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO, use high freq MCU)
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);

void setup()
{
  tm.displayBegin(); // Initialise display module
  tm.displayText("helowrld"); // (Try to) display helowrld on 7-segment displays
  delay(1000); // Wait 1000ms (=1s)
  tm.reset(); // Clear the display
}

void loop()
{
  // For i: 0 -> 7
  for(int i=0; i<8; i++) {
    tm.setLED(i, 1); // Turn LED at position i ON
    tm.displayASCII(i, '-'); // Display '-' character on 7-segment digit at position i
    delay(100); // Wait 100ms
    tm.displayASCII(i, ' '); // Clear the 7-segment digit at position i
    tm.setLED(i, 0); // Turn LED at position i OFF
  }
  
  // For i: 6 -> 1
  for(int i=6; i>0; i--) {
    tm.setLED(i, 1); // Turn LED at position i ON
    tm.displayASCII(i, '-'); // Display '-' character on 7-segment digit at position i
    delay(100); // Wait 100ms
    tm.displayASCII(i, ' '); // Clear the 7-segment digit at position i
    tm.setLED(i, 0);// Turn LED at position i OFF 
  }
  
  // For i: 0 -> 7
  for(int i=0; i<8; i++) {
    tm.setLED(i, 1); // Turn LED at position i ON
    tm.displayASCIIwDot(i, '0'+i);  // Display number i on 7-segment digit at position i with dot turned on
    delay(500); // Wait 500ms
    
  }

  tm.reset(); // Clear the display

  // For i: 0->1000
  for(int i=0; i<1000; i++) {
    tm.displayIntNum(millis(), true); // Display the number of milliseconds since last reset on display with leading zeros
  }
  
  tm.displayText("Velleman"); // (Try to) display Velleman on 7-segment displays
  delay(2000); // wait 2000ms (=2s)
  tm.reset(); // Clear the display
  tm.displayText("Whadda"); // (Try to) display Whadda on 7-segment displays
  delay(2000); // wait 2000ms (=2s)
}
