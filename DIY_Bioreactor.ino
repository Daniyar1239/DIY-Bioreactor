#include <Time.h>
#include <TimeLib.h>

#define DELAY 60000  // 60s
#define PH_MIN_VALUE 3.6
#define PH_CALIBRATION 2.2
#define PH_OFFSET -1

//L298N driver //Motor A
const int motorPin1 = 9;
const int motorPin2 = 10;
// Motor B
const int motorPin3 = 6;
const int motorPin4 = 5;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(12, INPUT_PULLUP);  //float switch, which measures the liquid level
  Serial.begin(9600);
}

void loop(){
  time();
  turbidity();
  PHsensor();
  Serial.print(",liquid level:");
  prLevel();
  stirrer();
  pumpingControl(measurePH2(), liquidLevel());
}

// setting time
void time(){
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(":");
}

// liquid level
int liquidLevel(){
  return digitalRead(12);
  }
  
// printing liquid level
void prLevel(){
  Serial.print(liquidLevel());
  delay(DELAY);
  }
  
// pumping
void pumpingControl(float PH, int liquidLevel){
  if (PH<=PH_MIN_VALUE && liquidLevel != 1){
    analogWrite(motorPin3, 255);
    analogWrite(motorPin4, 0);
  } 
  else{
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  }
}
  
// stirrer
void stirrer(){
  analogWrite(motorPin1, 100);
  analogWrite(motorPin2, 0);
}
  
// turbidity
void turbidity(){
  Serial.println(analogRead(A5)*(5.0/1023.0));
  delay(DELAY);
}
  
// pH sensor
float measurePH2(){
  int pH_sensorValue = analogRead(A2);
  float pH_voltage = pH_sensorValue * 5.0 / 1023.0;
  float pH_value = PH_CALIBRATION * (28.2 + PH_OFFSET - 6.5 * pH_voltage);
  return pH_value;
}
void PHsensor(){
  Serial.print(",");
  Serial.print("pH: ");
  Serial.print(measurePH2());
  delay(DELAY);
    
}
