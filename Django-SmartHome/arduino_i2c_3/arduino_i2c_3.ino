/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM

  Connect the positive side of the Buzzer to pin 3,
  then the negative side to a 1k ohm resistor. Connect
  the other side of the 1 k ohm resistor to
  ground(GND) pin on the Arduino.

  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

/*************************************************
 * Public Constants
 *************************************************/
#include <Servo.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x06
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 3
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int val = 0;
int num[20];
int k = 0;
int p = 0;
int sensorVal[5];
unsigned long previousMillis = 0;
unsigned long interval = 1000;
int ledState = LOW;
int flag[20];
int op;
int ret;
int motor_speed;
int LED_trigger;
int lock_trigger;
Servo servo1;
int LED_blink_trigger;
int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }

  } else {

    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);

}

int controlLED(){

    if(LED_trigger == 1){
        digitalWrite(13, HIGH);
        delay(100);
         Serial.println("LED activated.");
        return 1;
    }
    else{
        digitalWrite(13, LOW);
        delay(100);
        Serial.println("LED deactivated.");
        return 0;
    }
  
}

int controlMotor(){

    if(motor_speed){
        analogWrite(9, motor_speed);
        analogWrite(10, HIGH);
        Serial.println("Motor activated.");
        return 1;
    }else{
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        Serial.println("Motor deactivated.");
        return 0;
    }

    return 1;

}

int controlDoorLock(){

    if(lock_trigger == 1){
        for(int pos = 0; pos < 180; pos++){
          servo1.write(pos);
          delay(20);
        }
        Serial.println("Servo activated.");
        return 1;
    }else{
        for(int pos = 180; pos > 0; pos--){
          servo1.write(pos);
          delay(20);
        }
        Serial.println("Servo deactivated.");
        return 0;
    }

}


int blinkLED(){

  unsigned long currentMillis = millis();
  
  if(LED_blink_trigger == 1){
    
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (ledState == LOW){
      ledState = HIGH;
       Serial.println("LED Blink deactivated.");
    }
    else{
      ledState = LOW;
      Serial.println("LED Blink activated.");
    }
    digitalWrite(13, ledState);
  }
  
  }

}

void playSong(){

  if(song == 1){
    sing(1);
    Serial.println("Music activated.");
  }
  else{
    Serial.println("Music deactivated.");;
  }
  
}

void clearArray(int* num){
    for(int i = 0; i < 10;i++)
      num[i] = 0;
    k = 0;
}

void setup() {
  
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData); /* Call sendData() on master request */
  pinMode(3, OUTPUT); /*buzzer */
  pinMode(13, OUTPUT); /* Set up for LED */
  pinMode(6,INPUT); /* Set up for Motion Sensor */
  pinMode(A1,INPUT); /* Set up for Light Sensor */
  pinMode(A0,INPUT); /* Set up for Heat Sensor */
  pinMode(7,OUTPUT); /* Relay */
  pinMode(9,OUTPUT); /* Driver A */
  pinMode(10,OUTPUT); /* Driver B */
  servo1.attach(5);  /* Servo */
  servo1.write(90);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, 0);
  
}

void loop() {

  delay(1500);
  for(int i = 0; i < 10;i++)
    Serial.print(num[i]);
  Serial.print('\n');
   
  /* Get Control Signal */

  if(num[3] == 255){ /* Each control signal has length of 3, 255 for EOF */

    op = num[0];
    flag[op] = 1;
    if(op == 1)
        motor_speed = num[1];
    else if(op == 2)
        lock_trigger = num[1];        
    else if(op == 3)
        LED_trigger = num[1];
    else if(op == 5)
        LED_blink_trigger = num[1];
    else if(op == 4)
        song = num[1];

    clearArray(num);

  }

  /* Control Device */

  if(flag[1]){

        ret = controlMotor();
  }

  if(flag[2]){

        ret = controlDoorLock();

  }

  if(flag[3]){

        ret = controlLED();

  }

  if(flag[4]){

        playSong();
  }

  if(flag[5]){

        ret = blinkLED();
        
  }
  
}

void receiveData(int byteCount){
  
  while(Wire.available()) {
    val = Wire.read();
    num[k] = val;
    k++;
  }
  
}

void sendData(){
  
    Serial.print(p);
    Serial.print(":");
    Serial.print(sensorVal[p]);
    Serial.print("\n");
    Wire.write(sensorVal[p]);
    if(sensorVal[p] != -1)
      p++;
    else
      p = 0;
  
}
