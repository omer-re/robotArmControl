
// https://www.dofbot.com/post/arduino-based-4dof-robotic-arm-control
#include <Servo.h>


#define BASE_ANGLE 90
#define STEP 2
#define MARGIN 50
Servo servos[4];

#define ROTATION 0
#define ROTATION_HANDLE A4
#define ROTATION_SERVO 2


#define STRECH 1
#define ARM_STRECH_HANDLE A3
#define ARM_STRECH_SERVO 3

#define RAISE 2
#define ARM_RAISE_HANDLE A2
#define ARM_RAISE_SERVO 4

#define CLAMP 3
#define CLAMP_HANDLE A5
#define CLAMP_SERVO 5

int handlesvalue[]={BASE_ANGLE,BASE_ANGLE,BASE_ANGLE,70}; // reads 0-1023 values
int base_handlesvalue[]={BASE_ANGLE,BASE_ANGLE,BASE_ANGLE,70}; // 

static const uint8_t analog_pins[] = {ROTATION_HANDLE,  ARM_STRECH_HANDLE,  ARM_RAISE_HANDLE,   CLAMP_HANDLE}; 

static const uint8_t digital_pins[] = {ROTATION_SERVO,  ARM_STRECH_SERVO,   ARM_RAISE_SERVO,   CLAMP_SERVO}; 


void setup()
{
  
  Serial.begin(230400); 

  pinMode(ROTATION_HANDLE,INPUT); // rotating base
  pinMode(digital_pins[0],OUTPUT);
  servos[0].attach(digital_pins[0]);

  pinMode(analog_pins[1],INPUT);
  pinMode(digital_pins[1],OUTPUT);
  servos[1].attach(digital_pins[1]);

  pinMode(analog_pins[2],INPUT); // forward arm
  pinMode(digital_pins[2],OUTPUT);
  servos[2].attach(digital_pins[2]);

  pinMode(analog_pins[3],INPUT); // clamp
  pinMode(digital_pins[3],OUTPUT);
  servos[3].attach(digital_pins[3]);
  
  delay(2000);

  Serial.println("ZERO");
  delay(1000);
  Serial.println("DONE ZERO");

}

int new_angle, new_angle2;
void loop()

{


//  for (int i=0; i<4;i++){
//    if ((servos[i].read()<5) || (servos[i].read()>175)) {
//      Serial.print("ANGLE OUT OF BOUNDERIES  "); Serial.print(servos[i].read()) ;  Serial.print("  "); Serial.println(i);
//      continue;
//      }

     // A0 should be opposite directions
      handlesvalue[ROTATION] = analogRead(ROTATION_HANDLE);
      new_angle = map(handlesvalue[ROTATION], 0, 1023, 175, 5);
      servos[ROTATION].write(new_angle);      
      
      handlesvalue[STRECH] = analogRead(ARM_STRECH_HANDLE);
      new_angle = map(handlesvalue[STRECH], 0, 1023, 5, 175);
      servos[STRECH].write(new_angle);      
      
      handlesvalue[RAISE] = analogRead(ARM_RAISE_HANDLE);
      new_angle = map(handlesvalue[RAISE], 0, 1023, 40, 180);
      servos[RAISE].write(new_angle);      
      
      
      handlesvalue[CLAMP] = analogRead(CLAMP_HANDLE);
      new_angle = map(handlesvalue[CLAMP], 0, 1023, 95, 40);
      servos[CLAMP].write(new_angle);      
          
      
//    delay(5);
//  }
}
