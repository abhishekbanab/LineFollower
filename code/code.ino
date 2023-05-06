// variables for ir
const int ir_pin[5]={A0,A1,A2,A3,A4,A5};
int ir[5]={0,0,0,0,0};
int air[5]={0,0,0,0,0};
int speed=255;

// variables for motor
int motorL_pin1 = 9;
int motorL_pin2 = 10;
int motorR_pin1 = 11;
int motorR_pin2 = 12;

void setup(){
    Serial.begin(9600);
    for (int i = 0; i < 5; i++) {
        pinMode(ir_pin[i], INPUT);
    }
    pinMode(motorL_pin1, OUTPUT);
    pinMode(motorL_pin2, OUTPUT);
    pinMode(motorR_pin1, OUTPUT);
    pinMode(motorR_pin2, OUTPUT);
};

void read_ir(){
    for (int i = 0; i < 5; i++) {
        ir[i]=digitalRead(ir_pin[i]);
        air[i]=analogRead(ir_pin[i]);
    }

    // TO see output on Serial Monitor
    Serial.print("IR digital values: ");
    for (int i = 0; i < 5; ++i) {
        Serial.print(ir[i]);
        Serial.print(",");
    }
    Serial.println();

    Serial.print("IR analog values: ");
    for (int i = 0; i < 5; ++i) {
        Serial.print(air[i]);
        Serial.print(",");
    }
    Serial.println();
    // end here
}

// motor control
void left_on(){
    digitalWrite(motorL_pin1, HIGH);
    digitalWrite(motorL_pin2, LOW);
    analogWrite(motorL_pin1, speed);
}
void left_back(){
    digitalWrite(motorL_pin1, LOW);
    digitalWrite(motorL_pin2, HIGH);
    analogWrite(motorL_pin2, speed);
}
void left_off(){
    digitalWrite(motorL_pin1, LOW);
    digitalWrite(motorL_pin2, LOW);
}
void right_on(){
    digitalWrite(motorR_pin1, HIGH);
    digitalWrite(motorR_pin2, LOW);
    analogWrite(motorR_pin1, speed);
}
void right_back(){
    digitalWrite(motorR_pin1, LOW);
    digitalWrite(motorR_pin2, HIGH);
    analogWrite(motorR_pin2, speed);
}
void right_off(){
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
void softRight(){
    left_on();
    right_off();
}
void softLeft(){
    right_on();
    left_off();
}


void loop(){
    read_ir();

    if(ir[0]==0 && ir[1]==0 && ir[2]==1 && ir[3]==0 && ir[4]==0){
        moveStraight();
    }
    if(ir[0]==1 && ir[1]==1 && ir[2]==1 && ir[3]==0 && ir[4]==0){
        moveLeft();
    }
    if(ir[0]==0 && ir[1]==0 && ir[2]==1 && ir[3]==1 && ir[4]==1){
        moveRight();
    }
    if(ir[0]==0 && ir[1]==0 && ir[2]==0 && ir[3]==0 && ir[4]==0){
        stop();
    }


    if(ir[0]==0 && ir[1]==1 && ir[2]==0 && ir[3]==0 && ir[4]==0){
        softLeft();
    }
    if(ir[0]==0 && ir[1]==0 && ir[2]==0 && ir[3]==1 && ir[4]==0){
        softRight();
    }
};

//// PID control variables
//double setpoint = 2.0;
//double Kp = 0.3;
//double Ki = 0.1;
//double Kd = 0.2;
//double error, last_error = 0;
//double integral = 0;
//double derivative;
//// PID control function
//double PIDcontrol() {
//    error = setpoint - ir[2];
//    integral += error;
//    derivative = error - last_error;
//    last_error = error;
//
//    double pid_value = Kp * error + Ki * integral + Kd * derivative;
//
//    return pid_value;
//}
//void loop() {
//    readir();
//    calculatePID();
//
//    // use PID output to control motor speed
//    int leftSpeed = speed + pidValue;
//    int rightSpeed = speed - pidValue;
//
//    // limit the maximum speed
//    leftSpeed = constrain(leftSpeed, 0, 255);
//    rightSpeed = constrain(rightSpeed, 0, 255);
//
//    // control the motors based on PID output
//    if (pidValue > 0) {
//        left_on();
//        analogWrite(motorL_pin1, leftSpeed);
//        left_off();
//    }
//    else if (pidValue < 0) {
//        right_on();
//        analogWrite(motorR_pin1, rightSpeed);
//        right_off();
//    }
//    else {
//        moveStraight();
//    }
//}
