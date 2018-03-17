extern const TProgmemRGBPalette16 paletteBlueS04 PROGMEM;

int iLEDComplete[5][NUM_LEDS]     = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13},
                                    { 0, 1, 2, 3, 4, 5,-1,-1,-1,-1,-1,-1,-1,-1},
                                    { 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                    {10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                    {12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
                                 


void InitLED(void) {
    LedStripe[LEDS_ALL].iLedCount = NUM_LEDS;
    LedStripe[LEDS_ALL].iColorOffset = 3;
    LedStripe[LEDS_ALL].iIndexOffset = 0;
    LedStripe[LEDS_ALL].crgbPalette = RainbowStripeColors_p;
    LedStripe[LEDS_ALL].iBrightness[LEDS_LIGHT] = 255;
    LedStripe[LEDS_ALL].iBrightness[LEDS_DARK] = 255;
    LedStripe[LEDS_ALL].crgbPalette = RainbowStripeColors_p;
    LedStripe[LEDS_ALL].tblendLEDBlend = LINEARBLEND;
    memcpy(LedStripe[LEDS_ALL].iLedArray, iLEDComplete[LEDS_ALL], sizeof(LedStripe[LEDS_ALL].iLedArray));
    
    LedStripe[LEDS_Border].iLedCount = 6;
    LedStripe[LEDS_Border].iColorOffset = 0;
    LedStripe[LEDS_Border].iIndexOffset =0;
    LedStripe[LEDS_Border].crgbPalette = paletteBlueS04;
    LedStripe[LEDS_Border].iBrightness[LEDS_LIGHT] = 255;
    LedStripe[LEDS_Border].iBrightness[LEDS_DARK] = 255;
    LedStripe[LEDS_Border].tblendLEDBlend = LINEARBLEND;
    memcpy(LedStripe[LEDS_Border].iLedArray, iLEDComplete[LEDS_Border], sizeof(LedStripe[LEDS_ALL].iLedArray));
    
    LedStripe[LEDS_S].iLedCount = 3;
    LedStripe[LEDS_S].iColorOffset = 0;
    LedStripe[LEDS_S].iIndexOffset = 0;
    LedStripe[LEDS_S].crgbPalette = RainbowStripeColors_p;
    LedStripe[LEDS_S].iBrightness[LEDS_LIGHT] = 255;
    LedStripe[LEDS_S].iBrightness[LEDS_DARK] = 255;
    LedStripe[LEDS_S].tblendLEDBlend = LINEARBLEND;
    memcpy(LedStripe[LEDS_S].iLedArray, iLEDComplete[LEDS_S], sizeof(LedStripe[LEDS_ALL].iLedArray));
    
    LedStripe[LEDS_0].iLedCount = 3;
    LedStripe[LEDS_0].iColorOffset = 0;
    LedStripe[LEDS_0].iIndexOffset = 60;
    LedStripe[LEDS_0].crgbPalette = RainbowStripeColors_p;
    LedStripe[LEDS_0].iBrightness[LEDS_LIGHT] = 100;
    LedStripe[LEDS_0].iBrightness[LEDS_DARK] = 10;
    LedStripe[LEDS_0].tblendLEDBlend = LINEARBLEND;
    memcpy(LedStripe[LEDS_0].iLedArray, iLEDComplete[LEDS_0], sizeof(LedStripe[LEDS_ALL].iLedArray));
    
    LedStripe[LEDS_4].iLedCount = 2;
    LedStripe[LEDS_4].iColorOffset = 0;
    LedStripe[LEDS_4].iIndexOffset = 120;
    LedStripe[LEDS_4].crgbPalette = RainbowStripeColors_p;
    LedStripe[LEDS_4].iBrightness[LEDS_LIGHT] = 255;
    LedStripe[LEDS_4].iBrightness[LEDS_DARK] = 255;
    LedStripe[LEDS_4].tblendLEDBlend = LINEARBLEND;
    memcpy(LedStripe[LEDS_4].iLedArray, iLEDComplete[LEDS_4], sizeof(LedStripe[LEDS_ALL].iLedArray));
}

void SetLED(uint8_t iStripeID, uint8_t iColorOffset, uint8_t iIndexOffset, CRGBPalette16 crgbPalette, TBlendType tblendLEDBlend, uint8_t iBrightnessLight, uint8_t iBrightnessDark) {
    LedStripe[iStripeID].iColorOffset = iColorOffset;
    LedStripe[iStripeID].iIndexOffset = iIndexOffset;
    LedStripe[iStripeID].crgbPalette = crgbPalette;
    LedStripe[iStripeID].tblendLEDBlend = tblendLEDBlend;
    LedStripe[iStripeID].iBrightness[LEDS_LIGHT] = iBrightnessLight;
    LedStripe[iStripeID].iBrightness[LEDS_DARK] = iBrightnessDark;
}


