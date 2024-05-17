#include "readstdin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT_DEBUG 1

#define BUFFER_INCREMENTS 10
#define READ_SIZE 10 //Make sure READ_SIZE is not bigger than BUFFER_INCREMENTS

char * read_stdin()
{
	int buffer_used_size = 0;
	int buffer_available_size = sizeof(char) * BUFFER_INCREMENTS;
	char * buffer = malloc(buffer_available_size);

	if(PRINT_DEBUG >= 1) fprintf(stderr, "result:%s, result_size:%d\n", buffer, buffer_available_size);

	while(1)
	{
		if(buffer_used_size + READ_SIZE <= buffer_available_size) //Expandir el buffer
		{
			buffer_available_size += sizeof(char) * BUFFER_INCREMENTS;
			buffer = realloc(buffer, buffer_available_size);

			if(buffer == NULL)
			{
				if(PRINT_DEBUG >= 1) fprintf(stderr, "[ERROR] Failed to expand buffer to read stdin.\n");
				return NULL;
			}
		}

		char * new_read = malloc(sizeof(char) * READ_SIZE); //Crear el espacio en donde se va a leer stdin

		int read_result = fread(new_read, sizeof(char), READ_SIZE, stdin); //Leer sdtin, leer sizeof(char), READ_SIZE veces, si READ_SIZE es 10, se leen 10 bytes

		if(PRINT_DEBUG >= 1) fprintf(stderr, "[INFO] Read bytes: %d.\n", read_result);

		memcpy(buffer + buffer_used_size, new_read, sizeof(char) * READ_SIZE); //Copiar lo leído de new_read a buffer, pero con un padding para no sobreescribir lo que ya habíamos leído originalmente, el padding se cuenta en buffer_used_size

		free(new_read);

		buffer_used_size += read_result;

		if(feof(stdin))
		{
			if(PRINT_DEBUG >= 1) fprintf(stderr, "[INFO] stdin ended.\n");
			break;
		}
	}

	buffer[buffer_used_size] = '\0'; //NULL terminar el buffer para que sea un buen string

	if(PRINT_DEBUG >= 1) fprintf(stderr, "result:%s\navailable size:%d\nused size:%d\n", buffer, buffer_available_size, buffer_used_size);

	return buffer;
}
