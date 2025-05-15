#include <Adafruit_NeoPixel.h>

// — Use GPIO 48 explicitly; PIN_NEOPIXEL is only defined on some Adafruit boards :contentReference[oaicite:0]{index=0}
#define PIN_RGB     48
#define NUM_PIXELS  1

Adafruit_NeoPixel rgb_led(NUM_PIXELS, PIN_RGB, NEO_GRB + NEO_KHZ800);

int val1 = 245;   // starts high
int val2 = 66;    // starts low
int val3 = 66;    // starts low
int phase = 0;    // tracks which ramp we’re in (0…5)

void setup() {
  // Initialize Serial for optional debugging
  Serial.begin(115200);
  delay(500);

  // Ensure the data line is set up correctly :contentReference[oaicite:1]{index=1}
  pinMode(PIN_RGB, OUTPUT);

  // Initialize NeoPixel library
  rgb_led.begin();
  rgb_led.setBrightness(50);
  rgb_led.show();   // turn all pixels off initially
}

void loop() {
  // 1) Update the pixel color
  rgb_led.setPixelColor(0, rgb_led.Color(val1, val2, val3));
  rgb_led.show();        // send data to the LED :contentReference[oaicite:2]{index=2}
  delay(1);             // ≥15 ms latch delay avoids RMT/WiFi conflicts on S3 :contentReference[oaicite:3]{index=3}

  // 2) (Optional) print current state to Serial for debugging :contentReference[oaicite:4]{index=4}
  Serial.print("Phase "); Serial.print(phase);
  Serial.print(" — RGB: "); Serial.print(val1);
  Serial.print(","); Serial.print(val2);
  Serial.print(","); Serial.println(val3);

  // 3) Cycle through six mini-phases for a smooth loop:
  switch (phase) {
    case 0:                          // ramp val3 up
      if (++val3 >= 245) phase = 1;
      break;

    case 1:                          // ramp val1 down
      if (--val1 <= 66) phase = 2;
      break;

    case 2:                          // ramp val2 up
      if (++val2 >= 245) phase = 3;
      break;

    case 3:                          // ramp val3 down
      if (--val3 <= 66) phase = 4;
      break;

    case 4:                          // ramp val1 up
      if (++val1 >= 245) phase = 5;
      break;

    case 5:                          // ramp val2 down
      if (--val2 <= 66) phase = 0;
      break;
  }
}
