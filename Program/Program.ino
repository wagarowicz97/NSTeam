//
//Program
//
// Made by Amanda Matelska && Dawid Łuczak && Bartosz Pikos
// License: MIT




//deklaracja bibliotek
#include <PortExpander_I2C.h>
#include <Wire.h>

//definicja pinow czujnika odleglosci
#define trigPin 12
#define echoPin 11

//definicja ekspanderów
PortExpander_I2C pe1(0x20);
PortExpander_I2C pe2(0x24);

//deklaracja zmienniej true / false: tryb 2
boolean zm = false;

//deklaracja trybów
int tryb = 1;

//deklaracja guzikow
int ztryb = 6; //zmiana trybu
int zswiatla = 7; //zmiana swiatel w trybie 2

//deklaracja diod
//swiatla 1
int czerwony1 = 0;
int pomaranczowu1 = 1;
int zielony1 = 2;

//swiatla 2
int czerwony2 = 3;
int pomaranczowu2 = 4;
int zielony2 = 5;

//swiatla 3
int czerwony3 = 0;
int pomaranczowu3 = 1;
int zielony3 = 2;

//swiatla 4
int czerwony4 = 3;
int pomaranczowu4 = 4;
int zielony4 = 5;

void setup() {
  //deklaracja czujnika1
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //deklaracja guzikow
  pinMode (INPUT, zswiatla);
  pinMode(INPUT, ztryb);

  //uruchomienie ekspanderow
  pe1.init();
  pe2.init();

  //swiatla 1
  pe1.pinMode(OUTPUT, czerwony1);
  pe1.pinMode(OUTPUT, pomaranczowu1);
  pe1.pinMode(OUTPUT, zielony1);

  //swiatla 2
  pe1.pinMode(OUTPUT, czerwony2);
  pe1.pinMode(OUTPUT, pomaranczowu2);
  pe1.pinMode(OUTPUT, zielony2);

  //swiatla 3
  pe2.pinMode(OUTPUT, czerwony3);
  pe2.pinMode(OUTPUT, pomaranczowu3);
  pe2.pinMode(OUTPUT, zielony3);

  //swiatla 4
  pe2.pinMode(OUTPUT, czerwony4);
  pe2.pinMode(OUTPUT, pomaranczowu4);
  pe2.pinMode(OUTPUT, zielony4);
}

//funkcja czujnika1
int zmierzOdleglosc() {
  long czas, dystans;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;

  return dystans;
}
//funkcja zamiany swiatel
void cz1() {
  pe1.digitalWrite(pomaranczowu1, HIGH);
  pe2.digitalWrite(pomaranczowu3, HIGH);
  delay(1000);
  pe2.digitalWrite(czerwony3, LOW);
  pe1. digitalWrite(czerwony1, LOW);
  pe1.digitalWrite(pomaranczowu1, LOW);
  pe2.digitalWrite(pomaranczowu3, LOW);
  pe2.digitalWrite(zielony3, HIGH);
  pe1.digitalWrite(zielony1, HIGH);
}

void zc1() {
  pe2.digitalWrite(zielony3, LOW);
  pe1.digitalWrite(zielony1, LOW);
  pe1.digitalWrite(pomaranczowu1, HIGH);
  pe2.digitalWrite(pomaranczowu3, HIGH);
  delay(1000);
  pe1.digitalWrite(pomaranczowu1, LOW);
  pe2.digitalWrite(pomaranczowu3, LOW);
  pe2.digitalWrite(czerwony3, HIGH);
  pe1. digitalWrite(czerwony1, HIGH);
}

