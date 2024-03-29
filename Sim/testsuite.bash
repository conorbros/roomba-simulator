#!/bin/bash

y0=$(( $LINES / 2))
x0=$(( $COLUMNS / 2))


#==============================================================================
#	Operations available in the robot cleaner simulation.
#==============================================================================

function enter () {
	printf "${1} "
}

function return_to_base () {	
	printf "b "
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

function push_device_north () {
	for (( i = 0; i < $1; i++))
	do
		printf "i"
	done
}

function push_device_west () {
	for (( i = 0; i < $1; i++ ))
	do 
		printf "l"
	done
}

function push_device_south () {
	for (( i = 0; i < $1; i++ ))
	do
		printf "k"
	done
}

function push_device_east () {
	for (( i = 0; i < $1; i++ ))
	do
		printf "j"
	done
}

function set_delay () {
	printf "m${1} "
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

function set_robot_location_direction () {
	printf "v${1},${2},${3} "
}

function reset () {
	printf "r"
}

function display_help_screen () {
	printf "?"
}

function set_robot_battery () {
	printf "y${1} "
}

function set_robot_weight () {
	printf "w${1} "
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

function setup_rubbish () {
	enter "${1}"
	enter "${2}"
	enter "${3}"
}

#========================================================================
#	Run a single test.
#========================================================================	

function run_test () {
	echo " "
	echo "Test    : ${test_item}"
	echo "Category: ${category}"
	echo "Expect  : ${expect}"
	
	sleep 2
	echo ${cmd} | ./a1_n10009671

}

#==============================================================================
test_item="2, 3, 4, 5, 6.i, 6.iii, 8.i , 8.ii, 8.iii"
category="Setup simulation"
expect="Status display contains student number, robot direction, battery life, timer, robot weight and rubbish available. The terminal window should be outlined by a border, vertical by '|' characters, horizontal by '-' characters and corners by '+' characters. Command input area should be two rows at the bottom of the screen. The robot vacuum should be in the centre of the screen, represented by 9x9 polygon of '@' characters. The device should move directly downwards upon the P command being pressed. The device should be represented by a 9x3 rectangle of '#' characters, positioned in the middle along the top border"

cmd=$(
	setup_rubbish 0 0 0
	loop 70
	toggle_device_moving
	set_time_out 10
)

run_test

#==============================================================================
test_item="6.iv"
category="Toggling device movement"
expect="The device movement is toggled by the P command"

cmd=$(
	setup_rubbish 0 0 0 
	toggle_device_moving
	loop 50
	toggle_device_moving
	loop 50
	toggle_device_moving
	loop 50
	toggle_device_moving
	set_time_out 2
)

run_test

#==============================================================================
test_item="6.v"
category="Device is set back to middle after reset"
expect="The device is reset back to the middle of the screen after reset"

cmd=$(
	setup_rubbish 0 0 0 
	toggle_device_moving
	loop 50
	reset
	setup_rubbish 0 0 0 
	set_time_out 2
)

run_test

#==============================================================================
test_item="7.i"
category="Device battery"
expect="The device has an initial battery of 100, and it decreases at a rate of 1% per second, when this test times out the battery should be at 90%"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	set_time_out 4
)

run_test

#==============================================================================
test_item="7.iii"
category="Device battery should not be under 0 or over 100"
expect="The device battery should be set to 50, 100 and 1 in that order"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_battery 50
	loop 70
	set_robot_battery 150
	loop 70
	set_robot_battery 1
	set_time_out 2
)

run_test

#==============================================================================
test_item="8.iv, 8.v"
category="Charging station collision"
expect="The device should not overlap with the charging station and bounce off it as if it was a wall when not in return to base mode"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_location_direction 70 0 0
	toggle_device_moving
	set_time_out 4
)

run_test

#==============================================================================
test_item="9.i"
category="Return to base mode when battery below 25%"
expect="When the device's battery goes below 25% it should head towards the charging station"

cmd=$(
	setup_rubbish 0 0 0
	loop 5
	toggle_device_moving
	loop 60
	set_robot_battery 25
	set_time_out 4
)

run_test

#==============================================================================
test_item="9.i"
category="Return to base mode when weight is above 45g"
expect="When the device's weight goes above 45g it should head towards the charging station"

cmd=$(
	setup_rubbish 0 0 0
	loop 5
	toggle_device_moving
	loop 60
	set_robot_weight 50
	set_time_out 4
)

run_test

#==============================================================================
test_item="9.ii, 9.iii, 9.iv"
category="When in return to base, device passes over rubbish even if it has space to collect"
expect="The device does not collect rubbish when in return to base mode, even if there is space. When the devices collides with the station it should enter docked mode."

cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving 
	loop 60
	set_robot_weight 46
	set_robot_battery 30
	set_time_out 7
)

run_test

#==============================================================================
test_item="11.i"
category="When the simulation starts and is reset the vacuum's weight is 0g"
expect="When the simulation starts and is reset the vacuum's weight is 0g"


cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving
	loop 100
	reset
	setup_rubbish 1000 10 5
	set_time_out 2
)

run_test

#==============================================================================
test_item="11.ii, 11.iii"
category="Robot turns off pump and returns to base when it reaches above 45, will collect until it reaches 45"
expect="Robot turns off pump and returns to base when it reaches above 45, will collect until it reaches 45"


cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving
	set_time_out 7
)

run_test

#==============================================================================
test_item="12.i"
category="Dust has a mass of 1g, slime has a mass of 5g and trash has a mass of 20g"
expect="Picking up dust adds 1g to the weight, slime: 5g and trash: 20g, total should equal 26"

