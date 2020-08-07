#include "net.h"


int main(int argc, const char *argv[])
{
	NET st;
	st.socket_init();
	st.bind_init(&argv[1],&argv[2]);

	return 0;
}
