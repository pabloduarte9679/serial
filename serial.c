#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int main(){

  int serialPort = open("/dev/ttyUSB0", O_RDWR);

  if(serialPort < 0){
    perror("enable to open serial port");
    exit(1);
  }

  struct termios tty;
  memset(&tty,0,sizeof(tty));

  if(tcgetattr(serialPort, &tty) != 0){
    perror("unable to get serial port attr");
    close(serialPort);
    exit(1);
  }

  cfsetospeed(&tty,B9600);
  cfsetispeed(&tty,B9600);

  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); 
  tty.c_oflag &= ~OPOST; 
  tcsetattr(serialPort, TCSANOW, &tty);
  char letter = 'A';
	while(1){
  write(serialPort, &letter, sizeof(char));
  }

  close(serialPort);
  return 0;

}
