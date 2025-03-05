const int sensor_pin = 0;
int pulse_signal = 0;
float pulse_period = 0;
float BPM = 0;

// declare flags for data storage
bool any_peak_detected = false;
bool first_peak_detected = false;
unsigned long first_pulse_time = 0;
unsigned long second_pulse_time = 0;

// define thresholds
int upper_threshold = 340;
int lower_threshold = 320;

void setup() {

  Serial.begin(9600);

}

void loop() {

  // data acquisition
  delay(50);
  pulse_signal = analogRead(sensor_pin);
  //Serial.println(pulse_signal);


  if (pulse_signal > upper_threshold && any_peak_detected == false) {

    // add any peak flag when upper threshold is met and flag is removed
    any_peak_detected = true;
    
    // calculate pulse period from detected peaks
    if (first_peak_detected == false) {
      first_pulse_time = millis();
    } else {
      second_pulse_time = millis();
      pulse_period = second_pulse_time - first_pulse_time;
      first_pulse_time = second_pulse_time;
    }

    // add first peak flag when first upper threshold is met
    first_peak_detected = true;

  }

  if (pulse_signal < lower_threshold) {
    // remove any peak flag when lower threshold is met
    any_peak_detected = false;
  }
  
  // calculate BMP from pulse period
  BPM = 60000/pulse_period;
  Serial.println(BPM);

}
