#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/vfs.h>
#include <iostream>

using namespace std;

char* getTime() {
    time_t now;
    struct tm *ptr;
    static char tbuf[64];
    bzero(tbuf,64);
    time(&now);
    ptr = localtime(&now);
    strftime(tbuf,64, "%Y-%m-%e %H:%M:%S", ptr);
    return tbuf;
}

char* getDiscSize ()
{
	static char str[256];
    	bzero(str, 256);
	struct statfs fs;
	unsigned long long free, size,blocks;
	statfs("/home/osboxes/Desktop/fstat/file_name.txt", &fs);
	free = fs.f_bfree;
	size = fs.f_bsize;
	blocks=fs.f_blocks;
	double blocks_gb=blocks*size/1000000000.;
	double busy_gb=(blocks-free)*size/1000000000.;
	double free_gb=free*size/1000000000.;
sprintf(str, "Total number of bytes -> %.4f \nNumber of free bytes -> %.4f \nNumber of busy bytes -> %.4f \n", blocks_gb, free_gb, busy_gb);
	return str;
}

int writeLog(char msg[256]) { 
    FILE * pLog;
    pLog = fopen("/home/osboxes/Documents/daemon.log", "a");
    if(pLog == NULL) {
        return 1;
    }
    char str[312];
    bzero(str, 312);
    strcpy(str, getTime());
    strcat(str, " ==========================\n");
    strcat(str, msg);
    strcat(str, "\n");
    fputs(str, pLog);
    fclose(pLog);
    return 0;
}


int main(int argc, char* argv[]) {

    char logStart[] = {"Daemon Start"};
    writeLog(logStart);


    char *log;
    while(1) {
        log = getDiscSize();
        writeLog(log);
        sleep(60); // 1 min
    }

    return 0;
}
