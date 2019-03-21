#include "Wire.h" // This library allows you to communicate with I2C devices.

int16_t acc_x, acc_y,acc_z; // variables for accelerometer raw data
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int out1=2;     //output1 for HT12E IC
int out2=4;     //output1 for HT12E IC
int out3=7;    //output1 for HT12E IC
int out4=8;    //output1 for HT12E IC
char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  acc_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  acc_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  acc_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x3G (ACCEL_ZOUT_L)
  
  if(abs(acc_z)>abs(acc_x))   //hand horizontal
  {
    if ((acc_x>-5000 && acc_x<5000) && (acc_y>-5000 && acc_y<5000)) //stop
   {
    digitalWrite(out1,LOW);  
    digitalWrite(out2,LOW);   
    digitalWrite(out3,LOW);   
    digitalWrite(out4,LOW);
   } 

   else 
   { 
    if ((acc_x<(-6000)) && (acc_y>-5000 && acc_y<5000)) //forward
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,HIGH);   
     digitalWrite(out3,LOW);  
     digitalWrite(out4,HIGH);    
    }
    
    if ((acc_x>6000) && (acc_y>-5000 && acc_y<5000)) //backward
    {
     digitalWrite(out1,HIGH);   
     digitalWrite(out2,LOW);  
     digitalWrite(out3,HIGH);   
     digitalWrite(out4,LOW);  
    }   
    
    if ((acc_x>-5000 && acc_x<5000) && (acc_y<-8000)) //left
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,HIGH);   
     digitalWrite(out3,LOW);   
     digitalWrite(out4,LOW);
    }
    
    if ((acc_x>(-5000) && acc_x<5000) && (acc_y>8000))//right
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,LOW);   
     digitalWrite(out4,HIGH); 
    }
   }
  }
  else if(acc_x<0)  //hand down
  {
    if ((acc_z>-5000 && acc_z<5000) && (acc_y>-5000 && acc_y<5000)) //stop
   {
    digitalWrite(out1,LOW);  
    digitalWrite(out2,LOW);   
    digitalWrite(out3,LOW);   
    digitalWrite(out4,LOW);
   } 

   else 
   { 
    if ((acc_z<(-6000)) && (acc_y>-5000 && acc_y<5000)) //forward
    {
     digitalWrite(out1,HIGH);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,HIGH);  
     digitalWrite(out4,LOW);    
    }
    
    if ((acc_z>6000) && (acc_y>-5000 && acc_y<5000)) //backward
    {
     digitalWrite(out1,LOW);   
     digitalWrite(out2,HIGH);  
     digitalWrite(out3,LOW);   
     digitalWrite(out4,HIGH);  
    }   
    
    if ((acc_z>-5000 && acc_z<5000) && (acc_y<-6000)) //left
    {
     digitalWrite(out1,HIGH);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,LOW);   
     digitalWrite(out4,LOW);
    }
    
    if ((acc_z>(-5000) && acc_z<5000) && (acc_y>6000))//right
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,HIGH);   
     digitalWrite(out4,LOW); 
    }
   }
  }
  else if(acc_x>0)   //hands up
  {
    if ((acc_z>-5000 && acc_z<5000) && (acc_y>-5000 && acc_y<5000)) //stop
   {
    digitalWrite(out1,LOW);  
    digitalWrite(out2,LOW);   
    digitalWrite(out3,LOW);   
    digitalWrite(out4,LOW);
   } 

   else 
   { 
    if ((acc_z>(6000)) && (acc_y>-5000 && acc_y<5000)) //forward
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,HIGH);   
     digitalWrite(out3,LOW);  
     digitalWrite(out4,HIGH);    
    }
    
    if ((acc_z<-6000) && (acc_y>-5000 && acc_y<5000)) //backward
    {
     digitalWrite(out1,HIGH);   
     digitalWrite(out2,LOW);  
     digitalWrite(out3,HIGH);   
     digitalWrite(out4,LOW);  
    }   
    
    if ((acc_z>-5000 && acc_z<5000) && (acc_y>6000)) //left
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,HIGH);   
     digitalWrite(out3,LOW);   
     digitalWrite(out4,LOW);
    }
    
    if ((acc_z>(-5000) && acc_z<5000) && (acc_y<-6000))//right
    {
     digitalWrite(out1,LOW);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,LOW);   
     digitalWrite(out4,HIGH); 
    }
   }
  }
Serial.print("aX = "); Serial.print(convert_int16_to_str(acc_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(acc_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(acc_z));
  Serial.print("\n");
}
