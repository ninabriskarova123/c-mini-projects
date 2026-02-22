#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

char* playfair_encrypt(const char* key, const char* text);
char* playfair_decrypt(const char* key, const char* text);

#endif