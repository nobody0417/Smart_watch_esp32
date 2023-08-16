//nobody0417 v22_12_22
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <WiFi.h>
#include "time.h"
#include "icons.h"
//#include "basic_functions.h"


//lcd interface
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//touch buttons
#define TOUCH_THRESHOLD 20
int touchValue =100 ;

unsigned long lastTouchTime = 0; //for timer to go to home screen
#define TIMEOUT_DURATION 2000 // Timeout duration in milliseconds

const char* ssid = "WirelessNet";
const char* password = "cdevfrbgt";

const char* ntpServer = "pool.ntp.org";
//const long gmtOffset_sec = 3600;
//const int daylightOffset_sec = 3600;

//for home page
bool home = true;
//watch face
int watch_face = 5;
//defining stuct for time
struct tm timeinfo;
#define weather_HEIGHT 30
#define weather_WIDTH 30

void printLocalTime() {
  //struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


//connect to WiFi
void connect_wifi() {
  uint8_t count = 0;
  Serial.printf("Connecting to %s ", ssid);
  display.printf("Connecting to \n %s", ssid);
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    display.print(".");
    display.display();
    if (count >= 8) {
      count = 0;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.printf("Connecting to \n %s", ssid);
      display.display();
    }
  }
}
void disconnect_wifi() {
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
//setting time zone
void setTimezone(String timezone){
  Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  //display..printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void init_Time(String timezone){
  //struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
  if(!getLocalTime(&timeinfo)){
    Serial.println("  Failed to obtain time");
    return;
  }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
  printLocalTime();
}

/*
void get_time() {
  //init and get the time
  configTime(0, 0, ntpServer);
  printLocalTime();
}
*/
void oled_begin() {
  delay(250);                        // wait for the OLED to power up
  display.begin(i2c_Address, true);  // Address 0x3C default
                                     //display.setContrast (0); // dim display

  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, SH110X_WHITE);
  display.display();
}


//no need
/*
void oled_display_time() {
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  //struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    display.println("Failure is always an option");
    display.display();
    display.println("Failed to obtain time");
    display.display();
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  display.clearDisplay();
  display.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  display.display();
}

*/


void oled_display() {
  //display time
  //struct tm timeinfo;

  /*
  getLocalTime(&timeinfo);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(&timeinfo, "%H:%M:%S");
  display.println(&timeinfo, "%m %d %Y");
  display.println(&timeinfo, "%A");
  display.drawBitmap(90,2,darkcloudy,30,30,1);
  display.display();
  */
  getLocalTime(&timeinfo);
  oled_display1();
}


void setup() {
  oled_begin();
  //setting text style
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  Serial.begin(115200);

  connect_wifi();//connect to wifi

  Serial.println(" CONNECTED");
  init_Time("IST-5:30");//setting time zone
  //setTimezone("WET0WEST,M3.5.0/1,M10.5.0");
  disconnect_wifi(); //disconnecting wifi as we don't need it anymore 
  //time library takes care of time updating usng internal clock

  //for touch interupts
  touchAttachInterrupt(T4, touch1, TOUCH_THRESHOLD);
  touchAttachInterrupt(T5, touch2, TOUCH_THRESHOLD);
}
int x =0;


void loop() {
  //delay(100);
  //printLocalTime();
 // touch(); remove this
  if(home){
  oled_display();
 // Serial.println("in  oled display");
  //Serial.println(home);
  }
  if(x==1){
  gotTouch1();
  Serial.println("touch 1");
  }
    if(x==2){
  gotTouch2();
    Serial.println("touch 2");
  }
  // Check for timeout to go to home screen
  if (millis() - lastTouchTime >= TIMEOUT_DURATION) {
    returnToHomeScreen();
  }
}
