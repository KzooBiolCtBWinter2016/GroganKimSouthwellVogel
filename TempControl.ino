#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
int ONE_WIRE_BUS = 2;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
int HeaterPin =10;
int counter = 0;
int counterLow = 0;
int counterHigh = 0;
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
void setup(void)
{

Serial.begin(9600);
pinMode(HeaterPin,OUTPUT);
digitalWrite(HeaterPin,LOW);
// Start up the library
sensors.begin(); 
}

void loop(void)
{
// call sensors.requestTemperatures() to issue a global temperature
// request to all devices on the bus

  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
// prints current temperature on serialwrite
  Serial.print("Temperature for Device 1 is: ");
  float Temp;
  Serial.print(sensors.getTempCByIndex(0));
  Temp = sensors.getTempCByIndex(0);

//lower bound specification
  if(Temp<24)
  {
    counterLow = counterLow +1;
  
  }
  if (counterLow>= 1)
  {
    digitalWrite(HeaterPin,HIGH);
  }
  //specifying upper bound
  if(Temp>26)
  //desired range is 24-28
  {
    //reseting counter to turn off
    counterLow = 0;
    digitalWrite(HeaterPin,LOW);
  }
  delay(1000);
}

//end
