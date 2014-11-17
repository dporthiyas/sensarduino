#include <CapacitiveSensor.h> //Capacitive sensing library http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense
#define aref_voltage 3.3 
//The library was modified to reduce the amount of time between the high and low pulses from 10usec to 5usec
//This allowed for less noise spikes to occur

//The capacitive sensors require a send pin which generates the high and low pulses, pin 14
CapacitiveSensor cs_c12 = CapacitiveSensor(14,12);//capacitive sensor on pin 12 
CapacitiveSensor cs_c11 = CapacitiveSensor(14,11);//capacitive sensor on pin 11 
CapacitiveSensor cs_c10 = CapacitiveSensor(14,10);//capacitive sensor on pin 10 
CapacitiveSensor cs_c9 = CapacitiveSensor(14,9);  //capacitive sensor on pin 9
CapacitiveSensor cs_c8 = CapacitiveSensor(14,8);  //capacitive sensor on pin 8
CapacitiveSensor cs_c7 = CapacitiveSensor(14,7);  //capacitive sensor on pin 7
CapacitiveSensor cs_c6 = CapacitiveSensor(14,6);  //capacitive sensor on pin 6
CapacitiveSensor cs_c5 = CapacitiveSensor(14,5);  //capacitive sensor on pin 5
CapacitiveSensor cs_c2 = CapacitiveSensor(14,2);  //capacitive sensor on pin 2
CapacitiveSensor cs_c17 = CapacitiveSensor(14,17);//capacitive sensor on pin 17

const int pA9pin = A9; //pressure sensor on pin A9
const int pA8pin = A8; //pressure sensor on pin A8
const int pA7pin = A7; //pressure sensor on pin A7
const int pA6pin = A6; //pressure sensor on pin A6
const int pA5pin = A5; //pressure sensor on pin A5
const int pA4pin = A4; //pressure sensor on pin A4

const int indicator = 13; //indicator LED on pin 13 (built in) for program ON 
//7,10,8,11,9
const long c7Bias = 23;//1
const long c8Bias = 30;//3
const long c9Bias = 30;//5
const long c10Bias = 26;//2
const long c11Bias = 30;//4

//6,5,17,2,12
const long c12Bias = 26;//5
const long c2Bias = 29;//4
const long c5Bias = 29;//2
const long c6Bias = 22;//1
const long c17Bias = 31;//3

const int tempSensor = A1;

long c12 = 0; //variable to hold capacitive sensor reading on pin 12
long c11 = 0; //variable to hold capacitive sensor reading on pin 11
long c10 = 0; //variable to hold capacitive sensor reading on pin 10
long c9 = 0;  //variable to hold capacitive sensor reading on pin 9
long c8 = 0;  //variable to hold capacitive sensor reading on pin 8
long c7 = 0;  //variable to hold capacitive sensor reading on pin 7
long c6 = 0;  //variable to hold capacitive sensor reading on pin 6
long c5 = 0;  //variable to hold capacitive sensor reading on pin 5
long c2 = 0;  //variable to hold capacitive sensor reading on pin 2
long c17 = 0;  //variable to hold capacitive sensor reading on pin 17

int pA9 = 0; //variable to hold pressure sensor reading on pin A9
int pA8 = 0; //variable to hold pressure sensor reading on pin A8
int pA7 = 0; //variable to hold pressure sensor reading on pin A7
int pA6 = 0; //variable to hold pressure sensor reading on pin A6
int pA5 = 0; //variable to hold pressure sensor reading on pin A5
int pA4 = 0; //variable to hold pressure sensor reading on pin A4

float voltage;
float tempC;
float tempVal = 0;

void setup()
{
  Serial1.begin(9600); //Start up Serial1 (not Serial which is USB) which goes to Xbee
  
  pinMode(indicator,OUTPUT); 
  pinMode(tempSensor,INPUT);
  digitalWrite(indicator,HIGH);
  //delay(10);
  //digitalWrite(indicator,LOW);
  autoCalibrateOff(); //Turn the autocalibrate OFF so that raw data is kept with no calibration on restart 
  analogReference(EXTERNAL);
  delay(100);
}

void loop()
{
  readCaps(1,100,1); //Read capacitive sensors 
  readPres(); //Read pressure sensors
  //readTemp();
  printCapVals(1); //Print values read from capacitive sensors. 0 allows for values to be continued to be printed on same line.
  //printPresVals(0);//Print values read from pressure sensors. 1 gives a new line
  //Serial1.print("Temp (A1): ");
  //Serial1.println(tempC);
  delay(30);
}

void readTemp()
{
  tempVal = analogRead(tempSensor);
  voltage = tempVal * aref_voltage;  
  voltage = voltage / 1024.0;
  tempC = (voltage - 0.5) * 100;  
}

