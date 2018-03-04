#ifndef WIN_HEADERS_H
#define WIN_HEADERS_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define STRICT
#define WIN32_LEAN_AND_MEAN

#ifdef _WIN32
# include <windows.h>
#else
# include "compat.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#undef max
	#define max _MAX
	#undef min
	#define min _MIN
#endif

#endif	// WIN_HEADERS_H
