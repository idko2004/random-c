#include "string_array.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT_DEBUG 1

String str_init(int max_length)
{
	int size = max_length * sizeof(char) + 1;
	if(PRINT_DEBUG == 1) fprintf(stderr, "-- str_init max_length = %i, size = %i\n", max_length, size);
	
	String s;
	s.str = malloc(size);
	s.size_reserved = size;
	return s;
}

int str_copy(String * s, char * text)
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

char * str_get(String * s)
{
	return s->str;
}

void str_destroy(String * s)
{
	free(s->str);
	free(s);
	s = NULL;
}

int str_expand(String * s, int new_length)
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



String_Arr strarr_init(int capacity)
{
	int size = capacity * sizeof(String);

	String_Arr arr;
	arr.length = 0;
	arr.spaces_reserved = size;
	return arr;
}

int strarr_push_string(String_Arr * arr, String * s)
{
	if(arr == NULL || s == NULL)
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_string: arr or s are NULL\n");
		return 1;
	}

	if((arr->length) >= (arr->spaces_reserved)) //Comprobar si hay espacio
	{
		if(PRINT_DEBUG == 1) fprintf(stderr, "-- strarr_push_string is not yet capable of expanding\n");
		return 1;
	}

	arr->arr_str[arr->length] = s;
	arr->length++;
	return 0;
}


int main()
{
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

	printf("> strarr_push_string 1\n");
	strarr_push_string(&arr, &s);
}
