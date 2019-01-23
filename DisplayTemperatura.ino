#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    30

#define DEGREES_SIZE  4
#define SEGMENT_SIZE 3
#define SEGMENT_NUMBER 7

CRGB leds[NUM_LEDS];

const int DEGREES[DEGREES_SIZE] = {6, 7, 8, 9};

const int SEGMENTS_0[SEGMENT_NUMBER][SEGMENT_SIZE] = {
    {0, 1, 2},
    {2, 12, 16},
    {16, 22, 26},
    {24, 25, 26},
    {14, 23, 24},
    {0, 13, 14},
    {14, 15, 16}
};

const int SEGMENTS_1[SEGMENT_NUMBER][SEGMENT_SIZE] = {
    {3, 4, 5},
    {5, 10, 19},
    {19, 20, 29},
    {27, 28, 29},
    {17, 21, 27},
    {3, 11, 17},
    {17, 18, 19}
};

const int NUMBERS_ENCODED[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

String values[5] = {"20", "23", "29", "32", "37"};

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(9600);
}

void loop() {
  
  for (int i = 0; i < 5; i++){
    clearDisplay();
    writePanel(values[i]);
    writeLeds(DEGREES, 4, CRGB::White);
    FastLED.show();
    delay(2000);
  }
}

void clearDisplay(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void writePanel(String text) {
  char firstChar = text[0];
  writeSegments(firstChar, 0);

  char secondChar = text[1];
  writeSegments(secondChar, 1);
}

void writeSegments(char character, int displayIndex) {
  CRGB color = CRGB::White;

  int number = character - '0';
  const int (*segments)[SEGMENT_SIZE] = (displayIndex == 0) ? SEGMENTS_0 : SEGMENTS_1;
  int encodedSegments = NUMBERS_ENCODED[number];
  for (int i = 6; i >= 0; i--) {
    if ((encodedSegments >> i) & 1) {
        writeLeds(segments[i], SEGMENT_SIZE, color);
    }
  }
}

void writeLeds(const int arr[], int numberOfElements, CRGB color) {
  for (int i = 0; i < numberOfElements; i++) {
    leds[arr[i]] = color;
  }
}