#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// int mknod(const char *pathname, mode_t mode, dev_t dev);

int main() {

	char *fn="./myfifo";

	if (mknod(fn, 0666, S_IFIFO)==0) {

		fprintf(stderr,"Named Pipe \"%s\" created.\n",fn);

	}

	return 0;
}
