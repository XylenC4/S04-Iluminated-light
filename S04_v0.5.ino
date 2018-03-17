#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#define LED_PIN         12
#define NUM_LEDS        14
#define LEDS_ALL        0
#define LEDS_Border     1
#define LEDS_S          2
#define LEDS_0          3
#define LEDS_4          4
#define LEDS_LIGHT      0
#define LEDS_DARK       1
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

struct CRGBLED {
  int iColorOffset = 3;
  int iIndexOffset = 0;
  int iLedCount;
  int iBrightness[2] = {255,255};
  int iLedArray[NUM_LEDS];
  CRGBPalette16 crgbPalette;
  TBlendType tblendLEDBlend = NOBLEND;
};

CRGBLED LedStripe[5];
bool bIsDark = false;

extern int iBrightness;
extern int iMode;

bool bFirstRun = 1;
bool bOneStripeForAllLEDS = true;

int iUpdatesPerSecond = 25;

void setup() {
    Serial.begin(9600);
    InitLED();
    SetupSwitches();
    delay(500); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN>(leds, 0, NUM_LEDS);
    FastLED.setBrightness(255);
        
}


void loop()
{
  ReadSwitches();    
    static uint8_t startI ndex = 0;
    startIndex += 1; /* motion speed */
    
    SetLED(startIndex);
       
    FastLED.show();
    FastLED.delay(1000 / iUpdatesPerSecond);
}

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( RainbowColors_p, colorIndex, 255, LINEARBLEND);
        colorIndex += 3;
    }
}

void SetLEDArray(uint8_t colorIndex, CRGBLED LedConfig) {
   for( int i = 0; i < NUM_LEDS; i++) {
        int iLedNr = LedConfig.iLedArray[i];
        if(iLedNr>=0) {
          leds[iLedNr] = ColorFromPalette(LedConfig.crgbPalette, colorIndex, LedConfig.iBrightness[bIsDark]*iBrightness/100, LedConfig.tblendLEDBlend);
          colorIndex += LedConfig.iColorOffset;
//        Serial.print("LED");
//        Serial.print(i);
//        Serial.print("=");
//        Serial.println(iLedNr);
        }
    };
//    Serial.print(":iMode:");
//    Serial.print(iMode);
//    Serial.print("colorIndex:");
//    Serial.print(colorIndex);
//    Serial.print(":iColorOffset:");
//    Serial.println(LedConfig.iColorOffset);
   }
