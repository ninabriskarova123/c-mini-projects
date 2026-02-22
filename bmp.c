#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

char* reverse(const char* text){

    if(!text){
        return NULL;
    }

    size_t len = strlen(text);

    char *result = malloc(len + 1);

    if(!result){
        free(result);
        return NULL;
    }

    int a = 0;

    for(size_t i = len; i > 0; i--){

        char j = toupper(text[i - 1]);

        result[a++] = j;

        
    }

    result[a] = '\0';
    return result;
}

char* vigenere_encrypt(const char* key, const char* text){

    if(!key || !text){
        return NULL;
    }

    size_t len = strlen(text);
    char *encrypted = malloc(len + 1);

    if(!encrypted){
        free(encrypted);
        return NULL;
    }

    size_t len_key = strlen(key);

    if(!len_key){

        return NULL;
    }

    int a = 0;
    int b = 0;
    
    for(size_t i = 0; text[i] != '\0'; i++){

       char j = text[i];

       if(!isalpha(j)){

        encrypted[b++] = text[i];
        continue;

       }

       char text_char = toupper(j);

       int text_index = text_char - 'A';

       char key_char = toupper(key[a % len_key]);

       int key_index = key_char - 'A';

       int value = (text_index + key_index) % 26;

       int new_char  = value + 'A';

       encrypted[b++] = new_char;
       a++;

    }

    encrypted[b] = '\0';

    return encrypted;

}

char* vigenere_decrypt(const char* key, const char* text){
   
    if(!key || !text){
        return NULL;
    }

    size_t len = strlen(text);
    char *decrypted = malloc(len + 1);


    if(!decrypted){
        free(decrypted);
        return NULL;
    }

    size_t len_key = strlen(key);

    if(!len_key){
        return NULL;
    }

    int a = 0;
    int b = 0;

    for(size_t i = 0; text[i] != '\0'; i++){

        char j = toupper(text[i]);


        if(!isalpha(j)){
            decrypted[b++] = j;
            continue;
        }

        int index_char = j - 'A';

        char k = toupper(key[a % len_key]);

        int index_key = k - 'A';

        int value = (index_char - index_key + 26) % 26;

        int new_char = value + 'A';
        decrypted[b++] = new_char;
        a++;

    }

    decrypted[b] = '\0';
    return decrypted;
    
}

unsigned char* bit_encrypt(const char* text){

    if(!text){
        return NULL;
    }

    size_t len = strlen(text);
    unsigned char *encrypted = malloc(len + 1);

    if(!encrypted){
        free(encrypted);
        return NULL;
    }

    int a = 0;

    for(size_t i = 0; text[i] != '\0'; i++){

        char byte = text[i];

        char half_high = (byte >> 4) & 0x0F;
        char half_low = byte & 0x0F;

        char change_high = ((half_high & 0xA) >> 1) | ((half_high & 0x5) << 1);

        char new_low = half_low ^ change_high;

        encrypted[a++] = (change_high << 4) | new_low; 

    }

    encrypted[a] = '\0';

    return encrypted;

}

char* bit_decrypt(const unsigned char* text){

    if(!text){
        return NULL;
    }

    size_t len = strlen((const char*)text);
    char *decrypted = malloc(len + 1);

    if(!decrypted){
        free(decrypted);
        return NULL;
    }

    int a = 0;


    for(size_t i = 0; text[i] != '\0'; i++){
        
        char byte = text[i];

        char change_high = (byte >> 4) & 0x0F; 
        char new_low = byte & 0x0F;        

        char half_low = new_low ^ change_high; 

        char half_high =((change_high & 0x0A) >> 1) | ((change_high & 0x05) << 1);                

        decrypted[a++] = (half_high << 4) | half_low;  

    }

    decrypted[a] = '\0';

    return decrypted;

}


unsigned char* bmp_encrypt(const char* key, const char* text){

        if(!key || !text){
            return NULL;
        }

        char* reversed = reverse(text);

        if(!reversed){
            return NULL;
        }

        char* vig = vigenere_encrypt(key, reversed);

        if(!vig){
            free(reversed);
            return NULL;
        }
        
           free(reversed);

        unsigned char* result = bit_encrypt(vig);

        if(!result){
            free(vig);
            return NULL;
        }

        free(vig);

        return result;

}

char* bmp_decrypt(const char* key, const unsigned char* text){

    if(!text || !key){
        return NULL;
    }

    unsigned char* bit = bit_decrypt(text);

    if(!bit){
        return NULL;
    }

    char* vig = vigenere_decrypt(key, bit);

    if(!vig){
        free(bit);
        return NULL;
    }

    free(bit);

    char* result = reverse(vig);

    if(!result){
        free(vig);
        return NULL;
    }

    free(vig);

    return result;

}

int main(){
   /* char* reversed = reverse("Hello world!");
printf("%s\n", reversed);

char* encrypted;

// basic test with long text
encrypted = vigenere_encrypt("CoMPuTeR", "Nina!");
printf("%s\n", encrypted);
// "JSXAI PSINR!"
*/


  /*
   const char* text = "Hello World!";

    // ENCRYPT
    unsigned char* encrypted = bit_encrypt(text);

    printf("Encrypted (hex): ");
    for (int i = 0; i < strlen(text); i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");

    // DECRYPT
    char* decrypted = bit_decrypt(encrypted);

    printf("Decrypted text: %s\n", decrypted);

    // Kontrola
    if (strcmp(text, decrypted) == 0)
        printf("OK - decrypt funguje\n");
    else
        printf("ERROR - decrypt nefunguje\n");

    free(encrypted);
    free(decrypted);
    */

    /*
     const char* key  = "CoMPuTeR";
    const char* text = "Hello world!";

    char* enc = vigenere_encrypt(key, text);
    printf("Encrypted: %s\n", enc);   // očakáva sa: "JSXAI PSINR!"

    char* dec = vigenere_decrypt(key, enc);
    printf("Decrypted: %s\n", dec);   // očakáva sa: "HELLO WORLD!"

    // kontrola
    if (strcmp(dec, "HELLO WORLD!") == 0) printf("OK\n");
    else printf("ERROR\n");

    free(enc);
    free(dec);

    */
    const char* key  = "keY";
    const char* text = "ahoj";

    unsigned char* encrypted = bmp_encrypt(key, text);

    if (!encrypted) {
        printf("Encrypt failed\n");
        return 1;
    }

    printf("Encrypted (hex): ");
    for (int i = 0; i < strlen(text); i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");

    char* decrypted = bmp_decrypt(key, encrypted);

    if (!decrypted) {
        printf("Decrypt failed\n");
        free(encrypted);
        return 1;
    }

    printf("Decrypted text: %s\n", decrypted);

    if (strcmp(decrypted, "AHOJ") == 0)
        printf("OK - decrypt funguje\n");
    else
        printf("ERROR - nieco je zle\n");

    free(encrypted);
    free(decrypted);

    return 0;
}


