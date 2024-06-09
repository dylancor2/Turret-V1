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
Servo x;
Stepper y(2048, step1, step3, step2, step4);



void setup() {
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  x.attach(servopin);
  y.setSpeed(5);
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  digitalWrite(ledpin, HIGH);
  Serial.println("Connection is good");
  resetX();
}

void loop() {
  /*
   * Ascii conversions
   * 1 - 49 - up (y)
   * 2 - 50 - down (y)
   * 3 - 51 - up (x)
   * 4 - 52 - down (y)
   * 5 - 53 - done
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
      done();
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
    xpos+=5;
  }
}

void xDown(){
  if(xpos > 0){
    x.write(xpos-3);
    xpos-=5;
  }
}

void done(){
  digitalWrite(ledpin, LOW);
}
