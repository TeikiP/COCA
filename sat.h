#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all.h"

//Liste chainee de sommets
typedef struct List List;

struct List {
	int numero;
	int hauteur;
	List* next;
};

//Main
int main();

//Contraintes 1 a 4 telles que dans l'enonce
char* clause1(int k);
char* clause2(int k);
char* clause3(int k);
char* clause4(int k);

//Ecriture dans un fichier
void writeToFile(char* input, FILE* fichier);

//Affichage du graphe couvrant
void printSommets(int k, char* lastLine);

//Interpretation de la sortie de Glucose
List* readSommets(int k, char* lastLine);

//Construction de la liste chainee
List* storeSommet(int k, int valeur, List* sommets);
