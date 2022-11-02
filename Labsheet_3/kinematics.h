// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

#include "encoders.h"

// Class to track robot position.
class Kinematics_c {
  private:
  const int HALF_X_ROTA = 178; //half a wheel rotation approximately 5cm
  const int FULL_X_ROTA = HALF_X_ROTA * 2;
  const int THETA_ROTA = 1000;

  //measuring the distance from our starting point in 5cm increments
  int distance_x = 0;
  int distance_y = 0;

  int theta;
  int theta_direction;
  float r;

  public:
  
    // Constructor, must exist.
    Kinematics_c() {

    } 

    void initialize()
    { 
      r = 4.5;
      theta = 0;
      setupEncoder0();
      setupEncoder1();
    }

    // Use this function to update
    // your kinematics
    void update() 
    {
      if (isBotRotating())
      {
        updateTheta();
      }
      else
      {
        updateDistanceX();
      }
    }

    void updateTheta()
    {
      
      //theta = theta + ((count_el - count_er) / r);
      //Serial.println(theta);     
      if(theta_direction == 1)
      {
        // r =  4.5
        theta += 1;
        Serial.println(theta);
      }
      else if (theta_direction == -1)
      {
        theta -= 1;
        Serial.println(theta);
      }
      else
      {
        theta += 0;
      }
    }

    void resetRotationVals()
    {
      theta = 0;
      count_er = 0;
      count_el = 0;
    }

    void setTheta(int new_theta)
    {
      theta = new_theta;
    }

    void resetKinematics()
    {
      count_er = 0;
      count_el = 0;
      theta = 0;
      distance_x = 0;
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
      if (count_er > last_er && count_el < last_el) //left
      {
        last_el = count_el;
        last_er = count_er;
        theta_direction = -1;
        return true;
      } 
      else if (count_el > last_el && count_er < last_er) //right
      {
        last_el = count_el;
        last_er = count_er;
        theta_direction = +1;
        return true;
      }     
      else
      {
        return false;
      }
    }

  int getDistanceX()
  {
    return distance_x;
  }

  int getTheta()
  {
    return theta;
  }

  void resetDistanceX()
  {
    distance_x = 0;
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
