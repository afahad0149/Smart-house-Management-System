//Name: Akib Ahmed Fahad
//ID: 011162083

//slave 50 (Node-2)
#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <Wire.h>


long distance = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(50); //slave id = 50
  Serial.begin(9600);
  Wire.onReceive(myFunction); //reads the data sent from Node-1 (master) and processes it
  Serial.println("***Slave (50) Terminal***");
  pinMode(7, INPUT_PULLUP);//P1 push button is connected with pin 7
  pinMode(6, INPUT_PULLUP);//P2 push button is connected with pin 6
  pinMode(5, INPUT_PULLUP);//P3 push button is connected with pin 5
  vw_set_ptt_inverted(true);  //Required for DR3100 (433.92 MHz transceiver module)
  vw_setup(2000);             //Transmission speed in bps
  vw_set_tx_pin(12);          //Set transmit pin
  
}

void myFunction()
{
  //prompts the distance
  
  String s1 = "";
  while(Wire.available() > 0)
  {
    s1 = s1 + (char)Wire.read(); //copying the distance data as characters and appending them to the empty string
  }

  long duration = s1.toInt(); //coverting the distance data to long

  //calculating distance in cm
  distance = (duration * 0.034)/2; // The speed of sound is 0.034cm/microseconds

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

}

void loop() {
  // put your main code here, to run repeatedly:
  //push button and RF-transmission

  if (digitalRead(7) == HIGH && digitalRead(6) == HIGH && digitalRead(5) == HIGH)//when all buttons are not pressed
  {
    Wire.onReceive(myFunction);
    delay(50);

  }
  if (digitalRead(7) == LOW) //p1 button is pressed
  {
    char msg[100] = {'1', 'P', '1', ' ', 'p', 'u', 's', 'h', ' ', 'b', 'u', 't', 't', 'o', 'n', ' ', 'i', 's', ' ', 'p', 'r', 'e', 's', 's', 'e', 'd', '.'}; //define message
    vw_send((uint8_t *)msg, 27);   //transmit a message
    delay(100);
  }
  
  
  else if (digitalRead(6) == LOW) //p2 button is pressed
  {
    char msg[100] = {'2', 'P', '2', ' ', 'p', 'u', 's', 'h', ' ', 'b', 'u', 't', 't', 'o', 'n', ' ', 'i', 's', ' ', 'p', 'r', 'e', 's', 's', 'e', 'd', '.'}; //define message
    vw_send((uint8_t *)msg, 27);   //transmit a message
    delay(100);
  }


  else if (digitalRead(5) == LOW)// p3 button is pressed
  {
    char msg[100] = {'3', 'P', '3', ' ', 'p', 'u', 's', 'h', ' ', 'b', 'u', 't', 't', 'o', 'n', ' ', 'i', 's', ' ', 'p', 'r', 'e', 's', 's', 'e', 'd', '.'}; //define message
    vw_send((uint8_t *)msg, 27);   //transmit a message
    delay(100);
  }
}
