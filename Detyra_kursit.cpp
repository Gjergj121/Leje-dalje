#include <stdio.h>
#include <stdlib.h>

struct data{
    char idnr[15];
    char emer[30];
    char mbiemer[30];
    int ditelindja;
    int id_familja;
}qytetar[5000];

/* prototipet e funksioneve */

int main(){
    FILE *fptr;
    if( (fptr=fopen("prov1.txt", "r")) == NULL ){
        printf("Gabim ne hapjen e file-it");
        return 0;
    }
    int counter = 0;
    /*hedhim elementet e file ne vektorin qytetar */
    fseek(fptr, 37, SEEK_SET);// anashkalojme rreshtin e pare
    while(!feof(fptr)){
        fscanf(fptr, "%s", qytetar[counter].idnr );
        fscanf(fptr, "%s", qytetar[counter].emer );
        fscanf(fptr, "%s", qytetar[counter].mbiemer );
        fscanf(fptr, "%d", &qytetar[counter].ditelindja );
        fscanf(fptr, "%d", &qytetar[counter].id_familja );
        counter++;
    }

    for(int i = 0; i < counter; i++){
        printf("%s %s %s %d %d\n", qytetar[i].idnr, qytetar[i].emer, qytetar[i].mbiemer, qytetar[i].ditelindja, qytetar[i].id_familja);
    }
    
    return 0;
}