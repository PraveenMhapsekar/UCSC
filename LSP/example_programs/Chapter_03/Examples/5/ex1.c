#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

struct stat     statbuf;
struct passwd  *pwd;

int main(int argc, char **argv) {
	uid_t uid,cuid;
	uid_t euid;
	char buf[10];
	
	if (lstat(argv[1],&statbuf)==-1)
		return 0;

	if (statbuf.st_mode & S_ISUID)
		printf("File '%s' has SUID bit set.\n", argv[1]);

	cuid=uid=getuid();
	pwd=getpwuid(uid);
	printf("Process is run by NONROOT user='%s'\n",pwd->pw_name);

	euid=geteuid();
	pwd=getpwuid(euid);
	printf("Process has an effective userid='%s'\n",pwd->pw_name);

	printf("Now running setuid() to est uid to ROOT\n");

	if (setuid(euid)) {
		perror("setuid");
		return 1;
	}

	uid=getuid();
	pwd=getpwuid(uid);
	printf("Process is now running as user='%s'\n",pwd->pw_name);

	printf("Process is now running setuid() to reset uid to NONROOT.\n");
	setuid(cuid);

	uid=getuid();
	pwd=getpwuid(uid);
	printf("Process is now back running as NONROOT user='%s'\n",pwd->pw_name);

	return 0;

}
