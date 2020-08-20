#include<TimerOne.h>
int latchPin = 12;
int clockPin = 13;
int dataPin = 11; 
int latchPin2 = 6;
int clockPin2 = 7;
int dataPin2 = 5;
int i = 0, j = 0, k = 0,cathode_decimal_value = 0, cathode_decimal_value2 = 0;
boolean durum = false;
int two_multiple = 1;
int anode_decimal[] = {1, 2, 4, 8, 16, 32, 64, 128};
int cathode_decimal[8];
int cathode_decimal2[8];
int text_to_display[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
int text_to_display2[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  for (j = 0; j < 8; j++)
  {
    for (i = 0; i < 8; i++) {
      if (text_to_display[i][j] == 0) {
        if (i > 0)
        {
          for (k = 0; k < i; k++)
          {
            two_multiple = two_multiple * 2;
          }
        }
        cathode_decimal_value = cathode_decimal_value + two_multiple;
        two_multiple = 1;
      }
    }
    cathode_decimal[j] = cathode_decimal_value;
    cathode_decimal_value = 0;

  }

  for (j = 0; j < 8; j++)
  {
    for (i = 0; i < 8; i++) {
      if (text_to_display2[i][j] == 0) {
        if (i > 0)
        {
          for (k = 0; k < i; k++)
          {
            two_multiple = two_multiple * 2;
          }
        }
        cathode_decimal_value2 = cathode_decimal_value2 + two_multiple;
        two_multiple = 1;
      }
    }
    cathode_decimal2[j] = cathode_decimal_value2;
    cathode_decimal_value2 = 0;
  }
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(screenUpdate);

}
void loop() {
  if (durum) {
      for (j = 0; j < 8; j++)
      {
        for (i = 0; i < 5; i++)
        {
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, anode_decimal[j]);
          digitalWrite(latchPin, HIGH);
          digitalWrite(latchPin2, LOW);
          shiftOut(dataPin2, clockPin2, MSBFIRST, cathode_decimal[j]);
          digitalWrite(latchPin2, HIGH);
        }
      }

    }
  else {
      for (j = 0; j < 8; j++)
      {
        for (i = 0; i < 5; i++)
        {
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, anode_decimal[j]);
          digitalWrite(latchPin, HIGH);
          digitalWrite(latchPin2, LOW);
          shiftOut(dataPin2, clockPin2, MSBFIRST, cathode_decimal2[j]);
          digitalWrite(latchPin2, HIGH);
        }
      }

    }
}

void screenUpdate() {
  durum = !durum;
}
