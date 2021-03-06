#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl8,  liftBumper,     sensorTouch)
#pragma config(Sensor, dgtl9,  claw,           sensorDigitalOut)
#pragma config(Sensor, dgtl10, lock,           sensorDigitalOut)
#pragma config(Sensor, dgtl11, liftEnc,        sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftWheel1,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           leftLift1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightLift1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftLiftMid,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftWheel2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightWheel2,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightLiftMid,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightWheel1,   tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "JonLib/PID.h"
#include "JonLib/drivebase.h"
#include "JonLib/autonomous.h"

int encoderVert = 1000;

void setLeftWheelSpeed (int speed) {
	motor[leftWheel1] = speed;
	motor[leftWheel2] = speed;
}

void setRightWheelSpeed (int speed) {
	motor[rightWheel1] = speed;
	motor[rightWheel2] = speed;
}

void drivebase (int left, int right, int deadbands) {
	setLeftWheelSpeed(abs(left)<deadbands?0:left);
	setRightWheelSpeed(abs(right)<deadbands?0:right);
}

void lift(int power){
	motor[leftLift1] = power;
	motor[leftLift2] = power;
	motor[leftLiftMid] = power;
	motor[rightLift1] = power;
	motor[rightLift2] = power;
	motor[rightLiftMid] = power;
}


int liftSpeed = 0;
int liftTarget = 0;
task autonLiftControl () {
	while(abs(SensorValue[liftEnc]-liftTarget)>10 || liftTarget==0&&!SensorValue[liftBumper]) {
		lift(sgn(liftTarget-SensorValue[liftEnc])*abs(liftSpeed));
		delay(5);
	}
	lift((SensorValue[liftEnc]<encoderVert)*!SensorValue[liftBumper]*10);
	stopTask(autonLiftControl);
}

void moveLiftAuto(int target, int speed) {
	liftSpeed = speed;
	liftTarget = target;
	startTask(autonLiftControl);
}

void init() {
	while(!SensorValue[liftBumper]) {
		lift(-25);
		delay(25);
	}
}

void pre_auton() {}

#include "autonomousPrograms.h"
task autonomous() {
	rightStars();
}

task usercontrol() {

	//init();

	while (true) {
		drivebase(vexRT(Ch3), vexRT(Ch2), 10);


		//if(vexRT(Btn5D) && !SensorValue[liftBumper])
		//liftPID.target = liftPID.target-10<0?0:liftPID.target-10;
		//else if(vexRT(Btn5U))
		//liftPID.target+=10;

		if(vexRT(Btn5D) && !SensorValue[liftBumper])
			lift(-127);
		else if(vexRT(Btn5U))
			lift(127);
		else
			lift((SensorValue[liftEnc]<encoderVert)*!SensorValue[liftBumper]*10);

		if(SensorValue[liftBumper]) {
			SensorValue[liftEnc] = 0;
		}


		if(vexRT(Btn6U)) {
			SensorValue[claw] = !SensorValue[claw];
			while(vexRT(Btn6U)) { delay(5); }
		}
		//displayLCDNumber(1,0, SensorValue[liftEnc]);
		delay(25);
	}
}
