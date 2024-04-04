#include "seed.h"

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_DEBUG 1

char * seedfile_path = NULL;


void set_seedfile_path(char * path, char * program_folder)
{
	char * filename = "seed";

	if(path[strlen(path) - 1] == '/' || path[strlen(path) - 1] == '\\') //Remover el último caracter si es un / para que no haya un // sin querer
	{
		path[strlen(path) - 1] = '\0';
	}

	//Concatenar las dos partes
	seedfile_path = malloc(strlen(path) + strlen(program_folder) + strlen(filename) + 1);

	strcpy(seedfile_path, path);
	strcat(seedfile_path, program_folder);
	strcat(seedfile_path, filename);

	//Concatenar las dos partes (de una forma quizás no muy eficiente)
	//snprintf(seedfile_path, strlen(path) + strlen(end_part_of_path) + 1, "%s%s", path, end_part_of_path);

	if(PRINT_DEBUG == 1) fprintf(stderr, "seedfile path set to %s\n", seedfile_path);
}

void find_seedfile_path()
{
	char * random_c_path = getenv("RANDOM_C_PATH");
	if(random_c_path != NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "RANDOM_C_PATH variable found: %s\n", random_c_path);
		set_seedfile_path(random_c_path, "/");
		return;
	}

	char * xdg_data_home = getenv("XDG_DATA_HOME");
	if(xdg_data_home != NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "XDG_DATA_HOME variable found: %s\n", xdg_data_home);
		set_seedfile_path(xdg_data_home, "/idko2004-random-c/");
		return;
	}

	char * home = getenv("HOME");
	if(home != NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "HOME variable found: %s\n", home);
		set_seedfile_path(home, "/.local/share/idko2004-random-c/");
		return;
	}

	if(PRINT_DEBUG == 1) fprintf(stderr, "No RANDOM_C_PATH, XDG_DATA_HOME, or HOME env vars found\n");
	seedfile_path = "seed"; //Así debería crear el archivo en el directorio del proyecto o en pwd, no sé cual
}

int get_seed(time_t *seed)
{
	FILE *fileptr = fopen(seedfile_path, "rb");

	if(fileptr == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "Failed to open seed file as readable\n");
		return 1;
	}

	fread(seed, sizeof(*seed), 1, fileptr);
	fclose(fileptr);

	return 0;
}

int save_seed(time_t *seed)
{
	FILE *fileptr = fopen(seedfile_path, "wb");

	if(fileptr == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "Failed to open seed file as writable\n");
		return 1;
	}

	fwrite(seed, sizeof(*seed), 1, fileptr);
	fclose(fileptr);

	return 0;
}

void generate_seed()
{
	find_seedfile_path();

	time_t seed;
	int result = get_seed(&seed);

	if(result == 1) //File does not exist
	{
		time(&seed);
		save_seed(&seed);
		if(PRINT_DEBUG == 1) fprintf(stderr, "Default seed: %ld\n", seed);
		
		srand(seed);
		return;
	}

	time_t new_seed = time(NULL);

	if(PRINT_DEBUG == 1)
	{
		fprintf(stderr, "Old seed: %ld\n", seed);
		fprintf(stderr, "seed: %ld\n", new_seed);
	}

	if(seed == new_seed) //Same seed
	{
		seed += seed;
		save_seed(&seed);
		if(PRINT_DEBUG == 1) fprintf(stderr, "Same seed\nNew seed created: %ld\n", seed);
		
		srand(seed);
		return;
	}

	seed = new_seed;
	save_seed(&seed);

	srand(seed);
}
