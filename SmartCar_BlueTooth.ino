#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

const int LeftMotorPin1 =2 ; // 直流电机信号输出
const int LeftMotorPin2 = 3;
const int RightMotorPin1 = 4;
const int RightMotorPin2 = 5;
const int LeftSpeedPin = 10;
const int RightSpeedPin = 11;
int LedPin = 13;
String comdata= "";
String hexdata= "";
char inChar;
int timer =200;
int Speed = 5;
int SpeedAmount = 1;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, mySerial.");
  
  pinMode(LeftMotorPin1, OUTPUT); //声明各引脚模式
  pinMode(LeftMotorPin2, OUTPUT);
  pinMode(RightMotorPin1, OUTPUT);
  pinMode(RightMotorPin2, OUTPUT);
  pinMode(LeftSpeedPin, OUTPUT);
  pinMode(RightSpeedPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
}

void loop() //主体
{
  delay(2);
  // if(Serial.available())  //判断是否有数据发送过来
  // (Speed/5) * 255
  analogWrite(LeftSpeedPin, Speed * 51);
  analogWrite(RightSpeedPin, Speed * 51);

  while (mySerial.available())
  {
    //读入之后将字符串，串接到comdata上面。
    hexdata = hexdata + String(mySerial.read(),HEX);
    comdata = comdata + mySerial.read();
    inChar = mySerial.read();
    
    //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
    delay(20);
    //Serial.print("comdata:");
    //Serial.println(comdata);
    //Serial.print("hexdata:");
    //Serial.println(hexdata);
    Serial.print("inChar:");
    Serial.println(inChar);
    Serial.println("----------------");
    Serial.print("Speed:");
    Serial.println(Speed);
    Serial.println("*****************");
    
    switch(inChar)
    {
      case '1':Forward();break;
      case '2':Backward();break;
      case '3':Left_Forward();break;
      case '4':Right_Forward();break;
      case '5':Left_Backward();break;
      case '6':Right_Backward();break;
      case 'Q':Speed_Up();break;
      case 'R':Speed_Down();break;
      case 'S':Halt();break;
      case 'T':Route_O();break;
      case 'U':Route_Z();break;
      //case '1':LED();break;
      default:Halt();
    }
  }      
}

// 前进
void Forward()
{
  digitalWrite(LeftMotorPin1, HIGH);
  digitalWrite(LeftMotorPin2, LOW);
  digitalWrite(RightMotorPin1, HIGH);
  digitalWrite(RightMotorPin2, LOW);
}

//后退
void Backward()
{
  digitalWrite(LeftMotorPin1, LOW);
  digitalWrite(LeftMotorPin2, HIGH);
  digitalWrite(RightMotorPin1, LOW);
  digitalWrite(RightMotorPin2, HIGH);
  //delay(timer);
}

//暂停0.5s
  void Halt() {
  digitalWrite(LeftMotorPin1, HIGH);
  digitalWrite(LeftMotorPin2, HIGH);
  digitalWrite(RightMotorPin1, HIGH);
  digitalWrite(RightMotorPin2, HIGH);
  delay(200);
}

//左转
void Left()
{
  digitalWrite(LeftMotorPin1, LOW);
  digitalWrite(LeftMotorPin2, HIGH);
  digitalWrite(RightMotorPin1, HIGH);
  digitalWrite(RightMotorPin2, LOW);
}

//右转
void Right()
{
  digitalWrite(LeftMotorPin1, HIGH);
  digitalWrite(LeftMotorPin2, LOW);
  digitalWrite(RightMotorPin1, LOW);
  digitalWrite(RightMotorPin2, HIGH);
}

//Left_Forward
void Left_Forward()
{
  Forward();
  Left();
}

//Right_Forward
void Right_Forward()
{
  Forward();
  Right();
}

//Left_Backward
void Left_Backward()
{
  Backward();
  Left();
}

//Right_Backward
void Right_Backward()
{
  Backward();
  Right();
}

//Route_O
void Route_O()
{
  for (int i=0;i<10;i++)
  {
    Left_Forward();  
  }
}

//Route_Z
void Route_Z()
{
  for (int i=0;i<5;i++)
  {
    Forward();  
  }
  
  for (int i=0;i<5;i++)
  {
    Left_Forward();  
  }
  
  for (int i=0;i<5;i++)
  {
    Forward();  
  }
}

//Speed_Up
void Speed_Up()
{
  Speed += SpeedAmount;
  if (Speed == 0 || Speed == 5) 
  {
    SpeedAmount = -SpeedAmount;
   }
  delay(100);
}

//Speed_Down
void Speed_Down()
{
  Speed -= SpeedAmount;
  if (Speed == 0 || Speed == 5) 
  {
    SpeedAmount = -SpeedAmount;
   }
  delay(100);
}

//LED
void LED()
{
  digitalWrite(LedPin, HIGH);
  delay(200);
  digitalWrite(LedPin, LOW);
}


