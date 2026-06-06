#include <Servo.h>

Servo horizontal; 
int servoh = 90;   // Horizontal servo start position

Servo vertical;   
int servov = 90;   // Vertical servo start position

// LDR pins - 
int ldrlt = A0; // top left
int ldrrt = A1; // top right
int ldrld = A2; // down left
int ldrrd = A3; // down right

void setup() {
  Serial.begin(9600);
  horizontal.attach(10); // Horizontal servo pin
  vertical.attach(11);   // Vertical servo pin
  
  horizontal.write(servoh);
  vertical.write(servov);
  delay(2000);
}

void loop() {
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down right
  
  Serial.print("TL: "); Serial.print(lt); Serial.print(" | ");
  Serial.print("TR: "); Serial.print(rt); Serial.print(" | ");
  Serial.print("DL: "); Serial.print(ld); Serial.print(" | ");
  Serial.print("DR: "); Serial.println(rd);

  int dtime = 10; 
  int tol = 50; 
  
  int avt = (lt + rt) / 2; // average top
  int avd = (ld + rd) / 2; // average down
  int avl = (lt + ld) / 2; // average left
  int avr = (rt + rd) / 2; // average right

  int dvert = avt - avd; // check difference up/down
  int dhoriz = avl - avr; // check difference left/right
  
  // Vertical movement
  if (-1*tol > dvert || dvert > tol) {
    if (avt > avd) {
      servov = ++servov;
      if (servov > 180) { servov = 180; }
    } else if (avt < avd) {
      servov = --servov;
      if (servov < 0) { servov = 0; }
    }
    vertical.write(servov);
  }
  
  // Horizontal movement
  if (-1*tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
      servoh = --servoh;
      if (servoh < 0) { servoh = 0; }
    } else if (avl < avr) {
      servoh = ++servoh;
      if (servoh > 180) { servoh = 180; }
    }
    horizontal.write(servoh);
  }
  
  delay(dtime);
}
