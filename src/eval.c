#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"

/*
 * Takes in a null terminated string and returns the result, in null terminated string form.
 * Currently just copies it.
 * TODO Fix this to actually eval stuff.
 */
char* eval(char* s1){
	char* s2 = malloc(strlen(s1)*sizeof(char));
	strcpy(s2,s1);

	return s2;
}

