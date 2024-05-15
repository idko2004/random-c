#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strarr.h"
#include "seed.h"

void print_help()
{
	printf("Usage:\n\trandom [PARTICIPANTS]\n\trandom [OPTION]\n\nOptions:\n\t-h, --help\tPrint this screen.\n\t-d, --dice N\tGenerate a random number between 1 and N, by default N is 6.\n");
}

int list_mode(int argc, char *argv[])
{
	Strarr *  participants = strarr_new(argc);

	for(int i = 1; i < argc; i++) //Usar los argumentos como participantes
	{
		strarr_push(participants, argv[i]);
	}

	if(participants->length < 2)
	{
		if(participants->length == 0) print_help();
		else fprintf(stderr, "Not enough participants\n");
		
		return 1;
	}

	int r = rand() % participants->length; //Sacar el resto de r con el número de participantes, así siempre está in-bounds.

	if(r < 0) r *= -1; //Si el número es negativo, hacerlo positivo.
	
	char *winner = strarr_get(participants, r);

	printf("%s\n", winner);

	return 0;
}

int dice_mode(int argc, char *argv[])
{
	long int max = 6;

	if(argc > 2)
	{
		char *n = malloc(strlen(argv[2]) + 1); //Alojar memoria para copiar el string de argv[2]
		strcpy(n, argv[2]);
		char *endptr; //Al parecer hay que declarar un char justo después para que sepa donde parar

		max = strtol(n, &endptr, 10); //Convertir string a long int
	}

	if(max < 2) //Comprobar si el número es válido, no es negativo, ni es 1, strtol devuelve 0 si el número no es válido así que también eso.
	{
		fprintf(stderr, "Maybe that isn't a valid number.\n");
		return 1;
	}

	long int r = (rand() % max) + 1;
	if(r < 0) r *= -1;

	printf("%ld\n", r);

	return 0;
}

int main(int argc, char *argv[])
{
	generate_seed();

	if(argc < 2)
	{
		if(argc == 1) print_help();
		else fprintf(stderr, "Not enough participants\n");

		return 1;
	}

	char *command = argv[1];

	if(command == NULL) //En principio debería ser false siempre, pero por si acaso.
	{
		fprintf(stderr, "Not enough participants\n");
		return 1;
	}

	if(strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0)
	{
		print_help();
		return 0;
	}
	else if(strcmp(command, "-d") == 0|| strcmp(command, "--dice") == 0)
	{
		return dice_mode(argc, argv);
	}
	else
	{
		return list_mode(argc, argv);
	}
}

