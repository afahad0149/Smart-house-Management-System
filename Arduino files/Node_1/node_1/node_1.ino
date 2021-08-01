//Name: Akib Ahmed Fahad
//ID: 011162083

//Master (Node 1)

#include <Wire.h>
#include <dht.h>
dht DHT;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT); // sets the trigPin (pin 12) as O/P
  pinMode(11, INPUT);  // sets the echoPin (pin 11) as I/P
  Wire.begin(6);  //Address of Master is 60 
  Serial.begin(9600);
  Serial.println("***Master (6) Terminal***");
}

void loop() {
  // put your main code here, to run repeatedly:

  //Collecting distance data from ultrasonic sensor and sending it to node 3
  // Clears the trigPin
  digitalWrite(12, LOW); // trigPin is set low
  delayMicroseconds(2);   // for 2 microseconds for initializing

  //set the trigPin on HIGH state for 10 microseconds
  digitalWrite(12, HIGH); //trigPin is set as high
  delayMicroseconds(10); //10 microseconds
  digitalWrite(12, LOW);

  // Reads the echoPin, returns the sound wave travel time in -microseconds-
  long duration = pulseIn(11, HIGH);
  String dur = String(duration);

  /*
  //for debugging purposes
  Serial.print("Master sends: ");
  Serial.println(dur);
  */

  //Transmit the duration data to Node 2
  Wire.beginTransmission(50); //begin data transfer to slave id 50 (Node 2)
  Wire.write(dur.c_str()); //data send after converted into a C-style null terminated String
  Wire.endTransmission(50); //end data transfer to slave id 50

  //delay(100);

  //Collecting temperature data from DHT11 and sending it to node 2

  DHT.read11(5);  //sending DHT11 sensor's data to arduino via pin 5
  String temp = String(DHT.temperature);

  //for debugging purposes
  Serial.print("Master sends: ");
  Serial.println(temp);
  
  Wire.beginTransmission(100); //begin data transfer to slave id 100 (Node 3)
  Wire.write(temp.c_str()); //data send after converted into a C-style null terminated String
  Wire.endTransmission(100); //end data transfer to slave id 100
  delay(100);

}
