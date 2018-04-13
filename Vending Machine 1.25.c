#define __STDIO__
#define __STRING__
#define __ERRNO__
#define __WINDOWS__
#define __MATH__
#define __STDLIB__
#define __CONIO__
#define __STACK__
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include "stack.h"

#define __TEKS__ 30
int WINAPI Test(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow, char text[]);
void setup();
void vending();
void init_help();
void insertMinuman(char nama[],int harga,int stok);
int buy(int pilihan);
void clean_input();
int conf(char text[]);
int login();
int mainadmin();
int stokadmin();
int hargaadmin();
int addadmin();
int bacall();
int linectr(char namafile[]);
void fav(int i,int stok);
struct minuman;
void tukarnode(struct minuman *a, struct minuman *b);
void bubbleSort(struct minuman *start) ;
void tulisll(struct minuman *ll);

int varMinuman = 4;
char admin[2][__TEKS__] = {"admin","1606828085"};

Stack tumpukan;


struct minuman
{
    char minuman[__TEKS__];
    int stok;
    int price;
    struct minuman *nextptr;
}*stminuman;

int main() {
  int error_catch;
  int choice;
  char *getError;
  char input[__TEKS__];
  int repeat;
  setup();
  do{
      init_help();
      vending();
      printf("\nSilahkan masukkan minuman yang diinginkan, dan tekan enter: ");
      choice = strtol(gets(input), &getError, 10);
      if (!( strcmp(input, admin[0]))) {
          int tmp = login();
          if(tmp){
              repeat = mainadmin();
          }else{
              repeat=1;
          }

      }else if ( getError[0] != NULL ){
          Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
          repeat = 1;
          system("cls");
      }else if ((choice>=1)&&(choice<=varMinuman)){
          buy(choice);
          repeat = conf("ExtProg");
      }else{
          Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err02");
          repeat = 1;
          system("cls");
      }
  }while(repeat==1);


  return 0;
}

void setup(){ //Inisialisasi awal vending machine
    tumpukan.data = NULL;
    tumpukan.choice =NULL;
    createEmpty(&tumpukan);
    int i;
    for (i=0;i<119;i++)
        printf("-");
    printf("\n");
    for (i=0;i<53;i++)
        printf("-");
    printf("Vending Machine");
    for (i=68;i<119;i++)
        printf("-");
    printf("\n");
    for (i=0;i<119;i++)
        printf("-");
    printf("\n");
    /* Source code pada bagian ini diubah
    dari source code dari proglan scele
    khususnya di linked list */
    if (!bacall()){
    struct minuman *fnminuman, *tmp, *snminuman, *tnminuman;
    stminuman = (struct minuman*) malloc(sizeof(struct minuman));
    if (stminuman == NULL){
      printf("Tidak dapat alokasi memori, harap restart program.\n");
      getch();
      exit(EXIT_FAILURE);
    }

    sprintf(stminuman->minuman,"Aqua Gelas");
    stminuman -> price = 1000;
    stminuman -> stok = 10;
    stminuman -> nextptr =NULL;
    tmp = stminuman;

    fnminuman = (struct minuman*) malloc(sizeof(struct minuman));
    if (fnminuman == NULL){
        printf("Tidak dapat alokasi memory, harap restart program\n");
        getch();
        exit(EXIT_FAILURE);
    }

    sprintf(fnminuman ->minuman,"Equil");
    fnminuman -> price = 16750;
    fnminuman ->stok = 15;
    fnminuman ->nextptr = NULL;
    tmp ->nextptr = fnminuman;
    tmp = tmp ->nextptr;

    snminuman = (struct minuman*)malloc(sizeof(struct minuman));
    sprintf(snminuman ->minuman,"Coca-cola");
    snminuman -> price = 5000;
    snminuman ->stok = 30;
    snminuman ->nextptr = NULL;
    tmp ->nextptr = snminuman;
    tmp = tmp ->nextptr;

    tnminuman = (struct minuman*)malloc(sizeof(struct minuman));
    sprintf(tnminuman ->minuman,"Mijon");
    tnminuman -> price = 10000;
    tnminuman ->stok = 100;
    tnminuman ->nextptr = NULL;
    tmp ->nextptr = tnminuman;
    tmp = tmp ->nextptr;
    tulisll(stminuman);
    }
    bubbleSort(stminuman);
}

