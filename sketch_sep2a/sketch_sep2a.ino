#include "kaulab.h"
#include "Values.h"

RobotData robotData;

void Obsticales(){
/*
  If obstacle is in the way of the robot
  Suspend all other tasks       vTaskSuspend()
  Go around obstacle
  Resume other tasks            vTaskResume()
*/
 Serial.println("Obsticle körswadawdwadawdawdwadwadaw");
  if(ObstacleInWay){
    n++;

     if(robotData.medsols == true){
       zRobotSetMotorSpeed(1, -40);
      zRobotSetMotorSpeed(2, -80);
    }
    else{
       zRobotSetMotorSpeed(1, -80);
      zRobotSetMotorSpeed(2, -40);
    }
    if(n > 10){
      ObstacleInWay = false;

      for(int i = 0; i< NR_OF_TASKS; i++)
    {
        vTaskResume(*zTaskList[i].handle);
    }
    vTaskSuspend(*zTaskList[2].handle);
    }
  }
}

void SensorData(){
  /*
  *   Read sensor data and update which way robot should drive
  */


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
 // DebugPrint(robotData);
}

void SonicData(){

  robotData.ultrasensor = zRobotGetUltraSensor();
  if (robotData.ultrasensor < 30 && robotData.ultrasensor > 10) {
    /*
    * Avoid obstacle
    */
    Serial.println("TaskResume");
    vTaskResume(*zTaskList[2].handle);    //Resume task
    vTaskSuspend(*zTaskList[0].handle);
    vTaskSuspend(*zTaskList[3].handle);
    ObstacleInWay = true;
    n = 0;
    vTaskSuspend(*zTaskList[1].handle);
    
  }
  else if(robotData.ultrasensor < 10){
    zRobotSetMotorSpeed(1, 0);
    zRobotSetMotorSpeed(2, 0);
    zDie(1, "To close");
  }
}
void Drive(){
 
  zRobotSetMotorSpeed(1, -robotData.moter_Right);
  zRobotSetMotorSpeed(2, robotData.moter_Left);
  Serial.println("Driving");
  Serial.println(robotData.moter_Right);
}
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
  vTaskSuspend(*zTaskList[2].handle);   //Suspend Task until needed
}

void loop() {
  
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
/*
void Drive(int R, int L) {
  zRobotSetMotorSpeed(1, -R);
  zRobotSetMotorSpeed(2, L);
}
*/
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
