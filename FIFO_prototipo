#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void FIFO(int dim, int *RAM, int ind);

/*Sposta tutti gli elementi dell'array a destra di una posizione, perdendo l'ultimo elemento e duplicandom il primo*/
void right_shift(int dim, int *array);

/*Stampa l'array*/
void stampa_array(int* A, int dim);

int main(){

    int A[5]={4, 3, 2, 1, 0};
    int indirizzo=5;

    stampa_array(A, 5);

    FIFO(5, A, indirizzo);

    stampa_array(A, 5);
    
    return 0;
}

void FIFO(int dim, int *RAM, int ind){

    //faccio scorrere tutti gli elementi della RAM avanti di una posizione (perdendo traquillamente l'ultimo perche' non ci serve)
    right_shift(dim, RAM);

    //aggiungo ind come primo elemento della RAM
    RAM[0]=ind;

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
