#!/bin/bash

echo $LINES
echo $COLUMNS


#==============================================================================
#	Operations available in the robot cleaner simulation.
#==============================================================================

function enter () {
	printf "${1} "
}

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
	printf "v "
	printf "${1} "
	printf "${2} "
	printf "${3} "
}

function reset () {
	printf "r "
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
test_item="2"
category="Setup simulation"
expect="Status display contains student number, robot direction, battery life, timer, robot weight and rubbish available"

cmd=$(
	setup_rubbish 0 0 0
	set_time_out 3
)

#run_test

#==============================================================================
test_item="3"
category="Command Input area"
expect="Command input area should be two rows at the bottom of the screen"

cmd=$(
	setup_rubbish 0 0 0
	set_time_out 3
) 

#run_test

#==============================================================================
test_item="4"
category="Border lines"
expect="The terminal window should be outlined by a border, vertical by '|' characters, horizontal by '-' characters and corners by '+' characters"

cmd=$(
	setup_rubbish 0 0 0
	set_time_out 3
)

#run_test

#==============================================================================
test_item="5"
category="Robot Vacuum"
expect="The robot vacuum should be in the centre of the screen, represented by 9x9 polygon of '@' characters"

cmd=$(
	setup_rubbish  0 0 0 
	set_time_out 3
)

#run_test

#==============================================================================
test_item="6.i"
category="Device in motion"
expect="The device should move directly downwards upon the P command being pressed"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	set_time_out 5
)

#run_test

#==============================================================================
test_item="6.ii, 6.iii"
category="Device collision"
expect="The device should pause for a time slice and turn a random angle between 30 and 60 degrees when it collides with wall or the charging station"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	set_time_out 20
)

#run_test

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
	set_time_out 5
)

#run_test

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
	set_time_out 5
)

#run_test

#==============================================================================
test_item="7.i"
category="Device battery"
expect="The device has an initial battery of 100, and it decreases at a rate of 1% per second, when this test times out the battery should be at 90%"

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	set_time_out 10
)

#run_test

#==============================================================================
test_item="7.iii"
category="Device battery should not be under 0 or over 100"
expect="The device battery should be set to 50, 100 and 0 in that order"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_battery 50
	loop 70
	set_robot_battery 150
	loop 70
	set_robot_battery -10
	set_time_out 7
)

#run_test

#==============================================================================
test_item="8.i , 8.ii, 8.iii"
category="Charging station"
expect="The device should be represented by a 9x3 rectangle of '#' characters, positioned in the middle along the top border"

cmd=$(
	setup_rubbish 0 0 0 
	set_time_out 3
)

#run_test

#==============================================================================
test_item="8.iv, 8.v"
category="Charging station collision"
expect="The device should not overlap with the charging station and bounce off it as if it was a wall when not in return to base mode"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_location_direction 0 0 0
	toggle_device_moving
	set_time_out 10
)

#run_test

#==============================================================================
test_item="9.i"
category="Return to base mode when battery below 25%"
expect="When the device's battery goes below 25% it should head towards the charging station"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_location_direction 50 50 0
	loop 5
	toggle_device_moving
	loop 60
	set_robot_battery 27
	set_time_out 20
)

#run_test

#==============================================================================
test_item="9.i"
category="Return to base mode when weight is above 45g"
expect="When the device's weight goes above 45g it should head towards the charging station"

cmd=$(
	setup_rubbish 0 0 0
	set_robot_location_direction 50 50 0
	loop 5
	toggle_device_moving
	loop 60
	set_robot_weight 50
	set_time_out 20
)

#run_test

#==============================================================================
test_item="9.ii"
category="When in return to base, device passes over rubbish even if it has space to collect"
expect="The device does not collect rubbish when in return to base mode, even if there is space. When the devices collides with the station it should enter docked mode."

cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving 
	loop 60
	set_robot_weight 46
	set_time_out 15
)

#run_test

#==============================================================================
test_item="9.ii, 9.iii"
category="When in return to base, device passes over rubbish even if it has space to collect"
expect="The device does not collect rubbish when in return to base mode, even if there is space. When the devices collides with the station it should enter docked mode."

cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving 
	loop 60
	set_robot_weight 46
	set_time_out 15
)

#run_test

#==============================================================================
test_item="9.iv"
category="When the device is docked, DOCKED must be displayed in the command area, the battery indicator must show it is recharging, the robot remains docked until it is fully recharged, and it should move away from the station as per normal collision detection."
expect="DOCKED to be displayed, battery indicator shows charging, device remains docked until fully charged, leaves dock by turning away from it."

cmd=$(
	setup_rubbish 0 0 0
	toggle_device_moving
	loop 40
	set_robot_battery 30
	return_to_base
	set_time_out 15
)

#run_test

#==============================================================================
test_item="10"
category="Battery fully discharged"
expect="a rectangle to be placed in the centre of the screen with a simulation over message, leaves existing images in place, gives option of either reset or quit, everything should remain frozen."

cmd=$(
	setup_rubbish 500 5 2
	set_robot_location_direction 0 30 0
	toggle_device_moving
	set_robot_battery 4
	loop 50
	quit 
)

#run_test

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
	set_time_out 5
)

#run_test

#==============================================================================
test_item="11.ii, 11.iii"
category="Robot turns off pump and returns to base when it reaches above 45, will collect until it reaches 45"
expect="Robot turns off pump and returns to base when it reaches above 45, will collect until it reaches 45"


cmd=$(
	setup_rubbish 1000 10 5
	toggle_device_moving
	set_time_out 20
)

run_test

#==============================================================================
test_item="12.i"
category="Dust has a mass of 1g, slime has a mass of 5g and trash has a mass of 20g"
expect="Picking up dust adds 1g to the weight, slime: 5g and trash: 20g"

cmd=$(
	setup_rubbish 0 0 0
	drop_dust 
)










