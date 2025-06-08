#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LRU(int dim, int *RAM, int ind, int c);

/*Sposta tutti gli elementi dell'array a destra di una posizione, perdendo l'ultimo elemento e duplicandom il primo*/
void right_shift(int dim, int *array);

/*Stampa l'array*/
void stampa_array(int* A, int dim);

/*Trova la posizione del valore val nell'array*/
int trova_posizione(int* A, int dim, int val);

int main(){

    int A[5]={4, 3, 2, 1, 0};
    int indirizzo=2;

    stampa_array(A, 5);

    LRU(5, A, indirizzo, 1);

    stampa_array(A, 5);
    
    return 0;
}

void LRU(int dim, int *RAM, int ind, int c){

    if(c==0){           //La pagina non e' in RAM e ne devo sostituire una

        //faccio scorrere tutti gli elementi della RAM avanti di una posizione (perdendo traquillamente l'ultimo perche' non ci serve)
        right_shift(dim, RAM);

        //aggiungo ind come primo elemento della RAM
        RAM[0]=ind;
    }
    else{               //La pagina e' gia' in RAM e devo solo portarla in testa
        //sposto gli elementi prima della pagina ind di un posto a destra
        right_shift(trova_posizione(RAM, dim, ind), RAM);

        //aggiungo ind come primo elemento della RAM
        RAM[0]=ind;
    }
    
}

void right_shift(int dim, int *array){
    for(int i = dim-1; i >= 0; i--){
        array[i+1] = array[i];
    }
}

//funzione di servizio
void stampa_array(int* A, int dim){
    printf("[");
    if(A != NULL & dim > 0){
        printf("%d", A[0]);
    }
    for(int i = 1; i < dim; i++){
        printf(",%d", A[i]);
    }
    printf("]");
}

int trova_posizione(int* A, int dim, int val){
    for(int i=0; i<dim; i++){
        if(*(A+i)==val)
            return i;
    }
}
