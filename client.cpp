#include "net.h"

int main(int argc, const char *argv[])
{
	NET a;
	a.socket_init();
	a.cbind_init();
	a.connect_init();
	

	return 0;
}