void vending(){
  struct minuman *tmp;
  char temp2[50];
  int i = 0;
  if(stminuman == NULL)
  {
      printf("Ada error!.");
      getch();
      exit(EXIT_FAILURE);
  }
  else
  {
      printf("%-4s %-20s %-10s %-7s\n","No","Nama minuman","Harga","stok");
      tmp = stminuman;
      while(tmp != NULL)
      {
          printf("%-4s ", itoa((i++)+1,temp2,10));
          printf("%-20s ", tmp ->minuman);
          printf("%-10s ", itoa(tmp->price,temp2,10));
          printf("%-7s", itoa(tmp->stok,temp2,10));
          fav(i-1,tmp->stok);
          printf("\n");
          tmp = tmp->nextptr;
      }
  }

}

void init_help(){ //Untuk menampilkan tulisan saja
    printf("\nBerikut adalah list minuman yang tersedia\n");
    printf("\n");
}

void insertMinuman(char nama[],int harga,int stok)
{
    varMinuman ++;
    struct minuman *fnNode, *tmp;
    fnNode = (struct minuman*)malloc(sizeof(struct minuman));
    if(fnNode == NULL)
    {
        printf(" Memory can not be allocated.");
    }
    else
    {
        fnNode ->price = harga;
        sprintf(fnNode ->minuman,nama);
        fnNode -> stok = stok;
        fnNode ->nextptr = NULL;
        tmp = stminuman;
        while(tmp->nextptr != NULL)
            tmp = tmp->nextptr;
        tmp->nextptr = fnNode;
    }
    tulisll(stminuman);
}

int buy(int pilihan){
  pilihan --;
  struct minuman *ennode;
  ennode = stminuman;

  int i;
  for (i=0;i<pilihan;i++){
    ennode = ennode ->nextptr;
  }
  char tmp[200];
  char getError;
  int repeat;
  int stokakhir = 1;
  int stokawal = ennode ->stok;
  if (stokawal==0){
      sprintf(tmp,"Stok %s sedang habis!",ennode ->minuman);
      Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
      return 0;
  } else if (stokawal==1){
    sprintf(tmp,"Telah terbeli %s sebanyak 1 seharga %d",ennode ->minuman,ennode ->price);
    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
    ennode -> stok --;
    return 1;
  }else{
    do{
      system("cls");
      printf("Untuk menambah stok tekan d, dan untuk mengurangi stok tekan a. Lalu tekan enter untuk mengubahnya.Untuk batal tekan b\n");
      if (stokakhir ==1){
          printf("%s :   %d +",ennode ->minuman,stokakhir);getError = getch();
      }else if (stokakhir == stokawal){
          printf("%s : - %d  ",ennode ->minuman,stokakhir);getError = getch();
      }else{
          printf("%s : - %d +",ennode ->minuman,stokakhir);getError = getch();
      }
      if (getError == 13)
          repeat = 0;
      else if ((getError == 97)&&(stokakhir!=1)){
          repeat = 1;
          stokakhir--;
      }else if((getError==100)&&(stokakhir!=stokawal)){
          repeat = 1;
          stokakhir++;
      }else if (getError==98){
          sprintf(tmp,"Batal membeli %s",ennode ->minuman);
          Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
          return 1;
      }
    }while(repeat==1);
  }
  sprintf(tmp,"Telah terbeli %s sebanyak %d dengan total harga Rp.%d",ennode ->minuman,stokakhir,(ennode ->price) * stokakhir);
  Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
  ennode ->stok -=stokakhir;
  tulisll(stminuman);
  push(&tumpukan,stokakhir,pilihan);
  return 1;
}

int WINAPI Test(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow, char text[]){
    if (strcmp(text,"Err01")==0){
        MessageBox(NULL, "Harap masukkan nomor saja!", "Error",MB_ICONSTOP);
    }else if(strcmp(text,"Err02")==0){
        MessageBox(NULL, "Pilihan yang anda inginkan tidak ada, pilihlah sesuai yang ada saja!", "Error",MB_ICONWARNING);
    }else if(strcmp(text,"Err03")==0){
        MessageBox(NULL, "Sudah mencapai jumlah minuman maksimum, tidak bisa menambah jenis minuman lagi!", "Error",MB_ICONSTOP);
    }else{
        MessageBox(NULL, text, "Info",MB_ICONINFORMATION);
    }

    return 0;
}

