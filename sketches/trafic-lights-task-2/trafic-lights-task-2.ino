// For reference, see: http://www.makeuseof.com/tag/arduino-traffic-light-controller/
int button = 12;
int red = 10;
int yellow = 9;
int green = 8;
String state = "green";

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  assertState();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (pressed_button()) {
      changeState();
  }
  assertState();
}

bool pressed_button(void) {
  if (digitalRead(button) == HIGH) {
    delay(15);  // Software debounce
    if (digitalRead(button) == HIGH) {
      return true;
    }
  }
  return false;
}

void assertState() {
  if (state == "green") {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  } else if (state == "red") {
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }
}

void changeState() {
  if (state == "green") {
    changeToRed();
  }else if (state == "red") {
    changeToGreen();
  }
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

  state = "red";
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

  state = "green";
}

