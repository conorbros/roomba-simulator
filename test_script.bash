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

function quit_simulation () {
	printf "q "
	printf "q "
}

function reset_simulation () {
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
category="Setup terminal"
details="Status display and input window"
expect="Status display contains student number, robot direction, battery life, timer, robot weight and rubbish available"

cmd=$(
	enter 1
	loop 20
	reset 5
)

run_test

#==============================================================================

