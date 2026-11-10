// * Library imports
#include <Arduino.h>
#include <BluetoothAudio.h>
#include <I2S.h>

// * Status LED pins
#define LED_ON 16
#define LED_BT_ON 17

// * DAC pins
#define I2S_DATA_PIN 15
#define I2S_BCLK_PIN 13   // LRCK = GPIO14

// * Controller pins
#define JOYSTICK_X 26
#define JOYSTICK_Y 27
#define BTN_SEL 18
#define BTN_BACK 19

// * WIFi params
const char *SSID = "";
const char *PASS = "";

I2S i2s(OUTPUT);
A2DPSink a2dp;

void connectCB(void *param, bool connected) {
  (void) param;
  Serial.println(connected ? "A2DP connected" : "A2DP disconnected");
}

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);

  pinMode(LED_ON, OUTPUT);
  pinMode(LED_BT_ON, OUTPUT);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(BTN_SEL, INPUT);
  pinMode(BTN_BACK, INPUT);

  i2s.setDATA(I2S_DATA_PIN);
  i2s.setBCLK(I2S_BCLK_PIN);

  a2dp.setName("Oscilloscope Player");
  a2dp.setConsumer(new BluetoothAudioConsumerI2S(i2s));
  a2dp.onConnect(connectCB);
  a2dp.begin();

  Serial.println("A2DP sink running");

  digitalWrite(LED_BUILTIN, 1);
}

void loop() {
  digitalWrite(LED_ON, 1);
  digitalWrite(LED_BT_ON, 1);
}