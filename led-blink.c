/*

Example of programming GPIO from C or C++ using the sysfs interface on
a Raspberry Pi.

Will toggle GPIO24 (physical pin 18) at a 100 millisecond rate for 10
seconds and then exit.

Jeff Tranter <jtranter@ics.com>

*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



 int export_pin(){

// Export the desired pin by writing to /sys/class/gpio/export
 
     int fd = open("/sys/class/gpio/export", O_WRONLY);
     if (fd == -1) {
         perror("Unable to open /sys/class/gpio/export");
         exit(1);
     }

     if (write(fd, "24", 2) != 2) {
         perror("Error writing to /sys/class/gpio/export");
         exit(1);
    }

   return fd;
}



 int unexport_pin(){
    // Unexport the pin by writing to /sys/class/gpio/unexport
    
     int fd = open("/sys/class/gpio/unexport", O_WRONLY);

    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }

    if (write(fd, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(1);
    }
 
    return fd; 
  
}



int main()
{
 
  int fd;   

   //fd = export_pin();
  //close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    close(fd);

    fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/value");
        exit(1);
    }

    // Toggle LED 500 ms on and 500ms off forever

      while (1) {
        if (write(fd, "1", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);       
        }
        usleep(500000);

        if (write(fd, "0", 1) != 1) {
            perror("Error writing to /sys/class/gpio/gpio24/value");
            exit(1);
        }
       
        usleep(500000);
    }

    close(fd);

   // fd = unexport_pin();
    
   // close(fd);

    // And exit
    return 0;
}
