#include "net.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("parameter(argc) != 3\n");
		printf("sample : ./server 192.168.0.200 8888\n");

		return -1;
	}

	NET a(argv[1],argv[2]);

   a.connect_init();
	
	while(1){
		a.main_interface();
	};

	return 0;
}

