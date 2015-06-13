// Constants
#define nSensors 2
#define noiseDiffBarrier 100

int sensorValue = 0;
byte Pins[] = {A0,A1};
int values[nSensors]={0};

void setup() {
  Serial.begin(9600);  // Such serial, many wow
}

void loop() {
  
  // Check sensors
  
  int signal=0;
  for (int x = 0; x < nSensors; ++x){  // For each sensor
    // Read new value
    int newValue = analogRead(Pins[x]);
    
    int diff = abs(sensorValue - newValue);
    
    // test cheat
    //diff = 200;
    
    sensorValue = newValue;
    
    // Check for threshold
    if(diff > noiseDiffBarrier){
      signal += 1 << x;
    }
  }
  
  if(signal > 0){
    Serial.println(signal);
  }
  
  //delay(1000);
  delay(1);        // delay in between reads for stability
}
