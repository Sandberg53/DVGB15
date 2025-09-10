#include "kaulab.h"
#include "Values.h"

RobotData robotData;
void run(int Right, int Left){
  zRobotSetMotorSpeed(1, -Right);
  zRobotSetMotorSpeed(2, Left);
}

void Obsticales(){
 if(ObstacleInWay){
  n++;
  if(n < 4){
   !robotData.medsols ? run(0, 200) : run(200, 0);
  }
  else if(n >= 4 && n < 8){
    !robotData.medsols ? run(100, 100) : run(100, 100);
  }
  else if(n >= 8 && n < 14){
    !robotData.medsols ? run(180, 0) : run(0, 180);
  }
  else if(zRobotGetLineSensor() != 3){
    ObstacleInWay = false;
  }
  else if(n > 70){
    run(0,0);
  }
  else{
    run(100, 100);
  }
  }
 
 }

void SensorData(){
  /*
  *   Read sensor data and update which way robot should drive
  */
  if(!ObstacleInWay){
    ReadLineSensor();
  }
}

void SonicData(){
  if(!ObstacleInWay){
    ReadSonicSensor();
  }
}
void Drive(){
 if(!ObstacleInWay){
  zRobotSetMotorSpeed(1, -robotData.moter_Right);
  zRobotSetMotorSpeed(2, robotData.moter_Left);
  Serial.println("Driving");
  Serial.println(robotData.moter_Right);
}}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LineSensor line;
  SonicSensor sonic;
  Driver drive;
  Obsticale obsticale;
  zInitialize();
  zScheduleTask(SensorData, line.Period, line.ExecTime);
  zScheduleTask(SonicData, sonic.Period, sonic.ExecTime);
  zScheduleTask(Obsticales, obsticale.Period, obsticale.ExecTime);
  zScheduleTask(Drive, drive.Period, drive.ExecTime);
  

  zStart();
}

void loop() {
  
}
void ReadSonicSensor(){
  robotData.ultrasensor = zRobotGetUltraSensor();
  if (robotData.ultrasensor < DistanceToInterupt && robotData.ultrasensor > DistanceToInterupt - 20){
    ObstacleInWay = true;
    n = 0;    
  }
  else if(robotData.ultrasensor < DistanceToInterupt - 20){
    run(-100, -100);
  }
}
void ReadLineSensor(){
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
