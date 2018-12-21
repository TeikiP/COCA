#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sat.h"
#include "all.h"

#define MAX_STRING_SIZE 500000

//Variables globales
int nbClauses;
int nbSommets;


//Fonction main.
//Doit etre appelee avec un entier positif pour unique argument.
int main(int argc, char **argv) {
	//Initialisation
	FILE* fichier;
	FILE* glucose;

	char* firstLine;
	char* clauses[4];
	char* output;

	nbClauses = 0;
	nbSommets = orderG();

	//Robustesse sur la hauteur
	if (argc == 1) {
		printf("Veuillez fournir une hauteur en argument (tel que \"./Sat 8\").\n");
		exit(0);
	}

	int k = (int) strtol(argv[1], NULL, 10);

	if (k < 0) {
		printf("La hauteur fournie doit etre positive.\n");
		exit(0);
	}

	//Ouverture du fichier
	fichier = NULL;
	fichier = fopen("sortie.txt", "w");

	if (fichier != NULL) {
		//Construction des clauses
		clauses[0] = clause1(k);
		clauses[1] = clause2(k);
		clauses[2] = clause3(k);
                clauses[3] = clause4(k);

		firstLine = malloc(sizeof(char)*MAX_STRING_SIZE);
		sprintf(firstLine, "p cnf %d %d\n", nbSommets*(k+1), nbClauses);

		//Ecriture dans le fichier
		writeToFile("c\n", fichier);
		writeToFile("c comments\n", fichier);
		writeToFile("c\n", fichier);
		writeToFile(firstLine, fichier);
		writeToFile(clauses[0], fichier);
                writeToFile(clauses[1], fichier);
                writeToFile(clauses[2], fichier);
                writeToFile(clauses[3], fichier);

		//Fermeture et destruction
		free(firstLine);
		free(clauses[0]);
                free(clauses[1]);
                free(clauses[2]);
                free(clauses[3]);

		fclose(fichier);
	}

	else {
		printf("Impossible d'ouvrir le fichier sortie.txt.\n");
		exit(0);
	}

	//Affichage standard
	printf("Hauteur : %d\n", k);
	printf("Nombre de sommets : %d\n", orderG());
	printf("Nombre d'arretes : %d\n", sizeG());
	printf("Nombre de variables : %d\n", nbSommets*(k+1));
	printf("Nombre de clauses : %d\n", nbClauses);

	//Execution de Glucose
	glucose = popen("./glucose-syrup-4.1/simp/glucose -model sortie.txt", "r");

	//Affichage de la sortie de Glucose
	output = malloc(sizeof(char)*MAX_STRING_SIZE);

	printf("\nOutput : \n");
	while(fgets(output, MAX_STRING_SIZE, glucose) != NULL)
		printf("%s", output);

	//Affichage de l'arbre couvrant si il existe
	printSommets(k, output);

	//Fermeture
	pclose(glucose);
	free(output);

	return 0;
}


//Fonction correspondant a la premiere contrainte de l'enonce.
//Prend la hauteur k en argument.
//Renvoie une chaine de caracteres correspondant aux clauses.
char* clause1(int k) {
        int i, j, a, b;
        char* convert = malloc(sizeof(char)*MAX_STRING_SIZE);
	char* clauses = malloc(sizeof(char)*MAX_STRING_SIZE);
	clauses[0] = 0;

	//Il existe au moins un entier j tel que X(i, j) est vrai (i represente le sommet, j represente la hauteur)
        for (i=0; i<nbSommets; i++) {
		for (j=0; j<=k; j++) {
			sprintf(convert, "%d ", i*(k+1)+j+1); //conversion de X(i, j) en une variable pour Glucose sous forme de string
			clauses = strcat(clauses, convert); //ajout aux clauses precedentes
		}

                clauses = strcat(clauses, "0\n"); //fin de clause
		nbClauses++;
        }

	//Il existe un unique entier a ou b tel que X(i, a || b) est vrai
	for (i=0; i<nbSommets; i++)
		for (a=0; a<=k; a++)
			for (b=0; b<=k; b++)
				if (a!=b) {
					sprintf(convert, "-%d -%d ", i*(k+1)+a+1, i*(k+1)+b+1); //conversion
					clauses = strcat(clauses, convert); //concatenation
					clauses = strcat(clauses, "0\n"); //fin de clause
					nbClauses++;
				}

        free(convert);
        return clauses;
}


//Fonction correspondant a la deuxieme contrainte de l'enonce.
//Prend la hauteur k en argument.
//Renvoie une chaine de caracteres correspondant aux clauses.
char* clause2(int k) {
        int i, j;
        char* convert = malloc(sizeof(char)*MAX_STRING_SIZE);
        char* clauses = malloc(sizeof(char)*MAX_STRING_SIZE);
	clauses[0] = 0;

	//Il y a au moins un sommet i de hauteur 0
	for (i=0; i<nbSommets; i++) {
		sprintf(convert, "%d ", i*(k+1)+1); //conversion
		clauses = strcat(clauses, convert); //concatenation
	}

	clauses = strcat(clauses, "0\n"); //fin de clause
	nbClauses++;

	//Il y a au plus un sommet de hauteur 0
	for (i=0; i<nbSommets; i++)
		for (j=0; j<nbSommets; j++)
			if (i != j) {
				sprintf(convert, "-%d -%d ", i*(k+1)+1, j*(k+1)+1); //conversion
				clauses = strcat(clauses, convert); //concatenation
				clauses = strcat(clauses, "0\n"); //fin de clause
				nbClauses++;
			}

	free(convert);
	return clauses;
}


