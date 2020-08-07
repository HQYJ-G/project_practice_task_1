#include "net.h"


int main(int argc, char *argv[])
{
	int fd;
	NET st;

	st.socket_init();
	st.bind_init();
	st.linsten_init();
	st.accept_init();
#if 0	
	st.epoll_init();
	st.epoll_add();
	while(1){
		st.epoll_waits();
		
	}o
#endif
	return 0;
}