void readCaps(int input, int resolution, int x)//function to read in capacitive sensor values
{
  long start = millis();

  c12 = cs_c12.capacitiveSensorRaw(resolution); 
  c11 = cs_c11.capacitiveSensorRaw(resolution);
  c10 = cs_c10.capacitiveSensorRaw(resolution);
  c9 = cs_c9.capacitiveSensorRaw(resolution);
  c8 = cs_c8.capacitiveSensorRaw(resolution);
  c7 = cs_c7.capacitiveSensorRaw(resolution);
  c6 = cs_c6.capacitiveSensorRaw(resolution);
  c5 = cs_c5.capacitiveSensorRaw(resolution);
  c2 = cs_c2.capacitiveSensorRaw(resolution);
  c17 = cs_c17.capacitiveSensorRaw(resolution);

  if(input == 1)
    hardcodeDown(100,x);  
}

void readPres()//function to read in pressure sensor values
{
  pA9 = analogRead(pA9pin);//analog input 
  pA8 = analogRead(pA8pin);
  pA7 = analogRead(pA7pin);
  pA6 = analogRead(pA6pin);
  pA5 = analogRead(pA5pin);
  pA4 = analogRead(pA4pin);

  presMap();
}

void presMap()
{
  pA9 = map(pA9,1023,0,0, 1023);
  pA8 = map(pA8,1023,0,0, 1023);
  pA7 = map(pA7,1023,0,0, 1023);
  pA6 = map(pA6,1023,0,0, 1023);
  pA5 = map(pA5,1023,0,0, 1023);
  pA4 = map(pA4,1023,0,0, 1023);  
}

void printCapVals(int t)//function to print out capacitive sensor values
{
  
  //Serial1.print("Caps (12,10,8,11,9):");
  //Serial1.print("\t");
  //cap set 1
  Serial1.print(c7);
  Serial1.print("\t"); 
  Serial1.print(c10); 
  Serial1.print("\t");
  Serial1.print(c8); 
  Serial1.print("\t");
  Serial1.print(c11); 
  Serial1.print("\t");
  Serial1.print(c9);
  //cap set 2
  Serial1.print("\t"); 
  Serial1.print(c6); 
  Serial1.print("\t");
  Serial1.print(c5); 
  Serial1.print("\t");
  Serial1.print(c17); 
  Serial1.print("\t");
  Serial1.print(c2);
  Serial1.print("\t");
  Serial1.print(c12);
  
  if(t == 0) //bias to give new line or allow other printing on same line
    Serial1.print("\t");
  else
    Serial1.println();  
}

void printPresVals(int t)//function to print out pressure sensor values
{
  //Serial1.print("Pres ( R L - A,8,7,9,4,6,5):");
  //Serial1.print("\t");
  Serial1.print(pA7); 
  Serial1.print("\t");
  Serial1.print(pA8); 
  Serial1.print("\t");
  Serial1.print(pA4); 
  Serial1.print("\t");
  Serial1.print(pA9); 
  Serial1.print("\t");
  Serial1.print(pA5);
  Serial1.print("\t"); 
  Serial1.print(pA6); 

  if(t == 0)//bias to give new line or allow other printing on same line
    Serial1.print("\t");
  else
    Serial1.println();
}


void autoCalibrateOff(
)//function to turn autocalibration OFF. The values were obtained from the library documentation
{
  cs_c12.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c11.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c9.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c8.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c7.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_c17.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void hardcodeDown(int div,int sub)
{//7,10,8,11,9
  c7 = c7/div;
  c10 = c10/div;  
  c8 = c8/div;
  c11 = c11/div;
  c9 = c9/div;
  
  //6,5,17,2,12
  c6 = c6/div;
  c5 = c5/div;  
  c17 = c17/div;
  c2 = c2/div;
  c12 = c12/div;
  
  if(sub == 1)
  {
    c7 = c7 - c7Bias;
    c10 = c10 - c10Bias;
    c8 = c8 - c8Bias;
    c11 = c11 - c11Bias;
    c9 = c9 - c9Bias;
    
    c6 = c6 - c6Bias;
    c5 = c5 - c5Bias;
    c17 = c17 - c17Bias;
    c2 = c2 - c2Bias;
    c12 = c12 - c12Bias;
  }
  /*
  c12 = stayPositive(c12 - c12Bias);
  c11 = stayPositive(c11 - c11Bias);
  c10 = stayPositive(c10 - c10Bias);
  c9 = stayPositive(c9 - c9Bias);
  c8 = stayPositive(c8 - c8Bias);
  c7 = stayPositive(c7 - c7Bias);
  c6 = stayPositive(c6 - c6Bias);
  c5 = stayPositive(c5 - c5Bias);
  c2 = stayPositive(c2 - c2Bias);
  */
}

long stayPositive(long in)
{
  if(in<0)
    return 0;
  else 
    return in;  
}





