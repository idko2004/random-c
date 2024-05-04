#ifndef STRARR_H  /* Include guard */
#define STRARR_H

typedef struct
{
	char ** str_arr; //La array donde se guardan los punteros hacia los strings
	int * arr_spaces_reserved; //La array donde se guarda la memoria reservada para cada string en str_arr
	int spaces_reserved; //La cantidad de punteros que puede guardar str_arr, se cuenta de la misma forma que length
	int length; //La cantidad de punteros que str_arr tiene actualmente
} Strarr;

int strarr_initialize(Strarr * strarr, int capacity); //Inicializa Strarr, debe ejecutarse justo después de crear Strarr

int strarr_expand_array(Strarr * strarr, int new_capacity); //Expande el array (str_arr) a la capacidad indicada, la capacidad indicada será el nuevo spaces_reserved

int strarr_expand_string(Strarr * strarr, int index, int new_capacity); //Expande un string ya establecido en el index indicado, con la capacidad indicada, la capacidad indicada ya debe incluir el caracter NULL

int strarr_push(Strarr * strarr, char * str); //Añade un string al final del array

char * strarr_get(Strarr * strarr, int index); //Obtiene el string guardado en el index especificado del array

#endif
