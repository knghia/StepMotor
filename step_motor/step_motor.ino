#define DIR_PIN 2
#define STEP_PIN 5
#define ENABLE_PIN 6

#define STEP_ORIGIN 1.8
#define RESOLUTION 16
#define STEP_INVERS RESOLUTION/STEP_ORIGIN

int part_angle = 0;

void run_step(int angle){
  if (angle == part_angle){
    return;
  }
  for (int i=0;i<angle*STEP_INVERS;i++){
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN,LOW);
    delayMicroseconds(500);
  }
  part_angle= angle;
}

void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN,OUTPUT);
  pinMode(STEP_PIN,OUTPUT);
  pinMode(ENABLE_PIN,OUTPUT);
}

void loop() {
  run_step(90);
  while(1);
}
