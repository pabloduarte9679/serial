#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int main(){

  int serialPort = open("/dev/ttyUSB0", O_RDWR);

  struct termios tty;
  memset(&tty, 0, sizeof(tty));

  cfsetospeed(&tty, B9600);
  cfsetispeed(&tty, B9600);
  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_oflag &= ~OPOST;
  tcsetattr(serialPort, TCSANOW, &tty);  

  uint8_t bytes[sizeof(float)];

  for (int i = 0; i < sizeof(float); i++) {
        if (read(serialPort, &bytes[i], sizeof(uint8_t)) < 0) {
            perror("Unable to read from serial port");
            close(serialPort);
            exit(1);
        }
    }

  float receivedValue;
  memcpy(&receivedValue, bytes,sizeof(float));
  printf("Received value: %f\n", receivedValue);

  close(serialPort);
  return 0;
  

}
