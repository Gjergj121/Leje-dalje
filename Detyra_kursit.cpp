#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shtetas{
    char idnr[15];
    char emer[30];
    char mbiemer[30];
    int ditelindja;
    int id_familja;
}*shtetasptr;
typedef struct shtetas Shtetas;

struct data {
    int dita;
    int muaji;
    int viti;
};
typedef struct data Data; 

struct leje{
    float ora;
    int dita = 0, muaji = 0, viti = 0;
    char id[15];
}*a[2000];
typedef struct leje Leje;
int size_leje[2000];// size i cdo pointeri

FILE *fptr2;

int counter = 0, size = 3; // variabla global
/* prototipet e funksioneve */
int menu();
void perzgjedhja();
void shto_shtetas();
void shto_shtetas(Shtetas qytetar);
void ndrysho_shtetas();
void ndrysho_shtetas(Shtetas qytetar);
void leje_dalje();
int mosha_lejuar(Shtetas q, Data d);
int aprovimi_lejes(Shtetas qytetar, Data d, float ora);
void hedhja_file(Shtetas qytetar, Data d, float ora);

int main(){
    FILE *fptr; // krijojme nje pointer qe pointon ne nje file
    if( (fptr=fopen("prov1.txt", "r")) == NULL ){
        printf("Gabim ne hapjen e file-it");
        return 0;
    }
    shtetasptr = (Shtetas*) malloc(size*sizeof(Shtetas)); // alokoj memorjen

    /*hedhim elementet e file ne pointerin dataptr */
    fseek(fptr, 37, SEEK_SET);// anashkalojme rreshtin e pare te file
    while(!feof(fptr)){ // derisa te arrijme ne fund te file-it
        fscanf(fptr, "%s", (shtetasptr+counter)->idnr );
        fscanf(fptr, "%s", (shtetasptr+counter)->emer );
        fscanf(fptr, "%s", (shtetasptr+counter)->mbiemer );
        fscanf(fptr, "%d", &(shtetasptr+counter)->ditelindja );
        fscanf(fptr, "%d", &(shtetasptr+counter)->id_familja );
        counter++;
        if(counter == size){// nese e kemi zene te gjithe memorjen e alokuar e dyfishojme ate
            size *= 2;
            shtetasptr = (Shtetas*) realloc(shtetasptr, size*sizeof(Shtetas));
        }
    }
    for(int i = 0; i < 2000; i++){ // alokojme memorien per secilin pointer te leje-daljes
    size_leje[i] = 1;
    a[i] = (Leje*) malloc(sizeof(Leje));
}
/*    for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (shtetasptr+i)->idnr, (shtetasptr+i)->emer, (shtetasptr+i)->mbiemer, (shtetasptr+i)->ditelindja, (shtetasptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
*/
    perzgjedhja();
    fclose(fptr);
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

void perzgjedhja(){
    int zgjedhja = menu();

    while(1){
        switch(zgjedhja){
            case 0:
                return;
                break;
            case 1:
                shto_shtetas();
                 for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (shtetasptr+i)->idnr, (shtetasptr+i)->emer, (shtetasptr+i)->mbiemer, (shtetasptr+i)->ditelindja, (shtetasptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
                break;
            case 2:
                ndrysho_shtetas();
                 for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", (shtetasptr+i)->idnr, (shtetasptr+i)->emer, (shtetasptr+i)->mbiemer, (shtetasptr+i)->ditelindja, (shtetasptr+i)->id_familja);
    }
    printf("\nKemi %d qytetare ", counter);
                break;
            case 3:
                leje_dalje();
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
}

void shto_shtetas(){
    Shtetas qytetar;
    printf("Vendosni IDNR : ");
    scanf("%s", qytetar.idnr);
    printf("Vendosni emrin : ");
    scanf("%s", qytetar.emer);
    printf("Vendosni mbiemrin : ");
    scanf("%s", qytetar.mbiemer);
    printf("Vendosni datelindjen (VVVVMMDD) : ");
    scanf("%d", &qytetar.ditelindja);
    printf("Vendosni ID e familjes : ");
    scanf("%d", &qytetar.id_familja);
    int i;
    for(i = 0; i < counter; i++){
        if( strcmp(qytetar.idnr,(shtetasptr+i)->idnr) == 0){
            printf("\nKy shtetas ndodhet ne liste\n");
            break;
        }
    }
    if(i == counter){ // tregon qe shtetasi eshte unik
        shto_shtetas(qytetar);
    } 
}

void shto_shtetas(Shtetas qytetar){
    int j, k;
    for(j = counter-1; j >= 0; j--){
            if(qytetar.id_familja == (shtetasptr+j)->id_familja ){
                for(k = counter-1; k > j; k--){
                    *(shtetasptr+k+1) = *(shtetasptr+k);
                }
                *(shtetasptr+j+1) = qytetar;
                break;
            }
        }
        if(j == -1){
            *(shtetasptr+counter) = qytetar;
        }
        counter++;
        size++;
        shtetasptr = (Shtetas*) realloc(shtetasptr, size*sizeof(Shtetas));
        return;
}

void ndrysho_shtetas(){
    Shtetas qytetar;
    printf("Vendosni IDNR e shtetasit : ");
    scanf("%s", qytetar.idnr);
    printf("Ndryshoni te dhenat :\n");
    printf("Vendosni emrin : ");
    scanf("%s", qytetar.emer);
    printf("Vendosni mbiemrin : ");
    scanf("%s", qytetar.mbiemer);
    printf("Vendosni datelindjen (VVVVMMDD) : ");
    scanf("%d", &qytetar.ditelindja);
    printf("Vendosni ID e familjes : ");
    scanf("%d", &qytetar.id_familja);

    ndrysho_shtetas(qytetar);
    return;
}

void ndrysho_shtetas(Shtetas qytetar){
    int i, j, k;
    for(i = 0; i < counter; i++){
        if(strcmp(qytetar.idnr, (shtetasptr+i)->idnr) == 0){
            strcpy((shtetasptr+i)->emer, qytetar.emer);
            strcpy((shtetasptr+i)->mbiemer, qytetar.mbiemer);
            (shtetasptr+i)->ditelindja = qytetar.ditelindja;
            (shtetasptr+i)->id_familja = qytetar.id_familja;
            /* e vendos ne vendin e duhur ne liste (Bubble sort) */
            Shtetas temp;
            for(j = 0; j < counter-1; j++){
                for(k = 0; k < counter-1-j; k++){
                    if( (shtetasptr+k)->id_familja > (shtetasptr+k+1)->id_familja ){
                            temp = *(shtetasptr+k);
                            *(shtetasptr+k) = *(shtetasptr+k+1);
                            *(shtetasptr+k+1) = temp;
                    }
                }
            }
            return;
        }
    } 
    printf("Ky shtetas nuk ndodhet ne sistem\n");
    return;
}


void leje_dalje(){
    Shtetas qytetar;
    Data d;
    printf("Vendosni ID e personit qe deshiron leje-dalje : ");
    scanf("%s", qytetar.idnr);
    int i;
    float ora;
    /* kontrollojme nese ekziston ky shtetas */
    for(i = 0; i < counter; i++){
        if(strcmp( (shtetasptr+i)->idnr, qytetar.idnr ) == 0){
            strcpy(qytetar.emer, (shtetasptr+i)->emer);
            strcpy(qytetar.mbiemer, (shtetasptr+i)->mbiemer);
            qytetar.ditelindja = (shtetasptr+i)->ditelindja;
            qytetar.id_familja = (shtetasptr+i)->id_familja;
        }
        break;
    }
    if(i == counter){// pra nuk u gjet nje shtetas me ate ID
        printf("Ky shtetas nuk ndodhet ne sistem!");
        return;
    }
    printf("Vendosni daten (diten/muajin/vitin) e daljes : ");
    scanf("%d %d %d",&d.dita, &d.muaji, &d.viti );
    printf("Vendosni oren (8.00-15.00) : ");
    scanf("%f", &ora);
    if(ora < 8 || ora > 15){
        printf("Orar i papranueshem!");
        return;
    }
    int mosha = mosha_lejuar(qytetar, d); 
    if(mosha == 0){
        return;
    }
    int aprovim = aprovimi_lejes(qytetar, d, ora);
    if(aprovim == 0){
        return;
    }
    hedhja_file(qytetar, d, ora);
    return;
}

int mosha_lejuar(Shtetas q, Data d){
    Data dtl;
    dtl.dita = q.ditelindja % 10;
    q.ditelindja /= 10;
    dtl.dita += (q.ditelindja % 10)*10;
    q.ditelindja /= 10;
    dtl.muaji = q.ditelindja % 10;
    q.ditelindja /= 10;
    dtl.muaji += (q.ditelindja % 10)*10;
    q.ditelindja /= 10;
    dtl.viti = q.ditelindja;

    if(d.viti-dtl.viti > 18){
        return 1;
    }
    else if (d.viti-dtl.viti < 18){
        printf("Shtetasi eshte nen 18 vjec!");
        return 0;
    }
    else {
        if(d.muaji > dtl.muaji){
            return 1;
        }
        else if (d.muaji < dtl.muaji){
            printf("Shtetasi eshte nen 18 vjec!");
            return 0;
        }
        else {
            if(d.dita >= dtl.dita){
                return 1;
            }
            else{
                printf("Shtetasi eshte nen 18 vjec!");
                return 0;
            }
        }
    }
}

int aprovimi_lejes(Shtetas qytetar, Data d, float ora){
    int i;
    for(i = 0; i < size_leje[qytetar.id_familja]; i++){
        if(d.viti == (a[qytetar.id_familja]+i)->viti && d.muaji  == (a[qytetar.id_familja]+i)->muaji && d.dita == (a[qytetar.id_familja]+i)->dita ){
            break;
        }
    }
    if(i == size_leje[qytetar.id_familja]){// tregon qe nuk u gjet asnje pjestar i familjes me leje ne ate date
        a[i-1]->dita = d.dita;
        a[i-1]->muaji = d.muaji;
        a[i-1]->viti = d.viti;
        a[i-1]->ora = ora;
        strcpy(a[i-1]->id, qytetar.idnr);
        size_leje[qytetar.id_familja]++;
        a[qytetar.id_familja] = (Leje*)realloc(a[qytetar.id_familja], size_leje[qytetar.id_familja]*sizeof(Leje));
        printf("Leja u pranua!");
        return 1;
    }
    else{
        printf("Eshte dhene nje leje per familjen tuaj ne ate dite!");
        return 0;
    }
}

void hedhja_file(Shtetas qytetar, Data d, float ora){
    if( (fptr2 = fopen("LejeDaljet.txt", "a")) == NULL){
        printf("Gabim ne hapjen e file-it");
        return;
    }
    fprintf(fptr2, "%s %d %d %d %.2f\n", qytetar.idnr, d.dita, d.muaji, d.viti, ora);
    fclose(fptr2);
    return;
}