#include "seed.h"

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int PRINT_DEBUG = 1;

int get_seed(time_t *seed)
{
	FILE *fileptr = fopen("seedfile", "rb");

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
	FILE *fileptr = fopen("seedfile", "wb");

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
