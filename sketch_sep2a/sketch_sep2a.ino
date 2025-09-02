#include "kaulab.h"
#include "Values.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  zInitialize();
}
//zRobotGetLineSensor returns 0 for black and 3 for white
// 1 == moter_Left sensor black
// 2 == moter_Right sensor black
// 3 == both sensor white
// 0 == both sensor black


void loop() {
  int ultrasensor = zRobotGetUltraSensor();
  int linesensor = zRobotGetLineSensor();
          Serial.print("Distance = ");
          Serial.println(zRobotGetUltraSensor());
          Serial.print("line ");
          Serial.println(zRobotGetLineSensor());
  if (linesensor == 0) {
    moter_Right = gas;
    moter_Left = gas;
  } else if (linesensor == 2) {
    moter_Right = nogas;
    moter_Left = gas;
    rightside = false;
  } else if (linesensor == 1) {
    moter_Right = gas;
    moter_Left = gas;
    rightside = true;
  } else if (linesensor == 3) {  // white
    if (rightside) {
      moter_Right = gas;
      moter_Left = nogas;
    } else {
      moter_Right = nogas;
      moter_Left = gas;
    }
  }
  if (ultrasensor < 20) {
    /*
    * Avoid obstacle
    */
    Obstacle(rightside);
  }
  Drive(moter_Right, moter_Left);
}
void Obstacle(bool RI) {
  /*if (!RI) {
    moter_Left = nogas - 10;
    moter_Right = gas;
  } else {
    moter_Left = gas;
    moter_Right = nogas - 10;
  }
  Drive(moter_Right, moter_Left);
  delay(70);
  moter_Right = moter_Left = gas;

  Drive(moter_Right, moter_Left);
  delay(300);*/
}

void Drive(int R, int L) {
  Serial.print("drivinh r ");
  Serial.println(R);
  Serial.print("drivinh L ");
  Serial.println(L);
  zRobotSetMotorSpeed(1, -R);
  zRobotSetMotorSpeed(2, L);
}
