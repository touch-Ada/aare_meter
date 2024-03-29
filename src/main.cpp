/**
 * aare_meter
 *
 * Reads the current temperature of the Aare from aare.guru
 * Transforms the temperature into a value between 0 and MAX_DAC_VALUE
 * Sends this value to a voltmeter which serves as thermometer
 * Repeats the request every 10 minutes
 */

#include "Arduino.h"
#include <HTTPClient.h>
#include <driver/dac.h>
#include <WiFiManager.h>

#define MIN_TEMPERATURE 0.0
#define MAX_TEMPERATURE 25.0
#define MAX_DAC_VALUE 255
#define HTTP_SUCCESS_CODE 200

// WiFiManager to configure WiFi
WiFiManager wifiManager;

// url containing the REST call to the aare.guru API
String request_url = "http://aareguru.existenz.ch/v2018/today?values=aare&city=bern&app=touch-ada&version=1.3";

// HTTPClient to perform request on aare.guru
HTTPClient client;

void setup()
{
  // set the data rate in bits per second (baud) for serial data transmission
  Serial.begin(9600);

  // setup an access point named 'aare_meter' for WiFi configuration in the browser
  wifiManager.autoConnect("aare_meter");

  // initialize DAC
  dac_output_enable(DAC_CHANNEL_1);
}

void loop()
{
  // set up connection to aare.guru and send request in order to obtain the current temperature
  client.begin(request_url);

  // placeholder for the response of aare.guru
  String payload;

  // get response code of aare.guru (may be OK, not found, internal server error etc.)
  int httpCode = client.GET();

  // check if the response of aare.guru is 200, meaning OK
  if (httpCode == HTTP_SUCCESS_CODE)
  {
    // read the body of the request, in this case the temperature
    payload = client.getString();

    // show the received temperature on the terminal
    Serial.print("Aare temperature: ");
    Serial.println(payload);

    // transform the temperature from text to a floating-point number
    float temperature = payload.toFloat();

    // make sure that the temperature does not exceed the limits of the scale
    if (temperature > MAX_TEMPERATURE)
    {
      Serial.println("Setting temperature from " + payload + " to 25");
      temperature = MAX_TEMPERATURE;
    }
    if (temperature < MIN_TEMPERATURE)
    {
      Serial.println("Setting temperature from " + payload + " to 0");
      temperature = MIN_TEMPERATURE;
    }

    // calculate the DAC (digital-to-analog converter) value
    int temperature_dac = MAX_DAC_VALUE / MAX_TEMPERATURE * temperature;

    // show the DAC value on the terminal
    Serial.print("DAC value: ");
    Serial.println(temperature_dac);

    // send the DAC value to the corresponding pin on the microcontroller
    dacWrite(DAC1, temperature_dac);
  }
  else
  {
    // print an error containing the error code if the the answer of aare.guru was not OK
    Serial.println("Error " + String(httpCode) + " on HTTP request");
  }
  // terminate the connection to aare.guru
  client.end();

  // wait for 5 minutes before repeating the loop
  delay(300000);
}
