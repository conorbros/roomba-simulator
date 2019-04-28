#/bin/bash

test_num=0
REPORT_FILE=test_report.txt

echo "Test run starting at $(date)"

#==============================================================================
#	Commands available in the Simulation
#==============================================================================

function return_to_base () {
	printf "b "
}

function drop_dust () {
	printf "d "
	printf "${1}"
	printf "${2}"
}

function drop_slime () {
	printf "s "
	printf "${1}"
	printf "${2}"
}

function drop_trash () {
	printf "t "
	printf "${1}"
	printf "${2}"
}
}

function push_device_north () {
	printf "d "
}

function push_device_west () {
	printf "j "
}

function push_device_south () {
	printf "k "
}

function push_device_east () {
	printf "l "
}

function set_delay () {
	printf "m${1}"
}

function set_time_out () {
	printf "o${1} "
}

function toggle_device_moving () {
	printf "p "
}

function quit () {
	printf "q "
	printf "q "
}

function reset () {
	printf "r "
}

function display_help_screen () {
	printf "? "
}

function loop () {
	if (( $# >= 1 )) && (( $1 > 0 ))
	then
		for (( i = 0; i < $1; i++ ))
		do
			printf "!"
		done
	else
		printf "!"
	fi
}

function enter () {
	printf "${1} "
}

function setup_rubbish () {
	enter "${1}"
	enter "${2}"
	enter "${3}"
}

#========================================================================
#	Run a single test.
#========================================================================

function run_test () {
	(( test_num ++ ))
	echo "Test    : ${test_num}"
	echo "Category: ${category}"
	echo "Details : ${details}"
	echo "Expect  : ${expect}"

	read -p "Press r to run the test or s to skip..." run_or_skip

	if [ "${run_or_skip}" == "r" ]
	then
		echo ${cmd} | ./zdj2
		read -p "Did the test pass or fail (p/f)? " result
		echo "Test ${test_num}: ${result}" >>${REPORT_FILE}
	fi
}

#==============================================================================
category="Setup simulation"
details="Status display and input window"
expect="Status display contains student number, robot direction, battery life, timer, robot weight and rubbish available"

cmd=$(
	enter 1
	loop 20
)

run_test

#==============================================================================
category="Setup simulation"
details="Sets up the terminal, displays robot and 50 dust, 5 slime and 5 trash"
expect="Status display, robot in the middle, 50 dust, 5 slime and 5 trash"

cmd=$(
	setup_rubbish 50 5 5
	loop 20
	reset
)

run_test

#==============================================================================
category="Set robot moving"
details="Sets up the terminal and sets the robot to move"
expect="The robot to move straight downwards and bounce off the wall"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	reset
)

run_test

#==============================================================================
category="Robot picks up dust, slime and trash"
details="Drop 1 dust, 1 slime and 1 trash and test robot picks it up"
expect="Robot picks up the rubbish and this is reflected in the status display and the robot's weight increases"

middleYPos = $LINES/2
middleXPos = $COLUMNS/2

cmd=$(
	setup_rubbish 0 0 0
	drop_dust middleXPOS middleYPos-15
	drop_slime middleXPOS middleYPos-17
	drop_trash middleXPOS middleYPos-25
	toggle_device_moving
)

run_test

#==============================================================================
category="Robot battery decreases"
details="Robot battery decreases at a rate of 1% per second when the robot is moving"






