// 0 Is straight down, 90 is horizontal, 180 is straight up
unsigned int tilt_angle = 0;
// RPM (rotaions per minute)
unsigned int fly_speed = 0;

int TILT_CHANGE_POS = 10;
int TILT_CHANGE_NEG = -10;

int FLY_CHANGE_POS = 50;
int FLY_CHANGE_NEG = -50;

// Robot Map
// =================
// Motor ports
unsigned short M_PORT_1 = 1;
unsigned short M_PORT_2 = 2;
unsigned short M_PORT_3 = 3;
unsigned short M_PORT_4 = 4;
unsigned short M_PORT_5 = 5;
unsigned short M_PORT_6 = 6;
unsigned short M_PORT_7 = 7;
unsigned short M_PORT_8 = 8;
unsigned short M_PORT_9 = 9;
unsigned short M_PORT_10 = 10;

// Analog ports
unsigned short A_PORT_1 = 1;
unsigned short A_PORT_2 = 2;
unsigned short A_PORT_3 = 3;
unsigned short A_PORT_4 = 4;
unsigned short A_PORT_5 = 5;
unsigned short A_PORT_6 = 6;
unsigned short A_PORT_7 = 7;
unsigned short A_PORT_8 = 8;

// Digital ports
unsigned short D_PORT_1 = 1;
unsigned short D_PORT_2 = 2;
unsigned short D_PORT_3 = 3;
unsigned short D_PORT_4 = 4;
unsigned short D_PORT_5 = 5;
unsigned short D_PORT_6 = 6;
unsigned short D_PORT_7 = 7;
unsigned short D_PORT_8 = 8;
unsigned short D_PORT_9 = 9;
unsigned short D_PORT_10 = 10;
unsigned short D_PORT_11 = 11;
unsigned short D_PORT_12 = 12;

// Assignments
// ==================
// Drive train
unsigned short DRIVE_FRONT_LEFT = M_PORT_1;
unsigned short DRIVE_FRONT_RIGHT = M_PORT_2;
unsigned short DRIVE_BACK_LEFT = M_PORT_3;
unsigned short DRIVE_BACK_RIGHT = M_PORT_4;

// Tilt system
unsigned short TILT_LEFT = M_PORT_5;
unsigned short TILT_RIGHT = M_PORT_6;

// Flywheel
unsigned short FLYWHEEL = M_PORT_7;


static short last_buttons[44];
short set_tilt_speed = 0;


void setup_motors()
{
	// Talon SR's supposedly use the same PWM signals as the Vex 393 MC29
	motorType[DRIVE_FRONT_LEFT] = tmotorVex393_MC29;
	motorType[DRIVE_FRONT_RIGHT] = tmotorVex393_MC29;
	motorType[DRIVE_BACK_LEFT] = tmotorVex393_MC29;
	motorType[DRIVE_BACK_RIGHT] = tmotorVex393_MC29;
	motorType[TILT_LEFT] = tmotorVex393_MC29;
	motorType[TILT_RIGHT] = tmotorVex393_MC29;
	motorType[FLYWHEEL] = tmotorVex393_MC29;
}

void set_drivetrain_speeds(short left, short right)
{
	// Check for a roughly 10% deadzone on left and right
	if (left < 10 && left > -10)
	{
		left = 0;
	}
	if (right < 10 && right > -10)
	{
		right = 0;
	}
	// Set the motor speeds
	motor[DRIVE_FRONT_LEFT] = left;
	motor[DRIVE_FRONT_RIGHT] = right;
	motor[DRIVE_BACK_LEFT] = left;
	motor[DRIVE_BACK_RIGHT] = right;
}

void set_tilt_motor_speed(short tilt_speed)
{
	motor[TILT_LEFT] = tilt_speed;
	motor[TILT_RIGHT] = -tilt_speed;
}

void set_flywheel_motor_speed(short flywheel_speed)
{
	motor[FLYWHEEL] = flywheel_speed;
}

void map_controller()
{
	// Configure drivetrain
	set_drivetrain_speeds(vexRT[Ch3], vexRT[Ch2]);
	// Configure tilt
	if (!last_buttons[Btn5D] && vexRT[Btn5D])
	{
		set_tilt_speed += TILT_CHANGE_POS;
	}
	if (!last_buttons[Btn6D] && vexRT[Btn6D])
	{
		set_tilt_speed += TILT_CHANGE_NEG;
	}
	// set_tilt_speed is not capped currently. It should
	// always be within the range -127 to 127.
	set_tilt_motor_speed(set_tilt_speed);

	// Save the current button presses so they can be compared
	//later to see if the user just pressed the button or if they
	// are holding it down.
	last_buttons[Btn5U] = vexRT[Btn5U];
	last_buttons[Btn5D] = vexRT[Btn5D];
	last_buttons[Btn6U] = vexRT[Btn6U];
	last_buttons[Btn6D] = vexRT[Btn6D];
	last_buttons[Btn7U] = vexRT[Btn7U];
	last_buttons[Btn7D] = vexRT[Btn7D];
	last_buttons[Btn7L] = vexRT[Btn7L];
	last_buttons[Btn7R] = vexRT[Btn7R];
	last_buttons[Btn8U] = vexRT[Btn8U];
	last_buttons[Btn8D] = vexRT[Btn8D];
	last_buttons[Btn8L] = vexRT[Btn8L];
	last_buttons[Btn8R] = vexRT[Btn8R];
}

task main()
{
	setup_motors();

	while(true)
	{
		map_controller();
		// TODO: Check on if there is a more scientific wait time
		// I just picked 150 off the top of my head, but perhaps see
		// if we can set it to the PWM frequency, or maybe remove it all together.
		sleep(1000/150);
	}
}
