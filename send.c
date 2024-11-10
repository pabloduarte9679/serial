/*
  Code to send and receive data over serial port, and configure its settings 
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define SERIALPORT "/dev/ttyUSB0"

int main(void){
  int sp = open(SERIALPORT, O_RDWR);
  if(sp < 0){
    printf("Error opening serial port\n");
    exit(EXIT_FAILURE);
  }

  struct termios tty;
  if(tcgetattr(sp, &tty) != 0){
    printf("Error from tcgetattr\n");
    exit(EXIT_FAILURE);
  }
  // disable parity bit
  tty.c_cflag &= ~PARENB;
  // only one stop bit
  tty.c_cflag &= ~CSTOPB;
  // clear size
  tty.c_cflag &= ~CSIZE;
  // set eight bits
  tty.c_cflag |= CS8;
  // disable hardware control
  tty.c_cflag &= ~CRTSCTS;
  // enable read and disable signal lines
  tty.c_cflag |= CREAD | CLOCAL;
  // disable cannonical mode
  tty.c_lflag &= ~ICANON;
  // disable echo mode
  tty.c_lflag &= ~ECHO;
  tty.c_lflag &= ~ECHOE;
  tty.c_lflag &= ~ECHONL;
  // disable signal characters
  tty.c_lflag &= ~ISIG;
  // disable software control 
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  // disable special byte handle
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
  // prevent special interpretation of bytes
  tty.c_oflag &= ~OPOST;
  // prevent conversion of \n \r
  tty.c_oflag &= ~ONLCR;

  tty.c_cc[VTIME] = 10;
  tty.c_cc[VMIN] = 0;

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  if(tcsetattr(sp, TCSANOW, &tty) != 0){
    printf("Error setting parameters\n");
    exit(EXIT_FAILURE);
  }

  unsigned char msg[] = {'H', 'e', 'l', 'l', 'o'};
  write(sp, msg, sizeof(msg));
  
  char readbuf[256];
  memset(&readbuf, '\0', sizeof(readbuf));

  int nread = read(sp, &readbuf, sizeof(readbuf));

  if(nread < 0){
    printf("Error reading\n");
    return 1;
  }

  printf("READ: %s\n", readbuf);
  close(sp);
  return 0;
}