void clean_input(){
    while (getchar()!= '\n');
}

int conf(char text[]){ //Untuk menu konfirmasi
    system("cls");
    int repeat;
    char ext;
    if (strcmp(text,"ExtProg")==0){
        do{
            printf("Ingin keluar dari program?\nTekan y untuk keluar dan tekan n untuk tetap memakai program\n ");ext = getch();
            system("cls");
        }while((ext!=121)&&(ext!=110));
        if (ext==121)
            return 0;
        else
            return 1;
    }
}

int login(){ //Untuk login ke menu admin
    system("cls");
    char username[6];
    printf("Masukkan password: ");gets(username);
    if (strcmp(username,admin[1])==0){
        printf("Password Benar\n");
        printf("Press Any key to continue...");getch();system("cls");
        return 1;
    }else{
        printf("password Salah\n");
        printf("Press Any key to continue...");getch();system("cls");
        return 0;
    }
}

int mainadmin(){ //Menu admin
    int i;
    int choice;
    int repeat;
    int error_catch;
    char getError;

    do{
        system("cls");
        for (i=0;i<119;i++)
            printf("-");
        printf("\n");
        for (i=0;i<53;i++)
            printf("-");
        printf("Admin");
        for (i=58;i<119;i++)
            printf("-");
        printf("\n");
        for (i=0;i<119;i++)
            printf("-");
        printf("\n");
        printf("1. Tambah Stok\n");
        printf("2. Ubah Harga\n");
        printf("3. Tambah Jenis minuman\n");
        printf("4. Kembali ke Vending Machine\n");
        printf("5. Exit Program\n");
        printf("Masukkan nomor menu yang diinginkan, lalu tekan enter: ");error_catch = scanf("%d%c",&choice,&getError);
        if ((error_catch == 0) || (getError != '\n')){
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
            clean_input();
            repeat = 1;
            system("cls");
        }else if (choice==1){ //Menu tambah Stok
            repeat = stokadmin();
        }else if (choice==2){
            repeat = hargaadmin();
        }else if (choice==3){
            repeat = addadmin();
        }else if (choice==4){
            system("cls");
            return 1;
        }else if (choice==5){
            system("cls");
            return 0;
        }else{
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err02");
            repeat = 1;
            system("cls");
        }
    }while(repeat==1);

}

int stokadmin(){ // Untuk menu admin menambah stok
    system("cls");
    int stokakhir;
    char tmp[99];
    int repeat, choice,error_catch;
    int stokawal;
    char getError;
    do{
        printf("Menu Tambah Stok\n\n");
        vending();
        printf("%d    Cancel\n",varMinuman+1);
        printf("Masukkan nomor minuman yang ingin ditambahkan stoknya, lalu tekan enter: ");error_catch = scanf("%d%c",&choice,&getError);
        if ((error_catch == 0) || (getError != '\n')){
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
            clean_input();
            repeat = 1;
            system("cls");
        }else if ((choice>=1)&&(choice<=varMinuman)){
          struct minuman *ennode;
          ennode = stminuman;
          int i;
          choice --;
          for (i=0;i<choice;i++){
            ennode = ennode ->nextptr;
          }
            stokawal = ennode -> stok;
            stokakhir = stokawal;
            do{
                system("cls");
                printf("Untuk menambah stok tekan d, dan untuk mengurangi stok tekan a. Lalu tekan enter untuk mengubahnya.Untuk batal tekan b\n");
                if (stokakhir==stokawal){
                    printf("%s :   %d +",ennode ->minuman,stokakhir);getError = getch();
                }
                else{
                    printf("%s : - %d +",ennode ->minuman,stokakhir);getError = getch();
                }
                if (getError == 13)
                    repeat = 0;
                else if ((getError == 97)&&(stokakhir>stokawal)){
                    repeat = 1;
                    stokakhir--;
                }else if(getError==100){
                    repeat = 1;
                    stokakhir++;
                }else if (getError==98){
                    sprintf(tmp,"Stok tidak jadi ditambah");
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
                    return 1;
                }else{
                    repeat =1;
                }
            }while(repeat==1);
            sprintf(tmp,"Stok %s ditambahkan sebanyak %d sehingga stoknya sekarang sebanyak %d",ennode ->minuman,stokakhir-stokawal,stokakhir);
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
            system("cls");
            ennode ->stok = stokakhir;
            repeat = 0;
        }else if (choice==varMinuman+1){
            system("cls");
            return 1;
        }else{
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err02");
            repeat = 1;
            system("cls");
        }
    }while (repeat==1);
    tulisll(stminuman);
    return 1;
}

