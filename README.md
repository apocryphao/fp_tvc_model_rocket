# THRUST VECTOR CONTROL - MODEL ROCKET 

Current transitioning control system model from simulink into ROS 2 and Gazebo for Software in the loop simulations.

## Control System
The point of this project is to use thrust vector control from motor gimballing to control a rocket for stability. The goal is to launch the model rocket on a small angle and see if it can straighten itself upwards.
### Simulink Model
<img width="1619" height="591" alt="image" src="https://github.com/user-attachments/assets/25d72e75-9ecc-4da6-9db4-c5a772497ddb" />
5DOF variable mass control system with quaternion attitude estimation.

### Attitude Estimation 
<img width="1627" height="384" alt="image" src="https://github.com/user-attachments/assets/d1819a1d-6d8f-47ac-9838-977b5bf2fab5" />

#### Quaternion Error
<img width="1022" height="406" alt="image" src="https://github.com/user-attachments/assets/831faf5c-a557-4637-a597-cbf25ec799a7" />
The error quaternion is found through subtracting the measured quaternion (from the gyroscope in the IMU and converting euler -> quaternion) from the reference/desired quaternion. Notice however the desired_q is not just [1 0 0 0] or in otherwards facing straight up. This is because the reference frame of the 3dof or 6dof does NOT align with rockets but follows aircraft standards.

<img width="376" height="283" alt="image" src="https://github.com/user-attachments/assets/9e4fba0d-ca25-4d87-af69-c497ee08174c" />
Notice the direction of X (nose of the rocket) and Z. To counteract this, I added an initial angle of pi/2 in the pitch to start the x axis facing up, in other words changing the rocket from facing sideways to upwards. As such the reference quaternion also takes that trasnformation into account, resulting in the seen q_desired.


