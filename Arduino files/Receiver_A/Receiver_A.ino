//Name: Akib Ahmed Fahad
//ID: 011162083

#include <VirtualWire.h>
#include <VirtualWire_Config.h>

int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("***RECEIVER A Terminal***");
  vw_set_ptt_inverted(true);  //Required for DR3100 (433.92 MHz transceiver module)
  vw_setup(2000);             //Transmission speed in bps
  vw_set_rx_pin(11);          //Set receiver pin
  vw_rx_start();              //Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  //Attempt to read from the wireless receiver
  if (vw_get_message(buf, &buflen) > 0)  //check if a message is available, 'len' available space n buf, 'buf' pointer to the location to save the read data
  {
    char ch2 = buf[0];
    

    if (ch2 == '1')
    {
      //Serial.print(ch2);
      //Serial.print("Got: ");
      for (i = 1; i < buflen; i++)
      {
        char ch2 = buf[i];
        Serial.print(ch2);
        //Serial.print(" ");
      }

      Serial.println();
    }
  }
  
}
