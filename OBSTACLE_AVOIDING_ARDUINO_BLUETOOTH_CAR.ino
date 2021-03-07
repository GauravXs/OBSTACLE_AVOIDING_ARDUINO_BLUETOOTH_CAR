*****************************************************************************************
***************OBSTACLE_AVOIDING_ARDUINO_BLUETOOTH_CAR***********************************
*****************************************************************************************
// The Bluetooth control Application is available on playstore kindly use the below link.
//Link https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
//Note: This Code is Only Tested on this Application.
//Before uploading the code you have to install the necessary library
//Note - Disconnect the Bluetooth RX Cable before hiting the upload button otherwise you'll get compilation error message.
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install
//After downloading the library open Arduino IDE >> go to sketch >> Include Libray >> ADD. ZIP Libray >> Select the downloaded file
//Now You Can Upload the Code without any problem but make sure the bluetooth module isn't connected with Arduino while uploading code
//This Code uses IR sensor to avoid obstacles

#include <AFMotor.h>
#include <Servo.h>
#define RIGHT A2 //2nd Analog (A2) pin is connected to Right IR module
#define LEFT A3 //3nd Analog (A3) pin is connected to Left IR module

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo; // create servo object to control a servo
int pos = 83;// variable to store the servo position
// Note depending upon your design you need to modify the pos value or the servo motor might not work as expected

char command;

void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  Serial.println("Bluetooth Control Mode!");

  // turn on servo
  myservo.attach(9); // attaches the servo object on digitalpin 9
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
}

void loop()
{
  int Right_Value = digitalRead(RIGHT);
  int Left_Value = digitalRead(LEFT);
  command = Serial.read();
  Serial.print("RIGHT");
  Serial.println(Right_Value);
  Serial.print("LEFT");
  Serial.println(Left_Value);

  if ((Right_Value == LOW) && (Left_Value == LOW) && ((command == 'F') || (command == 'L') || (command == 'R') || (command == 'G') || (command == 'I')))
  {
    back();
  } else if ((Right_Value == HIGH) && (Left_Value == LOW) && ((command == 'F') || (command == 'L') || (command == 'R') || (command == 'G') || (command == 'I'))) 
  {
    left();
  } else if ((Right_Value == LOW) && (Left_Value == HIGH) && ((command == 'F') || (command == 'L') || (command == 'R') || (command == 'G') || (command == 'I'))) 
  {
    right();
  } else if ((command == 'F'))
  {
    forward();
  } else if ((command =='L'))
  {
    left();
  } else if ((command == 'R'))
  {
    right();
  } else if ((command == 'B'))
  {
    back();
  } else if ((command == 'G'))
  {
    forward_left();
  } else if ((command == 'I'))
  {
    forward_right();
  } else if ((command == 'H'))
  {
    back_left();
  } else if ((command == 'J'))
  {
    back_right();
  } else if ((command =='S'))
  {
    Stop();
  } else
  {
    Stop();
  }

   switch (command) {
      case 'L': //to move car in left direction
        myservo.write(135);
        break;
      case 'R': //to move car in right direction
        myservo.write(-25);
        break;
      case 'G': //to move car in forward left direction
        myservo.write(135);
        break;
      case 'I': //to move car in forward right direction
        myservo.write(-25);
        break;
      default:
        myservo.write(pos);
    }
}

void forward()
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void back()
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void left()
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void right()
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void Stop()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  myservo.write(pos);
}

void forward_left()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void forward_right()
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(0);
  motor4.run(RELEASE);
}

void back_left()
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void back_right()
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}
