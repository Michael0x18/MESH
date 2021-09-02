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
#include <fontlibc.h>
//#include "tigcclib.h"

fontlib_font_t *font_small;

const char* mods[]={
		"      ",
		"2nd   ",
		"ALPHA ",
		"alpha "
};
int8_t mode;

void draw_shell() {
	gfx_SetColor(43);
	gfx_SetTextFGColor(255);
	gfx_SetTextBGColor(1);
	gfx_FillRectangle(0, 0, 320, 30);
	//gfx_SetTextXY(2,2);
	fontlib_SetCursorPosition(2, 0);
	fontlib_DrawString("MESH V0.00");
	fontlib_SetCursorPosition(2,15);
	fontlib_DrawString(mods[mode]);

}

void mesh_mainloop() {
	gfx_SetDrawBuffer();
	short k = 0;
	while (1) {
		k=0;
		draw_shell();
		gfx_BlitBuffer();
		while(!k)
			k=os_GetCSC();
		//Do modifiers and keypresses
		switch(k){
		case 54:
			mode=mode==1?0:1;//2nd
			break;
		case 48:
			mode=mode==2?3:mode==3?0:2;//alpha stuff
			break;
		}


	}
}

int main(void) {
	font_small = fontlib_GetFontByIndex("DrMono", 3);
	fontlib_SetFont(font_small,0);
	fontlib_SetForegroundColor(255);
	fontlib_SetTransparency(true);
	fontlib_SetBackgroundColor(1);
	//gfx_SetTextScale(2, 2);
	//gfx_SetMonospaceFont(8);
	gfx_SetTransparentColor(1);
	gfx_SetTextTransparentColor(1);
	gfx_Begin();
	gfx_FillScreen(255);
	gfx_SetTextXY(0, 0);
	gfx_PrintString("Loading...");
	mesh_mainloop();
	gfx_End();
}
