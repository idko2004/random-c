#ifndef READSTDIN_H  /* Include guard */
#define READSTDIN_H

char * read_stdin(); //Lee el contenido de stdin hasta encontrar END OF FILE y lo devuelve en un char. Útil para leer pipes en bash. Puede devolver NULL si se encuentra con problemas.

#endif
