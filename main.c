#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Insert other functions here, or include header files

void setup () {
    // Insert setup logic here
}

void loop() {
    // Insert loop logic here.
}

int main() {
    setup_screen();
    setup();

    while ( /* Insert termination conditions here */ ) {
        loop();
        timer_pause( /* Insert delay expression here. */ );
    }

    return 0;
}