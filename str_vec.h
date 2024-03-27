#ifndef STR_VEC_H   /* Include guard */
#define STR_VEC_H

typedef struct {
    int len;
    int strings_len;

    char ** vector ;

} str_vec;

str_vec new_str_vec();

int split_str_to_vec(char * str, char separator  , str_vec * vec);

int vec_push_back(str_vec * vec, const char * the_str);

char * vec_get_back(str_vec * vec, int index);

int vec_remove(str_vec * vec, int index);

int vec_destroy(str_vec * vec);

#endif
