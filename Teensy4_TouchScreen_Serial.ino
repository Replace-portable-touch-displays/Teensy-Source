//#define DEBUG

const int ledPin = 13;
void setup() {
  // put your setup code here, to run once:

#ifndef DEBUG
  TouchscreenUSB.begin();
#endif
  Serial4.begin(115200);
  pinMode(ledPin, OUTPUT);
#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop() {
    parseLoop();
}

void parseLoop() {
  static char head;
  static byte data[10];
  static int finger, isPressed;
  static uint32_t x, y;
  if (Serial4.available() >= 7)
  {
    // Update datas
    head = Serial4.read();
    for (int i = 0; i < 6; i++)
    {
      data[i] = Serial4.read();
    }
    finger = data[0];
    isPressed = data[1];
    x = (data[2] << 8) | data[3];
    y = (data[4] << 8) | data[5];

    // Handle datas

#ifdef DEBUG
    Serial.print("head ");
    Serial.println(head);
    Serial.println(finger);
    Serial.println(x);
    Serial.println(y);
#endif
    if (head != 'a') // flush when we get data loss
    {
      while (Serial4.available() > 0) {
        Serial4.read();
      }
    }

    if (finger > 9)
    { // over the 10 finger not supported
      return;
    }

    if (isPressed == 1)
    {

#ifndef DEBUG
      TouchscreenUSB.press(finger, x, y);
#endif
      digitalWrite(ledPin, HIGH);   // set the LED on
      delay(10);                  // wait for a second
      digitalWrite(ledPin, LOW);    // set the LED off
    }
    else
    {

#ifndef DEBUG
      TouchscreenUSB.release(finger);
#endif
    }
  }
}
