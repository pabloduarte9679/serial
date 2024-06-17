#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int main() {
    int serialPort = open("/dev/ttyUSB0", O_RDWR);

    if (serialPort < 0) {
        perror("unable to open serial port");
        exit(1);
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serialPort, &tty) != 0) {
        perror("unable to get serial port attr");
        close(serialPort);
        exit(1);
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB; 
    tty.c_cflag &= ~CSTOPB; 
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; 

    tcsetattr(serialPort, TCSANOW, &tty);

    char hex = 0x79;
    while (1) {
        write(serialPort, &hex, sizeof(char));
    }

    close(serialPort);
    return 0;
}
