#include<stdio.h>
#include<string.h>

#define QUANTUM 2

// ALGORITMI IN FILE SEPARATI
void FIFO();
void LRU();

// POST: Traduce gli indirizzi virtuali in numero di pagina virtuale
int Pag_virtuale(int ind,int dimPag);


int main(){

    int alg; // Scelta del algoritmo da usare
    scanf("%d", &alg);

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

    FILE *File[nFileTraccia]; // Array che contiene i puntatori a tutti i file di tracci

    for(int i = 0; i < nFileTraccia; i++){
        char NomeFile[100]; // Variabile appoggio per poter memorizzare il nome del file
        scanf("%s", NomeFile); // Viene inserito il Nome del file, CON l'estensione .txt
        File[i] = fopen(strcat("tracce_indirizzi/",NomeFile), "r"); // !!! DA RIVEDERE !!!
    }

    for(int i = 0; i < nFileTraccia; i++){
        if(File[i] == NULL){
            fprintf(stderr,“Il file non può essere aperto\n”);
            return EXIT_FAILURE; // !!! Ricorda di aggiungere il controllo !!!
        }     
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

    for(int i = 0; i < nFileTraccia; i++){
        fclose(File[i]);
    }

}

int Pag_virtuale(int ind, int dimPag){
    return ind/dimPag;
}