dust_y=$(( y0 + 10))
slime_x=$(( x0 - 2))
slime_y=$(( y0 + 15))
trash_x=$(( x0 - 5)) 
trash_y=$(( y0 + 25))

cmd=$(
	setup_rubbish 0 0 0
	echo "d${x0},${dust_y}"
	echo "s${slime_x},${slime_y}"
	echo "t${trash_x},${trash_y}"
	toggle_device_moving
	set_time_out 4
)

run_test

#==============================================================================
test_item="13.i, 13.ii, 13.iii, 13.iv, 13.v"
category="Rubbish spawning"
expect="Dust max: 1000, slime max: 10, trash max: 5, trash spawns in random locations on reset. Trash does not overlap other trash, the borders, charging station or robot. The rubbish is immediately collected and added to the robot's weight and removed from the available rubbish count on the status display"

cmd=$(
	setup_rubbish 9999 9999 9999
	loop 100
	reset
	setup_rubbish 1000 10 5 
	loop 100 
	reset
	setup_rubbish 1000 10 5
	loop 100 
	reset
	setup_rubbish 1000 10 5
	loop 100 
	reset
	setup_rubbish 555 5 3
	set_time_out 2
)

run_test

#==============================================================================
test_item="14"
category="demonstrate pixel level collision"
expect="the dust in the corner will not be picked up"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_location_direction 0 0 0 
	echo "d0,0"
	set_time_out 2
)

run_test

#==============================================================================
test_item="15.i"
category="Dropping rubbish"
expect="Rubbish will be dropped at the supplied x, y coordinates. Rubbish will not be dropped when the rubbish limit is reached"

cmd=$(
	setup_rubbish 0 0 0
	echo "d10,10"
	loop 30
	echo "d10,14"
	loop 30
	echo "d10, 16"
	loop 60
	reset
	setup_rubbish 1000 0 0
	loop 30
	echo "d10,10"
	loop 30
	
	reset
	setup_rubbish 0 0 0
	echo "s20,10"
	echo "s20,15"
	loop 30
	reset
	setup_rubbish 0 10 0
	loop 30
	echo "s10,10"
	loop 30
	
	reset
	setup_rubbish 0 0 0
	loop 50
	echo "t30,10"
	loop 50
	echo "t30,20"
	loop 50
	reset 
	setup_rubbish 0 0 5
	loop 50
	echo "t10,10"
	
	set_time_out 3
)

run_test

#==============================================================================
test_item="15.ii"
category="Pushing the device up"
expect="The device moves 3 pixels in each direction. The device does not overlap the borders or the charging station"

cmd=$(
	setup_rubbish 0 0 0
	loop 30
	push_device_north 1
	loop 30
	push_device_north 1
	loop 30
	push_device_north 1
	loop 30
	
	loop 30
	push_device_south 1
	loop 30
	push_device_south 1
	loop 30
	push_device_south 1
	loop 30
	
	loop 30
	push_device_west 1
	loop 30
	push_device_west 1
	loop 30     
	push_device_west 1
	loop 30
	
	loop 30
	push_device_east 1
	loop 30
	push_device_east 1
	loop 30
	push_device_east 1
	loop 30
	
	reset
	setup_rubbish 0 0 0
	push_device_east 100
	loop 10
	push_device_north 100
	loop 10
	push_device_west 100
	
	set_time_out 3
)

run_test


#==============================================================================
test_item="15.ii"
category="Device in return to base reorients after being pushed"
expect="The device in return to base mode reorients after being pushed"

cmd=$(
	setup_rubbish 0 0 0
	return_to_base
	toggle_device_moving
	loop 50
	push_device_east 50
	set_time_out 3
)

run_test

#==============================================================================
test_item="15.iii"
category="Setting delay"
expect="The new time slice delay will be set to the user inputted value"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	set_delay 50
	loop 60
	set_delay 10
	loop 500
	set_delay 25
	loop 120
	set_delay 5
	set_time_out 2
)

run_test

#==============================================================================
test_item="15.iv"
category="Setting the time out period"
expect="The simulation will time out after 2 seconds"

cmd=$(
	setup_rubbish 0 0 0 
	set_time_out 2
)

run_test

#==============================================================================
test_item="15.vi"
category="Resetting the simulation"
expect="The simulation is reset"

cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving
	loop 100
	reset
	setup_rubbish 1000 10 5
	toggle_device_moving
	loop 100
	reset
	setup_rubbish 500 10 5
	set_time_out 2
)

run_test

#==============================================================================
test_item="15.vii"
category="Changing device location and direction"
expect="The device location and direction is set to the supplied x,y and direction"

cmd=$(
	setup_rubbish 0 0 0 
	toggle_device_moving
	loop 50
	echo "v10,10,0"
	loop 70
	echo "v20,20,90"
	set_time_out 2
)

run_test

#==============================================================================
test_item="15.vii"
category="Device will contiune towards base in return to base after being moved"
expect="The device will reorient and carry on its journey to base"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	loop 70
	return_to_base
	loop 60
	echo "v10,10,0"
	set_time_out 3
)

run_test

#==============================================================================
test_item="15.viii"
category="Set the robots weight"
expect="The robot's weight is set to the inputted value, provided it is between 0 and 65"

cmd=$(
	setup_rubbish 0 0 0
	loop 50
	echo "w50"
	loop 50
	echo "w70"
	loop 50
	echo "w-15"
	set_time_out 3
)

run_test

#==============================================================================
test_item="15.ix"
category="Set the robot's battery level"
expect="The robot's battery level can be manually set to be between 0 and 100"

cmd=$(
	setup_rubbish 0 0 0
	loop 50
	echo "y50"
	loop 50
	echo "y200"
	set_time_out 3
)

run_test






