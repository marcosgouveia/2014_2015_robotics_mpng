/**
 * @file    main_template.cpp
 * @brief   A template for webots projects.
 *
 * @author  Name Surname <nick@alumnos.uc3m.es>
 * @date    2014-07
 */

#include <iostream>
#include <cmath>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT      50
#define MAX_SPEED           50
#define DESIRED_ANGLE   40.0

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;
          Compass * _my_compass;

        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
             TURN_LEFTMORE,
            TURN_RIGHT,
            TURN_RIGHTMORE,
            OBSTACLE_AVOID,
           };

        Mode _mode;

    public:
        // You may need to define your private methods or variables, like
        //  Constructors, helper functions, etc.

        /**
         * @brief Empty constructor of the class.
         */
        MyRobot();
        
        /**
         * @brief Destructor of the class.
         */
        ~MyRobot();

        /**
         * @brief User defined function for initializing and running the template class.
         */
        void run();

         double convert_bearing_to_degrees(const double* in_vector); // Funcion de grados
};
