#include "include/controller.h"


double p_gain; //to turn into angular velocity
Eigen::Vector3d PID_gains;
double sampling_time;

//pid control variables
Eigen::Vector3d integral(0, 0, 0);
Eigen::Vector3d derivative(0, 0, 0);
Eigen::Vector3d prev_error(0, 0, 0);



void controller_init(double input_p_gain, Eigen::Vector3d input_PID_gains, double input_sampling_time) {
    p_gain = input_p_gain;
    PID_gains = input_PID_gains;
    sampling_time = input_sampling_time;
}

Eigen::Vector3d angular_velocity_error(Eigen::Vector3d current_angle_state) {
    return current_angle_state * p_gain;
}

/* implement this with IMU angular velocity data 
Eigen::Vector3d angular_velocity_inner_loop_error(Eigen::Vector3d error, Eigen::Vector3d measured_angular_velocity) {

    return error - measured_angular_velocity;
}
*/

Eigen::Vector3d pid_output(Eigen::Vector3d error) {
    integral = integral + (error * sampling_time);

    derivative = (error - prev_error)/sampling_time;

    prev_error = error;

    return (PID_gains.x() * error) + (PID_gains.y() * integral) + (PID_gains.z() * derivative);
}

Eigen::Vector3d desired_torque(Eigen::Vector3d angular_velocity_inner_loop_error) {
    return pid_output(angular_velocity_inner_loop_error);
}

Eigen::Vector3d control_system_output(Eigen::Vector3d current_angle_states) {
    return desired_torque(angular_velocity_error(current_angle_states));
}