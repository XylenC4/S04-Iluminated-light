#include <EEPROM.h>

bool bMemIsDark = 0;
int iDarknessDelay = 0;
int iBrightness, iSpeed;
int iMode = 1;
bool bTouchSensor, bMemTouchSensor;
#define MaxModi 10

extern const TProgmemRGBPalette16 paletteBlueS04 PROGMEM;
extern const TProgmemRGBPalette16 palettePurpleMediumPurpleColors PROGMEM;
extern const TProgmemRGBPalette16 paletteLawnGreenLightGreen PROGMEM;
extern const TProgmemRGBPalette16 paletteRedOrangeRed PROGMEM;

void SetupSwitches() {
    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(6,INPUT_PULLUP);
    pinMode(7,INPUT_PULLUP);
    pinMode(8,INPUT_PULLUP);
    pinMode(10,INPUT);
    pinMode(11,INPUT_PULLUP);
}

void ReadSwitches() {
    bool iLeft1 = !digitalRead(3);
    bool iLeft2 = !digitalRead(4);
    bool iLeft3 = !digitalRead(5);
    bIsDark     = digitalRead(11);
    iBrightness = (iLeft1*25+iLeft2*50+iLeft3*100);

    bool iRight1 = !digitalRead(6);
    bool iRight2 = !digitalRead(7);
    bool iRight3 = !digitalRead(8);
    iUpdatesPerSecond = iRight1*10+iRight2*25+iRight3*50;

    bTouchSensor = digitalRead(10);

    if(bTouchSensor&&!bMemTouchSensor) {
      iMode++;
      if(iMode>MaxModi) {iMode=1;}
      bMemTouchSensor = true;
    }
    else if(!bTouchSensor)  {
      bMemTouchSensor = false;
    }
    
//   Serial.print(iLeft1);
//   Serial.print(";");
//   Serial.print(iLeft2);
//   Serial.print(";");
//   Serial.print(iLeft3);
//   Serial.print(";");
//   Serial.print(iRight1);
//   Serial.print(";");
//   Serial.print(iRight2);
//   Serial.print(";");
//   Serial.print(iRight3);
//    
//   Serial.print(";iBrightness: ");
//   Serial.print(iBrightness);
//   Serial.print(":iMode:");
//   Serial.println(iMode);
//   Serial.print(":IsDark: ");
//   Serial.print(bIsDark);
//   Serial.print(":UpdatesPerSecond: ");
//   Serial.print(iUpdatesPerSecond);
//   Serial.print(":TouchSensor: ");
//   Serial.println(bTouchSensor);
}

void SetLED(uint8_t startIndex) {  
    static int iModeOld = 0;
    bool bModeChange;
    if(iMode!=iModeOld) {
      bModeChange=true;
      iModeOld = iMode;
      SaveModeToEEPROM(iMode);
      }
      else if(iMode==iModeOld) {
      bModeChange=false;
      }
    
    switch(iMode) {
    case 1:
      if(bModeChange) {InitLED();

      SetLED(LEDS_Border, 0,  0, paletteBlackFireBrick_1,   LINEARBLEND, 150, 150);
      SetLED(LEDS_S,      3,  0, paletteBlackDarkMagenta_1, LINEARBLEND, 150, 150);
      SetLED(LEDS_0,      3,  0, paletteBlackBlue_1,        LINEARBLEND, 150, 150);
      SetLED(LEDS_4,      3,  0, paletteBlackGoldenrod_1,   LINEARBLEND, 200, 255);
      }
      
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    break;
    case 2:
      if(bModeChange) {InitLED();}
      LedStripe[LEDS_Border].crgbPalette = paletteBlueS04;
      LedStripe[LEDS_S].crgbPalette      = paletteLawnGreenLightGreen;
      LedStripe[LEDS_0].crgbPalette      = palettePurpleMediumPurple;
      LedStripe[LEDS_4].crgbPalette      = paletteRedOrangeRed;
    
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    break;
    case 3:
    if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    break;
    case 4:
      if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_ALL].iIndexOffset, LedStripe[LEDS_ALL]);
    case 5:
      if(bModeChange) {InitLED();
      SetLED(LEDS_Border, 0, 0, paletteBlueS04, LINEARBLEND, 100, 100);
      SetLED(LEDS_S,      3, 0, CloudColors_p , LINEARBLEND, 100, 100);
      SetLED(LEDS_0,      3, 0, LavaColors_p  , LINEARBLEND, 100, 100);
      SetLED(LEDS_4,      3, 0, OceanColors_p , LINEARBLEND, 255, 255);
      }
      
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    case 6:
      if(bModeChange) {InitLED();
      SetLED(LEDS_Border, 0,  0, paletteBlackBlue, LINEARBLEND, 100, 100);
      SetLED(LEDS_S,      3, 60, paletteBlackBlue, LINEARBLEND, 100, 100);
      SetLED(LEDS_0,      3, 40, paletteBlackBlue, LINEARBLEND, 100, 100);
      SetLED(LEDS_4,      3, 20, paletteBlackBlue, LINEARBLEND, 255, 255);
      }
      
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    case 7:
      if(bModeChange) {InitLED();
      SetLED(LEDS_Border, 0,  0, paletteBlackBlue, LINEARBLEND, 100, 100);
      SetLED(LEDS_S,      3, 60, paletteBlackDarkMagenta, LINEARBLEND, 100, 100);
      SetLED(LEDS_0,      3, 30, paletteBlackDarkMagenta, LINEARBLEND, 100, 100);
      SetLED(LEDS_4,      3, 30, paletteBlackDarkMagenta, LINEARBLEND, 255, 255);
      }
      
      SetLEDArray(startIndex + LedStripe[LEDS_Border].iIndexOffset, LedStripe[LEDS_Border]);
      SetLEDArray(startIndex + LedStripe[LEDS_S].iIndexOffset     , LedStripe[LEDS_S]);
      SetLEDArray(startIndex + LedStripe[LEDS_0].iIndexOffset     , LedStripe[LEDS_0]);
      SetLEDArray(startIndex + LedStripe[LEDS_4].iIndexOffset     , LedStripe[LEDS_4]);
    break;
    case 8:
      if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_ALL].iIndexOffset, LedStripe[LEDS_ALL]);
    case 9:
      if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_ALL].iIndexOffset, LedStripe[LEDS_ALL]);
    case 10:
      if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_ALL].iIndexOffset, LedStripe[LEDS_ALL]);
    default:
      if(bModeChange) {InitLED();}
      SetLEDArray(startIndex + LedStripe[LEDS_ALL].iIndexOffset, LedStripe[LEDS_ALL]);
    break;
   }
}

extern void SaveModeToEEPROM(int iMode) {
  int iCheckMode = -1;
  EEPROM.write(0, iMode);
  iCheckMode = EEPROM.read(0);

  Serial.print("Write mode to eeprom-> ");
  Serial.print(iMode);
  Serial.print(" :verify write-> ");
  Serial.println(iCheckMode);
}

extern int LoadModeFromEEPROM() {
  int iMode = 0;
  iMode = EEPROM.read(0);
  
  Serial.print("Read mode from eeprom-> ");
  Serial.print(iMode);
  
  if(iMode<=0 || iMode>MaxModi) {
    iMode=1;
  }

  Serial.print(" : return->");
  Serial.println(iMode);
  
  return iMode;
}

