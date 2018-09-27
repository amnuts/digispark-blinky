#define STEPS 40
#define ADJUST 75

#define PIN_R 0
#define PIN_G 1
#define PIN_B 4

float sRGB[3];
float eRGB[3];

void setup()
{
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  randomSeed(seedOut(31));
  sRGB[0] = random(0, 255);
  sRGB[1] = random(0, 255);
  sRGB[2] = random(0, 255);
  float p = (float)ADJUST/100;
  eRGB[0] = max(0, min(255, sRGB[0] - (sRGB[0] * p)));
  eRGB[1] = max(0, min(255, sRGB[1] - (sRGB[1] * p)));
  eRGB[2] = max(0, min(255, sRGB[2] - (sRGB[2] * p)));
  on();
}

void loop()
{
  on();
  delay(random(100, 5000));
  if (random(0, 10000) < 3000) {
    fader();
  } else if (random(0, 10000) > 8000) {
    blinker();
  } else if (random(0, 10000) > 9500) {
    blinker();
    delay(350);
    blinker();
  }
}

void fader()
{
  int s = 0;
  while (s++ < STEPS) {
    analogWrite(PIN_R, sRGB[0] + (s * (eRGB[0] - sRGB[0]) / STEPS));
    analogWrite(PIN_G, sRGB[1] + (s * (eRGB[1] - sRGB[1]) / STEPS));
    analogWrite(PIN_B, sRGB[2] + (s * (eRGB[2] - sRGB[2]) / STEPS));
    delay(30);
  }
  while (s--) {
    analogWrite(PIN_R, sRGB[0] + (s * (eRGB[0] - sRGB[0]) / STEPS));
    analogWrite(PIN_G, sRGB[1] + (s * (eRGB[1] - sRGB[1]) / STEPS));
    analogWrite(PIN_B, sRGB[2] + (s * (eRGB[2] - sRGB[2]) / STEPS));
    delay(30);
  }
}

void blinker()
{
  off();
  delay(150);
  on();
}

void on()
{
  analogWrite(PIN_R, sRGB[0]);
  analogWrite(PIN_G, sRGB[1]);
  analogWrite(PIN_B, sRGB[2]);
}

void off() {
  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);
}

unsigned long seedOut(unsigned int noOfBits)
{
  unsigned long seed = 0, limit = 99;
  int bit0 = 0, bit1 = 0;
  while (noOfBits--) {
    for (int i = 0; i < limit; ++i) {
      bit0 = analogRead(0)&1;
      bit1 = analogRead(0)&1;
      if (bit1 != bit0) {
        break;
      }
    }
    seed = (seed << 1) | bit1;
  }
  return seed;
}
