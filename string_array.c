#include "string_array.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT_DEBUG 1

String str_init(int max_length) //Crea un String struct
{
	int size = max_length * sizeof(char) + 1;
	if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_init max_length = %i, size = %i\n", max_length, size);
	
	String s;
	s.str = malloc(size);
	s.size_reserved = size;
	return s;
}

int str_copy(String * s, char * text) //Copia un string (char *) al String struct
{
	if(s == NULL || text == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_copy: *s or *text are null\n");
		return 1;
	}
	
	//if(PRINT_DEBUG == 1) fprintf(stderr, "-- strlen(text) = %i, size_reserved = %i\n", strlen(text), s->size_reserved);

	if(strlen(text) > (s->size_reserved)) //Reservar más espacio si no cabe
	{
		if(str_expand(s, strlen(text) + 1) != 0)
		{
			if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_copy: *s or *text are null\n");
			return 1;
		}
	}

	strcpy(s->str, text);
	return 0;
}

char * str_get(String * s) //Obtiene el string (char *) guardado en el String struct
{
	return s->str;
}

void str_destroy(String * s) //Libera la memoria del String struct
{
	free(s->str);
	free(s);
	s = NULL;
}

int str_expand(String * s, int new_length) //Aumenta la capacidad del string (char *) almacenado en el String struct
{
	if(s == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_expand: s is NULL\n");
		return 1;
	}

	int size = new_length * sizeof(char) + 1;
	if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_expand: size = %i\n", size);

	if(size <= (s->size_reserved))
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_expand: new size is smaller or the same than current size\n");
		return 1;
	}

	if(realloc(s->str, size) == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_expand: failed to expand\n");
		return 1;
	}

	s->size_reserved = size;

	return 0;
}



String_Arr strarr_init(int capacity) //Crear un nuevo struct que guarda un array del struct String
{
	int size = capacity * sizeof(String);

	String_Arr arr;
	arr.arr_str = malloc(size);
	arr.length = 0;
	arr.spaces_reserved = capacity;
	return arr;
}

int strarr_expand(String_Arr * arr, int new_capacity) //Expandir el array de String_Arr para que quepan más String struct en él
{
	if(arr == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_expand: s is NULL\n");
		return 1;
	}

	if(new_capacity <= (arr->spaces_reserved))
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_expand: new capacity is less or equals to current capacity\n");
		return 1;
	}

	int size = new_capacity * sizeof(String);
	if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_expand: new size will be %i\n", size);

	if(realloc(arr->arr_str, size) == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_expand: failed to expand\n");
		return 1;
	}

	arr->spaces_reserved = new_capacity;
	return 0;
}

int strarr_push_struct(String_Arr * arr, String * s) //Añadir un String struct al final del array
{
	if(arr == NULL || s == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_struct: arr or s are NULL\n");
		return 1;
	}

	if((arr->length) >= (arr->spaces_reserved)) //Comprobar si hay espacio
	{
		if(strarr_expand(arr, arr->length + 1) != 0)
		{
			if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_struct: String_Arr did not expand\n");
			return 1;
		}
	}

	arr->arr_str[arr->length] = *s;
	arr->length++;
	return 0;
}

int strarr_push_new_struct(String_Arr * arr, int str_length) //Crea un String struct y lo añade al final de String_Arr
{
	if(arr == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_new_struct: arr is NULL\n");
		return 1;
	}

	if((arr->length) >= (arr->spaces_reserved)) //Comprobar si hay espacio
	{
		if(strarr_expand(arr, arr->length + 1) != 0)
		{
			if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_struct: String_Arr did not expand\n");
			return 1;
		}
	}

	String s = str_init(str_length);

	if(strarr_push_struct(arr, &s) != 0)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_new_struct: Failed to push the String struct down to the String_Arr\n");
		return 1;
	}

	return 0;
}

String strarr_get_struct_at(String_Arr * arr, int index) //Obtener por valor el String struct en el índice dado
{
	if(index == -1)
	{
		index = arr->length - 1;
	}

	return arr->arr_str[index];
}

