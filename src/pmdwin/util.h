//=============================================================================
//			Utility Functions
//				Programmed by C60
//=============================================================================

#ifndef UTIL_H
#define UTIL_H

#ifdef _WIN32
# include <windows.h>
#else
# include "compat.h"
#endif

typedef unsigned char uchar;
typedef unsigned short ushort;

__int64 GetFileSize_s(char *filename);
char *tab2spc(char *dest, const char *src, int tabcolumn);
char *delesc(char *dest, const char *src);
char *zen2tohan(char *dest, const char *src);

#endif
