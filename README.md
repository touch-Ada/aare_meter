# aare_meter
Retro thermometer of the river Aare.
The project uses ESP32 DAC to display the temperature on an analog voltmeter.
This project is used for training / worshops for female IT newbies.

![aare_meter](https://github.com/touch-Ada/aare_meter/blob/main/img/aare_meter_code.jpeg)

## Prerequisites
### Visual Studio Code
Visual Studio Code is an IDE (Integrated Development Environment).  
It helps us writing code, just like Word helps us writing Text.  
https://code.visualstudio.com/download  

### PlatformIO
PlatformIO is a tool for writing software for embedded systems, meaning a combination of Hardware and Software.  
It helps us deploying the code on our ESP32 microcontroller.  
https://platformio.org/install/ide?install=vscode  

### CH340 Driver
The driver allows us to communicate between our PC and the microcontroller.  
https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all  

## Deployment
To deploy the code, use the `upload` function of PlatformIO within Visual Studio Code.

## WiFi configuration
The WiFi configuration is done with the help of https://github.com/tzapu/WiFiManager  
Once the code is deployed, connect any of your devices (laptop, tablet, smartphone) to the WiFi named *aare_meter* (no password needed).  
Then, enter in the address bar the IP 192.168.4.1. There you can select your WiFi and enter the password if needed.  
Once confirmed, the ESP32 will restart again and connect with your WiFi.
