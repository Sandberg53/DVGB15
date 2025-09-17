#include "kaulab.h"
#include "Values.h"

RobotData robotData;

void run(int Right, int Left){
  zRobotSetMotorSpeed(1, -Right);
  zRobotSetMotorSpeed(2, Left);
}

void TaskLineSensor(){
  if(!OBSTACLE_DETECTED && !OBSTACLE_TO_CLOSE){     //If no obstacle in front of car - read sensor else continue
    robotData.linesensor = zRobotGetLineSensor();
    float error = 0;
    if(lasterror == 0 && robotData.linesensor == 3){
      lasterror = MEDSOLS > MOTSOLS ? -1 : 1;
    }
    switch (robotData.linesensor){
      case 0: error = 0; break;
      case 1: error = -1; MEDSOLS++; break;
      case 2: error = 1;  MOTSOLS++; break;
      case 3: error = lasterror; break;
    }

    integral += error;
    float derivative = error - lasterror;
    float correction = Kp * error + Ki * integral + Kd * derivative;

    int leftspeed = BASE_SPEED - correction;
    int rightspeed = BASE_SPEED + correction;

    run(leftspeed, rightspeed);
    lasterror = error;
  }
}

void TaskObstacleCheck(){
  robotData.ultrasensor = zRobotGetUltraSensor();
  if((robotData.ultrasensor > 20 && robotData.ultrasensor < INTERUPT_DISTANCE && !OBSTACLE_TO_CLOSE) || (OBSTACLE_DETECTED && !OBSTACLE_TO_CLOSE)){
    OBSTACLE_DETECTED ? n++ : n = 0;
    OBSTACLE_DETECTED = true;
    if(n < 3){
      MEDSOLS < MOTSOLS ? run(0, 200) : run(200, 0);
    }
    else if(n >= 3 && n < 7){
      MEDSOLS < MOTSOLS ? run(100, 100) : run(100, 100);
    }
    else if(n >= 7 && n < 10){
      MEDSOLS < MOTSOLS ? run(350, 0) : run(0, 350);
    }
    else if(n > 9 && n < 70){
      MEDSOLS > MOTSOLS ? run(100, 80) : run(80, 100);
    }
    else if(n > 70){
      run(0,0);
    }

    if(zRobotGetLineSensor() != 3 && n > 10){
      OBSTACLE_DETECTED = false;
    }
  }
  else if (robotData.ultrasensor < 25 && !OBSTACLE_DETECTED){
    OBSTACLE_TO_CLOSE = true;
    run(-100, -100);
  }
  else if(robotData.ultrasensor > 25 && OBSTACLE_TO_CLOSE){
    OBSTACLE_TO_CLOSE = false;
  }
}

void setup() {
  LineSensor line;
  SonicSensor sonic;
  zInitialize();
  /*
      Task period and time analyzation:
        CPU Utilazation = ExecTime_1 / PeriodTime_1 + ExecTime_2 / PeriodTime_2 ...
        If this exeeds 1 the processor cant schedule all tasks and will eventually fail
  */

  zScheduleTask(TaskObstacleCheck, sonic.Period, sonic.ExecTime);
  zScheduleTask(TaskLineSensor, line.Period, line.ExecTime);
  zStart();
}

void loop() {
  
}