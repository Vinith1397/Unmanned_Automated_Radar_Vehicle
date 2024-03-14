#include<Servo.h>
#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
const int trig_pin=10;
const int echo_pin=9;
int combination=3;
int distance,distance1,distance2;
long duration;
Servo myservo;
//LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
LiquidCrystal lcd(A5,A4,A0,A1,A2,A3);
SoftwareSerial BT(1,0); //TX, RX respetively
String readdata;
//motor right
int motorpinr1=6;
int motorpinr2=7;
//motor left
int motorpinl1=4;
int motorpinl2=5;
void forward()
{ 
  digitalWrite(motorpinl1,HIGH);
  digitalWrite(motorpinl2,LOW);
  digitalWrite(motorpinr1,HIGH);
  digitalWrite(motorpinr2,LOW);
  lcd.setCursor(0,1);
  lcd.print("OPN : forward !");
//  delay(1000);
}
void wireless()
{
    lcd.setCursor(0,0);
    lcd.print("enter wireless      ");
   // delay(3000);
    lcd.setCursor(0,1);
    lcd.print("mode                 ");  
    delay(20000);
while(Serial.available()>0)
{  //Check if there is an available byte to read
    //delay(10); //Delay added to make thing stable
    lcd.setCursor(0,0);
    lcd.print("wireless mode      ");   
    //delay(3000);
    lcd.setCursor(0,1);
    lcd.print("entering bluetooth      ");
    delay(3000);
    char c = Serial.read(); //Conduct a serial read
  //  char x =c; //build the string- "forward", "reverse", "left" and "right"
//int y=x.length();
    Serial.print("the string is  =");
   Serial.print(c);
    Serial.print(".\n");
    lcd.setCursor(0,1);
    lcd.print("entering loop      ");

//if(x>0)
//{
//  Serial.println(x);
  
  if(c == 'f')
  {
    lcd.setCursor(0,0);
    lcd.print("manual forward      ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    digitalWrite(4, LOW);
    digitalWrite (5, HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    delay(2000);
    digitalWrite(4, LOW);
    digitalWrite (5, LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(2000);
  }
      else if(c == 'b')
  {
    lcd.setCursor(0,0);
    lcd.print("manual backward      ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7,LOW);
    delay(2000);
    digitalWrite(4, LOW);
    digitalWrite (5, LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(2000);  
  }
   else if (c == 'r')
  {
    lcd.setCursor(0,0);
    lcd.print("manual right      ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    digitalWrite (4,LOW);
    digitalWrite (5,HIGH);
    digitalWrite (6,LOW);
    digitalWrite (7,LOW);
    delay(2000);
    digitalWrite(4, LOW);
    digitalWrite (5, LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(2000);
  }
     else if ( c == 'l')
  {
    lcd.setCursor(0,0);
    lcd.print("manual left      ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    digitalWrite (4, LOW);
    digitalWrite (5, LOW);
    digitalWrite (6, LOW);
    digitalWrite (7, HIGH);
    delay (2000);
    digitalWrite(4, LOW);
    digitalWrite (5, LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(2000);
  }
 /*   else if (readdata == "stop")
  {
    digitalWrite (3, LOW);
    digitalWrite (4, LOW);
    digitalWrite (5, LOW);
    digitalWrite (6, LOW);
    delay (100);
  }*/
}
}
int calculateDistance()
{
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);
  duration=pulseIn(echo_pin,HIGH);
  distance=duration*0.034/2;
  return distance;
}  
  void autoprog()
  {
  //  delay(5000);
    myservo.write(100);
    delay(5000);
   lcd.setCursor(0,0);  
   lcd.print("autoprog mode         ");
   lcd.setCursor(0,1);
   lcd.print("                       ");
   int d,d1,d2,d3,d4,d5,dright,dleft,dk;
   lcd.setCursor(0,0);  
   lcd.print("center position         ");
   lcd.setCursor(0,1);
   lcd.print("analyzing front          ");
   //myservo.write(100);
   dk=calculateDistance();
   //delay(5000);
   Serial.print(100);
   Serial.print("=");
   Serial.print(dk);
   Serial.print(".\n");
   //myservo.write(100);
   delay(1000);
   lcd.setCursor(0,0);
   lcd.print("analyzing done       ");
   lcd.setCursor(0,1);
   lcd.print("                     ");  
  // delay(3000); 
 //  myservo.write(100);
   if(dk>40)
   {
       //lcd
       lcd.setCursor(0,0);
       lcd.print("no obstacle         ");
       lcd.setCursor(0,1);
       lcd.print("moving forward      ");
      // void forward();
        digitalWrite(motorpinl1,LOW);
        digitalWrite(motorpinl2,HIGH);
        digitalWrite(motorpinr1,LOW);
        digitalWrite(motorpinr2,HIGH);
        lcd.setCursor(0,1);
        lcd.print("OPN : forward!!");
        delay(1000);
        digitalWrite(motorpinl1,LOW);
        digitalWrite(motorpinl2,LOW);
        digitalWrite(motorpinr1,LOW);
        digitalWrite(motorpinr2,LOW);
     //   break;
   }
   if(dk<40)
   {
       lcd.setCursor(0,0);  
       lcd.print("checking right         ");
       lcd.setCursor(0,1);
       lcd.print("obstacle front           ");
       myservo.write(100);
      delay(2000);
       myservo.write(180);
      delay(1000);
      myservo.write(100);
      delay(5000);
      myservo.write(9);
   delay(1000);
      
       int dx=0,dy=0,dz=0,dt=0;
       d2=calculateDistance();
       Serial.print(5);
       Serial.print("=");
       Serial.print(d2);
       Serial.print(".\n");   
       
       //delay(100);
       for(int i=10;i<=12;i+=1)
       {
           myservo.write(i);
           delay(1000);
           Serial.print(i);
           d3=calculateDistance();
           Serial.print("=");
           Serial.print(d3);
           Serial.print(".\n");
           dx=dx+d3;
       }
       Serial.print("dx =");
       Serial.print(dx);
       Serial.print(".\n");
       myservo.write(20);
       for(int i=22;i<=45;i+=1)
       {
           myservo.write(i);
           delay(1000);
           Serial.print(i);
           d4=calculateDistance();
           Serial.print("=");
           Serial.print(d4);
           Serial.print(".\n");
           dy=dy+d4;       
       }
       Serial.print("dy =");
       Serial.print(dy);
       Serial.print(".\n");
       myservo.write(55);
       delay(200);
       for(int i=61;i<=62;i+=1)
       {
           myservo.write(i);
           delay(1000);
           Serial.print(i);
           d5=calculateDistance();
           Serial.print("=");
           Serial.print(d5);
           Serial.print(".\n");
           dz=dz+d5; 
       }
       Serial.print("dz =");
       Serial.print(dz);
       Serial.print(".\n");
       myservo.write(77);
       delay(1000);
       myservo.write(100);
       distance2=calculateDistance();
       Serial.print(100);
       Serial.print("=");
       Serial.print(distance2);
       Serial.print(".\n");         
       lcd.setCursor(0,0);
       lcd.print("center position      ");
      // delay(3000);
       lcd.setCursor(0,1);
       lcd.print("                     ");
       dt=dx+dy+dz;
       Serial.print("dt =");
       Serial.print(dt);
       Serial.print(".\n");
       dright=(dt/(32*40));
       Serial.print("dright =");
       Serial.print(dright);
       Serial.print(".\n");
       if((dt/(32*40))>1)
       {        
           delay(2000);
           lcd.setCursor(0,0);
           lcd.print("OPN : right !     ");
           digitalWrite(motorpinl1,LOW);
           digitalWrite(motorpinl2,HIGH);
           digitalWrite(motorpinr1,LOW);
           digitalWrite(motorpinr2,LOW);
           delay(1500);
           digitalWrite(motorpinl1,LOW);
           digitalWrite(motorpinl2,LOW);
           digitalWrite(motorpinr1,LOW);
           digitalWrite(motorpinr2,LOW);
           lcd.setCursor(0,1);
           lcd.print("checking front      ");
           delay(1000);
//           break;
       }
       else
       {
           int da=0,db=0,dc=0,df=0,d6;
           lcd.setCursor(0,0);
           lcd.print("obstacle - right  ");
           lcd.setCursor(0,1);
           lcd.print("checking left <--    ");
           myservo.write(110);
           distance1=calculateDistance();
           Serial.print(110);
           Serial.print("=");
           Serial.print(distance1);
           Serial.print(".\n");     
           for(int i=131;i<=179;i+=1)
           {
               
               digitalWrite(trig_pin,LOW);
               delayMicroseconds(2);
               digitalWrite(trig_pin,HIGH);
                delayMicroseconds(10);
               digitalWrite(trig_pin,LOW);
               duration=pulseIn(echo_pin,HIGH);
               d6=duration*0.034/2;
               myservo.write(i);
               delay(1000);
               Serial.print(i);
               Serial.print("=");
               Serial.print(d6);
               Serial.print(".\n");
              da=da+d6;
           }
           Serial.print("da =");
           Serial.print(da);
           Serial.print(".\n");
           delay(500);
           myservo.write(180);
           db=calculateDistance();
           Serial.print(180);
           Serial.print("=");
           Serial.print(db);
           Serial.print(".\n");
           dc=da+db;
           Serial.print("dc =");
           Serial.print(dc);
           Serial.print(".\n");
           dleft=dc/(49*40);          
          delay(5000);
           myservo.write(100);
           df=calculateDistance();
           lcd.setCursor(0,0);
           lcd.print("center position         ");
          // lcd.setCursor(0,1);
          // lcd.print("obstacle - left");
           Serial.print("100 =");
           Serial.print(df);
           Serial.print(".\n");
           delay(5000);
           Serial.print("dleft =");
       Serial.print(dleft);
       Serial.print(".\n");
           if((df<45)&(dleft<1))
           {
           digitalWrite(motorpinl1,HIGH);
           digitalWrite(motorpinl2,LOW);
           digitalWrite(motorpinr1,HIGH);
           digitalWrite(motorpinr2,LOW);
           lcd.setCursor(0,0);
           lcd.print("                   ");
           lcd.setCursor(0,1);
           lcd.print("OPN : backward!!   ");
//           break;
           }
           else
           {
               delay(5000);
               lcd.setCursor(0,0);
               lcd.print("OPN : left !!     ");
               digitalWrite(motorpinl1,LOW);
               digitalWrite(motorpinl2,LOW);
               digitalWrite(motorpinr1,LOW);
               digitalWrite(motorpinr2,HIGH);
               delay(500);
               digitalWrite(motorpinl1,LOW);
               digitalWrite(motorpinl2,LOW);
               digitalWrite(motorpinr1,LOW);
               digitalWrite(motorpinr2,LOW);
               lcd.setCursor(0,1);
               lcd.print("checking front      ");
               delay(1000);
//               break;
           }
       }
   }}

void setup() {
  // put your setup code here, to run once:
pinMode(trig_pin,OUTPUT);
pinMode(echo_pin,INPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(11,OUTPUT);
lcd.begin(16,2);
Serial.begin(9600);
myservo.attach(8);
//BT.begin(9600);
pinMode(motorpinl1, OUTPUT);  //in1
pinMode(motorpinl2, OUTPUT);  //in2
pinMode(motorpinr1, OUTPUT);  //in3
pinMode(motorpinr2, OUTPUT);   //in4
//digitalWrite(12,HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly 
  digitalWrite(11,HIGH);
  lcd.setCursor(0,0);
  lcd.print("|     THE      |           ");
  lcd.setCursor(0,1);
  lcd.print("|   URABELT    |         ");
  delay(5000);
  if(digitalRead(3)==HIGH)
  {
    Serial.print("mode is wireless.");
  //  Serial.print(df);
    Serial.print("\n");
    wireless();
  }
  while(digitalRead(3)==LOW)
  {
    Serial.print("mode is autoprog");
    //Serial.print(df);
    Serial.print(".\n");
    autoprog();
  }
  
}
