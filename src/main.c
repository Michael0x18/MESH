/*
 * main.c
 *
 * MESH
 *
 * Michael0x18
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include "tigcclib.h"



void draw_shell(){
	gfx_FillScreen(255);
	gfx_SetColor(43);
	gfx_SetTextFGColor(255);
	gfx_SetTextBGColor(1);
	gfx_FillRectangle(0,0,320,30);
	gfx_SetTextXY(2,2);
	gfx_PrintString("MESH V0.00");
}

void mesh_mainloop(){
	gfx_SetDrawBuffer();
	short k=0;
	while(1){
		draw_shell();
		gfx_BlitBuffer();
		k=ngetchx();
		if(k==KEY_CLEAR){
			break;
		}

	}
}

int main(void){
	//gfx_SetTextScale(2, 2);
	gfx_SetMonospaceFont(8);
	gfx_SetTransparentColor(1);
	gfx_SetTextTransparentColor(1);
	gfx_Begin();
	gfx_FillScreen(255);
	gfx_SetTextXY(0,0);
	gfx_PrintString("Loading...");
	mesh_mainloop();
	gfx_End();
}
