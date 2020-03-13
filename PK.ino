#define LED_PORT 13//лента
#define NUMB 45//датчик их 45 последний 44
#define Bright 255       // максимальная яркость (0 - 255)        
#include "FastLED.h"
CRGB leds[NUMB];//масив диодов

int numb = 44;
int timeStart = 175;

int in1 = 50;
void setup() {
  pinMode(A3, OUTPUT);
  Serial.begin(9600);


  LEDS.setBrightness(Bright); // яркость
  FastLED.addLeds<WS2812, LED_PORT, GRB>(leds, NUMB); // порт и масив диодов

  LEDS.showColor(CRGB(0, 0, 255));
  delay(timeStart);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(timeStart);
  LEDS.showColor(CRGB(255, 0, 0));
  delay(timeStart);
  LEDS.showColor(CRGB(0, 0, 0));

}

void loop() {
  unsigned long T = millis();
  Rand(( random(20, 100) * 1000), random(0, 100), random(0, 6));

}
void Rand(unsigned long T, int  TimeSpeed, int R) {
  //R = 5;
  Serial.print("\nНовый режим...");
  Serial.print("\n\tНа время: ");
  Serial.print(T / 1000);

  Serial.print("\n\tСо скоростью: ");
  Serial.print(TimeSpeed);

  Serial.print("\n\tНомер режима: ");
  Serial.print(R);



  T += millis();
  if (R == 0) {
    Serial.print("\n\tВыбран режим: R_Standart");
    R_Standart(T, TimeSpeed);

  }

  if (R == 1) {
    Serial.print("\n\tВыбран режим: R_Puls");
    R_Puls(T, TimeSpeed);
  }

  if (R == 2) {
    Serial.print("\n\tВыбран режим: R_Random");
    R_Random(T, TimeSpeed);
  }
  if (R == 3) {
    Serial.print("\n\tВыбран режим: R_Triger");
    R_Triger(T, TimeSpeed);
  }
  if (R == 4) {
    Serial.print("\n\tВыбран режим: R_Gladkiy");
    R_Gladkiy(T, TimeSpeed);
  }
  if (R == 5) {
    Serial.print("\n\tВыбран режим: R_Solo");
    R_Solo(T, TimeSpeed);
  }

  Serial.print("\nРежим закончился.");
  Serial.print("\n");
}


void R_Standart(unsigned long T, int TimeSpeed) {

  int lastR = 0, lastG = 0, lastB = 255;
  while (millis() <= T) {
    lastR = random(0, 3) * 85;
    lastG =  random(0, 3) * 85;
    lastB =  random(0, 3) * 85;
    for (int i = 0; i <= numb; i++) {
      LedCol(i, lastR, lastG, lastB);
      delay(110 - TimeSpeed);
    }
  }
}

void R_Random(unsigned long T, int TimeSpeed) {

  TimeSpeed = TimeSpeed - 80;
  int lastR = 0, lastG = 0, lastB = 255, i = 0;
  while (millis() <= T) {
    i = random(0, numb);
    lastR = random(0, 3) * 85;
    lastG =  random(0, 3) * 85;
    lastB =  random(0, 3) * 85;
    LedCol(i, lastR, lastG, lastB);
    delay(25 - TimeSpeed);
  }


}

void R_Triger(unsigned long T, int TimeSpeed) {
  T = T / 2;
  int lastR = 0, lastG = 0, lastB = 255, i = 0;
  while (millis() <= T) {
    lastR = random(0, 3) * 85;
    lastG =  random(0, 3) * 85;
    lastB =  random(0, 3) * 85;
    for (int i = 0; i <= numb; i++)
      LedCol(i, lastR, lastG, lastB);
    delay(180 - TimeSpeed);
  }


}
void R_Gladkiy(unsigned long T, int TimeSpeed) {

  TimeSpeed = (TimeSpeed / 15) * 3;
  int lastR = 0, lastG = 0, lastB = 0, i = 0;
  lastR = random(0, 3) * 85;
  lastG =  random(0, 3) * 85;
  lastB =  random(0, 3) * 85;
  int a = random(0, 3);
  //a=0;
  int b = 1;
  while (millis() <= T) {
    if (a == 0)
    {
      lastR = lastR + TimeSpeed * b;
    }
    if (a == 1)
    {
      lastG = lastG + TimeSpeed * b;
    }
    if (a == 2) {
      lastB = lastB + TimeSpeed * b;
    }

    if (lastR > 255 || lastG > 255 || lastB > 255) {
      b = b * (-1);
    }
    if (lastR < 0 || lastG < 0 || lastB < 0) {
      b = b * (-1);
    }
    for (int i = 0; i <= numb; i++)
      LedCol(i, lastR, lastG, lastB);
    delay(1);

  }


}
void R_Solo(unsigned long T, int TimeSpeed) {

  int lastR = 0, lastG = 0, lastB = 255, i = 0;
  lastR = random(0, 3) * 85;
  lastG =  random(0, 3) * 85;
  lastB =  random(0, 3) * 85;
  while (millis() <= T) {

    for (int i = 0; i <= numb; i++) {
      if (i == 0) {
        LedCol(i, 0, 0, lastB);
        LedCol(44, 0, lastG, 0);
        LedCol(43, lastR, 0, 0);
        LedCol(42, 0, 0, 0);

      }
      if (i == 1) {
        LedCol(i, 0, 0, lastB);
        LedCol(0, 0, lastG, 0);
        LedCol(44, lastR, 0, 0);
        LedCol(43, 0, 0, 0);

      }
      if (i == 2) {
        LedCol(i, 0, 0, lastB);
        LedCol(1, 0, lastG, 0);
        LedCol(0, lastR, 0, 0);
        LedCol(44, 0, 0, 0);

      }
      if (i >= 3) {
        LedCol(i, 0, 0, lastB);
        LedCol(i - 1, 0, lastG, 0);
        LedCol(i - 2, lastR, 0, 0);
        LedCol(i - 3, 0, 0, 0);
      }


      delay(110 - TimeSpeed);
    }
  }


}
void R_Puls(unsigned long T, int TimeSpeed) {

  //10 11 12 11
  int i = 16;
  int j = 15;
  int k = 44;

  bool r = true;
  bool l = true;

  int R = 255;
  int G = 0;
  int B = 0;

  while (millis() <= T) {
    ////////////
    LedCol(i, R, G, B);
    i++;
    //////////////
    if (j >= 0) {
      LedCol(j, R, G, B);
      j--;
    }
    else {
      LedCol(k, R, G, B);
      k--;
    }
    ///////////

    if (i == 38) {
      i = 16;
      j = 15;
      k = 44;
      R = random(0, 3) * 85;
      G = random(0, 3) * 85;
      B = random(0, 3) * 85;
    }
    delay(110 - TimeSpeed);
  }
}

void LedCol(int i, int r, int g, int b) {
  if (i < 0) i = 0;
  if (i > numb) i = numb;

  leds[i].r = Rgb(r);
  leds[i].g = Rgb(g);
  leds[i].b = Rgb(b);
  LEDS.show();
}

int Rgb(int i) {
  if (i < 0)i = 0;
  if (i > 255)i = 255;
  return   i;
}
