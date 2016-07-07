/*
Beachball Spinner Control
*/

// Music Note Definitions
#define  c     3830    // 261 Hz
#define  d     3400    // 294 Hz
#define  e     3038    // 329 Hz
#define  f     2864    // 349 Hz
#define  g     2550    // 392 Hz
#define  a     2272    // 440 Hz
#define  b     2028    // 493 Hz
#define  C     1912    // 523 Hz
// Define a special note, 'R', to represent a rest
#define  R     0
// DURATION OF THE NOTES
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

// Piezo Speaker is controlled by this PWM pin
int piezoPin = D2;

// Motor is controlled by this PWM pin
int motorPin = A4;

// Define a variable for beachball status off by default
int status = 0;

// Define a variable for beachball speed
int speed = 0;

// Define a variable if music is playing
int mstatus = 0;

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

int imperialMarch() {
    tone( piezoPin, g, Q );
    delay(500);
    tone( piezoPin, g, Q );
    delay(500);
    tone( piezoPin, g, Q );
    delay(500);
    tone( piezoPin, d, E+S);
    delay(500);
    tone( piezoPin, a, E+S );
    delay(500);
    tone( piezoPin, g, S );
    delay(500);
    tone( piezoPin, d, E+S );
    delay(500);
    tone( piezoPin, a, E+S );
    delay(500);
    tone( piezoPin, g, S );
}

// Play the imperial march once
int playMarch() {
    if ( mstatus != 1 ) {
        mstatus = 1;
        //imperialMarch();
    }
}

// Do this once on startup
void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

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
    // Play Music
    playMarch();
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
