
# Arduino Timer with Load Control

This project implements a timer on an Arduino Mini that toggles an output pin for controlling a load (e.g., lamp, relay) for **3 hours ON** and **3 hours OFF** in a loop. The circuit uses a transistor to safely manage the load.

## Features

- **3-hour ON/OFF cycle** using the `millis()` function (non-blocking).
- Load control through an NPN transistor or MOSFET.
- Supports both inductive and resistive loads.

## Components Required

1. **Arduino Mini** (or any Arduino board).
2. **NPN Transistor** (e.g., 2N2222, BC547) or **MOSFET** (e.g., IRF540N, IRLZ44N).
3. **Resistor** (1 kΩ for the transistor base).
4. **Diode** (1N4007, for inductive loads like motors or relays).
5. **Load** (e.g., lamp, relay).
6. **External Power Supply** (if needed for the load).
7. **Jumper Wires**.

## Circuit Diagram

Below is the schematic for connecting the Arduino to a load using a transistor:

```
   +5V (or external supply) --------------+
                                          |
                                         ( )
                                          |
                    +---------------------+
                    |                    |
                    |       Transistor   |
                 [Base]---[Resistor 1 kΩ]--- Arduino Output Pin (D3)
                 [Emitter]------------------- GND Arduino
                 [Collector]---|>|--- Load (e.g., Lamp)
                                |
                               GND Load
```

### Notes:
- For inductive loads (e.g., relays, motors), connect a diode (1N4007) parallel to the load to prevent back-EMF damage.
- Ensure the external power supply shares a common ground (GND) with the Arduino.
- Use a logic-level MOSFET (e.g., IRLZ44N) for higher power loads.

## Arduino Code

The Arduino code toggles the output pin for 3 hours ON and 3 hours OFF. Copy the following code into the Arduino IDE or download the `.ino` file.

### Code:
```cpp
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
```

Alternatively, [download the `.ino` file here](arduino_timer.ino).

## How It Works

1. The code initializes the output pin (`D3`) as an output and starts with it turned OFF.
2. The `millis()` function is used to measure the elapsed time without blocking the loop.
3. The output pin toggles between ON and OFF states every 3 hours.
4. The transistor acts as a switch to control the load:
   - When the Arduino output pin is HIGH, the transistor turns ON, allowing current to flow through the load.
   - When the Arduino output pin is LOW, the transistor turns OFF, stopping the current.

## Applications

- Periodic automation tasks (e.g., lighting, motors, relays).
- Energy-saving systems.
- Industrial timers.

## License

This project is open-source and available under the MIT License.
