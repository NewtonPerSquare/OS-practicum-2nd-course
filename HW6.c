#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


#define delta 4
                    
char* input_word(char* fl, FILE* F){ //modified function from prev homeworks, fl == 1 <=> EOF                
    int c;
    char *p_str = NULL;
    int i = 0;
    while (((c = fgetc(F)) != '\n') && (c != EOF) && (c != ' ')){
        if (i % delta == 0){
            p_str = realloc(p_str, delta + i);
        }
        if (p_str != NULL){
            p_str[i] = (char) (c % 256);
        }
        else{
            printf("memory error");
            break;
        }
        i++;
    }
    if (i % delta == 0 && p_str != NULL){
        p_str = realloc(p_str, delta + i);
        if (p_str != NULL){
            p_str[i] = '\0';
        }
        else{
            printf("memory error");
            return NULL;
        }
    }
    else{
        if (p_str != NULL){
            p_str[i] = '\0';
        }
        else{
            p_str = malloc(1);
            *p_str = '\0';
        }
    }
    if (fl != NULL){     //the word is read, changing the flag
        if (c == EOF){
            *fl = 1;
        }
        else{
            *fl = 0;
        }
    }
    return p_str;
}


int main(int argc, char** argv){
    ////
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
    ////
    char to_merge = 0;      //need to merge sequent empty strings in one
    int quantity = 1;       //strings per click
    int shift = 0;          //shift in file
    if (argc != 2){         //getting parameters from command line
        for (int i = 1; i < argc-1; i++){
            if (strcmp(argv[i], "-s") == 0){
                to_merge = 1; 
                printf("a1\n");  
            }
            else if ((argv[i])[0] == '-')
                quantity = atoi((argv[i]) + 1);
            else
                shift = atoi((argv[i]) + 1);
        }
    }
    FILE * F = fopen(argv[argc-1], "r");
    if (F == NULL)
        exit(2);

    char c;                 //symbol (space or q)
    char fl = 0;            
    char* str = NULL;       //buffer
    char skip = 0;          //flag to skip
    char sequence = 0;       //for merging situation
    int counter = quantity; //counter of how many times to output before next input 
    printf("Press space to output, q to quit\n");
    while ((skip) || ((scanf("%c", &c) != EOF) && c != 'q')){       
        //if we skip, it doesn't requrie input(very convinient)
        if (c == ' '){
            str = input_word(&fl, F);
            
            if(fl == 1){            //fl == 1 <=> eof - end the program
                for (int i = 0; i < strlen(str); i++)
                    printf("%c", str[i]);
                free(str);
                break;
            }

            if(shift > 0){ 
                shift--;
                skip = 1;
                free(str);
                continue;
            }

            if ((to_merge == 1) && (str[0] == '\0')){   //skipping sequent empty strings
                if (sequence){
                    free(str);
                    skip = 1;
                    continue;
                }
                sequence = 1;
            }
            else
                sequence = 0;
            skip = 0;

            if (quantity > 1){      //several strings in one time
                if(counter > 1){
                    counter--;
                    skip = 1;
                }
                else{
                    skip = 0;
                    counter = quantity;
                }
            }
            printf("%s\n", str);
            free(str);      //clear buffer         
        }
    }
    ////
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    ////
    fclose(F);
    return 0;
}