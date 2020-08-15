#define ENABLE_PIN 8

#define DIR_PIN 5
#define STEP_PIN 2

#define RIGHT LOW
#define LEFT OUTPUT

#define STEP_ORIGIN 1.8
#define RESOLUTION 32
#define STEP_INVERS RESOLUTION/STEP_ORIGIN

int part_angle = 0;

void run_step(int angle){
  if (angle == part_angle){
    return;
  }
  if (angle < part_angle){
    int dental = part_angle - angle;
    digitalWrite(DIR_PIN, LEFT);
    for (int i=0;i<dental*STEP_INVERS;i++){
      digitalWrite(STEP_PIN,HIGH);
      delayMicroseconds(100);
      digitalWrite(STEP_PIN,LOW);
      delayMicroseconds(100);
    }
    part_angle= angle;
    return;
  }
  if (angle > part_angle){
    int dental = angle-part_angle;
    digitalWrite(DIR_PIN, RIGHT);
    for (int i=0;i<dental*STEP_INVERS;i++){
      digitalWrite(STEP_PIN,HIGH);
      delayMicroseconds(100);
      digitalWrite(STEP_PIN,LOW);
      delayMicroseconds(100);
    }
    part_angle= angle;
    return;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN,OUTPUT);
  pinMode(STEP_PIN,OUTPUT);
  pinMode(ENABLE_PIN,OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, RIGHT);
}

void loop() {
  String angle_serial = Serial.readString();
  if (angle_serial[0] == ':'){
    angle_serial.remove(0,1);
    int angle_num = angle_serial.toInt();
    run_step(angle_num);
  }
}


