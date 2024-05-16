#ifndef SPLITSTR_H  /* Include guard */
#define SPLITSTR_H

#include "strarr.h"

Strarr * split_string(char * input, char splitter); //Separa el string input en trozos cada que se encuentre el caracter splitter, y los guarda en un Strarr. Si el caracter splitter no está presente en input, se devuelve el input entero dentro del Strarr (strarr_get(arr, 0) == input). Si se encuentra con problemas, puede devolver NULL.

#endif
