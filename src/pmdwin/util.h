//=============================================================================
//			Utility Functions
//				Programmed by C60
//=============================================================================

#ifndef UTIL_H
#define UTIL_H

typedef unsigned char uchar;
typedef unsigned short ushort;

char *tab2spc(char *dest, const char *src, int tabcolumn);
char *delesc(char *dest, const char *src);
char *zen2tohan(char *dest, const char *src);

#endif // UTIL_H
