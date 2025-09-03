#include "kaulab.h"
#include "Values.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  zInitialize();
}

void loop() {
  RobotData robotData;
  robotData.ultrasensor = zRobotGetUltraSensor();
  robotData.linesensor = zRobotGetLineSensor();

  if (robotData.linesensor == 0) {
    robotData.moter_Right = gas;
    robotData.moter_Left = gas;
  } else if (robotData.linesensor == 2) {
    robotData.moter_Right = nogas;
    robotData.moter_Left = gas;
    robotData.medsols = false;
  } else if (robotData.linesensor == 1) {
    robotData.moter_Right = gas;
    robotData.moter_Left = gas;
    robotData.medsols = true;
  } else if (robotData.linesensor == 3) {  // white
    if (robotData.medsols) {
      robotData.moter_Right = gas;
      robotData.moter_Left = nogas;
    } else {
      robotData.moter_Right = nogas;
      robotData.moter_Left = gas;
    }
  }
  if (robotData.ultrasensor < 20) {
    /*
    * Avoid obstacle
    */
    Obstacle(robotData.medsols);
  }
  Drive(robotData.moter_Right, robotData.moter_Left);
  DebugPrint(robotData);
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
  zRobotSetMotorSpeed(1, -R);
  zRobotSetMotorSpeed(2, L);
}
void DebugPrint(const RobotData& data){
  int intvalues[NUM_FIELDS] = {
    data.moter_Right,
    data.moter_Left,
    static_cast<int>(data.medsols),
    data.ultrasensor,
    data.linesensor
  };
  for(int i= 0; i< NUM_FIELDS; i++){
    Serial.print(DebugLabels[i]);
    Serial.flush();
    Serial.println(intvalues[i]);
  }
}
