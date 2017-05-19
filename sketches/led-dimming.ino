int LED = 5;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++)
  {
      delay(5);
      analogWrite(LED, i);
  }
    for (int i = 254; i >= 0; i--)
  {
      delay(5);
      analogWrite(LED, i);
  }
}