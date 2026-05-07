#include "Adafruit_PCF8574.h"
#include "LayoutSigns.h"

#define S3 22
#define S4 19
#define S5 18
#define S8 23
#define S11 28
#define S12 29
#define S13 30
#define S14 31
#define S9_2 24
#define S9_1 25
#define S10_2 26
#define S10_1 27
 

#define SV1 40
#define SV2 39 
#define SV3 38
#define SV4 37
#define SV5 36
#define SV6 35
#define SV7 34
#define SV8 33
#define SV9 32

#define SV10 41
#define SV11 42
#define SV12 43
#define SV13 44
#define SV14 45
#define SV15 46
#define SV16 47
#define SV17 48
#define SV18 49
#define SV19 50
#define SV20 51
#define SV21 52
#define SV22 53
#define SV23 54

#define W5 55
#define W7_9 56
#define W1_3 57
#define W11 58
#define W13 59
#define W15 60
#define W2_4 61
#define W6 62
#define W8_10 63
#define W14 64
#define W12 65
#define W16 66
#define W18 67
#define W20 68

// Константы времени выдержки смены сигнала
#define YEL_TIME 22*1000 // миллисек
#define GR_TIME 44*1000 // миллисек

uint64_t timer_N1 = 0;
uint64_t timer_N2 = 0;
uint64_t timer_C1 = 0;
uint64_t timer_C2 = 0;

short ws1_flag = 0;
bool stC = false;
bool stN = false;

Adafruit_PCF8574 pcf1;
Adafruit_PCF8574 pcf2;
Adafruit_PCF8574 pcf3;
Adafruit_PCF8574 pcf4;
Adafruit_PCF8574 pcf5;
Adafruit_PCF8574 pcf6;
Adafruit_PCF8574 pcf7;
Adafruit_PCF8574 pcf8;

// Module A (90)
Svetofor svet_N;
Svetofor svet_ND;
Svetofor svet_M1;
Svetofor svet_M3;
Svetofor svet_C8;

// Module B (91)
Svetofor svet_C6;
Svetofor svet_C4;
Svetofor svet_CII;
Svetofor svet_CI;
Svetofor svet_C3;

// Module D (93)
Svetofor svet_N6;
Svetofor svet_N4;
Svetofor svet_NII;
Svetofor svet_NI;
Svetofor svet_N3;
Svetofor svet_N5;

// Module E (94)
Svetofor svet_C;
Svetofor svet_CD;
Svetofor svet_M2;
Svetofor svet_M4;
Svetofor svet_M6;
Svetofor svet_M8;

