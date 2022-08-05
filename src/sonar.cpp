#ifndef SONAR_C
#define SONAR_C

#include "const.h"
#include "sonar.h"
#include "claw.h"
#include <NewPing.h>

NewPing* Sonar::sonar_ptr;

void Sonar::initializeSonar(NewPing* _sonar){
    sonar_ptr = _sonar;
}

float Sonar::getDist(float soundcm){
    float dur = sonar_ptr->ping_median(ITERATIONS);
    float dist = (dur/200)*soundcm;
    return dist;
}

void Sonar::detecting(float soundcm, int targ_base_pos) { //target base position is the estimated position
// the arm should be in to get the treasure

     int distance=-1, distanceL=-1, distanceR=-1, distanceL2=-1, distanceR2=-1;
     int treasure = 0;
     // int curr_base_pos= getBasePos();
     const int targL = targ_base_pos - ANGLE;
     const int targR = targ_base_pos + ANGLE;
     

     while(treasure ==0){
        int base_pos = Claw::baseRotate(targ_base_pos, 90);
        distance = getDist(soundcm);

        if (distance < 18){
            //Robot stops moving (wheel speed zero) 
            if (targL>=LEFTMOST) {
                base_pos = Claw::baseRotate(targL, base_pos);
                distanceL = getDist(soundcm);
            }

            if (targ_base_pos-10>=LEFTMOST) {
                base_pos = Claw::baseRotate(targ_base_pos-10, base_pos);
                distanceL2 = getDist(soundcm);
            }

            if (targ_base_pos+10<=RIGHTMOST)  {
                base_pos = Claw::baseRotate(targ_base_pos+10, base_pos);
                distanceR2 = getDist(soundcm);
            }

            if (targR<=RIGHTMOST) {
                base_pos = Claw::baseRotate(targR, base_pos);
                distanceR = getDist(soundcm);
            }


            if(((distanceL-distance)>= 6 && (distanceR-distance >= 6)) || 
            ((distanceL-distance) >= 6 && (distanceR == -1)) ||
            ((distanceR-distance) >= 6 && (distanceL == -1))) { // it's a potential treasure
                // if( abs(distance-distanceL2)<=7 && abs(distance-distanceR2)<=7){ //it's a treasure
                // rack extends until the IR sensor no longer detects a signal as the idle is between the claw
                // check the hall effect sensor
                int treasure_pos = base_pos;
                if(Claw::bomb() ==1 ){// trasure, claw picks up
                    Claw::ForwardStep(9);
                    Claw::clawPickUp(treasure_pos);
                }
                else{
                    //claw don't pick up
                }

                treasure == 1;
            
                //else{}
            }
            else{

            }
        }

    }

//    if(treasure==1){
//     //robot continues to move
//     delay(1000);
//    }
}

#endif