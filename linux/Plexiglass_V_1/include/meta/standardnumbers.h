#ifndef PLEX_STANDARDNUMBERS_H
#define PLEX_STANDARDNUMBERS_H

// This is a header that contains a set of standard numbers that aren't limits nor effected by memory size profiles.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// MATH

// the number of integers on the preloaded square root table

#define PLEX_STANDNUM_SQRTTABLE 1000

// the precision of random percentage generation which effects random numbers too. must be an integer higher than 0. The larger it is the more random variation there is.

#define PLEX_STANDNUM_RANDPERCPREC 10000

// decides the distance between randomly generated numbers in sequence

#define PLEX_STANDNUM_RANDGENWEIGHT 13579

// MEMORY

// this is the length of the buffer for printing memory lines. 256 should suffice unless for whatever reason you have really really long memory report lines.

#define PLEX_STANDNUM_MEMERRORPRINTBUFFLEN 256

// WINDOWING

// determines the screen's aspect ratio for PLEX units and screen offset. you multiply the height by this number to get the width. It's recommended not to change this in here but to instead use the 'PLEX_changeScreenRatio(const double ratio)' function at the beginning of your program.

#define PLEX_STARTING_ASPECTRATIO (1/3.0)

// INPUT

// determines the sensitivity of controller reading in input. The larger the number the more degrees

#define PLEX_STANDNUM_CONTROLLERSENSE 10000

// FONTS

// Standard bitmap font width @ 1/16th. You don't need to change this as passing it to draw functions that print strings on screen is optional.

#define PLEX_STANDNUM_FW 0.0625

// Standard bitmap font height @ 1/8th. You don't need to change this as passing it to draw functions that print strings on screen is optional.

#define PLEX_STANDNUM_FH 0.125

// the standard pecentage that determines the buffer space between printed characters. 0.8 means the character uses 80% of the space therefore there's a 20% space buffer around it.

#define PLEX_STANDNUM_LETTERBUFF 0.8

// STRINGS

// the number of decimals in a string converted from a number. you will have problems if this number is over 63. The larger this number is the more likely you are to have floating point issues. Keeping it a number smaller than 6 is reccomended.

#define PLEX_STANDNUM_NUMCONVPREC 5

// SPRITE THEATER DRAW LAYERS

// draw layers for the sprite theater. The lower the number the closer to the person viewing the screen it is.

#define PLEX_SPRITETHEATER_FONTLAYER 0
#define PLEX_SPRITETHEATER_BUBBLELAYER 1
#define PLEX_SPRITETHEATER_ARROWLAYER 2
#define PLEX_SPRITETHEATER_LABELLAYER 3
#define PLEX_SPRITETHEATER_ACTORLAYER 4
#define PLEX_SPRITETHEATER_BACKDROPLAYER 10000

#endif
