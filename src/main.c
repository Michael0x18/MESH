/*
 * main.c
 *
 * MESH Main File
 * main.c contains the GUI elements needed for the MESH frontend.
 * Yes, there are globals. Please don't kill me, Mateo.
 *
 * The real mathematical parsing occurs within the other files, and is linked
 * here solely by the "eval" function, which takes in an input string, and returns
 * the result.
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

#include "mesh.h"

#include "eval.h"

const char *mods[] = { "      ", "2nd   ", "ALPHA ", "alpha " };

const char *func_strings[] = { "   y=    Window   Zoom   trace   graph",
	"   F1      F2      F3      F4      F5 ",
	"   ??      ??      ??      ??      ?? ",
	"   ??      ??      ??      ??      ?? " };
int8_t mode;

uint8_t checkKey(void) {
    static uint8_t last_key;
    uint8_t only_key = 0;
    kb_Scan();
    for (uint8_t key = 1, group = 7; group; --group) {
        for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
            if (kb_Data[group] & mask) {
                if (only_key) {
                    last_key = 0;
                    return 0;
                } else {
                    only_key = key;
                }
            }
        }
    }
    if (only_key == last_key) {
        return 0;
    }
    last_key = only_key;
    return only_key;
}

/*
 * TODO do other key modes.
 */
const char *key_strings[56][4] = {
	{"<DOWN>",},//1
	{"<LEFT>",},//2
	{"<RIGHT>",},//3
	{"<UP>",},//4
	{"<ERR5>",},//5
	{"<ERR6>",},//6
	{"<ERR7>",},//7
	{"<ERR8>",},//8
	{"<NEWLINE>",},//9
	{"+",},//10
	{"-",},//11
	{"*",},//12
	{"/",},//13
	{"^",},//14
	{"<CLEAR>",},//15
	{"<ERR16>",},//16
	{"-",},//17
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
int offset;
int cur;

void equalize(){
	if(offset<0)offset=0;
	while(cur<0){
		cur++;
		offset--;
	}
	while(cur>40){
		cur--;
		offset++;
	}
	if(strlen(buffer) > 40 && strlen(buffer)-offset<40){
		offset=strlen(buffer)-40;
		cur=40;
	}
}

void addchar(char c){
	int i = strlen(buffer);
	if(i>=1024)return;
	while(i!=ind){
		buffer[i]=buffer[i-1];
		i--;
	}
	if(ind<1024){
		buffer[ind++]=c;
	}
	cur++;
	equalize();
}
void bs(void){
	if(ind==0)return;
	buffer[ind-1]='\0';
	ind--;
	int i = ind+1;
	do{
		buffer[i-1]=buffer[i];
		i++;
	}while(buffer[i]);
	buffer[i-1]='\0';
	cur--;
	equalize();
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
	gfx_FillRectangle_NoClip(0,210,320,15);
	//fontlib_SetCursorPosition(0,210-14*(((signed int)strlen(buffer))/40));//Ditching wrapping
	fontlib_SetCursorPosition(0,210);
	gfx_SetColor(0);
	//if(ind<40){
	//	fontlib_DrawString(buffer);
	//	gfx_VertLine(8*ind,210,14);
	//}else{
	//	fontlib_DrawString(buffer+strlen(buffer)-40);
	//	gfx_VertLine(319,210,14);
	//}gfx_SetColor(0);
	
	fontlib_DrawString(buffer+offset);
	gfx_VertLine_NoClip(8*cur,210,14);

	gfx_SetColor(43);
	gfx_SetTextFGColor(255);
	gfx_SetTextBGColor(1);
	gfx_FillRectangle_NoClip(0, 0, 320, 30);
	//gfx_HorizLine(0,210,320);
	gfx_SetColor(255);
	gfx_FillRectangle_NoClip(0, 225, 320, 15);
	gfx_SetColor(43);
	gfx_Rectangle_NoClip(0, 225, 64, 15);
	gfx_Rectangle_NoClip(64, 225, 64, 15);
	gfx_Rectangle_NoClip(128, 225, 64, 15);
	gfx_Rectangle_NoClip(192, 225, 64, 15);
	gfx_Rectangle_NoClip(256, 225, 64, 15);

	//gfx_SetTextXY(2,2);
	fontlib_SetForegroundColor(255);
	fontlib_SetCursorPosition(2, 0);
	fontlib_DrawString("MESH V0.01 -- EXPR version");
	fontlib_SetCursorPosition(2, 15);
	fontlib_DrawString(mods[mode]);
	fontlib_SetForegroundColor(0);
	fontlib_SetCursorPosition(0, 225);
	fontlib_DrawString(func_strings[mode]);
}

void scroll_history(void){
	//if(!gfx_vbuffer)exit(1);
	//memmove(gfx_vbuffer+320*30,gfx_vbuffer+320*15,320*195);
	//delay(1000);
	//while(!os_GetCSC);
	gfx_ShiftUp(14);
}


void submit(void){
	if(!strlen(buffer))return;
	gfx_SetColor(255);
	gfx_VertLine_NoClip(8*cur,210,14);
	scroll_history();
	cur=0;
	offset=0;
	ind=0;
	char *res = eval(buffer);
	//memset(buffer,0,1024);
	gfx_SetColor(255);
	gfx_FillRectangle_NoClip(0,210,320,15);
	fontlib_SetForegroundColor(120);
	fontlib_SetCursorPosition(strlen(res)<40?320-8*strlen(res):0,210);
	fontlib_DrawString(res);
	scroll_history();
	memset(buffer,0,1024);
}

void mesh_mainloop() {
	gfx_SetDrawBuffer();
	short k = 0;
	while (1) {
		k = 0;
		draw_shell();
		gfx_BlitBuffer();
		while (!k)
			k = checkKey();
		//Do modifiers and keypresses
		switch (k) {
			case 54://2nd
				mode = mode == 1 ? 0 : 1;
				break;
			case 48://alpha stuff
				mode = mode == 2 ? 3 : mode == 3 ? 0 : 2;
				break;
			case 1://down arrow TODO
				ind=strlen(buffer);
				if(ind<39){
					cur=ind;
					offset=0;
				}else{
					cur=40;
					offset=strlen(buffer)-40;
				}
				equalize();
				break;
			case 2://left arrow TODO
				if(ind){
					cur--;
					ind--;
				}
				equalize();
				break;
			case 3://right arrow TODO
				if(ind<strlen(buffer)){
					cur++;
					ind++;
				}
				equalize();
				break;
			case 4://up arrow TODO
				ind=0;
				cur=0;
				offset=0;
				equalize();
				break;
				//5-8 unused
			case 9://TODO ENTER -> SUBMIT
				submit();
				break;
			case 56://Trap delete
				bs();
				break;
			default:
				addstr(key_strings[k-1][mode]);
		}

	}
}



int main(void) {
	fontlib_font_t *font_small;
	gfx_SetClipRegion(0,30,320,225);
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
