int n = 0;

int BASE_SPEED = 100;
int INTERUPT_DISTANCE = 30;
bool OBSTACLE_DETECTED = false;
bool OBSTACLE_TO_CLOSE = false;
int MEDSOLS = 0;
int MOTSOLS = 0;

struct RobotData{
  int moter_Right = 0;
  int moter_Left = 0;
  bool medsols = false;
  int ultrasensor;
  int linesensor;
};
struct LineSensor{
  int Period = 3;
  int ExecTime = 1;
};
struct SonicSensor{
  int Period = 6;
  int ExecTime = 4;
};
/*  For PID controller  */
/*  Notes for tuning PID controller:
  +Start with only Kp,
  +When car follows line but oscillates slightly -> add Kd to stabalize
  +Add Ki if car drifts of line
*/
float Kp = 80.0;
float Kd = 0.0;
float Ki = 0.0;
float integral = 0;
float lasterror = 0;

