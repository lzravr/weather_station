#include "cactus_io_DHT22.h"
char c;

int photocellPinS = A0;
int photocellReadingS;
int photocellPins = A1;
int photocellReadings;
int photocellReadingAvg;
int sensorPinT = A2;
int LEDpin = 3;
int LEDbrightness;

int reading;
float voltage, temperature, temp2, hum2;
  
#define DHT1pin 2
#define DHT2pin 4
DHT22 dht(DHT1pin);
DHT22 dht2(DHT2pin);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  dht2.begin();
}

void loop()
{
  if(Serial.available())
  {
    c = Serial.read();

    switch(c)
    {
      case 'T':
      {
         dht.readTemperature();

         Serial.print('T');
         Serial.print(dht.temperature_C); 
         Serial.print('\n');
         
        break;
      }
      case 't':
      {
         dht2.readTemperature();

         Serial.print('t');
         Serial.print(dht2.temperature_C); 
         Serial.print('\n');

         break;
      }
      case 'V':
      {
        dht.readHumidity();
        if (isnan(dht.humidity)) 
        {
          Serial.println("DHT sensor read failure!");
          return;
        }

        Serial.print('V');
        Serial.print(dht.humidity);
        Serial.print('\n');
        
        break;
      }
      case 'v':
      {
        dht2.readHumidity();
        if (isnan(dht2.humidity)) 
        {
          Serial.println("DHT sensor read failure!");
          return;
        }

        Serial.print('v');
        Serial.print(dht2.humidity);
        Serial.print('\n');
        break;
      }
      case 'S':
      {
          pinMode(LEDpin, OUTPUT);
          analogWrite(LEDpin, LOW);
        
          pinMode(photocellPinS,INPUT);
          photocellReadingS = analogRead(photocellPinS);  

          Serial.print('S');
          Serial.print(photocellReadingS);
          Serial.print('\n');

          //photocellReadingS = 1023 - photocellReadingS;
          //LEDbrightness = map(photocellReadingS, 0, 1023, 0, 255);
          //analogWrite(LEDpin, LEDbrightness);
          
          if(photocellReadingS >= 0 && photocellReadingS < 10)
            analogWrite(LEDpin, 255);
            
          if(photocellReadingS >= 10 && photocellReadingS < 100)
            analogWrite(LEDpin, 128);
          
          if(photocellReadingS >= 100 && photocellReadingS < 200)
            analogWrite(LEDpin, 64);
            
          if(photocellReadingS >= 200 && photocellReadingS < 1023)
            analogWrite(LEDpin, 0);
          
        break;
      }
      case 's':
      {
        pinMode(LEDpin, OUTPUT);
        analogWrite(LEDpin, LOW);
        
        pinMode(photocellPins,INPUT);
        photocellReadings = analogRead(photocellPins);  

        Serial.print('s');
        Serial.print(photocellReadings);
        Serial.print('\n');

        //photocellReadings = 1023 - photocellReadings;
        //LEDbrightness = map(photocellReadings, 0, 1023, 0, 255);
       
        //analogWrite(LEDpin, LEDbrightness);
        
        if(photocellReadings >= 0 && photocellReadings < 10)
          analogWrite(LEDpin, 255);
          
        if(photocellReadings >= 10 && photocellReadings < 100)
          analogWrite(LEDpin, 128);
        
        if(photocellReadings >= 100 && photocellReadings < 200)
          analogWrite(LEDpin, 64);
          
        if(photocellReadings >= 200 && photocellReadings < 1023)
          analogWrite(LEDpin, 0);
        
        break;
      }
      case 'A':
      {
        dht.readTemperature();
        temperature = dht.temperature_C;
        dht2.readTemperature();
        temp2 = dht2.temperature_C;
              
        dht.readHumidity();
        if (isnan(dht.humidity)) 
        {
          Serial.println("DHT sensor read failure!");
          return;
        }
        dht2.readHumidity();
        if (isnan(dht.humidity)) 
        {
          Serial.println("DHT sensor read failure!");
          return;
        }
        
        pinMode(photocellPinS,INPUT);
        photocellReadingS = analogRead(photocellPinS);  
        
        pinMode(photocellPins,INPUT);
        photocellReadings = analogRead(photocellPins);
        
        //photocellReadings = 1023 - photocellReadings;
        //LEDbrightness = map(photocellReadings, 0, 1023, 0, 255);
        pinMode(LEDpin, OUTPUT);
        analogWrite(LEDpin, LOW);
        //analogWrite(LEDpin, LEDbrightness);
        
        photocellReadingAvg = (photocellReadings + photocellReadingS) / 2;
        
        if(photocellReadingAvg >= 0 && photocellReadingAvg < 10)
          analogWrite(LEDpin, 255);
          
        if(photocellReadingAvg >= 10 && photocellReadingAvg < 100)
          analogWrite(LEDpin, 128);
        
        if(photocellReadingAvg >= 100 && photocellReadingAvg < 200)
          analogWrite(LEDpin, 64);
          
        if(photocellReadingAvg >= 200 && photocellReadingAvg < 1023)
          analogWrite(LEDpin, 0);
        
        Serial.print('A');
        Serial.print(temperature);
        Serial.print(',');
        Serial.print(temp2);
        Serial.print(',');
        Serial.print(dht.humidity);
        Serial.print(',');
        Serial.print(dht2.humidity);
        Serial.print(',');
        Serial.print(photocellReadingS);
        Serial.print(',');
        Serial.print(photocellReadings);
        Serial.print('\n');

        break;
      }
    }
  }
  
}
