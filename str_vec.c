#include "str_vec.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


str_vec new_str_vec(){
    str_vec vec;
    vec.len = 0;
    vec.strings_len = 20;
    return vec;
}



int split_str_to_vec(char * str, char separator  , str_vec * vec){

    //Know how many separators there are.
        int how_many_separators_there_are = 0;
        for (int i = 0; i < strlen(str); ++i)
        {
            if( separator == str[i]){
                how_many_separators_there_are ++;
            }
        }


    //Create vector 
        vec->len = how_many_separators_there_are;
        vec->vector = (char **) calloc(vec->len ,sizeof(char*));

        if(vec->vector == NULL) return -1;

        //malloc space for every element.
        for (int i = 0; i < vec->len - 1; ++i)
        {
            vec->vector[i] = (char * ) malloc(vec->strings_len* sizeof(char) );
        }





    return 0;
}






int vec_push_back(str_vec * vec, const char * the_str){
    vec->len ++;

    if(vec->len - 1 == 0){
        vec->vector = (char **) calloc(1,sizeof(char*));
    }else{

        char ** aux_vector = (char **) realloc(vec->vector, vec->len * sizeof(char*));

        if(aux_vector != NULL)
            vec->vector = aux_vector;
        else
            return -1;

    }
    vec->vector[vec->len - 1] = (char * ) malloc(vec->strings_len* sizeof(char) );

    strcpy(vec->vector[vec->len - 1], the_str);

    return 0;
}


char * vec_get_back(str_vec * vec, int index){

    return vec->vector[index];

}


int vec_remove(str_vec * vec, int index){
    vec->len --;

    char ** new_vec = (char **) calloc(vec->len, sizeof(char*)  );

    
    if(new_vec == NULL) return -1;



    int sw = 0;
    for (int i = 0; i < vec->len + 1 ; ++i)
    {
        if(i != index){

            if(sw){
                new_vec[i - 1] = vec->vector[i];
            }else{
                new_vec[i ] = vec->vector[i];
            }
            
        }
        else
            sw = 1;
    }

    free(vec->vector[index]);
    free(vec->vector);   

    vec->vector = new_vec;


    return 0;
}



int vec_destroy(str_vec * vec){

    for (int i = 0; i < vec->len;  ++i)
    {
        free(vec->vector[i]);
    }


    free(vec->vector);
    vec->vector = NULL; 
    vec->len = 0;




    return 0;
}




/*
int main(int argc, char * argv[]){

    str_vec nombres = new_str_vec();


    vec_push_back(&nombres, "Marta");
    vec_push_back(&nombres, "Carlos");
    vec_push_back(&nombres, "Rosa");
    vec_push_back(&nombres, "Tamara");


    vec_remove(&nombres, 0);

    for(int i = 0; i < nombres.len; i++)
    {
        printf("%s\n", vec_get_back(&nombres, i));
    }
}
*/
