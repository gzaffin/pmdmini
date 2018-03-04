#ifndef PMDWIN_COMPAT_H
#define PMDWIN_COMPAT_H

#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long long int __int64;

#ifndef HAVE_STRNICMP
# define strnicmp strncasecmp
#endif

#ifndef HAVE__ISMBBLEAD
# define _ismbblead(c) \
   (((c) >= 0x80) && ((c) <= 0x9F) || \
    ((c) >= 0xE0) && ((c) <= 0xFC))
#endif

#ifndef HAVE__MBSRCHR
# define _mbsrchr(s,c) \
   strrchr((char *)(s), (c))
#endif

#ifndef MAX_PATH
# define MAX_PATH FILENAME_MAX
#endif

#ifndef _MAX_PATH
# define _MAX_PATH MAX_PATH
#endif

#ifndef MAX_DRIVE
# define MAX_DRIVE FILENAME_MAX
#endif

#ifndef _MAX_DRIVE
# define _MAX_DRIVE MAX_DRIVE
#endif

#ifndef MAX_DIR
# define MAX_DIR FILENAME_MAX
#endif

#ifndef _MAX_DIR
# define _MAX_DIR MAX_DIR
#endif

#ifndef MAX_FNAME
# define MAX_FNAME FILENAME_MAX
#endif

#ifndef _MAX_FNAME
# define _MAX_FNAME MAX_FNAME
#endif

#ifndef MAX_EXT
# define MAX_EXT FILENAME_MAX
#endif

#ifndef _MAX_EXT
# define _MAX_EXT MAX_EXT
#endif

# define PATH_DELIMIT_CHR '/'
# define PATH_DELIMIT_STR "/"

#ifndef API_ATTRIBUTE
# define API_ATTRIBUTE
#endif
#ifndef WINAPI
# define WINAPI
#endif

#ifdef __GNUC__
# define __PACKED__ __attribute__((packed))
#endif

#endif /* PMDWIN_COMPAT_H */