//Fonction correspondant a la troisieme contrainte de l'enonce.
//Prend la hauteur k en argument.
//Renvoie une chaine de caracteres correspondant aux clauses.
char* clause3(int k) {
	int i;
	char* convert = malloc(sizeof(char)*MAX_STRING_SIZE);
	char* clauses = malloc(sizeof(char)*MAX_STRING_SIZE);
	clauses[0] = 0;

	//Il y au moins un sommet i de hauteur k
	for (i=0; i<nbSommets; i++) {
		sprintf(convert, "%d ", i*(k+1)+k+1); //conversion
		clauses = strcat(clauses, convert); //concatenation
	}


	clauses = strcat(clauses, "0\n"); //fin de clause
	nbClauses++;

	free(convert);
	return clauses;
}


//Fonction correspondant a la quatrieme contrainte de l'enonce.
//Prend la hauteur k en argument.
//Renvoie une chaine de caracteres correspondant aux clauses.
char* clause4(int k) {
        int i, j, u;
        char* convert = malloc(sizeof(char)*MAX_STRING_SIZE);
	char* clauses = malloc(sizeof(char)*MAX_STRING_SIZE);
        clauses[0] = 0;

	//Pour chaque sommet i de hauteur j > 0 ...
	for (i=0; i<nbSommets; i++) {
		for (j=1; j<=k; j++) {
			sprintf(convert, "-%d ", i*(k+1)+j+1); //conversion
			clauses = strcat(clauses, convert); //concatenation

			//... il existe un sommet u tel que u et v sont adjacents et u a pour hauteur j-1
			for (u=0; u<nbSommets; u++) {
				if ((i!=u) && (are_adjacent(i,u)==1)) {
					sprintf(convert, "%d ", u*(k+1)+j); //conversion
					clauses = strcat(clauses, convert); //concatenation
				}
			}

			clauses = strcat(clauses, "0\n"); //fin de clause
			nbClauses++;
		}
	}

	free(convert);
        return clauses;
}


//Prend comme argument une chaine de caractere et un pointeur sur un flux de sortie.
//Ecrit la chaine de caractere 'input' dans la sortie 'fichier'.
//Affiche une erreur a la sortie standard en cas de probleme.
void writeToFile(char* input, FILE* fichier) {
	if (fputs(input, fichier) == EOF)
		printf("Erreur a l'ecriture dans le fichier.\n");
}


//Affiche a la sortie standard une representation du graphe couvrant.
//A pour arguments la hauteur k (entier) et une chaine
//de caractere correspondant a la derniere ligne renvoyee par Glucose.
void printSommets(int k, char* lastLine) {
	List *sommets, *position, *parent;

	sommets = readSommets(k, lastLine);
	position = sommets;

	//Affiche les sommets
	while (position != NULL) {
		if (position->hauteur == 0)
		        printf("Sommet %d (avec hauteur %d)\n", position->numero, position->hauteur);

		else {
			parent = sommets;

			while (parent->hauteur+1 != position->hauteur || are_adjacent(parent->numero, position->numero) == 0)
				parent = parent->next;

	        	printf("Sommet %d (avec hauteur %d, ayant pour parent %d)\n", position->numero, position->hauteur, parent->numero);
		}

		position = position->next;
	}

	//Supprime les structures alloues
	while (sommets != NULL) {
		position = sommets->next;

		free(sommets);

		sommets = position;
	}
}


//Recoit en argument la hauteur k et la derniere ligne de Glucose.
//Parcours et enregistre tous les sommets correspondant au
//graphe couvrant tels que decris par cette derniere ligne.
//Renvoie une liste chainee des sommets
List* readSommets(int k, char* lastLine) {
	List* sommets = NULL;

	int i = 0;
        int valeur = 0;
        int positive = 0;

        while (lastLine[i++] != '\0') {
		//Si ce n'est pas une valeur, reset et sauvegarde de la valeur precedente
                if (lastLine[i] == ' ' || (lastLine[i] == '0' && lastLine[i-1] == ' ')) {
                        if (valeur > 0)
                                sommets = storeSommet(k, valeur, sommets);

			positive = 1;
                        valeur = 0;
                }

		//Si c'est une negation, ignorer
                else if (lastLine[i] == '-') {
                        positive = 0;
                }

		//Si c'est une valeur positive, la garder en memoire
                else if (positive == 1) {
                        valeur *= 10;
                        valeur += lastLine[i] - '0';
                }
        }

	return sommets;
}


//Enregistre un sommet represente par un entier
//dans Glucose dans une liste chainee de sommets.
//--------------------------------------------------
//Prend en arguments un entier representant la hauteur,
//un entier represenant le sommet sous Glucose, et
//un pointeur sur une liste chainee de sommets.
//--------------------------------------------------
//Renvoie la liste chainee de sommets completee
//avec le nouveau sommet.
List* storeSommet(int k, int valeur, List* sommets) {
	List* position = sommets;

	int hauteur = valeur % (k+1);
	if (hauteur == 0)
	        hauteur = k;
        else
                hauteur--;

        int n = (valeur-1-hauteur)/(k+1);


	//Si la liste chainee existe deja, ajouter la nouvelle valeur
	if (sommets != NULL) {
		while (position->next != NULL)
			position = position->next;

		position->next = malloc(sizeof(List));
		position = position->next;
		position->numero = n;
		position->hauteur = hauteur;
		position->next = NULL;
	}

	//Sinon, creer la valeur initiale de la liste chainee
	else {
		sommets = malloc(sizeof(List));
		sommets->numero = n;
		sommets->hauteur = hauteur;
		sommets->next = NULL;
	}

	return sommets;
}