int hargaadmin(){ //untuk menu admin mengubah harga minuman
    system("cls");
    struct minuman *ennode;
    ennode = stminuman;
    int repeat,choice,error_catch;
    int newprice;
    char getError;
    char tmp[99];
    do{
        printf("Menu Ubah Harga\n\n");
        vending();
        printf("%d    Cancel\n",varMinuman+1);
        printf("Masukkan nomor minuman yang ingin diubah harganya, lalu tekan enter: ");error_catch = scanf("%d%c",&choice,&getError);
        if ((error_catch == 0) || (getError != '\n')){
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
            clean_input();
            repeat = 1;
            system("cls");
        }else if ((choice>=1)&&(choice<=varMinuman)){
            choice--;
            system("cls");
            int i;
            for (i=0;i<choice;i++){
              ennode = ennode ->nextptr;
            }
            do{
                printf("%s seharga %d\n",ennode->minuman,ennode ->price);
                printf("Masukkan harga baru yang diinginkan, lalu tekan enter. Untuk batal masukkan -1 atau angka negatif lalu enter: ");error_catch = scanf("%d%c",&newprice,&getError);
                if ((error_catch == 0) || (getError != '\n')){
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
                    clean_input();
                    repeat = 1;
                    system("cls");
                }else if(newprice<0){
                    sprintf(tmp,"Harga tidak jadi diubah");
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
                    return 1;
                }else{
                    ennode->price = abs(newprice);
                    sprintf(tmp,"Harga %s sekarang menjadi %d",ennode->minuman,ennode->price);
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
                    system("cls");
                    repeat = 0;
                }
            }while(repeat==1);

        }else if (choice==varMinuman+1){
            system("cls");
            return 1;
        }else{
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err02");
            repeat = 1;
            system("cls");
        }
    }while (repeat==1);
    bubbleSort(stminuman);
    tulisll(stminuman);
    createEmpty(&tumpukan);
    return 1;
}

int addadmin(){ // untuk menu admin menambah jenis minuman
    char tmp[99];
    struct minuman *ennode;
    ennode = stminuman;
    int repeat,error_catch;
    char getError;
    int newprice,newstok;
    char newminuman[__TEKS__];
    int i;
    do{
        repeat = 0;
        system("cls");
        printf("Menu Tambah jenis minuman\n");
        printf("Masukkan nama minuman yang ingin ditambahkan, lalu tekan enter. Untuk batal tulis cancel dan enter: ");gets(newminuman);
        if (!(strcmp(newminuman,"cancel"))){
            sprintf(tmp,"Tidak jadi ditambahkan minuman");
            Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
            system("cls");
            return 1;
        }
        for (i=0;i<varMinuman;i++){
            if ((strcmp(newminuman,ennode ->minuman))==0){
                printf("Minuman %s sudah ada,tidak bisa menambah dengan nama yang sama dengan minuman yang sudah ada",ennode -> minuman);
                getch();
                repeat = 1;
            }
            ennode = ennode -> nextptr;
        }
        if (repeat!=1){
            do{
                repeat = 0;
                system("cls");
                printf("Nama minuman: %s\n",newminuman);
                printf("Masukkan harga %s, lalu tekan enter: ",newminuman);error_catch = scanf("%d%c",&newprice,&getError);
                if ((error_catch == 0) || (getError != '\n')){
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
                    clean_input();
                    repeat = 1;
                }else if (newprice<=0){
                    printf("Harga tidak boleh negatif!\n");
                    printf("Press any key to continue..");getch();
                    repeat = 1;
                }
            }while(repeat==1);
            do{
                repeat = 0;
                system("cls");
                printf("Nama minuman: %s\n",newminuman);
                printf("Harga minuman: Rp. %d\n",newprice);
                printf("Masukkan stok %s, lalu tekan enter: ",newminuman);error_catch = scanf("%d%c",&newstok,&getError);
                if ((error_catch == 0) || (getError != '\n')){
                    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,"Err01");
                    clean_input();
                    repeat = 1;
                }else if (newstok<=0){
                    printf("Stok tidak boleh negatif!\n");
                    printf("Press any key to continue..");getch();
                    repeat = 1;
                }
            }while(repeat==1);
            repeat = 0;
        }
    }while(repeat==1);
    sprintf(tmp,"Ditambahkan %s Seharga Rp.%d dengan stok %d",newminuman,newprice,newstok);
    Test(GetModuleHandle(0),NULL,GetCommandLineA(),NULL,tmp);
    system("cls");
    insertMinuman(newminuman,newprice,newstok);
    bubbleSort(stminuman);
    createEmpty(&tumpukan);
    return 1;
}

