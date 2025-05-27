#include<stdio.h>

#define QUANTUM 2

// ALGORITMI IN FILE SEPARATI
void FIFO();
void LRU();

// POST: Traduce gli indirizzi virtuali in numero di pagina virtuale
int Pag_virtuale(int s,int dimPag);


int main(){

    int alg; // Scelta del algoritmo da usare
    scanf("%d", &dimRAM);

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
    FILE *pf1 = fopen("tracce_indirizzi/processo1.txt","r"), *pf2 = fopen("tracce_indirizzi/processo2.txt","r"); //apro in lettura i file traccia

    if(pf1 == NULL || pf2 == NULL){
        fprintf(stderr,“Il file non può essere aperto\n”);
        return EXIT_FAILURE;
    }

    //Algoritmo principale (ricevo indirizzi, calcolo numero di pagina virtuale, )
    //Serve : tradurre gli indirizzi, vedere se ci sono gia' in RAM (algoritmo di ricerca), se no page fault, se devo rimpiazzare: algoritmo

    for(int j = 0; j < QUANTUM; j++){ // leggo fino a QUANTUM dento ogni file
        char s[50];
        fgets(s, sizeof(s), pf1); 
        //... TRASFORMARE IN INTERO ...
        Pag_virtuale(s, dimPagina);
        if(alg == 0){
            // ...
        }
        else{
            // ...
        }
    }
    for(int j = 0; j < QUANTUM; j++){ // leggo fino a QUANTUM dento ogni file
        char s[50];
        fgets(s, sizeof(s), pf2);
        //... TRASFORMARE IN INTERO ...
        Pag_virtuale(s, dimPagina);
        if(alg == 0){
            // ...
        }
        else{
            // ...
        }
    }

    fclose(pf1);
    fclose(pf2);

}
