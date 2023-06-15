#include <LiquidCrystal.h>
#include <TimerOne.h>

byte ocitajTaster(){
  int tmp = analogRead(0);

  if(tmp > 620 && tmp < 660){
    return 1;                     //SELECT
  }
  else if(tmp > 390 && tmp < 430){
    return 2;                     //LEFT
  }
  else if(tmp > 80 && tmp < 120){
    return 3;                     //UP
  }
  else if(tmp > 240 && tmp < 280){
    return 4;                     //DOWN
  }
  else if(tmp >= 0 && tmp < 40){
    return 5;                     //RIGHT
  }
  else{
    return 0;
  }
}

float kasnjenje[11] = {
  0.01,
  0.007951672353008666,
  0.007048327646991334,
  0.006309898804344545,
  0.0056409421684897485,
  0.005,
  0.004359057831510251,
  0.0036901011956554544,
  0.002951672353008666,
  0.0020483276469913355,
  0.0
};


int DRV = 13;
int ZC = 2;
int dim_val = 0;
int dmt = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte temp = ocitajTaster();
byte prethodni;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);

  //postavljanje izlaznog pina i interrupt handler
  pinMode(DRV, OUTPUT);
  pinMode(ZC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), zero_cross, FALLING);
  
  Timer1.initialize(10000);
}

bool zc = false;

void zero_cross() {
  zc = true;
}

void handleTimerInterrupt1() {
  digitalWrite(DRV, LOW);
}

 

void loop() {
  // put your main code here, to run repeatedly:
  prethodni = temp;
  temp = ocitajTaster();

  if(prethodni != temp){
    lcd.clear();

    switch(temp){
      default:
        lcd.print(dim_val);
        lcd.print("%");
        Serial.println(kasnjenje[dim_val/10], 10);
        break;
      case 2:
        if (dim_val <= 10) {
          dim_val = 0;
        }
        else {
          dim_val -= 10;
        }
        break;
      case 3:
        if (dim_val >= 90) {
          dim_val = 100;
        }
        else {
          dim_val += 10;
        }
        break;
      case 4:
        if (dim_val <= 10) {
          dim_val = 0;
        }
        else {
          dim_val -= 10;
        }
        break;
      case 5:
        if (dim_val >= 90) {
          dim_val = 100;
        }
        else {
          dim_val += 10;
        }
        break;
    }
  }

  dmt = 1000000 * kasnjenje[dim_val/10];

  if (zc == true) {
    if (dim_val != 0) {
      delayMicroseconds(dmt);
      digitalWrite(DRV, HIGH);
      delayMicroseconds(100);
      digitalWrite(DRV, LOW);
    }
    zc = false;
  }
  
}
