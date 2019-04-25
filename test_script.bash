#/bin/bash

test_num=0
REPORT_FILE=test_report.txt

echo "Test run starting at $(date)"

#==============================================================================
#	Commands available in the Simulation
#==============================================================================

function return_to_base(){
	printf "b "
}

function drop_dust(){

}

function push_device_north(){
	printf "d "
}

function push_device_west(){
	printf "j "
}

function push_device_south(){
	printf "k "
}

function push_device_east(){
	printf "l "
}

function set_delay(){

}

function set_time_out(){

}

function toggle_device_moving(){
	printf "p "
}





