#if 1
void main(void)
{
    printf("Content-Type: text/plain\n");
    printf("Access-Control-Allow-Origin: *\n");
    printf("\n");

    system("uart_ctl 44");

   // printf("uart_ctl 4\n");
    return;
}

#else

    

#include <sys/types.h>
      #include <sys/stat.h>
      #include <fcntl.h>
      #include <termios.h>
      #include <stdio.h>
        
      //#define BAUDRATE B115200
      #define BAUDRATE B9600
      
      #define MODEMDEVICE "/dev/ttyS1"
      #define _POSIX_SOURCE 1 /* POSIX compliant source */
      #define FALSE 0
      #define TRUE 1
        
      volatile int STOP=FALSE; 
       
	  int main(void)
      {
        int fd,c, res;
        struct termios oldtio,newtio;
        char buf[255];

        printf("Content-Type: text/plain\n");
    printf("Access-Control-Allow-Origin: *\n");
    printf("\n");
        
        fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY  |  O_NONBLOCK |O_NDELAY);
        if (fd <0) {perror(MODEMDEVICE); exit(-1); }
        
        tcgetattr(fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));

        memcpy(&newtio, &oldtio, sizeof(struct termios));

        newtio.c_cflag &= ~PARENB;
        newtio.c_cflag &= ~CSTOPB;
        newtio.c_cflag &= ~CSIZE;
        newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
        newtio.c_cflag &= ~CRTSCTS;

        newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        newtio.c_oflag &= ~OPOST;
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_iflag &= ~(IXON | IXOFF | IXANY);
         
        newtio.c_cc[VTIME]    = 1;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 0;   /* blocking read until 1 chars received */
        
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);
       
	    	int cnt = 0;
	    	res = 0;
	    	strcpy(buf, "hello");
	    	printf("Start to xmt : %s (%d)\n", buf, strlen(buf));
          
	    	while (cnt < strlen(buf)) {

	    		res = write(fd, &buf[cnt], strlen(buf) - cnt);
	    		if (res > 0) {
	    			printf("tx: %d\n",res);
	    			cnt += res;
	    		} else
	    			printf("write error (%d)\n", res);
	    	}
	    		
	   
        //tcsetattr(fd,TCSANOW,&oldtio);
        close(fd);

        return;

      }
#endif