void tulisll(struct minuman *ll){
    FILE *fp;
    fp = fopen("tmp.txt","w");
    struct minuman *tmp;
    char temp2[50];
    int i = 0;
    if(ll == NULL)
    {
        printf("Ada error!.");
        getch();
        exit(EXIT_FAILURE);
    }
    else
    {
        tmp = ll;
        while(tmp != NULL)
        {
            fprintf(fp,"<Nama> ");
            fprintf(fp,tmp ->minuman);
            fprintf(fp,"</Nama>");
            fprintf(fp,"<Price> ");
            fprintf(fp,itoa(tmp->price,temp2,10));
            fprintf(fp,"</Price>");
            fprintf(fp,"<Stok> ");
            fprintf(fp,itoa(tmp->stok,temp2,10));
            fprintf(fp,"</Stok>\n");
            tmp = tmp->nextptr;
        }
    }
    fclose(fp);
}

int bacall(){
    int jmlbaris = linectr("tmp.txt");
    char tulisan[jmlbaris*3][50];
    char buff[50];
    char buff2[50];
    FILE *fp;
    fp = fopen("tmp.txt", "r");
    if (!fp)
        return 0;
    char c;
    int i =0;
    for (i=0;i<jmlbaris*3;i++)
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
        i++;
    }while(c!=EOF);
    fclose(fp);
    stminuman = (struct minuman*)malloc(sizeof(struct minuman));
    strcpy(stminuman->minuman,tulisan[0]);
    stminuman -> price = strtol(tulisan[1],NULL,10);
    stminuman -> stok = strtol(tulisan[2],NULL,10);
    stminuman -> nextptr =NULL;
    for (i=1;i<jmlbaris;i++){
        insertMinuman(tulisan[i*3],strtol(tulisan[(i*3)+1],NULL,10),strtol(tulisan[(i*3)+2],NULL,10));
    }
    return 1;
}

int linectr(char namafile[]){
    char buff[1000];
    FILE *fp;
    fp = fopen(namafile, "r");
    int i = 0;
    while(fgets(buff,1000,fp)!=NULL)
        i++;
    fclose(fp);
    return i;
}

void fav(int i,int stok){
    if (isEmpty(tumpukan))
    return;
    if (i==peekstr(tumpukan)&&(stok!=0))
        printf(" *Recently Bought");
}

void bubbleSort(struct minuman *start) //urutkan berdasarkan harga DESC (dari besar ke kecil)
{
    int swapped, i;
    struct minuman *ptr1;
    struct minuman *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->nextptr != lptr)
        {
            if (ptr1->price < ptr1->nextptr->price)
            {
                tukarnode(ptr1, ptr1->nextptr);
                swapped = 1;
            }
            ptr1 = ptr1->nextptr;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void tukarnode(struct minuman *a, struct minuman *b)
{
    struct minuman temp;
    sprintf(temp.minuman,a->minuman);
    temp.price = a->price;
    temp.stok = a->stok;

    sprintf(a->minuman,b->minuman);
    a->price = b->price;
    a->stok = b->stok;

    sprintf(b->minuman,temp.minuman);
    b->price = temp.price;
    b->stok = temp.stok;
}
