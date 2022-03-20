#include <SDI12.h> 

#define SERIAL_BAUD 115200    // Not sure if this should be 115200 for SDI12? 
#define DATA_PIN 7        

SDI12 mySDI12(DATA_PIN); 

//SDI 12 commands
#define myComAdress   "?!"    //ask the adress of the probe
#define myComId       "0I!"   //ask the identification
#define myComMeasure  "0M!"   //ask to start a measurement
#define myComSend     "0D0!"  //ask to send the measure
#define myComSetUnitCM  "0OSU+1!"  //set the unit
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

void measREFsensor(){
  delay(500);      // Not sure if this delay command is to control the starting point of the measurement? Not sure about the unit in delay command? 
  mySDI12.sendCommand(myComMeasure);
  while(mySDI12.available()){ mySDI12.read();}    
  delay(1000);    
  mySDI12.clearBuffer();   // Not sure about the purpose of this clearBuffer command after reading the measurements from the sensor?
  delay(500);
  mySDI12.sendCommand(myComSend);  
  delay(50);
  String rawdata = readsensor();
  mySDI12.clearBuffer();   
  delay(50); 
  Serial.println("rawdata = " +rawdata);
  delay(100);                               
}

void StartRefSensor(){
  mySDI12.begin();
  delay(2000); 
  
  Serial.print(F("'**** Identification of the sensor: "));
  mySDI12.sendCommand(myComId);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();
  
  Serial.print(F("'**** Adress of the sensor: "));
  mySDI12.sendCommand(myComAdress);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();

  Serial.print(F("'**** Set the unit of the sensor to be cm: "));
  mySDI12.sendCommand(myComSetUnitCM);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();
  
  Serial.print(F("'**** Unit 0+(0=m, 1=cm, 2=ft, 3=mbar, 4=psi): "));  //If here should be Unit 0+ or Unit +0 ?
  mySDI12.sendCommand(myComUnit);
  delay(300);
  Serial.println(readsensor());
  delay(500);
  mySDI12.clearBuffer();
}

void setup() {
   Serial.begin(SERIAL_BAUD); // open the serial port at SERIAL_BAUD bps
    while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB 
   }
   StartRefSensor();
}

void loop() {
   measREFsensor();
   delay(1000);
}
