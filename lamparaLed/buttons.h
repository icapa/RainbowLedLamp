#ifndef _BUTTONS_
#define _BUTTONS_

#define PULSED_SINGLE_R   1
#define PULSED_SINGLE_G   2
#define PULSED_SINGLE_B   3

#define PULSED_LONG_R   11
#define PULSED_LONG_G   12
#define PULSED_LONG_B   13

#define PULSED_MAGIC  100

void configure_buttons();
int button_loop();


#endif

