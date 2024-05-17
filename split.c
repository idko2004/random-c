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

	for(int i = 0; i < input_length; i++)
	{
		if(input[i] == splitter)
		{
			//start = donde empieza el string
			//i = end = donde termina el string

			int delta = i - start; //(i = end)
			char * copy = malloc((delta) * sizeof(char) + 1); //Reservar memoria para copiar el string, calculamos el tamaño a partir de la diferencia entre la última vez que encontramos un splitter (start) y en donde estamos ahora (end)
			memcpy(copy, &input[start], delta); //Copiamos la memoria del input a partir del índice en el que estemos, y recorremos la diferencia de bytes que haya entre la vez anterior y ahora.
			copy[delta] = '\0'; //NULL terminamos el string

			if(strarr_push(arr, copy)) //Copiamos el string al array
			{
				if(PRINT_DEBUG >= 1) fprintf(stderr, "[ERROR] split_string: can't push to strarr\n");
				return NULL;
			}
			//printf("%s\n", copy);

			start = i + 1; //Cambiar el inicio del siguiente string por el final de este.
			free(copy);
		}
	}

	if(arr->length == 0) //Si no se ha encontrado ningún splitter, guardar el input entero en la array
	{
		strarr_push(arr, input);
	}

	return arr;
}

