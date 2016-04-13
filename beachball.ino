/*
Beachball Spinner Control
*/

// Motor is controlled by this PWM pin
int motorPin = A4;

// Define a variable for beachball status off by default
int status = 0;

// Declare function
int beachBall(String command);

// Do this once on startup
void setup() {
  pinMode(motorPin, OUTPUT);

  // Expose variables to the cloud
  Particle.variable("status", status);

  // Expose function to the cloud
  Particle.function("beachball", beachBall);

  // Turn beachball off on restart
  beachballOff();
}


void loop() {
    // Do this in an endless loop
}

// POST function
// This  function gets called when there is a matching POST request
int beachBall(String command) {
  if (command == "on") {
    beachballOn();
    return 1;
  }
  if (command == "off") {
    beachballOff();
    return 1;
  }
  return -1;
}

int beachballOn() {
  analogWrite(motorPin, 75);  // Faster than 75 gets a little hairy
  int status = 1;
  return 1;
}
int beachballOff() {
  analogWrite(motorPin, 0);
  int status = 0;
  return 1;
}
