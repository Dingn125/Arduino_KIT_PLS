#define SERIAL_BAUD 115200    
#define DATA_PIN 12    

SDI12 mySDI12(DATA_PIN); 

#define myComSetUnit   "0OSU+1!"  //set the unit
#define myComUnit     "0OSU!" //ask for the unit of the measure, +0=m, +1=cm, +2=ft, +3=mbar, +4=psi 

String readsensor(){ 
  String sdiResponse = "";
  delay(30);
  while(mySDI12.available()){    
    char c = mySDI12.read();
    if ((c != '\n') && (c != '\r')) { sdiResponse += c; delay(5); }    // Not sure about the meaning of this command?
  }
  return sdiResponse;
}
void setup() {
   Serial.begin(SERIAL_BAUD); // open the serial port at SERIAL_BAUD bps
    while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB 
   }
   
   mySDI12.begin();
   delay(2000); 
  Serial.print(F("'**** Set the unit of the sensor: "));
  mySDI12.sendCommand(myComSetUnit);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();
  delay(500);
}

void loop() {
  Serial.print(F("'**** Unit 0+(0=m, 1=cm, 2=ft, 3=mbar, 4=psi): ")); 
  mySDI12.sendCommand(myComUnit);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();
  delay(1000);
}
