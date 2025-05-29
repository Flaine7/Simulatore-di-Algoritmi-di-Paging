#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define QUANTUM 2

// ALGORITMI IN FILE SEPARATI
void FIFO();
void LRU();

// POST: Traduce gli indirizzi virtuali in numero di pagina virtuale
int Pag_virtuale(int ind,int dimPag);


int main(){

    int alg; // Scelta del algoritmo da usare
    scanf("%d", &alg);

    if(alg == 0){
        //Creo lista
    }

    //Creazione RAM fisica
    int dimRAM; // numero page frame
    scanf("%d", &dimRAM);

    int RAM[dimRAM];

    for(int i = 0; i < dimRAM; i++){
        RAM[i] = -1; // -1 valore pari a VUOTO
    }

    //SOPRA : Matilde
    const int dimPagina = 4096; // Dim. pagina 
    //SOTTO: David

    //Lettura file

    int nFileTraccia; // Numero dei file di traccia 
    scanf("%d", &nFileTraccia);

    FILE *pFile[nFileTraccia]; // Array che contiene i puntatori a tutti i file di tracci

    for(int i = 0; i < nFileTraccia; i++){
        char NomeFile[100]; // Variabile appoggio per poter memorizzare il nome del file
        scanf("%s", NomeFile); // Viene inserito il Nome del file, CON l'estensione .txt
        pFile[i] = fopen(strcat("tracce_indirizzi/",NomeFile), "r"); // !!! DA RIVEDERE !!!
    }

    for(int i = 0; i < nFileTraccia; i++){
        if(pFile[i] == NULL){
            fprintf(stderr,“Il file non può essere aperto\n”);
            return EXIT_FAILURE; // !!! Ricorda di aggiungere il controllo !!!
        }     
    }

    //Algoritmo principale (ricevo indirizzi, calcolo numero di pagina virtuale, )
    //Serve : tradurre gli indirizzi, vedere se ci sono gia' in RAM (algoritmo di ricerca), se no page fault, se devo rimpiazzare: algoritmo

    while(ControlloFile(pFile, nFileTraccia) == 1){
        for(int i = 0; i < nFileTraccia; i++){
            for(int j = 0; j < QUANTUM; j++){ // leggo fino a QUANTUM dento ogni file
                if(pFile[i] != -1){
                    char s[50];
                    if(fgets(s, sizeof(s), pFile[i]) != NULL){
                        int ind = atoi(s);
                        ind = Pag_virtuale(ind, dimPagina);
                        
                        if(CercaPagina(RAM, ind) == 0){ //Se 0 pagina non trovata in RAM
                            if(RAMPiena(RAM) == 0){ //Se 0 c'e spazio libero in RAM
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
                                    FIFO(RAM, ind);
                                }
                                else{
                                    //David
                                } 
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
}

int Pag_virtuale(int ind, int dimPag){
    return ind/dimPag;
}
