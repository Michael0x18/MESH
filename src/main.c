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

const char *mods[] = { "      ", "2nd   ", "ALPHA ", "alpha " };

const char *func_strings[] = { "   y=    Window   Zoom   trace   graph",
	"   F1      F2      F3      F4      F5 ",
	"   ??      ??      ??      ??      ?? ",
	"   ??      ??      ??      ??      ?? " };
int8_t mode;

const char *key_strings[56][4] = {
	{"<DOWN>",},//1
	{"<LEFT>",},//2
	{"<RIGHT>",},//3
	{"<UP>",},//4
	{"<ERR5>",},//5
	{"<ERR6>",},//6
	{"<ERR7>",},//7
	{"<ERR8>",},//8
	{"\n",},//9
	{"+",},//10
	{"-",},//11
	{"*",},//12
	{"/",},//13
	{"^",},//14
	{"<CLEAR>",},//15
	{"<ERR16>",},//16
	{"~",},//17
	{"3",},//18
	{"6",},//19
	{"9",},//20
	{")",},//21
	{"tan(",},//22
	{"<VARS>",},//23
	{"<ERR24>",},//24
	{".",},//25
	{"2",},//26
	{"5",},//27
	{"8",},//28
	{"(",},//29
	{"<cos(>",},//30
	{"<PRGM>",},//31
	{"<STAT>",},//32
	{"0",},//33
	{"1",},//34
	{"4",},//35
	{"7",},//36
	{",",},//37
	{"sin(",},//38
	{"<APPS>",},//39
	{"X",},//40
	{"<ON>",},//41
	{"->",},//42
	{"ln(",},//43
	{"log(",},//44
	{"^2",},//45
	{"^~1",},//46
	{"<MATH>",},//47
	{"<ALPHA>",},//48
	{"<GRAPH>",},//49
	{"<TRACE>",},//50
	{"<ZOOM>",},//51
	{"<WINDOW>",},//52
	{"<Y=>",},//53
	{"<SECOND>",},//54
	{"<MODE>",},//55
	{"<DEL>",},//56
};

/*
 * Text input buffer
 */
char buffer[1024];
int ind;

void addchar(char c){
	if(ind<1024){
		buffer[ind++]=c;
	}
}
void bs(void){
	buffer[ind]=0;
	ind--;
}

void addstr(char* s){
	for(int i = 0; i < strlen(s); i++){
		addchar(s[i]);
	}
}

/*
 * Draws the user interface portion of the shell, notably excepting the cursor, and the history entries.
 * Called once per keypress.
 * TODO refactor code to not use globals.
 * TODO use keypadc to make platform independent.
 * TODO clipboard, but not in this function :)
 * TODO math parser
 * TODO history drawing
 * TODO more stuff.
 */
void draw_shell() {
	gfx_SetColor(255);
	gfx_FillRectangle(0,210,320,15);
	fontlib_SetCursorPosition(0,210-15*((signed int)strlen(buffer)%40));
	fontlib_DrawString(buffer);
	
	
	gfx_SetColor(43);
	gfx_SetTextFGColor(255);
	gfx_SetTextBGColor(1);
	gfx_FillRectangle(0, 0, 320, 30);
	//gfx_HorizLine(0,210,320);
	gfx_SetColor(255);
	gfx_FillRectangle(0, 225, 320, 15);
	gfx_SetColor(43);
	gfx_Rectangle(0, 225, 64, 15);
	gfx_Rectangle(64, 225, 64, 15);
	gfx_Rectangle(128, 225, 64, 15);
	gfx_Rectangle(192, 225, 64, 15);
	gfx_Rectangle(256, 225, 64, 15);

	//gfx_SetTextXY(2,2);
	fontlib_SetForegroundColor(255);
	fontlib_SetCursorPosition(2, 0);
	fontlib_DrawString("MESH V0.00");
	fontlib_SetCursorPosition(2, 15);
	fontlib_DrawString(mods[mode]);
	fontlib_SetForegroundColor(0);
	fontlib_SetCursorPosition(0, 225);
	fontlib_DrawString(func_strings[mode]);
}

void mesh_mainloop() {
	gfx_SetDrawBuffer();
	short k = 0;
	while (1) {
		k = 0;
		draw_shell();
		gfx_BlitBuffer();
		while (!k)
			k = os_GetCSC();
		//Do modifiers and keypresses
		switch (k) {
			case 54://2nd
				mode = mode == 1 ? 0 : 1;
				break;
			case 48://alpha stuff
				mode = mode == 2 ? 3 : mode == 3 ? 0 : 2;
				break;
			case 1://down arrow TODO
				break;
			case 2://left arrow TODO
				break;
			case 3://right arrow TODO
				break;
			case 4://up arrow TODO
				break;
				//5-8 unused
			case 9://TODO ENTER -> SUBMIT
				break;
			case 10:
				break;
			default:
				addstr(key_strings[k-1][mode]);
		}

	}
}

/*
 * Takes in a null terminated string and returns the result, in null terminated string form.
 * Currently just copies it.
 * TODO Fix this to actually eval stuff.
 */
char* eval(char* s1){
	char* s2 = malloc(strlen(s1)*sizeof(char));
	strcpy(s1,s2);

	return s2;
}

int main(void) {
	font_small = fontlib_GetFontByIndex("DrMono", 3);
	fontlib_SetFont(font_small, 0);
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
