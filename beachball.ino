/*
Beachball Spinner Control
*/

// Motor is controlled by this PWM pin
int motorPin = A4;

// Define a variable for beachball status off by default
int status = 0;

// Define a variable for beachball speed
int speed = 0;

// Declare functions
int beachBall(String command);

// Set the beachball speed
int beachBallv2(String command) {
    if ( command.length() > 0 ) {
        speed = command.toInt();
    }
    return speed;
}

// Spin or stop the ball based on speed setting
int spinner() {
    if ( speed > 0 && speed < 256 ) {
        analogWrite(motorPin, speed);
        status = 1;
    }

    if ( speed == 0 ) {
        analogWrite(motorPin, speed);
        status = 0;
    }
}

// Do this once on startup
void setup() {
  pinMode(motorPin, OUTPUT);

  // Expose variables to the cloud
  Particle.variable("status", status);
  Particle.variable("speed", speed);

  // Expose functions to the cloud
  Particle.function("beachball", beachBall);
  Particle.function("speedball", beachBallv2);

  // Turn beachball off on restart
  beachballOff();
}

void loop() {
    // Do this in an endless loop
    spinner();
}


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
  analogWrite(motorPin, 120);  // Faster than 120 gets a little hairy
  speed = 120;
  status = 1;
  return 1;
}
int beachballOff() {
  analogWrite(motorPin, 0);
  status = 0;
  speed = 0;
  return 1;
}
