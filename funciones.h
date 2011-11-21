# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# define BAUDRATE B38400
# define _ POSIX_ SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct termios oldtio;

int EnviaDatos(int fd, char *datos, int longitud){
	int iret, total=0;
	
	while(total < longitud){
		iret = write(fd,&datos[total], longitud-total);
		
		if(iret<0){
			return (iret);
		}else{
			total+=iret;
		}
	}
	
	return (total);
}

int RecibeDatos(int fd, char *datos, int longitud){
	return (read(fd,datos,longitud));
}

void ConfiguraPuerto(int fd){
	struct termios newtio; 
	 
	tcgetattr(fd,&oldtio); /* salva configuración actual del puerto */
	
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0; /* pone el modo entrada (no-canónico, sin eco,...) */
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = 0; /* temporizador entre carácter, no usado */
	newtio.c_cc[VMIN] = 0; /* asi no bloquea lectura */
	
	tcflush(fd,TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);
}

void RestauraPuerto(int fd){
	tcsetattr(fd,TCSANOW,&oldtio);
	close(fd);
}

