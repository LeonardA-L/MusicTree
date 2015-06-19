// Constants
#define nSensors 2
#define noiseDiffBarrier 100
#define loopDelay 10
#define commandSize 4
#define debug true
#define calibrationTime  5000

#define calibrationCommand "cal"
#define pingCommand "ping"


int sensorValue = 0;
byte Pins[] = {A0,A1};
int values[nSensors]={0};
int maxNoise[nSensors]={0};
boolean playing[nSensors]={false};
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
  Serial.println("Printing command back :");
  for(int i=0;i<commandSize;++i){
    if(commands[i] != ""){
      Serial.println(commands[i]);
    }
  } 
}

void resetCommands(){
  for(int i=0;i<commandSize;++i){
    if(commands[i] != ""){
      commands[i] = "";
    }
  }
}

// Commands
void ping(){
    Serial.println("pong");
}

void calibrateOne(int idx){
  String s = "Calibrating ";
  s.concat(idx);
  Serial.println(s);
  int i=0;
  int smax=0;
  for(;i<calibrationTime;i++){
    int newValue = analogRead(Pins[i]);
    if(newValue > smax){
     smax = newValue; 
    }
    delay(1);
  }
  s="End of calibration, max :";
  s.concat(smax);
  maxNoise[i] = smax;
  Serial.println(s);
  
}

void calibrateAll(){
  Serial.println("//------ Calibrate all -----");
  for(int i=0;i<nSensors;++i){
    calibrateOne(i);
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
    
    // Ping
    if(commands[0] == pingCommand){
     ping(); 
    }
    // Calibration
    else if(commands[0] == calibrationCommand){
     // Calibrating only one sensor, by id
     if(commands[1] != "" && commands[1].toInt() < nSensors){
      calibrateOne(commands[1].toInt());
     }
     // Or launching general calibration
    else{
     calibrateAll();
    } 
    }
    
    resetCommands();
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
