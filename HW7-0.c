#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include <unistd.h>
#include <fcntl.h>
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_COLOR "\033[0m"


int main(int argc, char ** argv)
{
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0600);
    lseek(fd, 0, SEEK_SET);
    if (fd < 0){
        fprintf(stderr, RED_TEXT "Creation_error\n" RESET_COLOR);
        return -1;
    }
    if (argc < 2){
        fprintf(stderr, RED_TEXT "File_to_create_was_not_chosen\n" RESET_COLOR);
        return -1;
    }
    int check;
    int n;
    printf(BLUE_TEXT "Print numbers to input. Print 0 to stop: " RESET_COLOR);
    scanf("%d", &n);
    while (n != 0){
        check = write(fd, &n, sizeof(int));
        if (check < 0){
            fprintf(stderr, RED_TEXT "Write_err" RESET_COLOR);
            return -1;
        }
        scanf("%d", &n);
    }
    if(close(fd) != 0)
        return -1;
    return 0;
}