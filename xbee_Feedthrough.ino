/*
  Used to connect xbee sheild to PC.
  ie, a terminal connection to the xBee via the Arduino acting as a virtual com port.
  
  Hardware is Arduino Uno with Seeed Studio xBee Sheild v2.
  
  Baudrate independent. Baudrate is whatever is set on the xbee. 
  (xBee's default is 9600).
  
  Constantly polls Rx pins and transfers level to Tx pin on the other port. 
  Does not actually use UART or SoftwareSerial lib, since the two port method is
  too slow at high baudrates, since digitalRead and digitalWrite are slow.
 
 The circuit: 
   -Arduino's hardware serial port (to PC)(pins are fixed)
     -D0 is RX (from PC)
     -D1 is Tx (to PC)
 
   -xBee serial port (pins are configurable D0-D7, adjust jumpers on sheild to match)
     -D5 is Rx (from xbee) (XB_TX on sheild, ie xBee's DOUT)
     -D6 is Tx (to xbee) (XB_RX on sheild, ie xBee's DIN)
     
     (D0-D7 restriction is because code below directly accesses PORTD on the ATmega128)
 
*/

//Configurable pins  (Restricted to D0 to D7, ie PORTD on the Amega128)
#define XBEE_RX_PIN 5  //Data from xBee
#define XBEE_TX_PIN 6  //Data to xBee

//Non configurable pins
#define PC_RX_PIN 0  //Data from PC
#define PC_TX_PIN 1  //Data to PC


void setup()  
{
  //First set the Tx pins as outputs. States will be set in the loop().
  pinMode(XBEE_TX_PIN, OUTPUT);
  pinMode(PC_TX_PIN, OUTPUT);
  
}


void loop() // run over and over
{  
  //Set the Tx pin to the xBee the same as the Rx pin from the PC.
  if(PIND & 1<<PC_RX_PIN) PORTD |= 1<<XBEE_TX_PIN;
  else PORTD &= ~(1<<XBEE_TX_PIN);
  
  //Set the Tx pin to the PC the same as the Rx pin from the xBee.
  if(PIND & 1<<XBEE_RX_PIN) PORTD |= 1<<PC_TX_PIN;
  else PORTD &= ~(1<<PC_TX_PIN);
  
}

