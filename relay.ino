/*
This will control a Relay using the Monitor (Serial communication)
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
enum States
{
  CWTURN_STATE,
  CCWTURN_STATE,
  IDLE_STATE
};
int currentState;
typedef struct
{
  int pin;
  bool isActivated;
} signal;
signal signal1;
signal signal2;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  currentState = IDLE_STATE;

  signal1.pin = 4;
  pinMode(signal1.pin, OUTPUT);
  digitalWrite(signal1.pin, HIGH);
  signal1.isActivated = false;

  signal2.pin = 3;
  pinMode(signal2.pin, OUTPUT);
  digitalWrite(signal2.pin, HIGH);
  signal2.isActivated = false;

}

void loop() {
  // print the string when a newline arrives:
  switch (currentState) {
    case IDLE_STATE: {
      Serial.println("Idle");
      if (signal1.isActivated == true) {
        digitalWrite(signal1.pin, HIGH);
        signal1.isActivated = false;
      }
      if (signal2.isActivated == true) {
        digitalWrite(signal2.pin, HIGH);
        signal2.isActivated = false;
      }
      break;
    }
    case CWTURN_STATE: {
      Serial.println("CW Engaged");
      if (signal1.isActivated == false) {
        digitalWrite(signal1.pin, LOW);
        signal1.isActivated = true;
      }
      if (signal2.isActivated == true) {
        digitalWrite(signal2.pin, HIGH);
        signal2.isActivated = false;
      }
      break;
    }
    case CCWTURN_STATE: {
      Serial.println("CCW Engaged");
      if (signal1.isActivated == true) {
        digitalWrite(signal1.pin, HIGH);
        signal1.isActivated = false;
      }
      if (signal2.isActivated == false) {
        digitalWrite(signal2.pin, LOW);
        signal2.isActivated = true;
      }
      break;
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      Serial.println(inputString);
      if (inputString == "CW\n") {
        Serial.println("Activating Clockwise");
        currentState = CWTURN_STATE;
      }
      else if (inputString == "CCW\n") {
        Serial.println("Activating Counter-Clockwise");
        currentState = CCWTURN_STATE;
      }
      else {
        Serial.println("Unknown input");
        currentState = IDLE_STATE;
      }
      inputString = "";
    }
  }
}