void cz2() {
  pe1.digitalWrite(pomaranczowu2, HIGH);
  pe2.digitalWrite(pomaranczowu4, HIGH);
  delay(1000);
  pe2.digitalWrite(czerwony2, LOW);
  pe1. digitalWrite(czerwony4, LOW);
  pe1.digitalWrite(pomaranczowu2, LOW);
  pe2.digitalWrite(pomaranczowu4, LOW);
  pe2.digitalWrite(zielony2, HIGH);
  pe1.digitalWrite(zielony4, HIGH);
}
void zc2() {
  pe2.digitalWrite(zielony2, LOW);
  pe1.digitalWrite(zielony4, LOW);
  pe1.digitalWrite(pomaranczowu2, HIGH);
  pe2.digitalWrite(pomaranczowu4, HIGH);
  delay(1000);
  pe1.digitalWrite(pomaranczowu2, LOW);
  pe2.digitalWrite(pomaranczowu4, LOW);
  pe2.digitalWrite(czerwony2, HIGH);
  pe1. digitalWrite(czerwony4, HIGH);

}
//dodawanie do trybu (tryb++)
void trybplus() {

  if (digitalRead(ztryb) == HIGH) {
    delay(500);
    tryb++;
    Serial.println(tryb);
  }
  while (digitalRead(ztryb) == HIGH);
  if (tryb > 4) {
    tryb = 1;
  }
}

//tryb awaryjny
void awaryjne() {
  pe1.digitalWrite(zielony1, LOW);
  pe1.digitalWrite(zielony2, LOW);
  pe2.digitalWrite(zielony3, LOW);
  pe2.digitalWrite(zielony4, LOW);
  pe1.digitalWrite(czerwony1, LOW);
  pe1.digitalWrite(czerwony2, LOW);
  pe2.digitalWrite(czerwony3, LOW);
  pe2.digitalWrite(czerwony4, LOW);


  pe1.digitalWrite(pomaranczowu1, HIGH);
  pe1.digitalWrite(pomaranczowu2, HIGH);
  pe2.digitalWrite(pomaranczowu3, HIGH);
  pe2.digitalWrite(pomaranczowu4, HIGH);
  delay(1500);
  pe1.digitalWrite(pomaranczowu1, LOW);
  pe1.digitalWrite(pomaranczowu2, LOW);
  pe2.digitalWrite(pomaranczowu3, LOW);
  pe2.digitalWrite(pomaranczowu4, LOW);
  delay(1500);
}

void loop() {

  trybplus();
  if (tryb == 1) {
    trybplus();
    delay(2000);
    trybplus();
    zc2();
    trybplus();
    cz1();
    trybplus();
    delay(2000);
    trybplus();
    zc1();
    trybplus();
    cz2();
  } else  if (tryb == 2) {
    if (digitalRead(zswiatla) == HIGH) {
      delay(50);
      zm = !zm;
      if (zm == true) {
        zc2();
        cz1();
      } else {
        zc1();
        cz2();
      }
    }
  } else if (tryb == 3) {
    pe1.digitalWrite(zielony2, LOW);
    pe2.digitalWrite(zielony4, LOW);
    if (zmierzOdleglosc() < 30) {
      pe1.digitalWrite(pomaranczowu1, HIGH);
      pe2.digitalWrite(pomaranczowu3, HIGH);
      delay(1000);
      pe1.digitalWrite(czerwony1, LOW);
      pe2.digitalWrite(czerwony3, LOW);
      pe1.digitalWrite(pomaranczowu1, LOW);
      pe2.digitalWrite(pomaranczowu3, LOW);
      pe1.digitalWrite(zielony1, HIGH);
      pe2.digitalWrite(zielony3, HIGH);
      delay(5000);
      pe1.digitalWrite(zielony1, LOW);
      pe2.digitalWrite(zielony3, LOW);
      pe1.digitalWrite(pomaranczowu1, HIGH);
      pe2.digitalWrite(pomaranczowu3, HIGH);
      delay(1000);
      pe1.digitalWrite(pomaranczowu1, LOW);
      pe2.digitalWrite(pomaranczowu3, LOW);
    } else {
      pe1.digitalWrite(czerwony2, HIGH);
      pe2.digitalWrite(czerwony4, HIGH);
      pe1.digitalWrite(czerwony1, HIGH);
      pe2.digitalWrite(czerwony3, HIGH);
    }
  } else if (tryb == 4) {
    awaryjne();
  }

}
