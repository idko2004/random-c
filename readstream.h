#ifndef READSTDIN_H  /* Include guard */
#define READSTDIN_H

#include <stdio.h>

char * read_stream_as_text(FILE * fileptr); //Lee el contenido de un stream hasta encontrar END OF FILE y lo devuelve en un char. Puede devolver NULL si se encuentra con problemas.

char * read_stdin(); //Lee stdin usando read_stream_as_text(), puede ser útil para leer pipes en bash

char * read_file_as_text(char * filepath); //Lee el archivo específicado como un string usando read_stream_as_text()

#endif
