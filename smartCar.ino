const int leftmotorpin1 =2 ; // 直流电机信号输出
const int leftmotorpin2 = 3;
const int rightmotorpin1 = 4;
const int rightmotorpin2 = 5;
const int TrigPin = 9;
const int EchoPin = 8;
float cm;

void setup()
{
Serial.begin(9600);
pinMode(leftmotorpin1, OUTPUT);
pinMode(leftmotorpin2, OUTPUT);
pinMode(rightmotorpin1, OUTPUT);
pinMode(rightmotorpin2, OUTPUT);
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);
}
void loop() //主体
{
  
digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);

cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm
cm = (int(cm * 100.0)) / 100.0; //保留两位小数
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(1000);  
  
// 前进
digitalWrite(leftmotorpin1, HIGH);
digitalWrite(leftmotorpin2, LOW);
digitalWrite(rightmotorpin1, HIGH);
digitalWrite(rightmotorpin2, LOW);

Serial.print("前进");
Serial.println();

//暂停0.5s
digitalWrite(leftmotorpin1, HIGH);
digitalWrite(leftmotorpin2, HIGH);
digitalWrite(rightmotorpin1, HIGH);
digitalWrite(rightmotorpin2, HIGH);
delay(500); 
Serial.print("暂停0.5s");
Serial.println();

//后退
digitalWrite(leftmotorpin1, LOW);
digitalWrite(leftmotorpin2, HIGH);
digitalWrite(rightmotorpin1, LOW);
digitalWrite(rightmotorpin2, HIGH);
delay(1000);
Serial.print("后退");
Serial.println();

//左转
digitalWrite(leftmotorpin1, LOW);
digitalWrite(leftmotorpin2, HIGH);
digitalWrite(rightmotorpin1, HIGH);
digitalWrite(rightmotorpin2, LOW);
delay(1000);
Serial.print("左转");
Serial.println();

//暂停0.5s
digitalWrite(leftmotorpin1, HIGH);
digitalWrite(leftmotorpin2, HIGH);
digitalWrite(rightmotorpin1, HIGH);
digitalWrite(rightmotorpin2, HIGH);
delay(500); 
Serial.print("暂停0.5s");
Serial.println();

//右转
digitalWrite(leftmotorpin1, HIGH);
digitalWrite(leftmotorpin2, LOW);
digitalWrite(rightmotorpin1, LOW);
digitalWrite(rightmotorpin2, HIGH);
delay(1000);
Serial.print("右转");
Serial.println();

//暂停0.5s
digitalWrite(leftmotorpin1, HIGH);
digitalWrite(leftmotorpin2, HIGH);
digitalWrite(rightmotorpin1, HIGH);
digitalWrite(rightmotorpin2, HIGH);
delay(500); 
Serial.print("暂停0.5s");
Serial.println();
}


