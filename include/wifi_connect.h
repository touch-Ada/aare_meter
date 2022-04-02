/**
 * This header file contains the needed WiFi functionality. 
 * This project is used to teach basic IT skills.
 * Thus, for the sake of simplicity, this file is not split up into a header-file and a cpp file, 
 * as it would be done normally.
 */


#include <WiFi.h>

void scanWifi()
{
  WiFi.mode(WIFI_STA);
  int16_t numberOfWifis = WiFi.scanNetworks();
  if (numberOfWifis > 0) 
  {
    for (int i = 0; i < numberOfWifis; i++)
    {
      Serial.print("WiFi name: ");
      Serial.println(WiFi.SSID(i));
      Serial.println("---");
    }
  }
  else
  {
    Serial.print("No WiFi found");
  }
}

void initWiFi(const char *ssid, const char *password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

boolean connectionOK()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    return WiFi.reconnect();
  }
  return true;
}