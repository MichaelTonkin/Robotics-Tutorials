// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

#include "encoders.h"

// Class to track robot position.
class Kinematics_c {
  private:
  const int HALF_X_ROTA = 170; //half a wheel rotation approximately 5cm
  const int FULL_X_ROTA = HALF_X_ROTA * 2;
  const int THETA_ROTA = 1000;

  //measuring the distance from our starting point in 5cm increments
  int distance_x = 0;
  int distance_y = 0;

  int theta;
  
  public:
  
    // Constructor, must exist.
    Kinematics_c() {

    } 

    void initialize()
    {    
      setupEncoder0();
      setupEncoder1();
    }

    // Use this function to update
    // your kinematics
    void update() 
    {
      //if one motor is increasing and the other is stable or decreasing, we are doing rotation
      //otherwise we are doing forward motion
      if (isBotRotating())
      {
        updateTheta();
      }
      else
      {
        updateDistanceX();
      }
      //boundCountE();
    }

    void updateTheta()
    {
       
    }

    //measure distance travelled
    int starting_x = HALF_X_ROTA;
    void updateDistanceX()
    {
      int new_x;

      new_x = starting_x - ((count_er + count_el) / 2);

      if (new_x <= 0)
      {
        distance_x += 1;
        count_er = 0;
        count_el = 0;
      }
    }

    int last_el = 0;
    int last_er = 0;
    bool isBotRotating()
    {
      if (count_er > last_er && count_el < last_el)
      {
        last_el = count_el;
        last_er = count_er;
        Serial.println("turning left");
        return true;
      } 
      else if (count_el > last_el && count_er < last_er)
      {
        last_el = count_el;
        last_er = count_er;
        Serial.println("turning right");
        return true;
      }     
      else
      {
        return false;
      }
    }

};

/*

      Serial.print("new x ");
      Serial.println(new_x);
      Serial.print("start x ");
      Serial.println(starting_x);
      Serial.println((count_er + count_el) / 2);
      Serial.println(count_er);
      Serial.println(count_el);
      */

#endif
