#ifndef STRARR_H  /* Include guard */
#define STRARR_H

typedef struct
{
	char ** str_arr; //La array donde se guardan los punteros hacia los strings
	int * arr_spaces_reserved; //La array donde se guarda la memoria reservada para cada string en str_arr
	int spaces_reserved; //La cantidad de punteros que puede guardar str_arr
	int length; //La cantidad de punteros que str_arr tiene actualmente
} Strarr;

int strarr_initialize(Strarr * strarr, int capacity); //Inicializa Strarr, debe ejecutarse justo después de crear Strarr

int strarr_push(Strarr * strarr, char * str); //Añade un string al final del array

char * strarr_get(Strarr * strarr, int index); //Obtiene el string guardado en el index especificado del array

#endif
