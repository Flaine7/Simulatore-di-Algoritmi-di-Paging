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
int ControlloFile(FILE **arr, int n);

//POST: Ritorna 1 se trova il numero n nella RAM, 0 altrimenti
int CercaPagina(int *RAM, int dimRAM, int n);

//POST: Ritorna 1 se la RAM e' piena, 0 altrimenti
int RAMPiena(int *RAM, int dimRAM);

//SPOST: Sposta tutti gli elementi dell'array di una posizione a destra (Duplicando il primo e perdendo l'ultimo)
void right_shift(int dim, int *array);

//POST: Trova la posizione dell'elemento val all'interno dell'array
int trova_posizione(int* A, int dim, int val);

int main(int argc, char *argv[]){

    if(argc != 5){
        printf("Numero incoretto di argomenti!");
        return 1;
    }

    int dimRAM = atoi(argv[1]);
    int alg = atoi(argv[2]);
    char PercorsoFile[100] = "";
    strcat(PercorsoFile, argv[3]);
    int nFileTraccia = atoi(argv[4]);

    //Creazione RAM fisica

    int RAM[dimRAM];

    for(int i = 0; i < dimRAM; i++){
        RAM[i] = -1; // -1 valore pari a VUOTO
    }

    const int dimPagina = 4096; // Dim. pagina

    //Lettura file

    FILE *pFile[nFileTraccia]; // Array che contiene i puntatori a tutti i file di traccia

    for(int i = 1; i <= nFileTraccia; i++){
        char str[2];
        sprintf(str, "%d", i);

        char NomeFile[20] = "";
        strcat(strcat(strcat(NomeFile, "Processo"), str), ".txt");

        char FileCompleto[200] = "";
        strcat(strcat(strcat(FileCompleto, PercorsoFile), "/"), NomeFile);

        pFile[i-1] = fopen(FileCompleto, "r");

        //printf("%s", FileCompleto);
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
                if(pFile[i] != NULL){
                    char s[50];
                    if(fgets(s, sizeof(s), pFile[i]) != NULL){
                        int ind = atoi(s);
                        ind = Pag_virtuale(ind, dimPagina);

                        if(CercaPagina(RAM, dimRAM, ind) == 0){ //Se 0 pagina non trovata in RAM
                            page_fault++;
                            if(RAMPiena(RAM, dimRAM) == 0){ //Se 0 c'e spazio libero in RAM
                                for(int k = dimRAM-1; k >= 0; k--){
                                    if(RAM[k] == -1){
                                        RAM[k] = ind;
                                        k = -1;
                                    }
                                }
                            }
                            else{
                                if(alg == 0){
                                    //FIFO
                                    FIFO(dimRAM, RAM, ind);
                                }
                                else{
                                    //LRU
                                    LRU(dimRAM, RAM, ind, 0);
                                }
                            }
                        }
                        else{
                            page_hit++;
                            if(alg != 0)
                            { //Metto la pagina usata in cima alla RAM se sto usando LRU
                                LRU(dimRAM, RAM, ind, 1);
                            }
                        }
                    }
                    else{
                        fclose(pFile[i]);
                        pFile[i] = NULL;
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

    fprintf(pf, "Page fault totali: %d\n", page_fault);
    fprintf(pf, "Page hit totali: %d\n", page_hit);
    fprintf(pf, "Fault rate complessivo: %f", (float)page_fault/(page_fault+page_hit));

    fclose(pf);

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

int ControlloFile(FILE **arr, int n){
    for(int i = 0; i < n; i++){
        if(*(arr + i) != NULL){
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
