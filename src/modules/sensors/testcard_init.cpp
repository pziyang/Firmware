#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>

#include "testcards.h"

#define MOUNTPOINT PX4_ROOTFSDIR"/fs/microsd"
static const char *log_root = MOUNTPOINT "/testcards/testcards.txt";

int testcard_init(vector<testcard_s>& testcards)
{
    std::fstream fs;
    fs.open (log_root, std::fstream::in);

    if (!fs.is_open()) {
        warnx("FATAL: Cannot load testcard file");
        return -1;
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        testcard_s temp;

        //process current line
        if (!(iss >>
                temp.id >>
                temp.freq >>
                temp.duration >>
                temp.amp >>
                temp.time_a >>
                temp.time_b)) {
            warnx("FATAL: Cannot load testcards input");
        }

        //pushback
        testcards.push_back(temp);
    }

    return 1;
}