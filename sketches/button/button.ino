int knapp = 2;
int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(knapp, INPUT);
}

void loop() {
  int knappVerdi = digitalRead(knapp);

  if (knappVerdi == HIGH) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}