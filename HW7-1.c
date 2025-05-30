#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define RED_TEXT "\033[1;31m"
#define MAGENTA_TEXT "\033[1;35m"
#define RESET_COLOR "\033[0m"

int main(int argc, char ** argv)
{
    struct stat stat_1; 
    struct stat stat_2;
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0600);
    if (argc < 3){
        fprintf(stderr, RED_TEXT "Not_enough_information_provided\n" RESET_COLOR);
        return -1;
    }
    if((fd1 < 0) || (fd2 < 0))
    {
        fprintf(stderr, RED_TEXT "Open_err\n" RESET_COLOR);
        return -1;
    }
    fstat(fd1, &stat_1);
    fstat(fd2, &stat_2); //get file descriptors
    if ((stat_1.st_dev == stat_2.st_dev) && (stat_1.st_ino == stat_2.st_ino)) //compare file descriptors
    {
        if((close(fd1) || close(fd2)) == 0){
            fprintf(stderr, MAGENTA_TEXT "Same_file\n" RESET_COLOR);
            return -1;
        }
        return 0;
    } 
    lseek(fd2, 0, SEEK_SET);
    ssize_t rez;
    int buf;
    char * str = calloc(1, 10);
    while((rez = read(fd1, &buf, sizeof(int))) > 0){ //write negative numbers
        if(buf < 0){
            sprintf(str, "%d\n", buf);               //write a number in str
            rez = write(fd2, str, strlen(str));
            if(rez < 0){
                fprintf(stderr, RED_TEXT "Write_error\n" RESET_COLOR);
                return -1;
            }
        }
    }
    if(lseek(fd1, 0, SEEK_SET) < 0){                 //again
        fprintf(stderr, RED_TEXT "Lseek_error\n" RESET_COLOR);
        return -1;
    }
    while((rez = read(fd1, &buf, sizeof(int))) > 0){
        if(buf >= 0){
            sprintf(str, "%d\n", buf);
            rez = write(fd2, str, strlen(str));
            if(rez < 0){
                fprintf(stderr, RED_TEXT "Write_error\n" RESET_COLOR);
                return -1;
            }
        }
    }
    free(str);
    if(close(fd1) != 0)
        return -1;
    if(close(fd2) != 0)
        return -1;
    return 0;
}