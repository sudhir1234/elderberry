/**
 * @file fcfutils.h
 * @brief Utility functions for the flight control framework (fcf)
 * @details The core framework file, it starts in the main function, introducing the rogram.  This program has signal handlers for when the user exits abrubtly using ctrl+Z, allowing a graceful shutdown of the software.  The main function also initializes the framework and the modules before running the main loop. Lastly, this file contains the struct that holds the callback functions and source tokens of each device.  

Below are the variables for this file:

 static const char STANDARD = 0;//< Standard callback\n
 static const char PPC = 1;//< Per poll cycle callback\n
 static struct pollfd * fds;//< File descriptor array\n
 static struct fcffd  * fdx;//< File description array\n
 static int nfds;//< Number of file descriptors in arrays\n
 static int fd_array_size;//< Allocated size of file descriptor array, fds\n
 static int run_fc;//< Main loop is running true/false\n

 * @author Team Elderberry
 * @date March 2nd, 2013
 */
#ifndef _FCFUTILS_
#define _FCFUTILS_

#define TRUE             1
#define FALSE            0

/**
 * @brief initialization for fcf data structures
 * @details Takes the global array size into a variable (this array size can be doubled when the array is full) Malloc commands create two arrays; fds and fdx.  The fds array is an array of pollfd pointers(required by the poll function). The fdx array has fcffd pointers(containing other information including callback actions).  The index of these two arrays are matched so the information is accurate and related.
 * @return 0
 */
extern int init_fcf();
/**
 * @brief increases the size of the file descriptor and file description arrays
 * @details Creates two temp structures for the new arrays.  The new arrays size is doubled from the previous ones.  
 * @return -1 Error in realloc command for one of the new arrays
 * @return 0 successfully doubled array-size and copied over old information.
 */
extern int expand_arrays();
typedef void (*pollfd_callback)(int fd_idx);
/**
 * @brief adds file descriptor on tot he end of the array
 * @details Checks to see if the file descriptor arrays are full.  If the arrays are full it calls the expand_arrays() fucntion (this will double the size of the arrays). It adds information to two arrays, the fds and fdx arrays.  The fds array has pollfd pointers (required by the poll system call) and the fdx array has fcffd pointers (required by our framework [containing callback functions and other information])
 * @return index of the last fd
 */
extern int fcf_add_fd(const char*, int, short, pollfd_callback);
/**
 * @brief simply removes a specified file descriptor from the arrays
 * @details If there are no fds in the array, the function errors out. If there are fd's in the arrays they are removed from both the fds and fdx arrays.  
 */
extern int fcf_remove_fd(int);
extern int fcf_remove_fd_by_token(const char *);
extern struct pollfd * fcf_get_fd(int);
/**
 * @brief stops main loop by setting run_fc to 0
 */
extern void fcf_stop_main_loop(void);
/**
 * @brief starts main loop by setting run_fc to 1
 */
extern void fcf_start_main_loop(void);

/**
 * @brief Main function for framework
 * @details Prints the licensing information, and software version number.  It contains the signal handler for graceful shutdown should the user CTRL-C out of the program. It then initializes the framework and runns the polling loop.
 * @return EXIT_SUCCESS
 * @return EXIT_FAILURE
 */
extern int main(int argc, char *argv[]);

/**
 * @brief polls file descriptors for changes.
 * @details While run_fc is 1 (controlled by fcf_stop_main_loop and fcf_start_main_loop).  The poll function is a system call [poll(array_of_fds, number_of_fds, negative_int) the negative integer indicates no timeout, if timeout is desired we recommend using timerfds].  The loop performs error checking, cycles through the array of fds whos r-events have changed.  We only loop through the arrays after a change has been detected.  After a change is detected and identified, the fd's callback function is called.
 * @return -1 ERROR
 * @return 0 upon success
 */
extern int fcf_run_poll_loop();

#endif
