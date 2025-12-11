/*****************************************************************
File:         getMotionStatus.ino
Description:  Device default select pin8 as intpin,and when no 
              interrupt occurs INT is Low level.The example shows
              Motion Detection.
******************************************************************/
#include "BMS56M206A.h"
BMS56M206A Mpu(8);//default select pin8 as intpin
//BMS56M206A Mpu(22,&Wire1);//BMCOM1
uint16_t cnt = 0;
  
void setup() {
  Mpu.begin();
  Serial.begin(9600);
  
  Mpu.setInterruptPinPolarity(ACTIVE_LOW);//when no interrupt occurs INT is Low level
  Mpu.setMotionThreshold(ACCEL_WOM_X_THR,255);  //set threshold value
  Mpu.setMotionOutConfig(INT_OUT_OR); //set output after all interrupt ‘or’ operation.
  Mpu.setINT(X_MOTION_MODE,true);//set x axis interrupt
}



void loop() {
  if(Mpu.getINT() == 0)
  {
    delay(100); //delay 100ms for reduce sensitivity.
    Mpu.clearINTFlag();//clear interrupt flag
    cnt++;
    if(cnt >= 0xffff) cnt = 0;
    Serial.print("Motion Detected!  x");
    Serial.println(cnt);
    Serial.println();
  }
  

}
