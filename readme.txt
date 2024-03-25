i due modelli impleentano due versioni leggermente diverse della soluzione ricorsiva. 
sudoku.c controlla ad ogni ricorsione la validita' della ricorsione mentre sudokuCopy.c
grazie a tre tabelle riesce a verificare con accesso diretto se e' possibile o meno inserire
il numero corrente nella posizione identificata da pos, ognuna delle tre tabelle ha una riga per ogni
numero e in questo vettore ogni entrata corrisponde a una riga/colonna/quadrato, i valori possono essere
zero (nella riga/colonna/quadrato non c'e' amcora nessuna occorrenza di quel simbolo) oppure uno (... c'e' una
occorrenza del simbolo)