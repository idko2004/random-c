#include "split.h"
#include "strarr.h"

//#include "strarr.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PRINT_DEBUG 0

Strarr * split_string(char * input, char splitter)
{
	Strarr * arr = strarr_new(1);

	int input_length = strlen(input);
	int start = 0;
	int end = 0;

	for(int i = 0; i < input_length; i++)
	{
		if(input[i] == splitter)
		{
			end = i; //Marcar el index como el final de este trozo de string
			char * copy = malloc((end - start) * sizeof(char) + 1); //Reservar memoria para copiar el string, calculamos el tamaño a partir de la diferencia entre la última vez que encontramos un splitter (start) y en donde estamos ahora (end)
			memcpy(copy, &input[start], end - start); //Copiamos la memoria del input a partir del índice en el que estemos, y recorremos la diferencia de bytes que haya entre la vez anterior y ahora.
			copy[end-start] = '\0'; //NULL terminamos el string

			if(strarr_push(arr, copy)) //Copiamos el string al array
			{
				if(PRINT_DEBUG >= 1) fprintf(stderr, "[ERROR] split_string: can't push to strarr\n");
				return NULL;
			}
			//printf("%s\n", copy);

			start = i + 1;
			free(copy);
		}
	}

	if(arr->length == 0) //Si no se ha encontrado ningún splitter, guardar el input entero en la array
	{
		strarr_push(arr, input);
	}

	return arr;
}

