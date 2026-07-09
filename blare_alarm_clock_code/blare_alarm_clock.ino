#include <Adafruit_GFX.h>      // core graphics library
#include <Adafruit_ST7789.h>   // driver for the ST7789 screen
#include <SPI.h>
int smooze = 2;
int hour_add = 1;
int hour_remove = 0;
int minute_add = 4;
int minute_remove = 5;
int hour = 0;
int minute = 0;
int seconds = 0;

// --- Pin assignments (change these to match how YOU wired it) ---
#define TFT_CS   7
#define TFT_RST  10
#define TFT_DC   8
#define TFT_SCLK 21
#define TFT_MOSI 20

// --- Objects live out here, outside any function ---
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// setup() runs ONCE when the board powers on
void setup() {
  Serial.begin(115200);          // lets the board talk to your computer

  tft.init(76, 284);             // screen dimensions
  tft.setRotation(2);            // orientation, could be different, try 0-3
  Serial.println("TFT Initialized!");

  tft.fillScreen(ST77XX_BLACK);  // clear the screen
  tft.setCursor(0, 0);           // top-left corner
  tft.setTextSize(2);            // a readable size
  tft.print("Hello, world!");    // draw some text so we know it works
  pinMode(snooze, INPUT);
  pinMode(hour_add, INPUT);
  pinMode(hour_remove, INPUT);
  pinMode(minute_add, INPUT);
  pinMode(minute_remove, INPUT);
}

// loop() runs OVER and OVER, forever
void loop() {
  // Your code goes here. Anything in here repeats forever!
  if (digitalRead(hour_add) == HIGH) {
    hour += 1;
  }
  if (digitalRead(hour_remove) == HIGH) {
    hour -= 1;
  }
  if (hour == 24) {
    hour = 0;
  }
  if (hour < 0) {
    hour = 23;
  }
  
  if (digitalRead(minute_add) == HIGH) {
    minute += 1;
  }
  if (digitalRead(minute_remove) == HIGH) {
    minute -= 1;
  }
  if (minute == 60) {
    minute = 0;
    hour += 1;
  }
  if (minute < 0) {
    minute = 59;
  }
  delay(1000);
  seconds += 1;
  if (seconds == 60) {
    seconds = 0;
    minute += 1;
  }
  tft.fillRect(20, 40, 150, 40, ST77XX_BLACK);

  tft.setCursor(20, 40);
  tft.setTextSize(4);
  tft.setTextColor(ST77XX_WHITE);

  if (hour < 10) tft.print("0");
  tft.print(hour);

  tft.print(":");

  if (minute < 10) tft.print("0");
  tft.print(minute);
}


