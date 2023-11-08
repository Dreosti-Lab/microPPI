// uPPI (micro-PPI)

// Specify pins
int piezo_pin = A0; // Analog 0 (labeled IN, but can be used as out on Uno R4)
int led_pin = 13;   // Digital 13

// Specify experiment parameters
int pulse_interval_ms = 5000;
int pre_pulse_interval_ms = 500;
int large_amp = 200;
int small_amp = 25;
int piezo_duration_ms = 10;
int led_duration_ms = 100;

void setup() {
  pinMode(led_pin, OUTPUT);
  analogWrite(piezo_pin, 0);
 } 

void loop() {
  // Pulse ----------------

  // Wait for next pulse
  delay(pulse_interval_ms);

  // Enable piezo and LED
  analogWrite(piezo_pin, large_amp);
  digitalWrite(led_pin, HIGH);

  // Wait for piezo end
  delay(piezo_duration_ms);
  analogWrite(piezo_pin, 0);

  // Wait for LED end
  delay(led_duration_ms - piezo_duration_ms);
  digitalWrite(led_pin, LOW);

  // Pre-pulse ----------------

  // Wait for next pre-pulse
  delay(pulse_interval_ms);

  // Enable piezo and LED
  analogWrite(piezo_pin, small_amp);
  digitalWrite(led_pin, HIGH);

  // Wait for piezo end
  delay(piezo_duration_ms);
  analogWrite(piezo_pin, 0);

  // Wait for LED end
  delay(led_duration_ms - piezo_duration_ms);
  digitalWrite(led_pin, LOW);

  // Wait for next pulse
  delay(pre_pulse_interval_ms);

  // Enable piezo and LED
  analogWrite(piezo_pin, large_amp);
  digitalWrite(led_pin, HIGH);

  // Wait for piezo end
  delay(piezo_duration_ms);
  analogWrite(piezo_pin, 0);

  // Wait for LED end
  delay(led_duration_ms - piezo_duration_ms);
  digitalWrite(led_pin, LOW);
}
