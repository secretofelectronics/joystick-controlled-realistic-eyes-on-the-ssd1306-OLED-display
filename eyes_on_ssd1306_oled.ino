#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick pins
const int joyX = A0;  // Analog pin for joystick X-axis
const int joyY = A1;  // Analog pin for joystick Y-axis

// Eye parameters
int eyeRadius = 15;  // Radius of the eyes (white part)
int pupilRadius = 3;  // Radius of the black pupil
int eyeSeparation = 40;  // Distance between two eyes
int centerX = SCREEN_WIDTH / 2;  // Horizontal center of the screen
int centerY = SCREEN_HEIGHT / 2;  // Vertical center of the screen

void setup() {
  // Initialize the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Set up joystick input
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);

  display.clearDisplay();
  display.display();
}

void loop() {
  // Read the joystick values
  int xVal = analogRead(joyX);  // 0 to 1023
  int yVal = analogRead(joyY);  // 0 to 1023

  // Map joystick values to movement range (-5 to 5) for controlling pupil movement
  int xOffset = map(xVal, 0, 1023, -5, 5);
  int yOffset = map(yVal, 0, 1023, -5, 5);

  // Calculate positions for pupils (center + joystick offset)
  int pupilXLeft = centerX + xOffset - eyeSeparation / 2;
  int pupilXRight = centerX + xOffset + eyeSeparation / 2;
  int pupilY = centerY + yOffset;

  // Clear the display
  display.clearDisplay();

  // Draw the left eye (outer white circle) at the left center
  display.fillCircle(centerX - eyeSeparation / 2, centerY, eyeRadius, SSD1306_WHITE);
  // Draw the black dot (pupil) inside the left eye
  display.fillCircle(pupilXLeft, pupilY, pupilRadius, SSD1306_BLACK);

  // Draw the right eye (outer white circle) at the right center
  display.fillCircle(centerX + eyeSeparation / 2, centerY, eyeRadius, SSD1306_WHITE);
  // Draw the black dot (pupil) inside the right eye
  display.fillCircle(pupilXRight, pupilY, pupilRadius, SSD1306_BLACK);

  // Display the result
  display.display();

  // Small delay to make the movement smooth
  delay(50);
}