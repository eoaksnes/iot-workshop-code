// For reference, see: http://www.makeuseof.com/tag/arduino-traffic-light-controller/
int red = 10;
int yellow = 9;
int green = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  // Set the initial state
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}

void loop() {
  changeToGreen();
  delay(5000);
  changeToRed();
}

void changeToRed() {
  // Green off, yellow on for three seconds
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  delay(3000);

  // Turn off yellow, then turn red on for five seconds
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
}

void changeToGreen() {
  // Red and yellow in for two seconds (red is already on though)
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  delay(2000);

  // Turn off red and yellow, then turn on green
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}

