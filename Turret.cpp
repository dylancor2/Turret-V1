#include <Stepper.h>
#include <Servo.h>

int serInfo = 0;
int xpos;

int ledpin = 12;
int servopin = 13;
int step1 = 8;
int step2 = 9;
int step3 = 10;
int step4 = 11;

bool shot;

Servo x, st1, st2;
Stepper y(2048, step1, step3, step2, step4);



void setup() {
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  x.attach(servopin);
  
  st1.attach(6);
  st2.attach(5);
  
  y.setSpeed(5);
  
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  digitalWrite(ledpin, HIGH);
  Serial.println("Connection is good");
  resetAll();
}

void loop() {
  /*
   * Ascii conversions
   * 1 - 49 - up (y)
   * 2 - 50 - down (y)
   * 3 - 51 - up (x)
   * 4 - 52 - down (y)
   * 5 - 53 - resetAll
   * 6 - 54 - Shoot gun
   */
  if (Serial.available() > 0) {
    serInfo = Serial.read();
    Serial.print("ARDUINO GOT: ");
    Serial.println(int(serInfo));
    switch(serInfo){
    case 49:{
      yUp();
      break;
    }
    case 50:{
      yDown();
      break;
    }
    case 51:{
      xUp();
      break;
    }
    case 52:{
      xDown();
      break;
    }
    case 53:{
      resetAll();
      break;
    }
    case 54:{
      shoot();
      break;
    }
    case 55:{
      last();
      break;
    }
  }
  }
  
}

void resetX(){
  x.write(90);
  xpos = 90;
}

void yUp(){
  y.step(15);
}

void yDown(){
  y.step(-15);
}

void xUp(){
  if(xpos < 180){
    x.write(xpos+3);
    xpos+=3;
  }
}

void xDown(){
  if(xpos > 0){
    x.write(xpos-3);
    xpos-=3;
  }
}

void resetAll(){
  digitalWrite(ledpin, LOW);
  x.write(90);
  xpos = 90;
  st1.write(180);
  st2.write(0);
  digitalWrite(ledpin, HIGH);
}

void last(){
  digitalWrite(ledpin, LOW);
  x.write(90);
  xpos = 90;
  st1.write(180);
  st2.write(0);
}

void shoot(){
  st1.write(0);
  st2.write(90);
}

