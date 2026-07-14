#include "include/controller.h"
#include "include/state_estimator.h"



int main() {
    Quaterniond example_q = Quaterniond(0, 0.73758, 0, 0.67526); //pi/2 + 0.087 rad on pitch. For testing

    double p_gain = 1;
    Eigen::Vector3d PID_gains(1, 0, 0);
    double sampling_time = 0.005;

    
    return 0;
}       