// variables for ir
const int ir_pin[8] = {0,1,2,3,4,5,6,7};
int ir[8] = {0, 0, 0, 0, 0,0,0,0};
int air[8] = {0, 0, 0, 0, 0,0,0,0};
int speed = 255;

// variables for motor
int motorL_pin1 = 8;
int motorL_pin2 = 9;
int motorR_pin1 = 10;
int motorR_pin2 = 11;
void display()
{
  // TO see output on Serial Monitor
  Serial.print("IR digital values: ");
  for (int i = 0; i < 8; ++i) {
    Serial.print(ir[i]);
    Serial.print(",");
  }
  Serial.println();

  Serial.print("IR analog values: ");
  for (int i = 0; i < 8; ++i) {
    Serial.print(air[i]);
    Serial.print(",");
    display();
  }
  Serial.println();
  // end here
}
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(ir_pin[i], INPUT);
  }
  pinMode(motorL_pin1, OUTPUT);
  pinMode(motorL_pin2, OUTPUT);
  pinMode(motorR_pin1, OUTPUT);
  pinMode(motorR_pin2, OUTPUT);
};

void read_ir() {
  for (int i = 0; i < 8; i++) {
    ir[i] = digitalRead(ir_pin[i]);
    air[i] = analogRead(ir_pin[i]);
  }

  
}

// motor control
void left_on() {
  digitalWrite(motorL_pin1, HIGH);
  digitalWrite(motorL_pin2, LOW);
  analogWrite(motorL_pin1, speed);
}
void left_back() {
  digitalWrite(motorL_pin1, LOW);
  digitalWrite(motorL_pin2, HIGH);
  analogWrite(motorL_pin2, speed);
}
void left_off() {
  digitalWrite(motorL_pin1, LOW);
  digitalWrite(motorL_pin2, LOW);
}
void right_on() {
  digitalWrite(motorR_pin1, HIGH);
  digitalWrite(motorR_pin2, LOW);
  analogWrite(motorR_pin1, speed);
}
void right_back() {
  digitalWrite(motorR_pin1, LOW);
  digitalWrite(motorR_pin2, HIGH);
  analogWrite(motorR_pin2, speed);
}
void right_off() {
  digitalWrite(motorR_pin1, LOW);
  digitalWrite(motorR_pin2, LOW);
}

// movement control
void moveStraight() {
  left_on();
  right_on();
}
void moveRight() {
  left_on();
  right_back();
}
void moveLeft() {
  left_back();
  right_on();
}
void stop() {
  left_off();
  right_off();
}
void softRight() {
  left_on();
  right_off();
}
void softLeft() {
  right_on();
  left_off();
}
void softerRight() {
  digitalWrite(motorR_pin1, HIGH);
  digitalWrite(motorR_pin2, LOW);
  analogWrite(motorR_pin1,(int)speed/2);
  left_off();
}
void softerLeft() {
  digitalWrite(motorL_pin1, HIGH);
  digitalWrite(motorL_pin2, LOW);
  analogWrite(motorL_pin1, (int)speed/2);
  right_off();
}


void loop() {
  read_ir();
  if(ir[0]==1 && ir[1]==1&&ir[2]==1 && ir[3]==0&&ir[4]==0 && ir[5]==1&&ir[6]==1 && ir[7]==1){
    Serial.println("moving staright");
  moveStraight();
  }
  if(ir[0]==1 && ir[1]==1&&ir[2]==0 && ir[3]==0&&ir[4]==1 && ir[5]==1&&ir[6]==1 && ir[7]==1){
    Serial.println("softer left");
  softerLeft();
  }
  if(ir[0]==1 && ir[1]==0 && ir[2]==0 && ir[3]==1 && ir[4]==1 && ir[5]==1&&ir[6]==1 && ir[7]==1){
    Serial.println("soft left");
  softLeft();
  }
  if(ir[0]==0 && ir[1]==0 && ir[2]==1 && ir[3]==1 && ir[4]==1 && ir[5]==1&&ir[6]==1 && ir[7]==1){
    Serial.println("moving left");
  moveLeft();}
  if(ir[0]==1 && ir[1]==1 && ir[2]==1 && ir[3]==1 && ir[4]==0 && ir[5]==0 && ir[6]==1 && ir[7]==1){
    Serial.println("softer right");
  softerRight();
  }
  if(ir[0]==1 && ir[1]==1 && ir[2]==1 && ir[3]==1 && ir[4]==1 && ir[5]==0 && ir[6]==0 && ir[7]==1){
    Serial.println("soft right");
  softRight();}
  if(ir[0]==1 && ir[1]==1 && ir[2]==1 && ir[3]==1 && ir[4]==1 && ir[5]==1&&ir[6]==0 && ir[7]==0){
    Serial.println("move right");
  moveRight();}
};
