#ifndef __STDIO__
#define __STDIO__
#include <stdio.h>
#endif  //__STDIO__

#ifndef __STRING__
#define __STRING__
#include <string.h>
#endif // __STRING__



typedef struct Stack{
    int TOP;
    int *data;
    int *choice;
}Stack;


void createEmpty(Stack *stac);
void push(Stack *stac,int x, int y);
void pop(Stack *stac);
int peekdata(Stack stac);
int peekstr(Stack stac);
int isEmpty(Stack stac);

#include "stack.c"
/*
char tulisan[1][50];

int main(){
    char buff[50];
    char buff2[50];
    FILE *fp;
    fp = fopen("tmp.txt", "r");
    char c;
    int i =0;
    for (i=0;i<12;i++)
        sprintf(tulisan[i],"");
    i = 0;
    do{
        fscanf(fp,"%s",buff);
        c = fgetc(fp);
        c = fgetc(fp);
        while((c!='<')&&(c!=EOF)&&(c!='\n')){
            sprintf(buff2,"%c",c);
            c = fgetc(fp);
            strcat(tulisan[i],buff2);
        }
        if ((!strcmp(tulisan[i],"\n"))||(!strcmp(tulisan[i],""))){
            sprintf(tulisan[i],"");
            i--;
        }
       // printf("Traced: %s",tulisan[i]);
        i++;
    }while(c!=EOF);
    fclose(fp);
    for (i=0;i<12;i++)
        printf("%s\n",tulisan[i]);
}
*/

/*
main() {
   FILE *fp;
   fp = fopen("test.txt", "r");
   char c = fgetc(fp);
   while (c!= EOF){
    printf("%c",c);
    c = fgetc(fp);
    if (c=='\n')
        printf("spasi");
   }
   fclose(fp);
   char arr[5][100]={"test","tis","tus","bal","spielen"};
   system("cls");
   printf("Will writing to file\n");
   fp = fopen("test.txt", "w");
   int i;
   for(i=0;i<5;i++){
    fprintf(fp,"<Nama>");
    fprintf(fp,arr[i]);
    fprintf(fp,"</Nama>\n");
   }
   fclose(fp);
   fp = fopen("test.txt", "r");
   c = fgetc(fp);
   while (c!= EOF){
    printf("%c",c);
    c = fgetc(fp);
   }
   fclose(fp);
}
*/
