/*
 * auto generated fcf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#include "testIMU.h"
#include "testLoggerDisk.h"
#include "testLoggerScreen.h"
#include "fcfutils.h"


/***************	CODE GENERATED SPACE	**************/

void fcf_init() {
	// Calls all init functions
	init_theo_imu();
	init_diskLogger();

	// Fetch all FileDescriptors
	//fcf_get_fd_structure(&fds, &fdx, &nfds);
}

void fcf_callback_gyr(char *buff, int length) {
	screenLogger_getMessage("gyr", buff, length);
	diskLogger_getMessage("gyr", buff, length);
}


void fcf_callback_acc(char *buff, int length) {
	screenLogger_getMessage("acc", buff, length);
	diskLogger_getMessage("acc", buff, length);
}


/****************	END CODE GENERATED SPACE	*****************/


int fcf_main_loop_run() {
	return run_poll_loop();
}

