#include <SoftwareSerial.h>
#include <IRremote.h>  // 使用IRRemote函数库

int RECV_PIN = 6;  // 红外接收器的 OUTPUT 引脚接在 PIN6 接口 定义RECV_PIN变量为PIN6接口
IRrecv irrecv(RECV_PIN); // 设置RECV_PIN定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置

SoftwareSerial mySerial(8, 9); // RX, TX

const int LeftMotorPin1 =2 ; // 直流电机信号输出
const int LeftMotorPin2 = 3;
const int RightMotorPin1 = 4;
const int RightMotorPin2 = 5;
const int LeftSpeedPin = 10;
const int RightSpeedPin = 11;

const int SoundPin = 7;
const int LedPin = 13;
const int PrPin = A0;
String comdata;
String hexdata;
String IR_RecvChar;
char inChar;
int timer =200;
int Speed = 3;
int SpeedAmount = 1;

void setup()
{
  Serial.begin(9600);  // 开启串口，波特率为9600
  Serial.println("Start!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, mySerial.");
  
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(LeftMotorPin1, OUTPUT); //声明各引脚模式
  pinMode(LeftMotorPin2, OUTPUT);
  pinMode(RightMotorPin1, OUTPUT);
  pinMode(RightMotorPin2, OUTPUT);
  pinMode(LeftSpeedPin, OUTPUT);
  pinMode(RightSpeedPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(SoundPin,INPUT);
}

void loop() //主体
{
  // if(Serial.available())  //判断是否有数据发送过来

  // Speed();
  
  BlueTooth();
  
  IR();
  
  //PR();
  
  //Sound();
  
     
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

/*
//Speed_Up
void Speed_Up()
{
  Speed = Speed + SpeedAmount;
  if (Speed == 0 || Speed == 5) 
  {
    SpeedAmount = -SpeedAmount;
   }
  delay(100);
}

//Speed_Down
void Speed_Down()
{
  Speed = Speed - SpeedAmount;
  if (Speed == 0 || Speed == 5) 
  {
    SpeedAmount = -SpeedAmount;
   }
  delay(100);
}

//Speed
void Speed()
{
  // (Speed/5) * 255
  analogWrite(LeftSpeedPin, Speed * 51);
  analogWrite(RightSpeedPin, Speed * 51);
}
*/

//LED
void LED()
{
  digitalWrite(LedPin, HIGH);
  delay(200);
  digitalWrite(LedPin, LOW);
}

//BlueTooth
void BlueTooth()
{
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
    //Serial.print("Speed:");
    //Serial.println(Speed);
    //Serial.println("*****************");
    
    switch(inChar)
    {
      case '1':Forward();break;
      case '2':Backward();break;
      case '3':Left_Forward();break;
      case '4':Right_Forward();break;
      case '5':Left_Backward();break;
      case '6':Right_Backward();break;
      //case 'Q':Speed_Up();break;
      //case 'R':Speed_Down();break;
      case 'S':Halt();break;
      case 'T':Route_O();break;
      case 'U':Route_Z();break;
      //case '1':LED();break;
      default:Halt();
    }
  } 
}



//IR
void IR()
{
  if (irrecv.decode(&results)) {   // 解码成功，把数据放入results变量中
    // 把数据输入到串口
    Serial.print("irCode: ");            
    Serial.print(results.value, HEX); // 显示红外编码
    Serial.print(",  bits: ");           
    Serial.println(results.bits); // 显示红外编码位数

    IR_RecvChar = String(results.value,HEX);
    IR_RecvChar.toUpperCase();
    Serial.print("IR_RecvChar:");
    Serial.println(IR_RecvChar);

    if (IR_RecvChar == "33B8A05F")
    {
      Forward();
      Serial.println("==Forward");
    }
    else if (IR_RecvChar == "33B8609F")
    {
      Backward();
      Serial.println("Backward");
    }
    else if (IR_RecvChar == "33B8E01F")
    {
      Left_Forward();
      Serial.println("Left");
    }
    else if (IR_RecvChar == "33B810EF")
    {
      Right_Forward();
      Serial.println("Right");
    }
    else if (IR_RecvChar == "33B820DF")
    {
      Halt();
      Serial.println("Halt");
    }
    else
    {
      Halt();
      Serial.println("Else");
    }
    
    irrecv.resume();    // 继续等待接收下一组信号
  }  
  delay(100); //延时600毫秒，做一个简单的消抖
}

//Photoresistor
void PR()
{
  int val = analogRead(PrPin);    //从传感器读取值
  Serial.print("PR_val:");
  Serial.println(val);
  Serial.println("#######################");
  
  if(val >= 512){      //512=2.5V，想让传感器敏感一些的时候，把数值调高，想让传感器迟钝的时候把数值调低。
    digitalWrite(LedPin, HIGH); //当val小于512(2.5V)的时候，led亮。
  }
  else{
    digitalWrite(LedPin, LOW);
  }
}

//Sound Sensor
void Sound()
{
  int sound =digitalRead(SoundPin);
  Serial.print("Sound:");
  Serial.println(sound);
  Serial.println("@@@@@@@@@@@@@@@@@@@@");
  if (sound == 0)                             //判断n是否为高电平，如果是执行下面的语句，不是则跳过。
  {
    digitalWrite(LedPin,HIGH);
    delay(1000);
  }
  else 
  {
    digitalWrite(LedPin,LOW);
  }
}


