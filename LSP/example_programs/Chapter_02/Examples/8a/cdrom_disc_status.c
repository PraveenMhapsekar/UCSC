// sourced from http://www.sslug.dk/~chlor/cdrom_disc_status.c
/*
 * cdrom_disc_status.c
 * Version: 1.0
 * by Hans Schou <chlor@schou.dk>
 * License: GPL
 *
 * Compile:
 *   gcc -o cdrom_disc_status cdrom_disc_status.c
 *
 * Known bugs:
 *   Can not compile on Linux S/390
 *   Can not compile on Linux Alpha XP1000
 */

#ifdef HAVE_CONFIG_H
#include <config.h> /* output from configure */
#endif

#include <sys/ioctl.h> /* ioctl */
#include <linux/cdrom.h> /* CDROM_DISC_STATUS */
#include <fcntl.h> /* O_RDONLY O_NONBLOCK */
#include <stdio.h> /* printf open close */

char package[] =
#ifdef PACKAGE
	"Builded with package: " PACKAGE "-" VERSION "\n";
#else
	"";
#endif

struct statustext {
		int statuscode;
		char *text;
} statustab[] = {
		{CDS_NO_INFO,         "CDS_NO_INFO"},
		{CDS_NO_DISC,         "CDS_NO_DISC"},
		{CDS_TRAY_OPEN,       "CDS_TRAY_OPEN"},
		{CDS_DRIVE_NOT_READY, "CDS_DRIVE_NOT_READY"},
		{CDS_DISC_OK,         "CDS_DISC_OK"},
		{CDS_AUDIO,           "CDS_AUDIO"},
		{CDS_DATA_1,          "CDS_DATA_1"},
		{CDS_DATA_2,          "CDS_DATA_2"},
		{CDS_XA_2_1,          "CDS_XA_2_1"},
		{CDS_XA_2_2,          "CDS_XA_2_2"},
		{CDS_MIXED,           "CDS_MIXED"}
};

#define STATUSCOUNT (sizeof(statustab) / sizeof(struct statustext))

/*
 * Function: text_status
 * Return: Short text description for cdrom status
 */
char *text_status( int status ) {
	/* Text from <linux/cdrom.h> */

	int i = 0;

	while (i < STATUSCOUNT) {
		if (status == statustab[i].statuscode)
			return statustab[i].text;
		i++;
	}

	return (char *)"unknown status";
}

/*
 * Function: cdrom_disc_status
 * Return: Status of cdrom drive
 */
int cdrom_disc_status( char *cddev ) {
	int cdrom = 0;
	int result = -1;

	cdrom = open( cddev, O_RDONLY | O_NONBLOCK );
	if ( cdrom > 0 ) {
		result = ioctl( cdrom, CDROM_DISC_STATUS );
		close( cdrom );
	}
	return result;
}

int main( int argc, char *argv[] ) {
	int status = -2;
	int i = 0;

	if ( argc != 2 ) {
		printf("cdrom_disc_status version 1.0\n");
		printf("%s", package);
		printf("\nUsage:\n  cdrom_disc_status <device>\n");
		printf("Example:\n  cdrom_disc_status /dev/cdrom\n");
		printf("\nReturn codes:\n");
		i = 0;
		while (i < STATUSCOUNT) {
			printf("%d %s\n", statustab[i].statuscode, statustab[i].text);
			i++;
		}
	} else {
		status = cdrom_disc_status(argv[1]);
		printf("%d %s\n", status, text_status(status) );
	}

	// return status;
	return 0;
}

