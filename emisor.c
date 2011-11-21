#include <stdio.h>
#include "funciones.h"
#define MODEMDEVICE "/dev/ttyS0"
#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1
volatile int STOP = FALSE;

main(int argc, char *argv[]){
	int fd, res, leidos;
	//char *buffer;
	//char buffer[255];
	unsigned long fileLen;
	FILE *file;
	
	if(argc<2){
		printf("Se debe pasar por argumento el nombre del archivo a enviar.\n");
		exit(-1);
	}

	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);

	if(fd < 0){ perror(MODEMDEVICE); exit(-1); }

	ConfiguraPuerto(fd);

	file = fopen(argv[1], "rb");
	
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	char buf[16];
	sprintf(buf, "%.15ld", fileLen);
	printf("%s",buf);
	
	write(fd, buf, 16);
	char buffer[255];

    while((res = fread(buffer, 1, 255, file)) > 0) {
        write(fd, buffer, res);
    }
	
	fclose(file);

	RestauraPuerto(fd);
}
