#include <Arduino.h>

#define ADC_RESOLUTION 0.0049 // 4.9 millivolts per unit

int index;
double voltage;
char LF = '\n';
String inString;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

void loop() {
  if (Serial.available() > 0)
  {
    inString = Serial.readStringUntil(LF);
    if (inString.equals("HBT\r"))
    {
      Serial.println("HBT OK");
    }
    else if (inString.equals("VER\r"))
    {
      Serial.println("VER TESTSTUB 1.0");
    }
    else if (inString.startsWith("MVC"))
    {
      // NOTE: pin specifiers are ignored, not checked.
      index = inString.length()-1;
      if (inString[index] == '\r')
      {
        inString[index] = ' '; // Replace CR with space
        voltage = analogRead(A1) * ADC_RESOLUTION;
        inString += voltage;
        inString += " ";
        voltage = analogRead(A2) * ADC_RESOLUTION;
        inString += voltage;
        inString += " ";
        voltage = analogRead(A3) * ADC_RESOLUTION;
        inString += voltage;

        Serial.println(inString);
      }
      else
      {
        Serial.println("BCM " + inString );
      }
    }
    else
    {
      Serial.println("BCM " + inString );
    }
  }
}
