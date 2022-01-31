#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MaxStates 100
#define MaxAlpha  15
#define nbrMaxBande 150
#define nbreAction  100


typedef struct {

    char currentState; // Etat courant
    char readSymb; 	// Symbole lu
    char nextState; // Etat suivant
    char writeSymb; // Symbole à écrire sur la bande de la Machine de Turing
    char direction; // Direction <, >, - Gauche, Droite et Stay exemple q0>

}TM_ptr;

typedef struct MT {
	char BANDE[nbrMaxBande];  // Bande semi finie
	char* Alphabet; // Alphabet
	char* EnsState; // Ensemble d etats
	unsigned int Cap; // Capacité de la bande
	TM_ptr table_transition[nbreAction]; // Matrice de transition C'est l'ensemble des transitions
	char CurrentState;  // Etat Courant
	unsigned int RdHeadPos;
    char readSb;

}TuringMachine;


TuringMachine initMT(char word[20], char file[100]);
void affiche_action(TM_ptr tm);
TuringMachine onePasCalculate(TuringMachine tm);
TuringMachine simulateTM(TuringMachine tm);
TuringMachine simulateTMa(TuringMachine tm);
int createmechineequi(char* file);



