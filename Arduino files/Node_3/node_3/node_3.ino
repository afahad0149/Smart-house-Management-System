#include <SD.h>

//Name: Akib Ahmed Fahad
//ID: 011162083

//slave 50 (Node-3)

int prev_temp = 25; // mid point of the range (0-50) as starting value of temperature 
int blue = 127, green = 0, red = 127; //mid values of Red and Blue according to the mid value of temperature

#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT); // Blue
  pinMode(10, OUTPUT); // Green
  pinMode(11, OUTPUT); // Red
  
  Wire.begin(100); //slave id = 100 (Node-3)
  //Serial.begin(9600); //for debugging purposes
  Wire.onReceive(myFunction);
  //Serial.println("***Slave (100) Terminal***"); //for debugging purposes
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void myFunction()
{
  Serial.print("Temperature: ");
  String s1 = "";
  while(Wire.available() > 0)
  {
    s1 = s1 + (char)Wire.read();
  }

  //Serial.println(s1);
  int temp = s1.toInt();
  //Serial.println(temp);

  int temp_diff = temp - prev_temp; 

  //changing blue and red in accordance to the temperature.
  // 256/50 = 5.12 = 5 so with each degree temperature change, red and blue values are changed by 5.

  blue += (temp_diff * 5);  // if temp_diff > 0 (i.e. temp increasing), blue increases
  red -= (temp_diff * 5);   // if temp_diff < 0 (i.e. temp decreasing), red increases

  //keeping the red and blue values within the range
  if (blue <= 0)
    blue = 0;
  if (red <= 0)
    red = 0;
  if (blue >= 255)
    blue = 255;
  if (red >= 255)
    red = 255;

  //outputing the rgb values to rgb led
  analogWrite(9, blue); // Blue
  analogWrite(10, green); // Green
  analogWrite(11, red); // Red
 
  prev_temp = temp; //updating prev_temp's value 
}
