#include "playfair_by_me.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct  
{
    int r;
    int c;
} Pos ;


static int build_table(const char *key,char t[5][5], Pos T[26]){

    if(!key){
        return 0;
    }

    int index = 0;
    int seen[26] = {0};

    for(size_t i = 0; key[i] && index < 25; i++){
       
        char j = toupper(key[i]);
        


        if(key[i] == ' '){
            continue;
        }

        if(!isalpha((unsigned char)j)){
            return 0;
        }

        if(j == 'W'){
            j = 'V';
        }

        int k = j - 'A';

        if(k < 0 || k > 25){
            return 0;
        }

        if(!seen[k]){
            seen[k] = 1;
            t[index / 5][index % 5] = j;
            index++;
        }
        
    }

    for(size_t i = 0; ALPHA[i] && index < 25; i++){

        char j = ALPHA[i];

        if(!isalpha((unsigned char)j)){
            return 0;
        }

        j = toupper(ALPHA[i]);

        int k = j - 'A';

        if(j == 'W'){
            continue;
        }

        if(k < 0 || k > 25){
            return 0;
        }

        if(!seen[k]){
            seen[k] = 1;
            t[index / 5][index % 5] = j;
            index++;
        }

    }

    if(index != 25){
        return 0;
    }

    for(int r = 0; r < 5; r++){
        for(int c = 0; c < 5; c++){
            
            char a = t[r][c];

            T[a - 'A'].r = r;
            T[a - 'A'].c = c;
        }
        
    }

    return 1;
}

static char* prepare_text_for_encrypt(const char *text){

    if (text == NULL){
        return NULL;
    }
    
    size_t len = strlen(text);

    char *result = malloc(2 * len + 2);
    if (result == NULL){
        return NULL;
    }
    

    int j = 0;

    for (size_t i = 0; i < len; i++){
   
        if (text[i] == ' '){
            continue;
        }
        

        if (!(isalpha((unsigned char)text[i]))){
            free(result);
            return NULL;
        }

        
        char a = toupper(text[i]);

        if (a == 'W'){
            a = 'V';
        }

        size_t k = i + 1;

        while (k < len && text[k] == ' '){
             k++;
        }
  
        if (k >= len){
            result[j++] = a;
            break;
        }

        if (!isalpha(text[k])){
            free(result);
            return NULL;
        }


        char b = toupper(text[k]);

        if (b == 'W'){
            b = 'V';
        }

        if (a == b && a != 'X'){
            result[j++] = a;
            result[j++] = 'X';
        }

        else{
            result[j++] = a;
            result[j++] = b;
            i = k;
        }
    }

    if(j % 2 != 0){
        result[j++] = 'X';
    }

    result[j] = '\0';
    return result;
}

static char* prepare_text_for_decrypt(const char *text){

    if (text == NULL){
        return NULL;
    }
    
    size_t len = strlen(text);

    char *result = malloc(2 * len + 2);

    if (result == NULL){
        return NULL;
    }
    

    int j = 0;

    for (size_t i = 0; i < len; i++){
   
        if (text[i] == ' '){
            continue;
        }
        

        if (!(isalpha(text[i]))){
            free(result);
            return NULL;
        }

        char a = toupper(text[i]);

        if(a == 'W'){
            free(result);
            return NULL;
        }

        result[j++] = a;
    }

    if(j % 2 != 0){
        free(result);
        return NULL;
    }

    result[j] = '\0';
    return result;
}


char* playfair_encrypt(const char* key, const char* text){
   
    if(!key || !text){
        return NULL;
    }

    char t[5][5];
    Pos T[26];
    
    if(!build_table(key, t, T)){
        return NULL;
    }

    char *prepared = prepare_text_for_encrypt(text);

    if(!prepared){
        return NULL;
    }

    size_t len = strlen(prepared);
    char *encrypted = malloc(2 * len + 2);
    
    if(!encrypted){
        free(prepared);
        return NULL;
    }

    int a = 0;

    for(size_t i = 0; i < len; i +=2){

        char j = prepared[i];
        char k = prepared[i + 1];

        int r1 = T[j - 'A'].r;
        int r2 = T[k - 'A'].r;

        int c1 = T[j - 'A'].c;
        int c2 = T[k - 'A'].c;

        if(r1 == r2){
            encrypted[a++] = t[r1][(c1 + 1) % 5]; 
            encrypted[a++] = t[r2][(c2 + 1) % 5];
        }else if(c1 == c2){
            encrypted[a++] = t[(r1 + 1) % 5][c1];
            encrypted[a++] = t[(r2 + 1) % 5][c2];
        }else{
            encrypted[a++] = t[r1][c2];
            encrypted[a++] = t[r2][c1];
        }

        encrypted[a++] = ' ';

    }

    if(a > 0){
        a--;
    }

        encrypted[a] = '\0';
        free(prepared);

        return encrypted;
    

}


char* playfair_decrypt(const char* key, const char* text){

    if(!key || !text){
        return NULL;
    }

    char t[5][5];
    Pos T[26];

    if(build_table(key, t, T) == 0){
        return NULL;
    }

    char *prepared = prepare_text_for_decrypt(text);

    if(!prepared){
        return NULL;
    }

    size_t len = strlen(prepared);
    char *decrypted = malloc(2 * len + 2);
 
    if(!decrypted){
        return NULL;
    }

    int a = 0;

    for(size_t i = 0; i < len; i += 2){


        char j = prepared[i];
        char k = prepared[i + 1];

        int r1 = T[j - 'A'].r;
        int r2 = T[k - 'A'].r;

        int c1 = T[j - 'A'].c;
        int c2 = T[k - 'A'].c;

        if(r1 == r2){
            decrypted[a++] = t[r1][(c1 + 4) % 5];
            decrypted[a++] = t[r2][(c2 + 4) % 5];
        }else if(c1 == c2){
            decrypted[a++] = t[(r1 + 4) % 5][c1];
            decrypted[a++] = t[(r2 + 4) % 5][c2];
        }else{
            decrypted[a++] = t[r1][c2];
            decrypted[a++] = t[r2][c1];
        }

    }

    decrypted[a] = '\0';
    free(prepared);

    return decrypted;


}
