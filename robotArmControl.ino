
// https://www.dofbot.com/post/arduino-based-4dof-robotic-arm-control
#include <ESP32Servo.h>


#define BASE_ANGLE 90
#define STEP 2
#define MARGIN 50
Servo servos[4];

int handlesvalue[]={BASE_ANGLE,BASE_ANGLE,BASE_ANGLE,70}; // reads 0-1023 values
int base_handlesvalue[]={BASE_ANGLE,BASE_ANGLE,BASE_ANGLE,70}; // 
static const uint8_t analog_pins[] = {A0,A1,A2,A3,A4};

void init_array(){
  for (int i=0;i<4;i++){
    base_handlesvalue[i]=analogRead(analog_pins[i]);
    Serial.print("base ");Serial.print(i);Serial.print("  is: ");Serial.println(base_handlesvalue[i]);
  }
    for (int i=0;i<4;i++){
      servos[i].write(BASE_ANGLE);
  }
  servos[3].write(70);
}

void setup()
{
  
  Serial.begin(230400); 

  pinMode(A0,INPUT); // rotating base
  pinMode(4,OUTPUT);
  servos[0].attach(4);

  pinMode(A1,INPUT);
  pinMode(5,OUTPUT);
  servos[1].attach(5);

  pinMode(A2,INPUT); // forward arm
  pinMode(6,OUTPUT);
  servos[2].attach(6);

  pinMode(A3,INPUT); // clamp
  pinMode(7,OUTPUT);
  servos[3].attach(7);
  
  delay(2000);

  Serial.println("ZERO");
  Serial.println("ZERO");
  init_array();
  delay(1000);
  Serial.println("DONE ZERO");

}

int new_angle, new_angle2;
void loop()

{

  handlesvalue[0] = analogRead(A0);
  handlesvalue[1] = analogRead(A1);
  handlesvalue[2] = analogRead(A2);
  handlesvalue[3] = analogRead(A3);

  bool hold_clamp=0;
  for (int i=0; i<4;i++){
//    if ((servos[i].read()<5) || (servos[i].read()>175)) {
//      Serial.print("ANGLE OUT OF BOUNDERIES  "); Serial.print(servos[i].read()) ;  Serial.print("  "); Serial.println(i);
//      continue;
//      }
      handlesvalue[i]=analogRead(analog_pins[i]);
     Serial.print("i=  ");Serial.print(i);Serial.print("  ");
     Serial.print("handlesvalue[i]:  ");Serial.print(handlesvalue[i]);Serial.print("  ");
     Serial.print("servos[i].read():  ");Serial.print(servos[i].read());Serial.print("  ");
     // A0 should be opposite directions
     if (i==0){
           if (handlesvalue[i]>(base_handlesvalue[i]+MARGIN)){
            new_angle=servos[i].read()-STEP;
            if (servos[i].read()<5) new_angle=5;
            servos[i].write(new_angle);
            
        }
         else if (handlesvalue[i]<(base_handlesvalue[i]-MARGIN)){
            new_angle=servos[i].read()+STEP;
            if (servos[i].read()>175) new_angle=175;

            servos[i].write(new_angle);      
          }
      
      }

      
      // A2 needs a limited range+oppiste direction
     else if (i==2){
           if (handlesvalue[i]>(base_handlesvalue[i]+MARGIN)){
            new_angle=servos[i].read()-STEP;
            if (servos[i].read()<65) new_angle=65;
            servos[i].write(new_angle);
        }
         else if (handlesvalue[i]<(base_handlesvalue[i]-MARGIN)){
            new_angle=servos[i].read()+STEP;
            if (servos[i].read()>177) new_angle=177;

            servos[i].write(new_angle);      
            // A1 moves as a derviative of A2
            servos[1].write(servos[1].read()+(new_angle/2))
          }
      
      }
      
      // A3 (clamp) has a much limited range
     else if ((i==3)){
         if (handlesvalue[i]>(base_handlesvalue[i]+2*MARGIN)){
            new_angle=servos[i].read()+STEP;
            if (servos[i].read()>95) new_angle=95;            
            servos[i].write(new_angle);
        }
         else if (handlesvalue[i]<(base_handlesvalue[i]-2*MARGIN)){
            new_angle=servos[i].read()-STEP;
            if (servos[i].read()<35) new_angle=35;
            servos[i].write(new_angle);      
          }
      
      }
      
        hold_clamp=0;
       Serial.print("new_angle:  ");Serial.println(new_angle);

    }  
//    delay(5);

}
