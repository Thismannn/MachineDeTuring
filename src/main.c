
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "machine.h"




int main(int argc, char **argv)
{
	
    printf("Welcome!\n");
    TuringMachine tm;
    
    //Mettre comme premier parametre le mot à lire et en deuxième le code de la machine a utiliser
    
    tm = initMT("11011011","Palindrome.txt");

    affiche_action(tm.table_transition[5]);
    tm = simulateTMa(tm);
    if(tm.CurrentState=='D' && tm.readSb =='_')
        printf("Le mot a été lu avec succès par l'automate\n");
    else

        printf("Ce  mot n'a pas pu etre lu \n");

    // Creation d'une machine de Turing en remplaçant l'alphabet {'a','b','c','d'} par l'alphabet {'00','01','10','11'}

    //createmechineequi("turingmach1.txt");

    return 0;
}