uint8_t getS7(){
  return pcf5.digitalRead(5);
}
uint8_t getS6(){
  return pcf5.digitalRead(4);
}
void setup() {
  setup_ard_pins();
  setup_pcfs();
  setup_svets();
  
  svet_N.set_pcf_pin(0, &pcf1, 0);
  svet_N.set_pcf_pin(1, &pcf1, 1);
  svet_N.set_pcf_pin(2, &pcf1, 2);

  svet_C8.set_pcf_pin(0, &pcf2, 2);
  svet_C8.set_pcf_pin(1, &pcf2, 3);
  svet_C8.set_pcf_pin(2, &pcf2, 4);
  svet_C8.set_pcf_pin(4, &pcf2, 5);

  Serial.begin(9600);
}
void svets_work(){
  svet_N.work(); svet_ND.work(); svet_M1.work(); svet_M3.work(); svet_C8.work();
  svet_C6.work(); svet_C4.work(); svet_CII.work(); svet_CI.work(); svet_C3.work();
  svet_N6.work(); svet_N4.work(); svet_NII.work(); svet_NI.work(); svet_N3.work(); svet_N5.work();
  svet_C.work(); svet_CD.work(); svet_M2.work(); svet_M4.work(); svet_M6.work(); svet_M8.work();
}
void setup_ard_pins(){
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  pinMode(19, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

  pinMode(W1_3, INPUT);
}
void setup_pcfs(){
  // Setup PCFs objects
  pcf1.begin(0x20, &Wire);
  pcf2.begin(0x21, &Wire);
  pcf3.begin(0x22, &Wire);
  pcf4.begin(0x23, &Wire);
  pcf5.begin(0x24, &Wire);
  pcf6.begin(0x25, &Wire);
  pcf7.begin(0x26, &Wire);
  pcf8.begin(0x27, &Wire);

  // Setup PCFs pin modes
  pcf1.pinMode(0, OUTPUT);
  pcf1.pinMode(1, OUTPUT);
  pcf1.pinMode(2, OUTPUT);
  pcf1.pinMode(3, OUTPUT);
  pcf1.pinMode(4, OUTPUT);
  pcf1.pinMode(5, OUTPUT);
  pcf1.pinMode(6, OUTPUT);
  pcf1.pinMode(7, OUTPUT);

  pcf2.pinMode(0, OUTPUT);
  pcf2.pinMode(1, OUTPUT);
  pcf2.pinMode(2, OUTPUT);
  pcf2.pinMode(3, OUTPUT);
  pcf2.pinMode(4, OUTPUT);
  pcf2.pinMode(5, OUTPUT);
  pcf2.pinMode(6, OUTPUT);
  pcf2.pinMode(7, OUTPUT);

  pcf3.pinMode(0, OUTPUT);
  pcf3.pinMode(1, OUTPUT);
  pcf3.pinMode(2, OUTPUT);
  pcf3.pinMode(3, OUTPUT);
  pcf3.pinMode(4, OUTPUT);
  pcf3.pinMode(5, OUTPUT);
  pcf3.pinMode(6, OUTPUT);
  pcf3.pinMode(7, OUTPUT);

  pcf4.pinMode(0, OUTPUT);
  pcf4.pinMode(1, OUTPUT);
  pcf4.pinMode(2, OUTPUT);
  pcf4.pinMode(3, OUTPUT);
  pcf4.pinMode(4, OUTPUT);
  pcf4.pinMode(5, OUTPUT);
  pcf4.pinMode(6, OUTPUT);
  pcf4.pinMode(7, OUTPUT);

  pcf5.pinMode(0, OUTPUT);
  pcf5.pinMode(1, OUTPUT);
  pcf5.pinMode(2, OUTPUT);
  pcf5.pinMode(3, OUTPUT);
  pcf5.pinMode(4, INPUT);
  pcf5.pinMode(5, INPUT);
  pcf5.pinMode(6, OUTPUT);
  pcf5.pinMode(7, OUTPUT);

  pcf6.pinMode(0, OUTPUT);
  pcf6.pinMode(1, OUTPUT);
  pcf6.pinMode(2, OUTPUT);
  pcf6.pinMode(3, OUTPUT);
  pcf6.pinMode(4, OUTPUT);
  pcf6.pinMode(5, OUTPUT);
  pcf6.pinMode(6, OUTPUT);
  pcf6.pinMode(7, OUTPUT);

  pcf7.pinMode(0, OUTPUT);
  pcf7.pinMode(1, OUTPUT);
  pcf7.pinMode(2, OUTPUT);
  pcf7.pinMode(3, OUTPUT);
  pcf7.pinMode(4, OUTPUT);
  pcf7.pinMode(5, OUTPUT);
  pcf7.pinMode(6, OUTPUT);
  pcf7.pinMode(7, OUTPUT);

  pcf8.pinMode(0, OUTPUT);
  pcf8.pinMode(1, OUTPUT);
  pcf8.pinMode(2, OUTPUT);
  pcf8.pinMode(3, OUTPUT);
  pcf8.pinMode(4, OUTPUT);
  pcf8.pinMode(5, OUTPUT);
  pcf8.pinMode(6, OUTPUT);
  pcf8.pinMode(7, OUTPUT);
}
void setup_svets(){
  // Module A (90)
  svet_N = Svetofor(true);
  svet_ND = Svetofor(true);
  svet_M1 = Svetofor(true);
  svet_M3 = Svetofor(true);
  svet_C8 = Svetofor(true);
  
  svet_N.set_pcf_pin(0, &pcf1, 0);
  svet_N.set_pcf_pin(1, &pcf1, 1);
  svet_N.set_pcf_pin(2, &pcf1, 2);
  svet_N.set_pcf_pin(3, &pcf1, 3);
  svet_N.set_pcf_pin(4, &pcf1, 4);

  svet_ND.set_pcf_pin(0, &pcf1, 5);
  svet_ND.set_pcf_pin(1, &pcf1, 6);
  svet_ND.set_pcf_pin(2, &pcf1, 7);

  svet_M1.set_pcf_pin(0, &pcf2, 0);
  svet_M1.set_pcf_pin(1, &pcf2, 1);

  svet_C8.set_pcf_pin(0, &pcf2, 2);
  svet_C8.set_pcf_pin(1, &pcf2, 3);
  svet_C8.set_pcf_pin(2, &pcf2, 4);
  svet_C8.set_pcf_pin(3, &pcf2, 5);

  svet_M3.set_pcf_pin(0, &pcf2, 6);
  svet_M3.set_pcf_pin(1, &pcf2, 7);
  
  // Module B (91)
  svet_C6 = Svetofor(true);
  svet_C4 = Svetofor(true);
  svet_CII = Svetofor(true);
  svet_CI = Svetofor(true);
  svet_C3 = Svetofor(true);

  svet_C6.set_pcf_pin(0, &pcf5, 0);
  svet_C6.set_pcf_pin(1, &pcf5, 1);
  svet_C6.set_pcf_pin(2, &pcf5, 2);
  svet_C6.set_pcf_pin(3, &pcf5, 3);

  svet_C6.set_pcf_pin(0, &pcf4, 4);
  svet_C6.set_pcf_pin(1, &pcf4, 5);
  svet_C6.set_pcf_pin(2, &pcf4, 6);
  svet_C6.set_pcf_pin(3, &pcf4, 7);

  svet_CI.set_pcf_pin(0, &pcf3, 0);
  svet_CI.set_pcf_pin(1, &pcf3, 1);
  svet_CI.set_pcf_pin(2, &pcf3, 2);
  svet_CI.set_pcf_pin(3, &pcf3, 3);

  svet_CII.set_pcf_pin(0, &pcf3, 4);
  svet_CII.set_pcf_pin(1, &pcf3, 5);
  svet_CII.set_pcf_pin(2, &pcf3, 6);
  svet_CII.set_pcf_pin(3, &pcf3, 7);

  svet_C4.set_pcf_pin(0, &pcf4, 4);
  svet_C4.set_pcf_pin(1, &pcf4, 5);
  svet_C4.set_pcf_pin(2, &pcf4, 6);
  svet_C4.set_pcf_pin(3, &pcf4, 7);
  
  // Module D (93)
  svet_N6 = Svetofor();
  svet_N4 = Svetofor();
  svet_NII = Svetofor();
  svet_NI = Svetofor();
  svet_N3 = Svetofor(true);
  svet_N5 = Svetofor(true);

  svet_N6.set_ard_pin(0, 2);
  svet_N6.set_ard_pin(1, 3);
  svet_N6.set_ard_pin(2, 4);
  svet_N6.set_ard_pin(3, 5);

  svet_N4.set_ard_pin(0, 6);
  svet_N4.set_ard_pin(1, 7);
  svet_N4.set_ard_pin(2, 8);
  svet_N4.set_ard_pin(3, 9);

  svet_NII.set_ard_pin(0, 10);
  svet_NII.set_ard_pin(1, 11);
  svet_NII.set_ard_pin(2, 12);
  svet_NII.set_ard_pin(3, 13);

  svet_NI.set_ard_pin(0, 14);
  svet_NI.set_ard_pin(1, 15);
  svet_NI.set_ard_pin(2, 16);
  svet_NI.set_ard_pin(3, 17);
  
  svet_N5.set_pcf_pin(0, &pcf8, 0);
  svet_N5.set_pcf_pin(1, &pcf8, 1);
  svet_N5.set_pcf_pin(2, &pcf8, 2);
  svet_N5.set_pcf_pin(3, &pcf8, 3);
  
  svet_N3.set_pcf_pin(0, &pcf8, 4);
  svet_N3.set_pcf_pin(1, &pcf8, 5);
  svet_N3.set_pcf_pin(2, &pcf8, 6);
  svet_N3.set_pcf_pin(3, &pcf8, 7);
  
  // Module E (94)
  svet_C = Svetofor(true);
  svet_CD = Svetofor(true);
  svet_M2 = Svetofor(true);
  svet_M4 = Svetofor(true);
  svet_M6 = Svetofor(true);
  svet_M8 = Svetofor(true);

  svet_C.set_pcf_pin(0, &pcf6, 0);
  svet_C.set_pcf_pin(1, &pcf6, 1);
  svet_C.set_pcf_pin(2, &pcf6, 2);
  svet_C.set_pcf_pin(3, &pcf6, 3);
  svet_C.set_pcf_pin(4, &pcf6, 4);

  svet_CD.set_pcf_pin(0, &pcf6, 5);
  svet_CD.set_pcf_pin(1, &pcf6, 6);
  svet_CD.set_pcf_pin(2, &pcf6, 7);
  
  svet_M2.set_pcf_pin(0, &pcf7, 0);
  svet_M2.set_pcf_pin(1, &pcf7, 1);

  svet_M4.set_pcf_pin(0, &pcf7, 2);
  svet_M4.set_pcf_pin(1, &pcf7, 3);

  svet_M6.set_pcf_pin(0, &pcf7, 4);
  svet_M6.set_pcf_pin(1, &pcf7, 5);

  svet_M8.set_pcf_pin(0, &pcf7, 6);
  svet_M8.set_pcf_pin(1, &pcf7, 7);
  
}
void loop() {
  // ============== Светофор Н ==============
  if (digitalRead(S3) == 1 && digitalRead(S4) == 0 && digitalRead(S10_1) == 0 && digitalRead(S8) == 0){
    if (digitalRead(SV2) == 1 && digitalRead(SV4) == 1 && digitalRead(SV8) == 1){
      if (digitalRead(W1_3) == 1 && digitalRead(W7_9) == 1 && digitalRead(W15) == 1){
        if (svet_NI.is_light(0) || svet_NI.is_light(1)){
          // Зеленый
          svet_N.get_default();
          svet_N.set(1, LOW);
        }
        else if (svet_NI.is_light(2)){
          // Желтый
          svet_N.get_default();
          svet_N.blink_on(3);
        }
        else if (svet_NI.is_light(3) && svet_NI.is_blink(0)){
          // Желтый мигающий
          svet_N.get_default();
          svet_N.blink_on(0);
        }
        else{
          // Красный
          svet_N.get_default();
          svet_N.set(2, LOW);
        }
      }
    }
  }
  else if (digitalRead(S3) == 1 && digitalRead(S4) == 0){
    // Желтый, желтый мигающий
    if (digitalRead(S10_1) == 0 && digitalRead(S8) && digitalRead(SV2) == 1 
    && digitalRead(SV4) == 1 && digitalRead(SV9) == 1
    && digitalRead(W1_3) == 1 && digitalRead(W7_9) == 1 && digitalRead(W15) == 0
    && (svet_N3.is_light(1) || svet_N3.is_light(0) || (svet_N3.is_light(3) && svet_N3.is_blink(0)))){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.blink_on(0);
    }
    else if (digitalRead(S9_1) == 0 && digitalRead(S8) == 0 && digitalRead(SV2) == 1
    && digitalRead(SV3) == 1 && digitalRead(SV7) == 1
    && digitalRead(W1_3) == 1 && digitalRead(W7_9) == 0 && digitalRead(W11) == 1
    && svet_NII.is_light(1) || svet_NII.is_light(0) || (svet_NII.is_light(3) && svet_NII.is_blink(0))){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.blink_on(0);
    }
    else if (digitalRead(W1_3) == 1 && digitalRead(W7_9) == 0 && digitalRead(W11) == 0
    && digitalRead(W13) == 1
    && digitalRead(S9_1) == 0 && digitalRead(S8) == 0
    && digitalRead(SV2) == 1 && digitalRead(SV3) == 1 && digitalRead(SV6) == 1
    && (svet_N4.is_light(0) || svet_N4.is_light(1) || (svet_N4.is_light(2) && svet_N4.is_blink(1)))){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.blink_on(0);
    }
    else if (digitalRead(W1_3) == 1 && digitalRead(W7_9) == 0 && digitalRead(W11) == 0
    && digitalRead(W13) == 0 && digitalRead(S9_1) == 0 && digitalRead(S8) == 0 
    && digitalRead(SV2) == 1 && digitalRead(SV3) == 1 && digitalRead(SV5) == 1
    && (svet_N6.is_light(0) || svet_N6.is_light(1) || (svet_N6.is_light(2) && svet_N6.is_blink(1)))){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.blink_on(0);
    }
    else{
      // Красный
      svet_N.get_default();
      svet_N.set(2, LOW);
    }
  }
  else if (digitalRead(W1_3) == 1 && digitalRead(S4) == 0 && digitalRead(S8) == 0 && digitalRead(SV2) == 1
  && digitalRead(S3) == 1){
    // Два желтых
    if (digitalRead(W7_9) == 1 && digitalRead(W15) == 0 && svet_N3.is_light(2) && digitalRead(S10_1) == 0
    && digitalRead(SV4) == 1 && digitalRead(SV9) == 1){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.set(0, LOW);
    }
    if (digitalRead(W7_9) == 0 && digitalRead(W11) == 1 && svet_NII.is_light(2)
    && digitalRead(S9_1) == 0 && digitalRead(SV3) == 1 && digitalRead(SV7) == 1){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.set(0, LOW);
    }
    if (digitalRead(W7_9) == 0 && digitalRead(W11) == 0 && digitalRead(W13) == 1 && svet_N4.is_light(3)
    && digitalRead(S9_1) == 0 && digitalRead(SV3) == 1 && digitalRead(SV6) == 1){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.set(0, LOW);
    }
    if (digitalRead(W7_9) == 0 && digitalRead(W11) == 0 && digitalRead(W13) == 0 && svet_N6.is_light(3)
    && digitalRead(S9_1) == 0 && digitalRead(SV3) == 1 && digitalRead(SV5) == 1){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.set(0, LOW);
    }
    if (digitalRead(S4) == 1){
      svet_N.get_default();
      svet_N.set(2, LOW);
      svet_N.blink_on(4);
    }
    else{
      // Красный
      svet_N.get_default();
      svet_N.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_N.get_default();
    svet_N.set(2, LOW);
  }
  Serial.println("=============");
  // ============== Светофор Н ==============

  // ============== Светофор Ч ==============
  if (digitalRead(W2_4) == 1 && digitalRead(S5) == 1 && digitalRead(S13) == 1
  && digitalRead(SV21) == 1 && digitalRead(SV22) == 1 && digitalRead(S6) == 1){
    if (digitalRead(W8_10) == 1 && digitalRead(W12) == 1 && digitalRead(SV12) == 1
    && digitalRead(SV16) == 1 && digitalRead(S9_2) == 0){
      if (svet_CII.is_light(1) || svet_CII.is_light(0)){
        // Зеленый
        svet_C.get_default();
        svet_C.set(1, LOW);
      }
      else if (svet_CII.is_light(2)){
        // Желтый
        svet_N.get_default();
        svet_N.blink_on(3);
      }
      else if ((svet_CII.is_light(0) && svet_CII.is_light(3))){
        // Желтый мигающий
        svet_C.get_default();
        svet_C.blink_on(0);
      }
      else{
        svet_C.get_default();
        svet_C.set(2, LOW);
      }
    }
    else{
      svet_C.get_default();
      svet_C.set(2, LOW);
    }
  }
  else if (digitalRead(S9_2) == 0 && digitalRead(SV10) == 1 && digitalRead(SV15) == 1
  && digitalRead(SV16) == 1){
    if ((svet_C6.is_light(1) || svet_C6.is_light(2) || (svet_C6.is_light(0) && svet_C6.is_light(3))) && digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 0){
      // Желтый, желтый мигающий
      svet_C.get_default();
      svet_C.blink_on(0);
      svet_C.set(3, LOW);
    }
    else{
      // Красный
      svet_C.get_default();
      svet_C.set(2, LOW);
    }
  }
  else if(digitalRead(W8_10) == 1 && digitalRead(W12) == 1 && digitalRead(W14) == 1
  && digitalRead(S9_2) == 0 && digitalRead(SV11) == 1 && digitalRead(SV16) == 1){
    if (svet_C4.is_light(1) || svet_C4.is_light(0)
    || (svet_C4.is_light(0) && svet_C4.is_light(3))){
      // Желтый, желтый мигающий
      svet_C.get_default();
      svet_C.blink_on(0);
      svet_C.set(3, LOW);
    }
    else{
      // Красный
      svet_C.get_default();
      svet_C.set(2, LOW);
    }
  }
  else if(digitalRead(SV13) == 1 && digitalRead(SV13) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1
  && digitalRead(S10_2) == 0 && digitalRead(W16) == 1 && digitalRead(W8_10) == 0){
    if (svet_CII.is_light(1) || svet_CII.is_light(0)
    || (svet_CII.is_light(0) && svet_CII.is_light(3))){
      // Желтый, желтый мигающий
      svet_C.get_default();
      svet_C.blink_on(0);
      svet_C.set(3, LOW);
    }
    else{
      // Красный
      svet_C.get_default();
      svet_C.set(2, LOW);
    }
  }
  else if(digitalRead(S10_2) == 0 && digitalRead(SV14) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1
  && digitalRead(W16) == 1 && digitalRead(W8_10) == 0){
    if (svet_C3.is_light(1) || svet_C3.is_light(0)
    || (svet_C3.is_light(0) && svet_C3.is_light(3))){
      // Желтый, желтый мигающий
      svet_C.get_default();
      svet_C.blink_on(0);
      svet_C.set(3, LOW);
    }
    else{
      // Красный
      svet_C.get_default();
      svet_C.set(2, LOW);
    }
  }
  else if (digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 0
  && digitalRead(S9_2) == 0 && digitalRead(SV10) == 1 && digitalRead(SV15) == 1 && digitalRead(SV16) == 1
  && svet_C6.is_light(2)){
    svet_C.get_default();
    svet_C.set(0, LOW);
    svet_C.set(3, LOW);
  }
  else if (digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 1
  && digitalRead(S9_2) == 0 && digitalRead(SV11) == 1 && digitalRead(SV15) == 1 && digitalRead(SV16) == 1
  && svet_C4.is_light(2)){
    svet_C.get_default();
    svet_C.set(0, LOW);
    svet_C.set(3, LOW);
  }
  else if (digitalRead(W8_10) == 0 && digitalRead(W16) == 1  && svet_CI.is_light(2)
  && digitalRead(S10_2) == 0 && digitalRead(S17) == 1 && digitalRead(S19) == 1 && digitalRead(SV13) == 1){
    svet_C.get_default();
    svet_C.set(0, LOW);
    svet_C.set(3, LOW);
  }
  else if (digitalRead(W8_10) == 0 && digitalRead(W16) == 0  && svet_C3.is_light(2)
  && digitalRead(S10_2) == 0 && digitalRead(S17) == 1 && digitalRead(S19) == 1 && digitalRead(SV14) == 1){
    svet_C.get_default();
    svet_C.set(0, LOW);
    svet_C.set(3, LOW);
  }
  else if(digitalRead(S5) == 1){
    svet_C.get_default();
    svet_C.set(2, LOW);
    svet_C.blink_on(4);
  }
  else{
    // Красный
    svet_C.get_default();
    svet_C.set(2, LOW);
  }
  // ============== Светофор Ч ==============

  // ============== Светофор НД ==============
  if ((digitalRead(W1_3) == 0 && digitalRead(W7_9) == 1 && digitalRead(W15) == 0
  && digitalRead(S10_1) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
  && digitalRead(SV2) == 1 && digitalRead(SV9) == 1) ||
  (digitalRead(W1_3) == 0 && digitalRead(W7_9) == 1 && digitalRead(W15) == 1
  && digitalRead(S10_1) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
  && digitalRead(SV2) == 1 && digitalRead(SV8) == 1) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 1
  && digitalRead(S9_1) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1) && digitalRead(SV3) == 1
  && digitalRead(SV7) == 1)) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 0
  && digitalRead(W13) == 1 && digitalRead(S9_1) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
  && digitalRead(SV3) == 1 && digitalRead(SV6) == 1) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 0
  && digitalRead(W13) == 0 && digitalRead(S9_1) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
  && digitalRead(SV3) == 1 && digitalRead(SV5) == 1) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 0 && && digitalRead(S9_1) == 0 && digitalRead(S7) == 0
  && digitalRead(SV1) == 1)){
    svet_ND.get_default();
    svet_ND.set(0, LOW);
    svet_ND.set(2, LOW);
  }
  else{
    // Красный
    svet_ND.get_default();
    svet_ND.set(1, LOW);
  }
  // ============== Светофор НД ==============

  // ============== Светофор ЧД ==============
  if (digitalRead(S12) == 0 && digitalRead(SV23) == 1){
    if (digitalRead(SV20) == 1 && digitalRead(S10_2) == 0){
      if ((digitalRead(W2_4) == 1 && digitalRead(W6) == 0 && digitalRead(W18) == 1
      && digitalRead(SV18) == 1) ||
      (digitalRead(W2_4) == 1 && digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(W16) == 0
      && digitalRead(SV14) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1) ||
      (digitalRead(W2_4) == 1 && digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(W16) == 1
      && digitalRead(SV13) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1)){
        svet_CD.get_default();
        svet_CD.set(0, LOW);
        svet_CD.set(2, LOW);
      }
      else{
        // Красный
        svet_CD.get_default();
        svet_CD.set(1, LOW);
      }
    }
    else if (digitalRead(SV22) == 1 && digitalRead(S9_2) == 0 digitalRead(SV21) == 1
    && digitalRead(SV16) == 1 && digitalRead(W2_4) == 0 && digitalRead(W8_10) == 1){
      if ((digitalRead(W12) == 1 && digitalRead(SV13) == 1)) ||
      (digitalRead(W12) == 0 && digitalRead(W14) == 1 && digitalRead(SV11) == 1 && digitalRead(SV15) == 1) ||
      (digitalRead(W12) == 0 && digitalRead(W14) == 0 && digitalRead(SV10) == 1 && digitalRead(SV15) == 1)){
        svet_CD.get_default();
        svet_CD.set(0, LOW);
        svet_CD.set(2, LOW);
      }
      else{
        // Красный
        svet_CD.get_default();
        svet_CD.set(1, LOW);
      }
    }
    else{
      // Красный
      svet_CD.get_default();
      svet_CD.set(1, LOW);
    }
  }
  else{
    // Красный
    svet_CD.get_default();
    svet_CD.set(1, LOW);
  }
  // ============== Светофор ЧД ==============

  // ============== Светофор ЧII==============
  if (digitalRead(SV7) == 1 && digitalRead(SV3) == 1 && digitalRead(S9_1) == 1
  && digitalRead(W11) == 1 && digitalRead(W1_3) == 1){
    if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(SV1) == 1
    && digitalRead(S7) == 0 && timer_N2 >= YEL_TIME){
      // Желтый
      svet_CII.get_default();
      svet_CII.set(1, LOW);
    }
    else if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(SV1) == 1
    && digitalRead(S7) == 0 && timer_N2 >= GR_TIME){
      // Зеленый
      svet_CII.get_default();
      svet_CII.set(1, LOW);
    }
    else if (digitalRead(W7_9) == 0 && digitalRead(W7_9) == 0 && digitalRead(SV2) == 1
    && digitalRead(S8) == 0  && timer_N1 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_CII.get_default();
      svet_CII.set(0, LOW);
      svet_CII.blink_on(3);
    }
    else{
      // Красный
      svet_CII.get_default();
      svet_CII.set(2, LOW);
    }
  }
  else{
      // Красный
      svet_CII.get_default();
      svet_CII.set(2, LOW);
  }
  // ============== Светофор ЧII ==============

  // ============== Светофор ЧI ==============
  if (digitalRead(W15) == 1 && digitalRead(W7_9) == 1 && digitalRead(S10_1) == 1
  && digitalRead(SV2) == 1 && digitalRead(SV4) == 1 && digitalRead(SV8) == 1){
    if (digitalRead(W1_3) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
    && timer_N2 >= YEL_TIME){
      // Желтый
      svet_CI.get_default();
      svet_CI.set(0, LOW);
    }
    else if (digitalRead(W1_3) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
    && timer_N2 >= GR_TIME){
      // Зеленый
      svet_CI.get_default();
      svet_CI.set(1, LOW);
    }
    else if (digitalRead(W1_3) == 1 && digitalRead(S8) == 0
    && timer_N1 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_CI.get_default();
      svet_CI.set(0, LOW);
      svet_CI.blink_on(3);
    }
    else{
      // Красный
      svet_CI.get_default();
      svet_CI.set(2, LOW);
    }
  }
  else{
      // Красный
      svet_CI.get_default();
      svet_CI.set(2, LOW);
  }
  // ============== Светофор ЧI ==============

  // ============== Светофор Ч3 ==============
  if (digitalRead(W7_9) == 1 && digitalRead(W15) == 1 && digitalRead(S10_1) == 1
  && digitalRead(SV2) == 1 && digitalRead(SV4) == 1 && digitalRead(SV9) == 1){
    if (digitalRead(W1_3) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
    && timer_N2 >= YEL_TIME){
      // Желтый
      svet_C3.get_default();
      svet_C3.set(0, LOW);
    }
    else if (digitalRead(W1_3) == 0 && digitalRead(S7) == 0 && digitalRead(SV1) == 1
    && timer_N2 >= GR_TIME){
      // Зеленый
      svet_C3.get_default();
      svet_C3.set(1, LOW);
    }
    else if (digitalRead(W1_3) == 1 && digitalRead(S8) == 0 && timer_N1 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_C3.get_default();
      svet_C3.set(0, LOW);
      svet_C3.blink_on(3);
    }
    else{
      // Красный
      svet_C3.get_default();
      svet_C3.set(2, LOW);
    }
  }
  else{
      // Красный
      svet_C3.get_default();
      svet_C3.set(2, LOW);
  }
  // ============== Светофор Ч3 ==============

  // ============== Светофор Н6 ==============
  if (digitalRead(W8_10) == 1 && digitalRead(W12) == 0  && digitalRead(W14) == 0
  && digitalRead(S9_2) == 1 && digitalRead(SV10) == 1 && digitalRead(SV15) == 1
  && digitalRead(SV16) == 1 && digitalRead(SV21) == 1 && digitalRead(SV22) == 1){
    if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= YEL_TIME){
      // Желтый
      svet_N6.get_default();
      svet_N6.set(1, LOW);
    }
    else if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= GR_TIME){
      // Зеленый
      svet_N6.get_default();
      svet_N6.set(0, LOW);
    }
    else if (digitalRead(W2_4) == 1 && digitalRead(S13) == 0 && timer_C2 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_N6.get_default();
      svet_N6.set(2, LOW);
      svet_N6.blink_on(1);
    }
    else{
      // Красный
      svet_N6.get_default();
      svet_N6.set(3, LOW);
    }
  }
  else{
    // Красный
    svet_N6.get_default();
    svet_N6.set(3, LOW);
  }
  // ============== Светофор Н6 ==============

  // ============== Светофор Н4 ==============
  if (digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 1
  && digitalRead(S9_2) == 1 && digitalRead(SV11) == 1 && digitalRead(SV15) == 1
  && digitalRead(SV16) == 1 && digitalRead(SV21) == 1 && digitalRead(SV22) == 1){
    if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= YEL_TIME){
      // Желтый
      svet_N4.get_default();
      svet_N4.set(1, LOW);
    }
    else if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= GR_TIME){
      // Зеленый
      svet_N4.get_default();
      svet_N4.set(0, LOW);
    }
    else if (digitalRead(W2_4) == 1 && digitalRead(S13) == 0 && timer_C2 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_N4.get_default();
      svet_N4.set(2, LOW);
      svet_N4.blink_on(1);
    }
    else{
      // Красный
      svet_N4.get_default();
      svet_N4.set(3, LOW);
    }
  }
  else{
    // Красный
    svet_N4.get_default();
    svet_N4.set(3, LOW);
  }
  // ============== Светофор Н4 ==============

  // ============== Светофор НII ==============
  if (digitalRead(W8_10) == 1 && digitalRead(W12) == 1
  && digitalRead(S9_2) == 1 && digitalRead(SV12) == 1 && digitalRead(SV16) == 1
  && digitalRead(SV16) == 1 && digitalRead(SV21) == 1 && digitalRead(SV22) == 1){
    if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= YEL_TIME){
      // Желтый
      svet_NII.get_default();
      svet_NII.set(0,  LOW);
    }
    else if (digitalRead(W2_4) == 0 && digitalRead(S12) == 0 && digitalRead(SV23) == 1
    && timer_C1 >= GR_TIME){
      // Зеленый
      svet_NII.get_default();
      svet_NII.set(1, LOW);
    }
    else if (digitalRead(W2_4) == 1 && digitalRead(S13) == 0 && timer_C2 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_CII.get_default();
      svet_CII.set(0, LOW);
      svet_CII.blink_on(3);
    }
    else{
      // Красный
      svet_NII.get_default();
      svet_NII.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_NII.get_default();
    svet_NII.set(2, LOW);
  }
  // ============== Светофор НII ==============

  // ============== Светофор НI ==============
  if (digitalRead(W2_4) == 1 && digitalRead(W16) == 1 && digitalRead(S10_2) == 1
  && digitalRead(SV13) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1){
    if (digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(SV12) == 0
    && digitalRead(SV20) == 1 && digitalRead(SV23) == 1 && timer_C1 >= YEL_TIME){
      // Желтый
      svet_NI.get_default();
      svet_NI.set(0);
    }
    else if (digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(SV12) == 0
    && digitalRead(SV20) == 1 && digitalRead(SV23) == 1 && timer_C1 >= GR_TIME){
      // Зеленый
      svet_NI.get_default();
      svet_NI.set(1, LOW);
    }
    else if (digitalRead(W8_10) == 1 && digitalRead(S13) == 0 && digitalRead(SV21) == 1
    && digitalRead(SV22) == 1 && timer_C2 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_NI.get_default();
      svet_NI.set(3, LOW);
      svet_NI.blink_on(0);
    }
    else{
      // Красный
      svet_NI.get_default();
      svet_NI.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_NI.get_default();
    svet_NI.set(2, LOW);
  }
  // ============== Светофор НI ==============

  // ============== Светофор Н3 ==============
  if (digitalRead(W2_4) == 1 && digitalRead(W16) == 0 && digitalRead(S10_2) == 1
  && digitalRead(SV14) == 1 && digitalRead(SV17) == 1 && digitalRead(SV19) == 1){
    if (digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(SV12) == 0
    && digitalRead(SV23) == 1 && timer_C1 >= YEL_TIME){
      // Желтый
      svet_N3.get_default();
      svet_N3.set(0, LOW);
    }
    else if (digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(SV12) == 0
    && digitalRead(SV23) == 1 && timer_C1 >= GR_TIME){
      // Зеленый
      svet_N3.get_default();
      svet_N3.set(1, LOW);
    }
    else if (digitalRead(W8_10) == 1 && digitalRead(S13) == 0 && digitalRead(SV21) == 1
    && digitalRead(SV22) == 1 && timer_C2 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_N3.get_default();
      svet_N3.set(3, LOW);
      svet_N3.blink_on(0);
    }
    else{
      // Красный
      svet_N3.get_default();
      svet_N3.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_N3.get_default();
    svet_N3.set(2, LOW);
  }
  // ============== Светофор Н3 ==============

  // ============== Светофор Н5 ==============
  if (digitalRead(W2_4) == 1 && digitalRead(W6) == 0 && digitalRead(W18) == 0
  && digitalRead(W8_10) == 1 && digitalRead(S10_2) == 1 && digitalRead(S12) == 0
  && digitalRead(SV18) == 1 && digitalRead(SV20) == 1 && digitalRead(SV23) == 1){
    if (timer_C1 >= YEL_TIME){
      // Желтый
      svet_N5.get_default();
      svet_N5.set(0, LOW);
    }
    else if (timer_C1 >= GR_TIME){
      // Зеленый
      svet_N5.get_default();
      svet_N5.set(1, LOW);
    }
    else{
      // Красный
      svet_N5.get_default();
      svet_N5.set(2, LOW);
    }
  }
  else if (digitalRead(SV18) == 1 && digitalRead(S14) == 0){
    // Белый
    svet_N5.get_default();
    svet_N5.blink_on(3);
  }
  else{
    // Красный
    svet_N5.get_default();
    svet_N5.set(2, LOW);
  }
  // ============== Светофор Н5 ==============

  // ============== Светофор Ч8 ==============
  if (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(S9_1) == 1
  && digitalRead(SV1) == 1){
    if (timer_N2 >= YEL_TIME){
      // Желтый
      svet_C8.get_default();
      svet_C8.set(0, LOW);
    }
    else if (timer_N2 >= GR_TIME){
      // Зеленый
      svet_C8.get_default();
      svet_C8.set(1, LOW);
    }
    else{
      // Красный
      svet_C8.get_default();
      svet_C8.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_C8.get_default();
    svet_C8.set(2, LOW);
  }
  // ============== Светофор Ч8 ==============

  // ============== Светофор Ч6 ==============
  if (digitalRead(W1_3) == 1 && digitalRead(W11) == 0 && digitalRead(W13) == 0
  && digitalRead(S9_1) == 1 && digitalRead(SV3) == 1 && digitalRead(SV5) == 1){
    if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(S7) == 0
    && digitalRead(SV1) == 1 && timer_N2 >= YEL_TIME){
      // Желтый
      svet_C6.get_default();
      svet_C6.set(0, LOW);
    }
    else if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(S7) == 0
    && digitalRead(SV1) == 1 && timer_N2 >= GR_TIME){
      // Зеленый
      svet_C6.get_default();
      svet_C6.set(1, LOW);
    }
    else if (digitalRead(W7_9) == 0 && digitalRead(S8) == 0 && digitalRead(W7_9) == 1
    && digitalRead(SV2) == 1 && timer_N1 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_C6.get_default();
      svet_C6.set(0, LOW);
      svet_C6.blink_on(3);
    }
    else{
      // Красный
      svet_C6.get_default();
      svet_C6.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_C6.get_default();
    svet_C6.set(2, LOW);
  }
  // ============== Светофор Ч6 ==============

  // ============== Светофор Ч4 ==============
  if (digitalRead(W1_3) == 1 && digitalRead(W11) == 0 && digitalRead(W13) == 1
  && digitalRead(S9_1) == 1 && digitalRead(SV3) == 1 && digitalRead(SV6) == 1){
    if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(S7) == 0
    && digitalRead(SV1) == 1 && timer_N2 >= YEL_TIME){
      // Желтый
      svet_C4.get_default();
      svet_C4.set(0, LOW);
    }
    else if (digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(S7) == 0
    && digitalRead(SV1) == 1 && timer_N2 >= GR_TIME){
      // Зеленый
      svet_C4.get_default();
      svet_C4.set(1, LOW);
    }
    else if (digitalRead(W7_9) == 0 && digitalRead(S8) == 0 && digitalRead(W7_9) == 1
    && digitalRead(SV2) == 1 && timer_N1 >= YEL_TIME){
      // Желтый мигающий и белый
      svet_C4.get_default();
      svet_C4.set(0, LOW);
      svet_C4.blink_on(3);
    }
    else{
      // Красный
      svet_C4.get_default();
      svet_C4.set(2, LOW);
    }
  }
  else{
    // Красный
    svet_C4.get_default();
    svet_C4.set(2, LOW);
  }
  // ============== Светофор Ч4 ==============

  // ============== М1 ==============
  if (digitalRead(W1_3) == 0 && digitalRead(W7_9) == 1 && digitalRead(W15) == 0
  && digitalRead(S10_1) == 0 && getS7() == 1){
    svet_M1.get_default();
    svet_M1.set(1, LOW);
  }
  else if (digitalRead(W1_3) == 0 && digitalRead(W7_9) == 1 && digitalRead(W15) == 1
  && digitalRead(S10_1) == 0 && getS7() == 1){
    svet_M1.get_default();
    svet_M1.set(1, LOW);
  }
  else if (digitalRead(S9_1) == 0 && getS7() == 1
  && ((digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 1) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 0 && digitalRead(W13) == 1) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 1 && digitalRead(W7_9) == 1 && digitalRead(W11) == 0 && digitalRead(W13) == 0) ||
  (digitalRead(W1_3) == 1 && digitalRead(W5) == 0))){
    svet_M1.get_default();
    svet_M1.set(1, LOW);
  }
  else{
    svet_M1.get_default();
    svet_M1.set(0, LOW);
  }
  // ============== М1 ==============

  // ============== М3 ==============
  if (digitalRead(W1_3) == 1 && digitalRead(S8) == 1
  && ((digitalRead(W7_9) == 1 && digitalRead(W15) == 1 && digitalRead(S10_1) == 0) ||
  (digitalRead(W7_9) == 0 && digitalRead(W11) == 1 && digitalRead(S9_1) == 0) ||
  (digitalRead(W7_9) == 0 && digitalRead(W11) == 0 && digitalRead(W13) == 1 && digitalRead(S9_1) == 0) ||
  (digitalRead(W7_9) == 0 && digitalRead(W11) == 0 && digitalRead(W13) == 0 && digitalRead(S9_1) == 0))){
    svet_M3.get_default();
    svet_M3.set(1, LOW);
  }
  else{
    svet_M3.get_default();
    svet_M3.set(0, LOW);
  }
  // ============== М3 ==============

  // ============== М6 ==============
  if (digitalRead(W18) == 1 && digitalRead(W20) == 1 && digitalRead(S14) == 1){
    svet_M6.get_default();
    svet_M6.set(1, LOW);
  }
  else{
    svet_M6.get_default();
    svet_M6.set(0, LOW);
  }
  // ============== М6 ==============

  // ============== М8 ==============
  if (digitalRead(W18) == 1 && digitalRead(W20) == 0 && digitalRead(S14) == 1){
    svet_M8.get_default();
    svet_M8.set(1, LOW);
  }
  else{
    svet_M8.get_default();
    svet_M8.set(0, LOW);
  }
  // ============== М8 ==============
  
  // ============== М2 ==============
  if (digitalRead(S12) == 1 && 
  ((digitalRead(W2_4) == 1 && digitalRead(W6) == 0 && digitalRead(W18) == 0 && digitalRead(S10_2) == 0) ||
  (digitalRead(W2_4) == 1 && digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(W16) == 0 && digitalRead(S10_2) == 0) ||
  (digitalRead(W2_4) == 1 && digitalRead(W6) == 1 && digitalRead(W8_10) == 1 && digitalRead(W16) == 0 && digitalRead(S10_2) == 0) ||
  (digitalRead(W2_4) == 0 && digitalRead(W8_10) == 1 && digitalRead(W12) == 1 && digitalRead(S9_2) == 0) ||
  (digitalRead(W2_4) == 0 && digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 1 && digitalRead(S9_2) == 0) ||
  (digitalRead(W2_4) == 0 && digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 0 && digitalRead(S9_2) == 0))){
    svet_M2.get_default();
    svet_M2.set(1, LOW);
  }
  else{
    svet_M2.get_default();
    svet_M2.set(0, LOW);
  }
  // ============== М2 ==============

  // ============== М4 ==============
  if (digitalRead(W2_4) == 1 && digitalRead(S13) == 1 && (
  ((digitalRead(W8_10) == 1 && digitalRead(W12) == 1 && digitalRead(S9_2) == 0) ||
  (digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 0 && digitalRead(S9_2) == 0) ||
  (digitalRead(W8_10) == 1 && digitalRead(W12) == 0 && digitalRead(W14) == 1 && digitalRead(S9_2) == 0) ||
  (digitalRead(W8_10) == 0 && digitalRead(W16) == 1 && digitalRead(S10_2) == 0) ||
  (digitalRead(W8_10) == 0 && digitalRead(W16) == 0 && digitalRead(S10_2) == 0)))){
    svet_M4.get_default();
    svet_M4.set(1, LOW);
  }
  else{
    svet_M4.get_default();
    svet_M4.set(0, LOW);
  }
  // ============== М4 ==============

  // Исполение команд светофорами, всегда в конце
  svets_work();
}