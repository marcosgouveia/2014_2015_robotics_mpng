/**
 * @file    main_template.cpp
 * @brief   A template for webots projects.
 *
 * @author  Name Surname <nick@alumnos.uc3m.es>
 * @date    2014-07
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;
    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

    _mode = FORWARD;
            // Sensores de la frente
    _distance_sensor[0] = getDistanceSensor("ds0"); //frente
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1"); //frente
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2"); //Izquierda frente
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3"); //Izquierda frente
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds12"); //derecha frente
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds13"); //derecha frente
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds14"); //frente
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds15"); //frente
    _distance_sensor[15]->enable(_time_step);

    _distance_sensor[4] = getDistanceSensor("ds4"); //Izquierda atras
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds5"); //Izquierda atras
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds6"); //atras
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds7"); //atras
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds8"); //atras
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds9"); //atras
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds10"); //derecha atras
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds11"); //derecha atras
    _distance_sensor[11]->enable(_time_step);


}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
        _my_compass->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{

    double ir1_val = 0.0, ir2_val = 0.0, ir13_val = 0.0, ir14_val = 0.0, ir0_val = 0.0, ir15_val = 0.0;

    while (step(_time_step) != -1) {
        // Read the sensors
              ir0_val = _distance_sensor[0]->getValue();
              ir1_val = _distance_sensor[1]->getValue();
              ir2_val = _distance_sensor[2]->getValue();
              ir13_val = _distance_sensor[13]->getValue();
              ir14_val = _distance_sensor[14]->getValue();
              ir15_val = _distance_sensor[15]->getValue();

              cout << "ds1: " << ir1_val << " ds2:" << ir2_val << endl;
              cout << "ds13: " << ir13_val << " ds14:" << ir14_val << endl;
              cout << "ds0: " << ir0_val << " ds15:" << ir15_val << endl;


             _mode = FORWARD;


            if (((ir14_val <100)&& (ir13_val <100)) && ((ir1_val <100)&& (ir2_val <100))){
                _mode = FORWARD;
            }
            else{

                 if (((ir14_val < 150)||(ir13_val < 150)) && ((ir1_val >150)|| (ir2_val >150))){
                    _mode = TURN_RIGHT;
                 }

                 if ((ir0_val > 150)&&(ir15_val < 150)){
                    _mode = TURN_RIGHTMORE;
                 }

                  if (((ir13_val > 150)|| (ir14_val > 150)) && ((ir1_val < 150)|| (ir2_val < 150))){
                _mode = TURN_LEFT;
                 }

                  if ((ir15_val > 150)&&(ir0_val < 150)){
                     _mode = TURN_LEFTMORE;
                  }

                 if ((ir15_val > 150)&&(ir0_val > 150)) {
                _mode = OBSTACLE_AVOID;
                }


            }
        // Send actuators commands according to the mode
        switch (_mode){
            case STOP:
                _left_speed = 0;
                _right_speed = 0;
                break;
            case FORWARD:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                break;
            case TURN_LEFT:
                _left_speed = MAX_SPEED / 20;
                _right_speed = MAX_SPEED;
                break;
            case TURN_LEFTMORE:
                _left_speed = MAX_SPEED / 30;
                _right_speed = MAX_SPEED;
                 break;
            case TURN_RIGHT:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED / 20;
                break;
            case TURN_RIGHTMORE:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED / 30;
                break;
            case OBSTACLE_AVOID:
                _left_speed = -MAX_SPEED /1.0;
                _right_speed = -MAX_SPEED / 20.0;
                break;

            default:
                break;
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}
