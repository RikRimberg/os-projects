#include <stdio.h>
#include <sys/stat.h>
#include <sys/vfs.h>


int main ()
{
    struct statfs fs;
    unsigned long long free, size,blocks;

    statfs("/home/osboxes/Desktop/fstat/file_name.txt", &fs);
    free = fs.f_bfree;
    size = fs.f_bsize;
    blocks=fs.f_blocks;
    double blocks_gb=blocks*size/1000000000.;
    double busy_gb=(blocks-free)*size/1000000000.;
    double free_gb=free*size/1000000000.;
    printf("Total number of bytes -> %.4f \n", blocks_gb);
    printf("Number of free bytes -> %.4f \n", free_gb);
    printf("Number of busy bytes -> %.4f \n", busy_gb);
    int c = getchar();
    return 0;
}

