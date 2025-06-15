#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QUANTUM 2

// ALGORITMI IN FILE SEPARATI
void FIFO(int dim, int *RAM, int ind);
void LRU(int dim, int *RAM, int ind, int c);

//POST: Traduce gli indirizzi virtuali in numero di pagina virtuale
int Pag_virtuale(int ind,int dimPag);

//POST: Ritorna 0 se tutti gli elementi dell'array da 0 a n sono pari a -1, 1 altrimenti
int ControlloFile(int *arr, int n);

//POST: Ritorna 1 se trova il numero n nella RAM, 0 altrimenti
int CercaPagina(int *RAM, int dimRAM, int n);

//POST: Ritorna 1 se la RAM e' piena, 0 altrimenti
int RAMPiena(int *RAM, int dimRAM);

//SPOST: Sposta tutti gli elementi dell'array di una posizione a destra (Duplicando il primo e perdendo l'ultimo)
void right_shift(int dim, int *array);

//POST: Trova la posizione dell'elemento val all'interno dell'array
int trova_posizione(int* A, int dim, int val);

int main(int dimRAM, int alg, char PercorsoFile[100], int nFileTraccia){

    //Creazione RAM fisica

    int RAM[dimRAM];

    for(int i = 0; i < dimRAM; i++){
        RAM[i] = -1; // -1 valore pari a VUOTO
    }

    const int dimPagina = 4096; // Dim. pagina

    //Lettura file

    FILE *pFile[nFileTraccia]; // Array che contiene i puntatori a tutti i file di tracci

    for(int i = 1; i <= nFileTraccia; i++){
        char NomeFile[20] = strcat(strcat("Processo", snprintf(i)), ".txt");
        pFile[i-1] = fopen(strcat(strcat(PercorsoFile, "/"), NomeFile), "r");
    }

    for(int i = 0; i < nFileTraccia; i++){
        if(pFile[i] == NULL){
            printf("Il file non può essere aperto\n");
            return 1;
        }
    }

    //Algoritmo principale (ricevo indirizzi, calcolo numero di pagina virtuale, )
    //Serve : tradurre gli indirizzi, vedere se ci sono gia' in RAM (algoritmo di ricerca), se no page fault, se devo rimpiazzare: algoritmo

    int page_fault = 0, page_hit = 0;

    while(ControlloFile(pFile, nFileTraccia) == 1){
        for(int i = 0; i < nFileTraccia; i++){
            for(int j = 0; j < QUANTUM; j++){ // leggo fino a QUANTUM dento ogni file
                if(pFile[i] != -1){
                    char s[50];
                    if(fgets(s, sizeof(s), pFile[i]) != NULL){
                        int ind = atoi(s);
                        ind = Pag_virtuale(ind, dimPagina);

                        if(CercaPagina(RAM, dimRAM, ind) == 0){ //Se 0 pagina non trovata in RAM
                            page_fault++;
                            if(RAMPiena(RAM, dimRAM) == 0){ //Se 0 c'e spazio libero in RAM
                                for(int k = 0; k < dimRAM; k++){
                                    if(RAM[k] == -1){
                                        RAM[k] = ind;
                                        k = dimRAM;
                                    }
                                }
                            }
                            else{
                                if(alg == 0){
                                    //FIFO
                                    FIFO(dimRAM, RAM, ind);
                                }
                                else{
                                    //David
                                    LRU(dimRAM, RAM, ind, 0);
                                }
                            }
                        }
                        else{ //Metto la pagina usata in cima alla RAM se sto usando LRU
                            page_hit++;
                            if(alg != 0)
                            {
                                LRU(dimRAM, RAM, ind, 1);
                            }
                        }
                    }
                    else{
                        fclose(pFile[i]);
                        pFile[i] = -1;
                    }
                }
            }
        }
    }

    FILE* pf;
    if(alg == 0){
        pf = fopen("FIFO.txt","w");
    }
    else{
        pf = fopen("LRU.txt","w");
    }
    if(pf == NULL){
        printf("Il file non può essere aperto\n");
        return 1;
    }

    fprintf(pf, "FIFO dell'algoritmo:");
    fprintf(pf, "Page fault totali: %d", page_fault);
    fprintf(pf, "Page hit totali: %d", page_hit);
    fprintf(pf, "Fault rate complessivo: %f", (float)page_fault/(page_fault+page_hit));

    return 0;
}

void FIFO(int dim, int *RAM, int ind){

    //faccio scorrere tutti gli elementi della RAM avanti di una posizione (perdendo traquillamente l'ultimo perche' non ci serve)
    right_shift(dim, RAM);

    //aggiungo ind come primo elemento della RAM
    RAM[0]=ind;

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

int Pag_virtuale(int ind, int dimPag){
    return ind/dimPag;
}

int ControlloFile(int *arr, int n){
    for(int i = 0; i < n; i++){
        if(*(arr+i) != -1){
            return 1;
        }
    }

    return 0;
}

int CercaPagina(int *RAM, int dimRAM, int n){
    for(int i = 0; i < dimRAM; i++){
        if(*(RAM+i) == n){
            return 1;
        }
    }

    return 0;
}

int RAMPiena(int *RAM, int dimRAM){
    for(int i = 0; i < dimRAM; i++){
        if(*(RAM + i) == -1){
            return 0;
        }
    }

    return 1;
}

void right_shift(int dim, int *array){
    for(int i = dim-1; i >= 0; i--){
        array[i+1] = array[i];
    }
}

int trova_posizione(int* A, int dim, int val){
    for(int i=0; i<dim; i++){
        if(*(A+i)==val)
            return i;
    }
}
