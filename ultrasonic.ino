const int PIN_ECHO = 5;
const int PIN_TRIG = 4;
const int PIN_LED = 13;

void setup()
{
Serial.begin(9600);
pinMode(PIN_LED, OUTPUT);

pinMode(PIN_ECHO, INPUT);
pinMode(PIN_TRIG, OUTPUT);
}


// led blink
void blink(const int interval = 300)
{
digitalWrite(PIN_LED, HIGH);
delay(interval);
digitalWrite(PIN_LED, LOW);
delay(interval);
}

// distance detect
int distanceDetect()
{
digitalWrite(PIN_TRIG, LOW); // 保持超声波控制接口低电平2us
delayMicroseconds(2);

digitalWrite(PIN_TRIG, HIGH); // 保持超声波控制接口高电平10us
delayMicroseconds(10);
digitalWrite(PIN_TRIG, LOW);    // 超声波控制接口转低电平以触发测距过程

// 距离测试公式为 脉冲长度 * 音速 / 2;
const float SONIC_SPEED = 0.034; // 音速在大气中传播速度为0.034千米/秒
long duration = pulseIn(PIN_ECHO, HIGH); // 读出脉冲时间
return duration * SONIC_SPEED / 2;
}

// loop control
void loop()
{
int val = Serial.read();
if (val == 'r')
{
// notify msg
blink();
Serial.println("cmd rcv, begin detect.");
// detect
int distance = distanceDetect();
if (0 >= distance)
{
Serial.println("detect fail.");
}
else
{
Serial.print("distance: ");
Serial.println(distance);
}
}

delay(500);
}
