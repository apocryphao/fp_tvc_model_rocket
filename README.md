# THRUST VECTOR CONTROL - MODEL ROCKET 

Current transitioning control system model from simulink into ROS 2 and Gazebo for Software in the loop simulations.

## Control System
The point of this project is to use thrust vector control from motor gimballing to control a rocket for stability. The goal is to launch the model rocket on a small angle and see if it can straighten itself upwards.

### Diagram
<img width="1421" height="397" alt="image" src="https://github.com/user-attachments/assets/6e030a0c-b121-4b0f-a5fc-4e139b189b36" />

### Simulink Model
<img width="1619" height="591" alt="image" src="https://github.com/user-attachments/assets/25d72e75-9ecc-4da6-9db4-c5a772497ddb" />
5DOF variable mass control system with quaternion attitude estimation.

### Attitude Estimation 
<img width="1627" height="384" alt="image" src="https://github.com/user-attachments/assets/d1819a1d-6d8f-47ac-9838-977b5bf2fab5" />
The attitude estimation strategy for this project revolves around using quaternions to turn into axis angles and finding the torque needed on the engine to fix the given error. 

#### Quaternion Error
<img width="1022" height="406" alt="image" src="https://github.com/user-attachments/assets/831faf5c-a557-4637-a597-cbf25ec799a7" />
The error quaternion is found through subtracting the measured quaternion (from the gyroscope in the IMU and converting euler -> quaternion) from the reference/desired quaternion. Using hamilton product / quaternion multiplication, we can get the error quaternion from multiplying reference and conjugate of measured quaternion. Notice however the desired_q is not just [1 0 0 0] or in otherwards facing straight up. This is because the reference frame of the 3dof or 6dof does NOT align with rockets but follows aircraft standards. 



Notice the direction of X (nose of the rocket) and Z. To counteract this, I added an initial angle of pi/2 in the pitch to start the x axis facing up, in other words changing the rocket from facing sideways to upwards. As such the reference quaternion also takes that trasnformation into account, resulting in the seen q_desired.

#### Swing Twist Decomposition 
<img width="1786" height="503" alt="image" src="https://github.com/user-attachments/assets/20ceabe7-c9bc-4f3c-9ebf-024dd584584e" />
Before we start converting the quaternion error into angles that we can feed into a controller, it is good to split the error into swing and twist, and take the swing quaternion as the new real error. This is because for this project, My gimbal mechanism has 2 servos and as such can only control 2 axis of rotations and CANNOT control roll. With this decomposition technique, we can find the angle rotation around one axis as twist, and **everything else** will be the swing. This means selecting rotation around the x axis for the twist, we can extract the swing which is everything but the angle around x, which is the one rotation we cannot perform. 


#### Quaternion to Axis Angle
<img width="1650" height="415" alt="image" src="https://github.com/user-attachments/assets/57e2400b-22bc-44da-8308-f2d3b87213ad" />
Axis angle is a way of demonstrating a singular or a set of infinite many transformations as 1 vector. Split into 4 parts, [tetha, v1, v2, v3], axis angle says that with a unit vector (v1, v2, v3), we can make a new axis that goes through the origin, and have a rotation around that axis to explain a transformation. This is a great alternative to euler angles for our purposes because the calculation from quaternion to axis angle has much less trigonometry than converting to euler.

### Controller
<img width="1505" height="443" alt="image" src="https://github.com/user-attachments/assets/be565067-58b8-42b4-9365-0feca1d3e4f8" />
The controller is quite bare bones, using a cascade control system (albeit not very complex, and just enough to be considered cascade(?)). Using a technique popular in quadcopter drone control systems of turning angle error into rate error with a p gain, we can subtract away the measured angular velocity from the gyrscope, giving us a small nested loop. 

With the new measured angular velocity error, we can finally feed it into PID controllers (note angular velocity error around x axis not having a controller because we cannot control roll as mentioned earlier). At the time of writing, the gain tuning is limited to Ziegler-Nichols method of having I and D gains at 0, to find P value for oscillation, and slowly bringing in D and then I gains. With the actual rocket and actuation design still being developed, the rigour in the tuning is set to another time. 

Feeding angular velocity into PID and getting torque might seem a bit strange. This is because that intitution is correct, getting torque from rate doesn't work like that normally. However, notice that the input is not angular velocity but is instead angular velocity *error*. This is confusing, especially with error already being used often in the control system everywhere, but remember this is the error from the angular velocity from p gain **subtracted** by measured angular velocity. w_error - w_measured. This is not angular rate, but is instead angular rate error which from the understanding of the euler torque to angular velocity and acceleration gives us the feasibility of outputting torque.

### Actuator Model 
<img width="1512" height="313" alt="image" src="https://github.com/user-attachments/assets/c25fa48f-c735-47e8-a5a2-5fc5267128a0" />
The actuator model is current bare bones as the real life thrust vector mount is still in development as mentioned above. There is a bunch of blocks but all this is, is to give angle limits, angle rate limits and a small delay. I've tried second order nonlinear actuator block but I am still quite new to modelling actuators so I've stuck with this for now to focus on other parts. Because the actuator characteristics and restricts are seen in the gimbal mount, the approach was to convert from torque into gimbal angles, put in the saturation block and the others, then convert back to torque to feed into the plant. This unwieldy sub system is ok to have for now because in the code none of this will be there. 

### Forces and Moments
<img width="1556" height="657" alt="image" src="https://github.com/user-attachments/assets/231c5c34-d748-457c-9f9a-e8f380bfccf4" />
Simple section on bringing in the torque and the rocket motor thrust to feed into the plant. 

### Inertia and Mass
<img width="1556" height="657" alt="image" src="https://github.com/user-attachments/assets/1c900a1c-fa40-4c24-b42f-0cbd09945cc5" />
The Inertia matrix is built from heavily simplfying the rocket body into tubes and using some common equations to build the inertia matrix. In the comming future as the rocket gets developed further, an accurate Iyy (rocket is assumed symmetric so Izz aso) will be exported from the software Open Rocket and converted to a loop up table for a higher quality Inertia matrix as it is extremely crucial for gimballing an rocket motor. The mass takes into account that the burning of the motor decreases the mass. 





