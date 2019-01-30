#include <FastLED.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <Ethernet.h>

#define LED_PIN  7
#define NUM_LEDS 30

#define BRIGHTNESS 255

#define DEGREES_SIZE   4
#define SEGMENT_SIZE   3
#define SEGMENT_NUMBER 7

uint8_t mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetClient ethernetClient;
HttpClient client = HttpClient(ethernetClient, "temperaturaaqui-proxy.azurewebsites.net", 80);

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

String currentTemperature = "00";

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);

  client.setTimeout(10000);

  Serial.println("configuring Ethernet...");
  if (!Ethernet.begin(mac)) {
    Serial.println("Failed to configure Ethernet");
    return;
  }
  Serial.println("Ethernet configured");
}

void updateTemperature() {
  Serial.println("fetching...");
  
  client.get("/api/temperature");
  int statusCode = client.responseStatusCode();
  if (statusCode == 200) {
    Serial.println("fetched successfully");
    String response = client.responseBody();
    currentTemperature = response;
    Serial.println(String(response) + " degrees Celcius");
  } else {
    Serial.println("failed to fetch");
    Serial.println("error code: " + String(statusCode));
  }
}

void loop() {
  updateTemperature();

  clearDisplay();
  writePanel();

  delay(60000);
}

void clearDisplay() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void writePanel() {
  writeLeds(DEGREES, 4, CRGB::White);

  Serial.println("writing...");

  char firstChar = currentTemperature[0];
  writeSegments(firstChar, 0);

  char secondChar = currentTemperature[1];
  writeSegments(secondChar, 1);

  FastLED.show();

  Serial.println("done writing.");
}

void writeSegments(char character, int displayIndex) {
  CRGB color = 0xFFFFFF;
  auto segments = (displayIndex == 0) ? SEGMENTS_0 : SEGMENTS_1;

  if (character == '-') {
    writeLeds(segments[6], SEGMENT_SIZE, color);
    return;
  }

  int number = character - '0';
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
