#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>	
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"
#define MAGENTA_TEXT "\033[1;35m"
#define CYAN_TEXT "\033[1;36m"
#define WHITE_TEXT "\033[1;37m"
#define RESET_COLOR "\033[0m"

char* Rights_to_string(int n) //converts rights[integer] to string[rwxrwxrwx]
{
    char* temp = "rwxrwxrwx";
    int len = strlen(temp);
    char* str = calloc(10, sizeof(char));
    str[9] = '\0';
    int mask = 1 << 8;
    for(int i = 0; i<len; i++){
        if(mask & n){
            str[i] = temp[i];
        }
        else{
            str[i] = '-';
        }
        mask >>= 1;
    }
    return str;
}

void describe_directory(char* Name, int level){
    printf("\n");           //for new component
    DIR* d = opendir(Name); 
    struct dirent *s;
    struct stat stat1;
    char* str;              //string buffers
    char* buf;
    char* bufname;          //buffer for name
    int lensym;
    while((s = readdir(d)) != NULL)
    {
        bufname = calloc(strlen(Name) + 1 + strlen(s->d_name) + 1, sizeof(char));
        strcpy(bufname, Name);
        bufname[strlen(Name)] = '/';
        strcat(bufname, s->d_name);         //create address from home directory
        lstat(bufname, &stat1);
        if(S_ISREG(stat1.st_mode)){         //regular file
            if ((stat1.st_mode & 72)){      //72 == 001001000 (check executability for user and group)
                if (level % 7 == 0){
                    printf(WHITE_TEXT);
                }
                if (level % 7 == 1){
                    printf(CYAN_TEXT);
                }
                if (level % 7 == 2){
                    printf(GREEN_TEXT);
                }
                if (level % 7 == 3){
                    printf(BLUE_TEXT);
                }
                if (level % 7 == 4){
                    printf(YELLOW_TEXT);
                }
                if (level % 7 == 5){
                    printf(MAGENTA_TEXT);
                }
                if (level % 7 == 6){
                    printf(RED_TEXT);
                }
                if (level > 0){
                    for(int i = 0; i-1<level; i++)
                        printf("\t");
                }
                printf("|%16s| ", s->d_name); // имя rwx идентификатор 
                str = Rights_to_string(stat1.st_mode); 
                printf("%10s ", str);

                free(str);
                printf("\n");
            }
        }
        else if(S_ISDIR(stat1.st_mode)){        //directory
            if((strcmp(s->d_name, "..") != 0) && (strcmp(s->d_name, ".") != 0)){     //ignore current and parent directory
                if (level % 7 == 0){
                    printf(WHITE_TEXT);
                }
                if (level % 7 == 1){
                    printf(CYAN_TEXT);
                }
                if (level % 7 == 2){
                    printf(GREEN_TEXT);
                }
                if (level % 7 == 3){
                    printf(BLUE_TEXT);
                }
                if (level % 7 == 4){
                    printf(YELLOW_TEXT);
                }
                if (level % 7 == 5){
                    printf(MAGENTA_TEXT);
                }
                if (level % 7 == 6){
                    printf(RED_TEXT);
                }
                if(level>0){
                    for(int i = 0; i-1<level; i++)
                        printf("\t");
                }
                printf("|%16s| ", s->d_name);
                str = Rights_to_string(stat1.st_mode); 
                printf("%10s ", str);
                free(str);
                printf(RESET_COLOR);
                describe_directory(bufname, level + 1);   //(do recursively for all inner directories)
            } 
        }
        else if(S_ISLNK(stat1.st_mode)){        //link
            if (level % 7 == 0){
                printf(WHITE_TEXT);
            }
            if (level % 7 == 1){
                printf(CYAN_TEXT);
            }
            if (level % 7 == 2){
                printf(GREEN_TEXT);
            }
            if (level % 7 == 3){
                printf(BLUE_TEXT);
            }
            if (level % 7 == 4){
                printf(YELLOW_TEXT);
            }
            if (level % 7 == 5){
                printf(MAGENTA_TEXT);
            }
            if (level % 7 == 6){
                printf(RED_TEXT);
            }
            if (level>0){
                for(int i = 0; i-1<level; i++)
                    printf("\t");
            }
            printf("|%16s| ", s->d_name);
            str = Rights_to_string(stat1.st_mode);
            printf("%10s ", str);
            free(str);
            buf = calloc(100, 1);
            lensym = readlink(bufname, buf, 30);    //reading the link
            if (lensym < 1){        //unsuccess
                free(buf);
                free(bufname);
                exit(-1);
            }
            printf(" link:%s", buf);
            free(buf); 
            printf("\n");  
        }
        free(bufname);
    }
    closedir(d);
}


int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, RED_TEXT"You didn't give me any directory =(\n"RESET_COLOR);
        return -1;
    }
    describe_directory(argv[1], 0);
    return 0;
}