#include <stdio.h>
#include <stdlib.h>
#include "playfair_by_me.h"

int main()
{
    char *encrypted = playfair_encrypt("Ahoj", "Balloon");

    if (encrypted != NULL)
    {
        printf("Encrypted: %s\n", encrypted);

        char *decrypted = playfair_decrypt("Ahoj", encrypted);

        if (decrypted != NULL)
        {
            printf("Decrypted: %s\n", decrypted);
            free(decrypted);
        }

        free(encrypted);
    }

    return 0;
}
