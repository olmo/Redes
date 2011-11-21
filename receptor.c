# include <stdio.h>
#include "funciones.h"
# define MODEMDEVICE "/dev/ttyS0"
# define _ POSIX_ SOURCE 1 /* fuentes cumple POSIX */
# define FALSE 0
# define TRUE 1
volatile int STOP=FALSE;

main(int argc, char *argv[]){
	int fd, res, cont=0;
	char buffer[255];
	//FILE *file;
	unsigned long cantidad;
	int i=0;
	
	if(argc<2){
		printf("Se debe pasar por argumento el nombre del archivo a recibir.\n");
		exit(-1);
	}

	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
	if (fd < 0) { perror(MODEMDEVICE); exit(-1); }

	ConfiguraPuerto(fd);
	
	//file = fopen(argv[1], "wb+");
	int file = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	
	res=0;
	char lon[16];
	while( cont < 16 ){ 
		res = read(fd,&lon[cont],16); 
		cont+=res;
	}
	cantidad=atoi(lon);
	printf("%ld", cantidad);
	
	cont=0;
	while(cont < cantidad){
		res = read(fd, buffer, 255);
		//for(i=0;i<res;i++)
			//printf("%c", buffer[i]);
		//fwrite(buffer,1,res,file);
		write(file, buffer, res);
		cont += res;
	}
	
	close(file);
  
	RestauraPuerto(fd);
}

