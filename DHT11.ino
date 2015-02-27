#define DHT11_PIN 14

 
byte read_dht11_dat()
{
    byte i = 0;
    byte result = 0;
 
    for(i=0;i<8;i++)
    {
       while(!(PINC&_BV(DHT11_PIN)));
       delayMicroseconds(30);
 
       if(PINC&_BV(DHT11_PIN))
           result|=(1<<(7-i));
 
       while((PINC&_BV(DHT11_PIN)));
    }
 
    return result;
}
 
void setup_dht11()
{
    DDRC |= _BV(DHT11_PIN);
    PORTC |= _BV(DHT11_PIN);
 
    Serial.begin(9600);
    Serial.println("Ready");
}
 
 
 
void setup()
{
    setup_dht11();
}
 
void loop()
{
    byte dht11_dat[5];
    byte dht11_in;
    byte i;
    PORTC &= ~_BV(DHT11_PIN);
    delay(18);
 
    PORTC|=_BV(DHT11_PIN);
    delayMicroseconds(40);
    DDRC &= ~_BV(DHT11_PIN);
    delayMicroseconds(40);
    dht11_in = PINC & _BV(DHT11_PIN);
 
    if(dht11_in)
    {
       Serial.println("dht11 start condition 1 not met");
       return;
    }
 
    delayMicroseconds(80);
    dht11_in=PINC & _BV(DHT11_PIN);
    if(!dht11_in)
    {
       Serial.println("dht11 start condition 2 not met");
       return;
    }
 
    delayMicroseconds(80);
 
    for(i=0;i<5;i++)
       dht11_dat[i]=read_dht11_dat();
 
    DDRC|=_BV(DHT11_PIN);
    PORTC|=_BV(DHT11_PIN);
    byte dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];
 
    if(dht11_dat[4]!=dht11_check_sum)
    {
       Serial.println("DHT11 checksum error");
    }
 
    Serial.print("humdity= ");
    Serial.print(dht11_dat[0], DEC);
    Serial.print(".");
    Serial.print(dht11_dat[1], DEC);
    Serial.print("%");
    Serial.print("temper = ");
    Serial.print(dht11_dat[2], DEC);
    Serial.print(".");
    Serial.print(dht11_dat[3], DEC);
    Serial.println("C");

}
