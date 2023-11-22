// uPPI_TR (micro-PPI)

// Specify pins
int piezo_pin = A0; // Analog 0 (labeled IN, but can be used as out on Uno R4)
int led_pin = 13;   // Digital 13

// Specify experiment parameters
int trial_interval_ms = 90000;  // Interval between pulse and prepulse trials
int prepulse_interval_ms = 300; // Interval between prepulse and pulse within a trial
int large_amp = 200;
int small_amp = 20;
int piezo_duration_ms = 10;
int led_duration_ms = 20; // 2 frames (100Hz) so we know we don't miss it.

// Variables to track timing
unsigned long currentMillis = 0;
unsigned long previousTrialMillis = 0;
unsigned long trialStartMillis = 0;
bool pulseTrial = true;

void setup() {
  pinMode(led_pin, OUTPUT);
  analogWrite(piezo_pin, 0);
}

void loop() {
  // Calculate elapsed time since the last trial
  currentMillis = millis();
  if (currentMillis - previousTrialMillis >= trial_interval_ms) { // if trial interval has passed...
    // Update the timing reference
    previousTrialMillis = currentMillis;

    // Set the start time of the trial
    trialStartMillis = currentMillis;

    // Check if it's a pulse trial or a prepulse trial
    if (pulseTrial) {
      // Pulse Trial ----------------
      analogWrite(piezo_pin, large_amp);
      digitalWrite(led_pin, HIGH);
      while (currentMillis - trialStartMillis < piezo_duration_ms) { // while we are still within the piezo duration...
        // update the time
        currentMillis = millis();
      }
      // once passed, turn the piezo off
      analogWrite(piezo_pin, 0);
      digitalWrite(led_pin, LOW);
    } else { // if it's a prepulse trial...
      // Prepulse Trial ----------------
      // do a prepulse
      analogWrite(piezo_pin, small_amp);
      digitalWrite(led_pin, HIGH);
      while (currentMillis - trialStartMillis < piezo_duration_ms) {
        // Wait for the piezo duration
        currentMillis = millis();
      }
      analogWrite(piezo_pin, 0);
      digitalWrite(led_pin, LOW);

      // Wait for the rest of the prepulse interval
      while (currentMillis - trialStartMillis < prepulse_interval_ms) {
        // update the time
        currentMillis = millis();
      }
      // Once passed...
      // do a pulse
      analogWrite(piezo_pin, large_amp);
      digitalWrite(led_pin, HIGH);
      while (currentMillis - trialStartMillis < piezo_duration_ms) {
        // Wait for the piezo duration
        currentMillis = millis();
      }
      analogWrite(piezo_pin, 0);
      digitalWrite(led_pin, LOW);
    }

    // Toggle the trial type for the next iteration
    pulseTrial = !pulseTrial;
  }
}
