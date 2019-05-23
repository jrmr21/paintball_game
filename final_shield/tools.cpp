#include "core_header.h"

// On encode un int (en base 10) en un nombre en base 255
// On stocke ce nombre dans un tableau de char pour le dans une trame
unsigned char* compress_char(unsigned int a)
{
	unsigned char res[2];
	float f;

	// Calcul de res[0]
    f = a / 255;
    // Arrondissement a l'inferieur du float
	f = ((int)f > f) ? (int) f - 1 : (int) f;

	res[0] = (int)f;
	res[1] = a % 255;

    return res;
}

// On decode deux char (en base 255) en un int (en base 10)
unsigned int decompress_char(unsigned char a[2])
{
    unsigned int res;

    res = a[0] * 255;
    res += a[1];

    printf("res = %d", res);
    return res;
}