#include "strarr.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT_DEBUG 1

int strarr_initialize(Strarr * strarr, int capacity)
{
	if(strarr == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_initialize: strarr is null\n");
		return 1;
	}

	if(capacity <= 0)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_initialize: capacity can't be that low\n");
		return 1;
	}

	strarr->str_arr = malloc(sizeof(void*) * capacity);
	strarr->arr_spaces_reserved = malloc(sizeof(int) * capacity);
	if(strarr->str_arr == NULL || strarr->arr_spaces_reserved == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_initialize: failed to allocate memory for the array\n");
		return 1;
	}

	for(int i = 0; i < capacity; i++) //Limpiar la array para que no tenga ram sucia
	{
		strarr->str_arr[i] = NULL;
		strarr->arr_spaces_reserved[i] = 0;
	}

	strarr->spaces_reserved = capacity;
	strarr->length = 0;

	return 0;
}

int strarr_expand_array(Strarr * strarr, int new_capacity)
{
	if(strarr == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_expand_array: strarr is null\n");
		return 1;
	}

	if(new_capacity < 1 || new_capacity < strarr->spaces_reserved)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_expand_array: this should be used to expand an array and not to shrink an array\n");
		return 1;
	}

	int new_str_arr_size = sizeof(void*) * new_capacity; //El calculo de tamaño viene de strarr_initialize
	int new_arr_spaces_reserved_size = sizeof(int) * new_capacity;

	void * new_str_arr = realloc(strarr->str_arr, new_str_arr_size);
	void * new_arr_spaces_reserved = realloc(strarr->arr_spaces_reserved, new_arr_spaces_reserved_size);

	if(new_str_arr == NULL || new_arr_spaces_reserved == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_expand_array: failed to expand arrays\n");
		return 1;
	}

	strarr->str_arr = new_str_arr;
	strarr->arr_spaces_reserved = new_arr_spaces_reserved;
	strarr->spaces_reserved = new_capacity;

	return 0;
}

int strarr_expand_string(Strarr * strarr, int index, int new_capacity)
{

}


int strarr_push(Strarr * strarr, char * str)
{
	if(strarr == NULL || str == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_push: strarr or str are null\n");
		return 1;
	}

	int index = strarr->length;

	if(index + 1 > strarr->spaces_reserved) //Expandir el array en caso de que no quepa
	{
		if(strarr_expand_array(strarr, index + 1) == 1)
		{
			//Hubo un problema expandiendo el array
			if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_push: array is too small to add a new string, tried to expand but failed\n");
			return 1;
		}
	}

	int str_length = strlen(str) + 1;

	char * copy = malloc(str_length); //Reservar espacio en memoria para el string
	if(copy == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_push: failed to allocate string\n");
		return 1;
	}

	strcpy(copy, str); //Copiar el string al nuevo espacio reservado

	strarr->str_arr[index] = copy; //Guardar el puntero en el array
	strarr->arr_spaces_reserved[index] = str_length; //Guardar el espacio reservado para el string
	strarr->length++;

	return 0;
}

char * strarr_get(Strarr * strarr, int index)
{
	if(strarr == NULL)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_get: strarr is null\n");
		return NULL;
	}

	if(index < 0 || index >= strarr->length)
	{
		if(PRINT_DEBUG >= 1) fprintf(stderr, "strarr_get: index out of bounds\n");
		return NULL;
	}

	char * result = strarr->str_arr[index];
	if(PRINT_DEBUG >= 1 && result == NULL) fprintf(stderr, "strarr_get: obtained string is null\n");

	return result;
}


int main()
{
		char * lyrics[] = 
	{
        "Twinkle", "twinkle", "little", "star",
        "How", "I", "wonder", "what", "you", "are",
        "Up", "above", "the", "world", "so", "high",
        "Like", "a", "diamond", "in", "the", "sky",
        "Twinkle", "twinkle", "little", "star",
        "How", "I", "wonder", "what", "you", "are"
    };

	Strarr arr;
	if(PRINT_DEBUG >= 1) fprintf(stderr, "main: initialize\n");
	strarr_initialize(&arr, 1);

	if(PRINT_DEBUG >= 1) fprintf(stderr, "main: loop\n");
	for(int i = 0 ; i < 32; i++)
	{
		printf(">>>%i\n", i);
		strarr_push(&arr, lyrics[i]);

		for(int j = 0; j < arr.length; j++)
		{
			printf("%i: %s\n", j, strarr_get(&arr, j));
		}
	}

	if(PRINT_DEBUG >= 1) fprintf(stderr, "main: push\n");
	strarr_push(&arr, "Enemy lasagna robust below wax");

	if(PRINT_DEBUG >= 1) fprintf(stderr, "main: get\n");
	printf("%s", strarr_get(&arr, 32));
	return 0;
}
