#include <Servo.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x04

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
  delay(3000);
  digitalWrite(13, 0);
  
  
}

void loop() {

  delay(1500);
  for(int i = 0; i < 10;i++)
    Serial.print(num[i]);
  Serial.print('\n');

  /* Get the Sensor Value */

  sensorVal[0] = digitalRead(6); /* Motion Sensor */
  delay(100);
  sensorVal[1] = analogRead(A1)/10; /* Light Sensor */
  delay(100);
  sensorVal[2] = 25; /* Heat Sensor */
  delay(100);
  sensorVal[3] = 0;
  delay(100);
  sensorVal[4] = -1; /* EOF */
  delay(100);

/*
  for (int i = 0; i < 5; i++){
    Serial.print(i);
    Serial.print(" ");
    Serial.print(sensorVal[i]);
    Serial.print("\n");
  }
*/
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

        Serial.print("Not Implemented");
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
