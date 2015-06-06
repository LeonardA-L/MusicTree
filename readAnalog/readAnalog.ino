// Constants
int sensorValue = 0;

void setup() {
  Serial.begin(9600);  // Such serial, many wow
}

void loop() {
  // Read new value
  int newValue = analogRead(A0);
  int diff = abs(sensorValue - newValue);
  sensorValue = newValue;
  // Check for threshold
  if(diff>100){
    Serial.println(diff);
  }
  delay(1);        // delay in between reads for stability
}
