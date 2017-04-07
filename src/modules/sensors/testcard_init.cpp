#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <systemlib/err.h>

#include <px4_defines.h>

#include "testcards.h"

#define MOUNTPOINT PX4_ROOTFSDIR"/fs/microsd/"
static const char *log_root = MOUNTPOINT"testcards/testcards.txt";

int testcard_init(testcard_s* &testcard_array, int& ncase)
{
	FILE		*fp;
	char		line[120];
	
	/* open the testcard file */
	fp = fopen(log_root, "r");

	if (fp == NULL) {
		warnx("Unable to open testcard.txt");
		return -1;
	}
	
	/* find number of testcards */
	fgets(line, sizeof(line), fp);

	/* allocate memory */
    ncase = atoi(line);
	testcard_array = new testcard_s[ncase];

	for (int i = 0; i < ncase; i++) {
		
		fgets(line, sizeof(line), fp);
        int ret = sscanf(line, "%x %f %f %f %f %f",
						 &(testcard_array[i].id),
						 &(testcard_array[i].freq),
						 &(testcard_array[i].duration),
						 &(testcard_array[i].amp),
						 &(testcard_array[i].time_a),
						 &(testcard_array[i].time_b));

		if (ret != 6) {
			warnx("Invalid number of parameters in test card");
			return -1;
		}
	}

	return 1;
}