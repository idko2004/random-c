#ifndef STRING_ARRAY_H  /* Include guard */
#define STRING_ARRAY_H

typedef struct 
{
    int size_reserved;
    char * str;
}String; //Permite guardar un string (char *)

typedef struct
{
    int length;
    int spaces_reserved;
    String ** arr_str;
}String_Arr; //Permite guardar un array de String struct

String str_init(int max_length);

int str_copy(String * s, char * text);

char * str_get(String * s);

void str_destroy(String * s);

int str_expand(String * s, int new_length);



String_Arr strarr_init(int capacity);



#endif
