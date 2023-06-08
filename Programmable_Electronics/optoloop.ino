/*
featured in video :
https://youtu.be/-LlhZCc0B6U

THE OPTO-LOOP EXPERIMENT

- The goal is to regulate the light intensity
  received by the phototransistor on the right side.

- The desired intensity is set by a potentiometer 
  connected to an analog input of the Arduino.

- The LED is controlled by a PWM output of the 
  Arduino.

- The phototransistor is connected to another analog 
  input, through a low-pass filter with a 100 ms time
  constant (1MOhm*0.1uF) in order to remove the PWM ripple.

OPEN LOOP MODE

- The PWM output is driven by the value set by 
  potentiometer, scaled by 1/4 to compensate the resolution
  difference between the ADC (10 bits) and the PWM (8 bits)

- the phototransistor signal is used just for 
  display, it is inverted to show the same polarity as the
  set value.

- the control is not accurate and is sensitive to 
  external disturbances like external light or optical obstacle 

ClOSED LOOP ( PROPORTIONAL )

- the signed error term is added to the PWM control,
  with a loop gain of 4.
  The accuracy is moderatly improved.

- any attempt to increase the gain leads to 
  instability 

ClOSED LOOP ( PROPORTIONAL+INTEGRAL )

- the error value is fed to an integrator, the 
  output of which is added to the PW control

- the accuracy is greatly improved as well as the 
  immunity against external disturbances

- the response speed could be improved by adding a 
  derivate term (PID control)

WIRING DETAILS

- the wiper of the potentiometer is connected to
  an analog input via a 220 Ohms resistor.

- the white LED is connected to a PWM output via a 560 Ohms resistor

- the NPN phototransistor emitter is connected to the ground,
  its collector is pulled up to +5V by a 4.7k resistor

- the phototransistor collector is connected to an analog input
  through a RC low-pass filter (1Mohm * 0.1 uF)

SOFTWARE DETAILS

- the program sends data to the arduino serial plotter on 4 channels,
  channels min and max are used only to freeze the vertical scale

- the program accepts commands from the PC via the input field of
  the serial plotter. These commands are used to :
	- switch between open-loop and closed-loop modes
	- adjust parameters like proportional gain, integral gain,
	  sampling period etc...
*/

#define BUTPIN 2
#define LEDPIN 13
#define ADCPIN 0
#define ADCPWM 4
#define PWMPIN 9

int period = 20;
int pgain = 1;
int igain = 4;
bool close = false;

void setup() {
  pinMode( BUTPIN, INPUT_PULLUP );
  pinMode( LEDPIN, OUTPUT );
  Serial.begin( 115200 );
  Serial.println("min max potentiometer phototransistor");
}

void loop() {
// variables for timing measurement
  static long start_time;
  static long loop_count;

// precision loop control
  static long tloop = 0;
  if  ( tloop == 0 )
      tloop = millis();
  tloop += period;

// analog processing
  int pot = analogRead( ADCPIN );
  int optical_return = 1023 - analogRead( ADCPWM );
  static int integrator = 0;
  int diff;

  // servo loop control
  if  ( close ) {
      // closed loop operation
      diff = pot - optical_return;
      integrator += diff;
      if  ( integrator > 10000 ) integrator = 10000; 
      if  ( integrator < -10000 ) integrator = -10000; 
      diff *= pgain;
      diff += ( integrator / igain );
      diff += ( pot/4 );
      if  ( diff > 255 ) diff = 255;
      if  ( diff < 0 ) diff = 0;
      analogWrite( PWMPIN, diff );
  } else {
      // open loop operation
      analogWrite( PWMPIN, pot / 4 );
  }
  
  // toggle button
  static bool plotting = true;
  static bool oldbutton = true;
  bool newbutton = digitalRead( BUTPIN );
  if ( newbutton != oldbutton )  {
      if ( newbutton == false ) {
      //   plotting = ! plotting;
        if ( plotting ) {
              plotting = false;
              long total_time = millis() - start_time;
              float ftotal = (float)total_time;
              float fperiod = ftotal / (float)loop_count;
              Serial.print("actual_period=");
              Serial.print(fperiod);
              Serial.print("_vs_");
              Serial.println(period);
            } else {
             plotting = true;
             start_time = millis();
             loop_count = 0;
         }
      digitalWrite( LEDPIN, plotting );    
      }
    oldbutton = newbutton;
    }

// remote control from the PC
  if  ( Serial.available() ) {
    char c = Serial.read();
    if  ( c == 'T' )  { period = Serial.parseInt(); }          
    if  ( c == 'g' )  { pgain = Serial.parseInt(); }          
    if  ( c == 'i' )  { igain = Serial.parseInt(); }
    if  ( c == 'c' )  { close = true; }
    if  ( c == 'o' )  { close = false; }
  }
  
// plotting process
  if  ( plotting ) {
      Serial.print( "0 1023 " );
      Serial.print( pot );
      Serial.print( " " );  Serial.print( optical_return );
      // Serial.print( " " );  Serial.print( diff );
      Serial.println();
    }
  loop_count++;

// precision loop control
//   delay(period);
  while ( millis()< tloop ) {}
}
