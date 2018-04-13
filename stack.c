#ifndef __STDIO__
#define __STDIO__
#include <stdio.h>
#endif // __STDIO__

#ifndef __STDLIB__
#define __STDLIB__
#include <stdlib.h>
#endif  //__STDLIB__

void createEmpty(Stack *stac){
    if (stac->data != NULL){
        free(stac->data);
    }
     if (stac->choice != NULL){
        free(stac->choice);
    }
    stac->data = (int*) malloc(sizeof(int));
    stac ->choice = (int*) malloc(sizeof(int));
    stac->TOP = 0;
}
void push(Stack *stac,int x,int y){
    int *temp;
    stac->TOP = stac->TOP + 1;
  //  printf("ALIVE");
    stac->data = (int*) realloc(stac->data,sizeof(int) * ((stac->TOP) + 1));
    stac ->choice = (int*) realloc(stac->choice,sizeof(int) * ((stac->TOP) + 1));
   // printf("DEAD");
    if (stac->data!=NULL){
    //stac.data = temp;
    stac->data[stac->TOP] = x;
    }else{
    free(stac->data);
    puts("Not enough memory.");
    exit(EXIT_FAILURE);
    }
    if (stac->choice!=NULL){
    //stac.data = temp;
    stac->choice[stac->TOP] = y;
    }else{
    free(stac->choice);
    puts("Not enough memory.");
    exit(EXIT_FAILURE);
    }
}
void pop(Stack *stac){
    stac->TOP = stac->TOP - 1;
    int *temp;
    stac->data = (int*) realloc(stac->data,sizeof(int)*(stac->TOP + 1));
    stac ->choice = (int*) realloc(stac->choice,sizeof(int) * ((stac->TOP) + 1));
    if (stac->data){
    //stac.data = temp;
    }else{
    free(stac->data);
    puts("Not enough memory.");
    exit(EXIT_FAILURE);
    }
    if (stac->choice!=NULL){
    //stac.data = temp;
    }else{
    free(stac->choice);
    puts("Not enough memory.");
    exit(EXIT_FAILURE);
    }
}
int peekdata(Stack stac){
    return stac.data[stac.TOP];
}

int peekstr(Stack stac){
    return stac.choice[stac.TOP];
}

int isEmpty(Stack stac){
    if (stac.TOP==0)
        return 1;
    else
        return 0;
}

