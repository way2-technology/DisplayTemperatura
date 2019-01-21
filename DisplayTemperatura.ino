#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    30

#define DEGREES_SIZE  4
#define ZERO_SIZE     12
#define ONE_SIZE      5
#define TWO_SIZE      11
#define THREE_SIZE    11
#define FOUR_SIZE     9
#define FIVE_SIZE     11
#define SIX_SIZE      12
#define SEVEN_SIZE    7
#define EIGHT_SIZE    13
#define NINE_SIZE     11

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  Serial.begin(9600);

}

const int DEGREES[DEGREES_SIZE] = {6, 7, 8, 9};

const int NUMBER_ZERO_0[ZERO_SIZE]    = {0, 1, 2, 13, 12, 14, 16, 23, 22, 24, 25, 26};
const int NUMBER_ONE_0[ONE_SIZE]      = {2, 12, 16, 22, 26};
const int NUMBER_TWO_0[TWO_SIZE]      = {0, 1, 2, 12, 16, 15, 14, 23, 24, 25, 26};
const int NUMBER_THREE_0[THREE_SIZE]  = {0, 1, 2, 12, 16, 15, 14, 22, 24, 25, 26};
const int NUMBER_FOUR_0[FOUR_SIZE]    = {0, 2, 13, 12, 14, 15, 16, 22, 28};
const int NUMBER_FIVE_0[FIVE_SIZE]    = {0, 1, 2, 13, 14, 15, 16, 22, 24, 25, 26};
const int NUMBER_SIX_0[SIX_SIZE]      = {0, 1, 2, 13, 14, 15, 16, 23, 22, 24, 25, 26};
const int NUMBER_SEVEN_0[SEVEN_SIZE]  = {0, 1, 2, 12, 16, 22, 26};
const int NUMBER_EIGHT_0[EIGHT_SIZE]  = {0, 1, 2, 13, 12, 14, 15, 16, 23, 22, 24, 25, 26};
const int NUMBER_NINE_0[NINE_SIZE]    = {0, 1, 2, 13, 12, 14, 15, 16, 22, 25, 26};

const int NUMBER_ZERO_1[ZERO_SIZE]    = {3, 4, 5, 11, 10, 17, 19, 21, 20, 27, 28, 29};
const int NUMBER_ONE_1[ONE_SIZE]      = {5, 10, 19, 20, 29};
const int NUMBER_TWO_1[TWO_SIZE]      = {3, 4, 5, 10, 17, 18, 19, 21, 27, 28, 29};
const int NUMBER_THREE_1[THREE_SIZE]  = {3, 4, 5, 10, 17, 18, 19, 20, 27, 28, 29};
const int NUMBER_FOUR_1[FOUR_SIZE]    = {3, 5, 11, 10, 17, 18, 19, 20, 29};
const int NUMBER_FIVE_1[FIVE_SIZE]    = {3, 4, 5, 11, 17, 18, 19, 20, 27, 28, 29};
const int NUMBER_SIX_1[SIX_SIZE]      = {3, 4, 5, 11, 17, 18, 19, 21, 20, 27, 28, 29};
const int NUMBER_SEVEN_1[SEVEN_SIZE]  = {3, 4, 5, 10, 19, 20, 29};
const int NUMBER_EIGHT_1[EIGHT_SIZE]  = {3, 4, 5, 11, 10, 17, 18, 19, 21, 20, 27, 28, 29};
const int NUMBER_NINE_1[NINE_SIZE]    = {3, 4, 5, 11, 10, 17, 18, 19, 20, 29};

String values[5] = {"20", "23", "29", "32", "37"};

void clearDisplay(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void loop() {
  
  for (int i = 0; i < 5; i++){
    clearDisplay();
    Serial.println(values[i]);
    writePanel(values[i]);
    writeChar(DEGREES, 4, 0xff3300);
    FastLED.show();
    delay(2000);
  }
  
  /*
    for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = 0xff3300;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(100);
    }
  */
}

void writePanel(String text) {
  char firstChar = text[0];
  writeChar(firstChar, 0);

  char secondChar = text[1];
  writeChar(secondChar, 1);
}

void writeChar(char character, int displayIndex) {
  CRGB color = CRGB::Red;
  switch (character) {
    case '1':
      writeChar(displayIndex == 0 ? NUMBER_ONE_0 : NUMBER_ONE_1, ONE_SIZE, color );
      break;
    case '2':
      writeChar(displayIndex == 0 ? NUMBER_TWO_0 : NUMBER_TWO_1, TWO_SIZE, color );
      break;
    case '3':
      writeChar(displayIndex == 0 ? NUMBER_THREE_0 : NUMBER_THREE_1, THREE_SIZE, color );
      break;
    case '4':
      writeChar(displayIndex == 0 ? NUMBER_FOUR_0 : NUMBER_FOUR_1, FOUR_SIZE, color );
      break;
    case '5':
      writeChar(displayIndex == 0 ? NUMBER_FIVE_0 : NUMBER_FIVE_1, FIVE_SIZE, color );
      break;
    case '6':
      writeChar(displayIndex == 0 ? NUMBER_SIX_0 : NUMBER_SIX_1, SIX_SIZE, color );
      break;
    case '7':
      writeChar(displayIndex == 0 ? NUMBER_SEVEN_0 : NUMBER_SEVEN_1, SEVEN_SIZE, color );
      break;
    case '8':
      writeChar(displayIndex == 0 ? NUMBER_EIGHT_0 : NUMBER_EIGHT_1, EIGHT_SIZE, color );
      break;
    case '9':
      writeChar(displayIndex == 0 ? NUMBER_NINE_0 : NUMBER_NINE_1, NINE_SIZE, color );
      break;
    case '0':
      writeChar(displayIndex == 0 ? NUMBER_ZERO_0 : NUMBER_ZERO_1, ZERO_SIZE, color );
      break;
  }
}

void writeChar(int arr[], int numberOfElements, CRGB color) {
  for (int i = 0; i < numberOfElements; i++) {
    leds[arr[i]] = color;
  }
}
