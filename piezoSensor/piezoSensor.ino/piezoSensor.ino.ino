// Constants
#define nSensors 2
#define noiseDiffBarrier 100
#define loopDelay 10
#define commandSize 4
#define debug false

int sensorValue = 0;
byte Pins[] = {A0,A1};
int values[nSensors]={0};
String input="";
String commands[commandSize];
int c;
boolean commandComplete = false;

void setup() {
  Serial.begin(9600);  // Such serial, many wow
  input.reserve(200);
  input="";
  c=0;
}

void listenSerial(){
  while (Serial.available()) {
     // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the input String:
    if(inChar == ' '){  // Split arguments
        commands[c] = input;
        input = "";
        c++;
    }
    else if(inChar=='\n'){  // Ship
      commandComplete = true;
    }
    else{
      input += inChar;
    }
  }
  commands[c] = input;
}

void printBackCommand(){
  for(int i=0;i<commandSize;++i){
    if(commands[i] != ""){
      Serial.println(commands[i]);
      commands[i] = "";
    }
  } 
}

void loop() {
  // Listen for instructions
  listenSerial();
  // at the end of the command
  if(commandComplete){
    commandComplete = false;
    c=0;
    input="";
    
    if(debug){
      printBackCommand();
    }
  }
  
  // Check sensors
  // -------------
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
  // -------------
  
  delay(loopDelay);        // delay in between reads for stability
}
