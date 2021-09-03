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
#include "../expr/expr.h"

/*
 * Takes in a null terminated string and returns the result, in null terminated string form.
 * Currently just copies it.
 * TODO Fix this to actually eval stuff.
 */

static struct expr_func user_funcs[]={
	{NULL,NULL,NULL,0},
};

char* eval(char* s1){
	static char s2[1024];
	//strcpy(s2,s1);
	struct expr_var_list vars = {0};
	struct expr *e = expr_create(s1, strlen(s1), &vars, user_funcs);
	if (e == NULL) {
    		sprintf(s2,"Syntax error");
    		return s2;
  	}
	float result = expr_eval(e);
	sprintf(s2,"%f",result);
	return s2;
}

