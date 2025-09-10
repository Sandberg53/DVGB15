int gas =130;
int nogas = 30;
int n = 0;
bool ObstacleInWay = false;
int NR_OF_TASKS = 4;
int DistanceToInterupt = 30;

struct RobotData{
  int moter_Right = 0;
  int moter_Left = 0;
  bool medsols = false;
  int ultrasensor;
  int linesensor;
};
struct LineSensor{
  int Period = 2;
  int ExecTime = 1;
};
struct SonicSensor{
  int Period = 7;
  int ExecTime = 4;
};
struct Driver{
  int Period = 2;
  int ExecTime = 1;
};

struct Obsticale{
  int Period = 5;
  int ExecTime = 10;
};


enum DebugField{
  Motor_Right,
  Motor_Left,
  Medsols,
  Distance,
  Line_Sensor,
  NUM_FIELDS
};

const char* DebugLabels[NUM_FIELDS] = {
  "Motor Right: ",
  "Motor Left: ",
  "Medsols: ",
  "Distance: ",
  "Line sensor: "
};