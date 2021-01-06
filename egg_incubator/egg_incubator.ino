#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Wire.h>

#define T_MIN    28
#define T_MAX    30

const int relayPin = D5;

Adafruit_BME280 bme;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!"); 
    for (;;);
  }

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  delay(2000);

  oled.setFont(&FreeSans9pt7b);
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 20);

  // Display static text
  oled.println("Initializing");
  oled.println("incubator...");
  oled.display();

  delay(3000);
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C    ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println();

  oled.clearDisplay();
  oled.setCursor(0, 25);
  oled.print("    T: ");
  oled.print(temperature);
  oled.print(" *C");
  oled.println();

  oled.print("    H: ");
  oled.print(humidity);
  oled.print("%");
  oled.display();

  if (temperature < T_MIN) {
    digitalWrite(relayPin, HIGH);
  }

  if (temperature > T_MAX) {
    digitalWrite(relayPin, LOW);
  }

  delay(1000);
}
