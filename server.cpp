#include "net.h"

int main(int argc, const char *argv[])
{
	NET a;
	a.socket_init();
	a.bind_init();
	a.listen_init();

	a.epoll_init();
	a.sepoll_add();
	while(1){
		a.epoll_waits();
		//a.accept_init();
	}
	return 0;
}
