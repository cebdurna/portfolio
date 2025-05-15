#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];  // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  // Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int pin1 = 18;
int pin2 = 19;
int pin3 = 20;

void setup()
{
  Serial.begin(115200);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))  //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);   //Turn off Green LED
}

bool enableDEmoji = true;
bool enableFEmoji = true;
bool enableTEmoji = true;

void loop()
{
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE;  //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }

    if ((beatAvg > 55) && (beatAvg < 100) && enableFEmoji && irValue > 50000)
    {
      enableDEmoji = true;
      enableFEmoji = false;
      enableTEmoji = true;
      digitalWrite(pin1, HIGH);
      delay(40000);
      digitalWrite(pin1, LOW);
    }
    else if ((beatAvg > 110) && enableTEmoji && irValue > 50000)
    {
      enableDEmoji = true;
      enableFEmoji = true;
      enableTEmoji = false;
      digitalWrite(pin2, HIGH);
      delay(40000);
      digitalWrite(pin2, LOW);
    }
    else if ((beatsPerMinute < 20) && enableDEmoji && (irValue > 50000))
    {
      enableDEmoji = false;
      enableFEmoji = true;
      enableTEmoji = true;
      digitalWrite(pin3, HIGH);
      delay(40000);
      digitalWrite(pin3, LOW);
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);

  if (irValue < 50000)
  {
    Serial.print(" No finger?");
  }

  Serial.println();
}