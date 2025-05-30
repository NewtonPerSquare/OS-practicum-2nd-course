#include <stdio.h>

int main(){
    int c;
    int sf = 0;
    int zf = 0;
    int nf = 0;
    while ((c = fgetc(stdin)) != '\n' && c != EOF){
        if (c == ' '){
            nf = 0;
            sf += 1;
            if (zf > 0){
                fputc('0',stdout);
                zf = 0;
            }
        }
        else if (sf > 0){
            fputc(' ',stdout);
            sf = 0;
        }
        if (c >= '0' && c <= '9'){
            if (c == '0' && nf == 0){
                zf += 1;
            }
            else{
                nf = 1;
                zf = 0;
                fputc(c, stdout);
            }
        }
        else if (c != ' '){
            if (zf > 0){
                while (zf>0){
                    fputc('0',stdout);
                    zf -= 1;
                }
            }
            fputc(c,stdout);
        }
    }
    if (zf > 0){
        fputc('0',stdout);
    }
    return 0;
}
