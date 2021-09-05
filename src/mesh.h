/*
 * MESH is a Mathematical Evaluation SHell for the TI 84 plus CE.
 * It is intended to run both under TIOS and BOS, with emphasis on
 * the latter.
 */
#ifndef mesh_h
#define mesh_h

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

uint8_t checkKey(void);
void equalize();
void addchar(char c);
void bs(void);
void addstr(char* s);
void draw_shell();
void scroll_history(void);
void submit(void);
void mesh_mainloop();
int main(void);

#endif /*MESH_H*/