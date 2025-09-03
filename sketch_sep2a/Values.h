int gas = 100;
int nogas = 30;

struct RobotData{
  int moter_Right = 0;
  int moter_Left = 0;
  bool medsols = false;
  int ultrasensor;
  int linesensor;
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