#!/bin/bash

# Verifica se il file C NON esiste ed esce
if ! test -f "Simulatore_Algoritmi_Paging.c"; then
    echo "File sorgente C non esiste."
    exit 1
fi

echo "Compilazione di file.c..."

#Compila il file e chiama l'eseguibile opt
gcc Simulatore_Algoritmi_Paging.c -o sim

# Verifica se l'eseguibile NON esiste ed esce
if ! test -f "sim"; then
    echo "L'eseguibile C non esiste."
    exit 1
else 
    echo -e "Compilazione riuscita.\n"
fi

#INPUT

echo "Inserire la dimesione della RAM (espressa in numero di page frame disponibili):"
read DimRAM

if [ $DimRAM -lt 1 ]; then
    echo "La RAM non puo' avere meno di 1 page frame."
    rm -f sim
    exit 1
fi

echo "Inserire il percorso della cartella contenente i file traccia (chiamati Processo*.txt):"
read PercorsoFile

if [ ! -d "$PercorsoFile" ]; then
    echo "$PercorsoFile non e' un percorso valido."
    rm -f sim
    exit 1
fi

#Conteggio numero file di tipo Processo*.txt contenuti nel directory PercorsoFile

dir="$PercorsoFile"
nFileTraccia=$(find "$dir" -type f -name Processo*.txt | wc -l)

#nFileTraccia=2

#ESECUZIONE
#FIFO

echo -e "\nFIFO in esecuzione..."

./sim $DimRAM 0 $PercorsoFile $nFileTraccia

c=$?

if [[ $c != 0 ]]; then
    echo "FIFO finito con errore."
    rm -f sim
    rm -f FIFO.txt
    exit 1
fi

#LRU

echo "LRU in esecuzione..."

./sim $DimRAM 1 $PercorsoFile $nFileTraccia

c=$?

if [[ $c != 0 ]]; then
    echo "LRU finito con errore."
    rm -f sim
    rm -f LRU.txt
    exit 1
fi

echo -e "\nRISULTATI DELLA SIMULAZIONE:"
echo -e "Frame disponibili: $DimRAM\n"

echo -e "\nFIFO dell'algoritmo:"
echo "$(cat FIFO.txt)"

echo -e "\nLRU dell'algoritmo:"
echo "$(cat LRU.txt)"

echo -e "\nPulizia dei file temporanei..."

rm -f FIFO.txt
rm -f LRU.txt
rm -f sim

echo "Script terminato"