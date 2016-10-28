void resetEncoders() {
	nMotorEncoder(leftWheel1) = 0;
	nMotorEncoder(rightWheel1) = 0;
}

void autonomousInit() {
	//failsafe - ensure robot is properly initialsied
  init();

  //clear the encoders before start of autonomous
	resetEncoders();

  //clear drivebase PID targets to prevent robot from running off anywhere
	l.target = 0;
	r.target = 0;

	startTask(drivebasePID);
}

void deployLift () {
	setWheelSpeed(127);
	wait1Msec(300);
	setWheelSpeed(-127);
	wait1Msec(100);
	SensorValue[claw] = 1;
	wait1Msec(200);
	setWheelSpeed(0);
}

//1==out
void leftStars () {
	deployLift();
	autonomousInit();
	wait1Msec(300);
	addTarget(900,900,127);
	wait1Msec(1600);
	addTarget(0);
	SensorValue[claw] = 0;
	moveLiftAuto(300,127);
	addTarget(-600,-600,127);
	wait1Msec(300);
	addTarget(-300,-1200, 127);
	wait1Msec(1200);
	addTarget(-900,-900,127);
	wait1Msec(500);
	moveLiftAuto(encoderVert, 127);
	wait1Msec(900);
	SensorValue[claw] = 1;
	wait1Msec(400);
	moveLiftAuto(0, 127);
	wait1Msec(100);
	addTarget(600,600,127);
}

void rightStars () {
	deployLift();
	autonomousInit();
	wait1Msec(300);
	addTarget(900,900,127);
	wait1Msec(1600);
	addTarget(0);
	SensorValue[claw] = 0;
	moveLiftAuto(300,127);
	addTarget(-600,-600,127);
	wait1Msec(300);
	addTarget(-1100,-400, 127);
	wait1Msec(1200);
	addTarget(-900,-900,127);
	wait1Msec(500);
	moveLiftAuto(encoderVert, 127);
	wait1Msec(900);
	SensorValue[claw] = 1;
	wait1Msec(400);
	moveLiftAuto(0, 127);
	wait1Msec(100);
	addTarget(600,800,127);
	wait1Msec(1000);
	addTarget(0);
}

void rightCube () {
	deployLift();
	autonomousInit();
	wait1Msec(300);
	addTarget(800,800,127);
	wait1Msec(100);
	SensorValue[claw] = 1;
	wait1Msec(1500);
	SensorValue[claw] = 0;
	addTarget(0);
	setWheelSpeed(0);
	wait1Msec(200);
	moveLiftAuto(300,127);
	addTarget(-550,170, 127);
	wait1Msec(2000);
	addTarget(-700,-700, 127);
	wait1Msec(500);
	moveLiftAuto(encoderVert,127);
	wait1Msec(1000);
	SensorValue[claw] = 1;
	moveLiftAuto(0,127);
	wait1Msec(100);
	addTarget(600,600,127);
	//while(!SensorValue[dgtl7])
	//	delay(5);
	//addTarget(0,0);
	//delay(300);
	//addTarget(0,-700, 127);
	//wait1Msec(500);
	//addTarget(800,800,127);
	//wait1Msec(800);
}

//smack into bar and pipe shot
//void rSCurveAuto () {
//	autonomousInit();
//	startFlywheel(pipeShot); //start to spin up flywheel as we drive across
//	addTarget(800,800,90); //begin to drive forward
//	wait1Msec(900);

//  //S Curve
//	addTargetNoIntegral(600,1000,100);
//	wait1Msec(800);
//	addTargetNoIntegral(1000,600,100);
//	intakeAutonomousIntake = true; //start spinning intake
//	wait1Msec(800);
//	addTargetNoIntegral(1200, 1200, 30); //finish driving straight
//	wait1Msec(500);

//  //shoot the balls
//	intakeAutonomousIndexer = true;
//	intakeAutonomousShoot = true;
//	wait1Msec(500);
//	addTarget(0); //stop the drivebase
//	wait1Msec(2000);

//  //return towards protected zone
//	resetEncoders(); //for some reason, this helps
//	addTarget(0,-450); //swing turn, align paralell with pipe
//	stopFlywheel(); //we don't need the flywheel anymore

//  //stop shooting
//	intakeAutonomousIntake = false;
//	intakeAutonomousIndexer = false;
//	intakeAutonomousShoot = false;

//	wait1Msec(2000);
//	addTarget(0);
//	wait1Msec(200);
//	addTarget(500);
//	wait1Msec(1500);
//	addTarget(800,-0); //swing turn, align to push stacks towards our protected zone
//	wait1Msec(700);

//  //spit out any balls
//	stopTask(intakeControl); //stop intake control task so that the intake can be controlled directly
//	motor[intake] = -127;
//	motor[indexer] = -127;

//	addTarget(800, 800, 90); //drive back towards protected zone to push stax
//	wait1Msec(1300);
//	addTarget(0);
//	wait1Msec(500);
//	addTarget(-800); //reverse back to starting position
//	wait1Msec(1300);

//  //shutdown, stop movement
//	stopTask(drivebasePID);
//	setWheelSpeed(0);

//	startTask(intakeControl); //failsafe - ensure that when usercontrol starts, we aren't without intake
//}
