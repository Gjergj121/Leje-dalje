#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char idnr[15];
    char emer[30];
    char mbiemer[30];
    int ditelindja;
    int id_familja;
}*dataptr;
/* prototipet e funksioneve */
int menu();
void perzgjedhja(int counter, int size);
int shto_shtetas(int count, int madhesia);
int shto_shtetas(int count, int madhesia, struct data shtetas);
void ndrysho_shtetas(int count);
void ndrysho_shtetas(int count, struct data shtetas);

int main(){
    FILE *fptr; // krijojme nje pointer qe pointon ne nje file
    if( (fptr=fopen("prov1.txt", "r")) == NULL ){
        printf("Gabim ne hapjen e file-it");
        return 0;
    }
    int counter = 0, size = 3;
    dataptr = (struct data*) malloc(size*sizeof(struct data)); // alokoj memorjen

    /*hedhim elementet e file ne pointerin dataptr */
    fseek(fptr, 37, SEEK_SET);// anashkalojme rreshtin e pare te file
    while(!feof(fptr)){ // derisa te arrijme ne fund te file-it
        fscanf(fptr, "%s", (dataptr+counter)->idnr );
        fscanf(fptr, "%s", (dataptr+counter)->emer );
        fscanf(fptr, "%s", (dataptr+counter)->mbiemer );
        fscanf(fptr, "%d", &(dataptr+counter)->ditelindja );
        fscanf(fptr, "%d", &(dataptr+counter)->id_familja );
        counter++;
        if(counter==size){// nese e kemi zene te gjithe memorjen e alokuar e dyfishojme ate
            size *= 2;
            dataptr = (struct data*) realloc(dataptr, size*sizeof(struct data));
        }
    }
/*    for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (dataptr+i)->idnr, (dataptr+i)->emer, (dataptr+i)->mbiemer, (dataptr+i)->ditelindja, (dataptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
*/
    perzgjedhja(counter, size);

    return 0;
}

int menu(){
    int choice;
    printf("\n-----------------------------------------");
    printf("\n              Detyre  Kursi\n");
    printf("\n1 - Shto nje shtetas te ri");
    printf("\n2 - Ndrysho nje shtetas");
    printf("\n3 - Apliko per Leje Dalje");
    printf("\n4 - Kontrollo nese nje shtetas ka leje");
    printf("\n5 - Printo leje daljet");
    printf("\n6 - Printo listen e 10 shtetasve\n    qe kane levizur me shpesh dhe\n    ato 10 qe kane levizur me pak");
    printf("\n0 - Mbyll programin");
    printf("\n-----------------------------------------\n");
    printf("\nZgjedhja juaj : ");
    scanf("%d", &choice);
    return choice;
}

void perzgjedhja(int counter, int size){
    int zgjedhja = menu();

    while(zgjedhja != 0){
        switch(zgjedhja){
            case 1:
                counter = shto_shtetas(counter, size);
                 for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (dataptr+i)->idnr, (dataptr+i)->emer, (dataptr+i)->mbiemer, (dataptr+i)->ditelindja, (dataptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
                break;
            case 2:
                ndrysho_shtetas(counter);
                 for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (dataptr+i)->idnr, (dataptr+i)->emer, (dataptr+i)->mbiemer, (dataptr+i)->ditelindja, (dataptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                printf("Zgjedhje e gabuar!\n");
                break;
        }
        printf("\nZgjedhja juaj : ");
        scanf("%d", &zgjedhja);
    }
    return;
}

int shto_shtetas(int count, int madhesia){
    struct data shtetas;
    printf("Vendosni IDNR : ");
    scanf("%s", shtetas.idnr);
    printf("Vendosni emrin : ");
    scanf("%s", shtetas.emer);
    printf("Vendosni mbiemrin : ");
    scanf("%s", shtetas.mbiemer);
    printf("Vendosni datelindjen (VVVVMMDD) : ");
    scanf("%d", &shtetas.ditelindja);
    printf("Vendosni ID e familjes : ");
    scanf("%d", &shtetas.id_familja);
    int i, j, k;
    for(i = 0; i < count; i++){
        if( strcmp(shtetas.idnr,(dataptr+i)->idnr) == 0){
            printf("\nKy shtetas ndodhet ne liste\n");
            break;
        }
    }
    if(i == count){ // tregon qe shtetasi eshte unik
        count = shto_shtetas(count, madhesia, shtetas);
    }
    return count;   
}

int shto_shtetas(int count, int madhesia, struct data shtetas){
    int j, k;
    for(j = count-1; j >= 0; j--){
            if(shtetas.id_familja == (dataptr+j)->id_familja ){
                for(k = count-1; k > j; k--){
                    *(dataptr+k+1) = *(dataptr+k);
                }
                *(dataptr+j+1) = shtetas;
                break;
            }
        }
        if(j == -1){
            *(dataptr+count) = shtetas;
        }
        count++;
        dataptr = (struct data*) realloc(dataptr, madhesia*sizeof(struct data)+1 );
        return count;
}

void ndrysho_shtetas(int count){
    struct data shtetas;
    printf("Vendosni IDNR e shtetasit : ");
    scanf("%s", shtetas.idnr);
    printf("Ndryshoni te dhenat :\n");
    printf("\nVendosni emrin : ");
    scanf("%s", shtetas.emer);
    printf("Vendosni mbiemrin : ");
    scanf("%s", shtetas.mbiemer);
    printf("Vendosni datelindjen (VVVVMMDD) : ");
    scanf("%d", &shtetas.ditelindja);
    printf("Vendosni ID e familjes : ");
    scanf("%d", &shtetas.id_familja);

    ndrysho_shtetas(count, shtetas);
    return;
}

void ndrysho_shtetas(int count, struct data shtetas){
    int i, j, k;
    for(i = 0; i < count; i++){
        if(strcmp(shtetas.idnr, (dataptr+i)->idnr) == 0){
            strcpy((dataptr+i)->emer, shtetas.emer);
            strcpy((dataptr+i)->mbiemer, shtetas.mbiemer);
            (dataptr+i)->ditelindja = shtetas.ditelindja;
            (dataptr+i)->id_familja = shtetas.id_familja;
            /* e vendos ne vendin e duhur ne liste (Bubble sort) */
            struct data temp;
            for(j = 0; j < count-1; j++){
                for(k = 0; k < count-1-j; k++){
                    if( (dataptr+k)->id_familja > (dataptr+k+1)->id_familja ){
                            temp = *(dataptr+k);
                            *(dataptr+k) = *(dataptr+k+1);
                            *(dataptr+k+1) = temp;
                    }
                }
            }
            return;
        }
    } 
    printf("Ky shtetas nuk ndodhet ne sistem\n");
    return;
}