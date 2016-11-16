#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <unistd.h>

struct stat     statbuf;
struct passwd  *pwd;
struct group  *grp;

int main(int argc, char **argv) {
	gid_t cgid,gid;
	gid_t egid;
	char buf[10];
	
	if (lstat(argv[1],&statbuf)==-1)
		return 0;

	if (statbuf.st_mode & S_ISGID)
		printf("File '%s' has SGID bit set.\n", argv[1]);

	cgid=gid=getgid();
	grp=getgrgid(gid);
	printf("Process is run by group='%s'\n",grp->gr_name);

	egid=getegid();
	grp=getgrgid(egid);
	printf("Process has an effective group='%s'\n",grp->gr_name);

	if (setgid(egid)) {
		perror("setgid");
		return 1;
	}

	gid=getgid();
	grp=getgrgid(gid);
	printf("Process is now running as group='%s'\n",grp->gr_name);
	
	setgid(cgid);
	gid=getgid();
	grp=getgrgid(gid);
	printf("Process is now back running as group='%s'\n",grp->gr_name);
	

	return 0;

}