String * strarr_get_struct_ptr_at(String_Arr * arr, int index) //Obtener el puntero del String struct en el índice dado
{
	if(index == -1)
	{
		index = arr->length - 1;
	}

	return &arr->arr_str[index];
}

char * strarr_get_str_at(String_Arr * arr, int index) //Obtener el string (char *) almacenado en el array en el índice dado
{
	if(index == -1)
	{
		index = arr->length - 1;
	}

	return arr->arr_str[index].str;
}

int strarr_set_str_at(String_Arr * arr, int index, char * text) //Copiar un string (char *) a un String struct almacenado en un String_Array
{
	if(arr == NULL || text == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_set_str_at: arr or char are NULL\n");
		return 1;
	}

	if(index == -1)
	{
		index = arr->length - 1;
	}

	if(index < 0 || index >= (arr->length))
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_set_str_at: index out of bounds (%i out of %i)\n", index, arr->length);
		return 1;
	}

	String s = arr->arr_str[index];

	if(str_copy(&s, text) != 0)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_set_str_at: Failed to copy to %i\n", index);
		return 1;
	}

	return 0;
}

int strarr_push_new_struct_and_set_str(String_Arr * arr, char * text) //Crear un String struct, asignarle texto y ponerlo al final de String_Arr
{
	if(arr == NULL || text == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_new_struct_and_set_str: arr or char are NULL\n");
		return 1;
	}

	if(strarr_push_new_struct(arr, strlen(text)) != 0)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_new_struct_and_set_str: Failed to create and push new String struct\n");
		return 1;
	}

	if(strarr_set_str_at(arr, -1, text) != 0)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_new_struct_and_set_str: Failed to set text to newly created String struct\n");
		return 1;
	}

	return 0;
}

int main()
{
	/*
	printf("> str_init\n");
	String s = str_init(7);

	printf("> str_copy 1\n");
	str_copy(&s, "1234567");

	printf("%s\n", str_get(&s));

	printf("> str_expand\n");
	str_expand(&s, 10);

	printf("> str_copy 2\n");
	str_copy(&s, "1234567890");

	printf("%s\n", str_get(&s));

	printf("> strarr_init\n");
	String_Arr arr = strarr_init(1);

	printf("> strarr_push_struct 1\n");
	strarr_push_struct(&arr, &s);

	printf("> strarr_get_struct_ptr_at \n");
	String * strptr = strarr_get_struct_ptr_at(&arr, 0);

	printf("> strget at pointer\n");
	char * asdf = str_get(strptr);
	printf("%s\n", asdf);

	printf("> strarr_get_struct_at \n");
	String str = strarr_get_struct_at(&arr, 0);

	printf("> strget at value\n");
	char * asdfg = str_get(&str);
	printf("%s\n", asdfg);

	printf("> strarr_get_str_at\n");
	char * asdf1 = strarr_get_str_at(&arr, 0);
	printf("%s\n", asdf1);


	printf("> strarr_push_new_struct 1\n");
	strarr_push_new_struct(&arr, 25);

	printf("> strarr_push_new_struct 2\n");
	strarr_push_new_struct(&arr, 25);

	printf("> strarr_push_new_struct 3\n");
	strarr_push_new_struct(&arr, 25);

	printf("> strarr_push_new_struct_and_set_str\n");
	strarr_push_new_struct_and_set_str(&arr, "tapa la patata");

	printf("> get text from newly created and pushed String\n");
	char * asdfgh = strarr_get_str_at(&arr, -1);
	printf("%s\n", asdfgh);
	*/

	String_Arr arr = strarr_init(1);

	for(int i = 0; i < 20; i++)
	{
		printf("> strarr_push_new_struct_and_set_str %i\n", i);
		strarr_push_new_struct_and_set_str(&arr, "enemy lasagna robust below wax semiautomatiq aqua accompany slacks why coffee gymnastic motorcycle unibrow existential plastic nightly cow");
		printf("%i done\n", i);
	}
}
