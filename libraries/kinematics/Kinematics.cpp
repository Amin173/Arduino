/*
  Copyright (c) 2016, Juan Jimeno
  Source: http://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
   Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
   Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
   Neither the name of  nor the names of its contributors may be used to
  endorse or promote products derived from this software without specific
  prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORTPPIPI (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include "Arduino.h"
#include "Kinematics.h"
#include "Math.h"

Kinematics::Kinematics(int motor_max_rpm, float wheel_diameter, float wheels_dist, int pwm_bits):
  wheel_diameter_(wheel_diameter),
  circumference_(PI * wheel_diameter_),
  max_rpm_(motor_max_rpm),
  wheels_dist_(wheels_dist),
  //lr_wheels_dist_(lr_wheels_dist),
  pwm_res_ (pow(2, pwm_bits) - 1)
{
}

Kinematics::output Kinematics::getRPM(float linear_x, float linear_y, float angular_z)
{
  //convert m/s to m/min
  float linear_vel_x_mins_ = linear_x * 60;
  float linear_vel_y_mins_ = linear_y * 60;

  //convert rad/s to rad/min
  float angular_vel_z_mins_ = angular_z * 60;
  
  float w=angular_vel_z_mins_;
  float v=sqrt(pow(linear_vel_x_mins_,2)+pow(linear_vel_y_mins_,2));
  
  float w_l=2*v/wheel_diameter_-wheels_dist_*w/wheel_diameter_;
  float w_r=2*v/wheel_diameter_+wheels_dist_*w/wheel_diameter_;
  
  //Vt = ω * radius
  //float tangential_vel_ = angular_vel_z_mins_ * wheels_dist_;
  
  //float x_rpm_ = linear_vel_x_mins_ / circumference_;
  //float y_rpm_ = linear_vel_y_mins_ / circumference_;
  //float tan_rpm_ = tangential_vel_ / circumference_;

  Kinematics::output rpm;

  //calculate for the target motor RPM and direction

  //front-left motor
  rpm.motor1 = w_l;
  //rear-left motor
  //rpm.motor2 = x_rpm_ + y_rpm_ - tan_rpm_;

  //front-right motor
  rpm.motor2 =w_r;
  //rear-right motor
  //rpm.motor4 = x_rpm_ - y_rpm_ + tan_rpm_;

  return rpm;
}

Kinematics::output Kinematics::getPWM(float linear_x, float linear_y, float angular_z)
{
  Kinematics::output rpm;
  Kinematics::output pwm;

  rpm = getRPM(linear_x, linear_y, angular_z);

  //convert from RPM to PWM
  //front-left motor
  pwm.motor1 = rpmToPWM(rpm.motor1);
  //rear-left motor
  pwm.motor2 = rpmToPWM(rpm.motor2);


  return pwm;
}


Kinematics::output Kinematics::getPWM2(int sensorvalue)
{
 
  Kinematics::output pwm;
int angle=sensorvalue-500;
if (abs(angle)>50){
  //front-left motor
  pwm.motor1 = 100;
  //rear-left motor
  pwm.motor2 = 100;
	if (angle>0){
	pwm.inversion1=	0;
	pwm.inversion2=	1;
		
	}
	if (angle<0){
	pwm.inversion1=	1;
	pwm.inversion2=	0;
	}
}
else {
	
	pwm.motor1=0;
	pwm.motor2=0;
	pwm.inversion1=0;
	pwm.inversion2=0;
}
return pwm;
}


Kinematics::velocities Kinematics::getVelocities(int motor1, int motor2)
{
  Kinematics::velocities vel;

  float average_rpm_x = (float)(motor1 + motor2) / 2; // RPM
  //convert revolutions per minute to revolutions per second
  float average_rps_x = average_rpm_x / 60; // RPS
  vel.linear_x = (average_rps_x * wheel_diameter_);// m/s

  float average_rpm_a = (float)(motor2 - motor1) / 2;
  //convert revolutions per minute to revolutions per second
  float average_rps_a = average_rpm_a / 60;
  vel.angular_z =  (average_rps_a * wheel_diameter_)/(wheels_dist_ / 2);

  return vel;
}

//Kinematics::velocities Kinematics::getVelocities(int motor1, int motor2, int motor3, int motor4)
//{
  //Kinematics::velocities vel;

  //float average_rpm_x = (float)(motor1 + motor2 + motor3 + motor4) / 4; // RPM
  //convert revolutions per minute to revolutions per second
  //float average_rps_x = average_rpm_x / 60; // RPS
  //vel.linear_x = (average_rps_x * circumference_); // m/s

  //float average_rpm_y = (float)(-motor1 + motor2 + motor3 - motor4) / 4; // RPM
  //convert revolutions per minute in y axis to revolutions per second
  //float average_rps_y = average_rpm_y / 60; // RPS
  //vel.linear_y = (average_rps_y * circumference_); // m/s

  //float average_rpm_a = (float)(-motor1 + motor2 - motor3 + motor4) / 4;
  //convert revolutions per minute to revolutions per second
  //float average_rps_a = average_rpm_a / 60;
  //vel.angular_z =  (average_rps_a * circumference_) / ((fr_wheels_dist_ / 2) + (lr_wheels_dist_ / 2));

  //return vel;
//}

int Kinematics::rpmToPWM(int rpm)
{
  //remap scale of target RPM vs MAX_RPM to PWM
  return (int)(((float) rpm / (float) max_rpm_) * pwm_res_);
}