
/*
 * Arduino Timer with Load Control
 * This program toggles an output pin to control a load (e.g., lamp, relay)
 * for 3 hours ON and 3 hours OFF using a transistor circuit.
 */

const int outputPin = 3; // Output pin for load control
unsigned long onDuration = 3UL * 60 * 60 * 1000; // ON time duration (3 hours in ms)
unsigned long offDuration = 3UL * 60 * 60 * 1000; // OFF time duration (3 hours in ms)

unsigned long previousMillis = 0; // Stores last timer update
bool isOn = false; // Current state of the output (ON/OFF)

void setup() {
  pinMode(outputPin, OUTPUT); // Set the output pin as OUTPUT
  digitalWrite(outputPin, LOW); // Start with the output OFF
}

void loop() {
  unsigned long currentMillis = millis(); // Get current time

  if (isOn && (currentMillis - previousMillis >= onDuration)) {
    // If ON duration has passed, turn OFF the output
    isOn = false;
    digitalWrite(outputPin, LOW); // Turn OFF the load
    previousMillis = currentMillis; // Reset the timer
  } 
  else if (!isOn && (currentMillis - previousMillis >= offDuration)) {
    // If OFF duration has passed, turn ON the output
    isOn = true;
    digitalWrite(outputPin, HIGH); // Turn ON the load
    previousMillis = currentMillis; // Reset the timer
  }
}
