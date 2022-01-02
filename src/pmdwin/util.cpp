//=============================================================================
//			Utility Functions
//				Programmed by C60
//=============================================================================

#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include "portability_fmpmdcore.h"
#include "util.h"


//=============================================================================
//	cがマルチバイト文字の第 1 バイトであれば 0 以外を返す
//=============================================================================
int32_t ismbblead(uint32_t c)
{
	if((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc)) {
		return 1;
	} else {
		return 0;
	}
}


//=============================================================================
//	TAB を SPACE に変換(tabcolumn カラム毎 / ESCシーケンス不可)
//=============================================================================
char *tab2spc(char *dest, const char *src, int32_t tabcolumn)
{
	int32_t		column = 0;
	char	*dest2;
	
	dest2 = dest;
	while(*src != '\0') {
		if(*src == '\t') {							// TAB
			src++;
			do {
				*dest = ' ';
				dest++;
			}while(++column % tabcolumn);
		} else if(*src == 0x0d || *src == 0x0a) {	// 改行
			column = 0;
			*dest = *src;
			dest++;
			src++;
		} else {
			*dest = *src;
			dest++;
			src++;
			column++;
		}
	}
	*dest = '\0';
	return dest2;
}


//=============================================================================
//	エスケープシーケンスの除去
//	カーソル移動系エスケープシーケンスには非対応
//=============================================================================
char *delesc(char *dest, const char *src)
{
	char	*dest2;
	uint8_t	*src2;
	uint8_t	*src3;
	size_t	i;
	
	if((src2 = src3 = (uint8_t *)malloc(strlen(src) + 32)) == NULL) {
		return NULL;
	};
	
	strcpy((char *)src2, src);
	
	// 31バイト連続 '\0' にする(8 以上なら OK なはずだけど，念のため）
	for(i = strlen((char *)src2); i < strlen((char *)src2) + 31; i++) {
		src2[i] = '\0';
	}
	
	dest2 = dest;
	
	while(*src2 != '\0') {
		if(*src2 == 0x1b) {		// エスケープシーケンス
			if(*(src2 + 1) == '[') {
				src2 += 2;
				while(*src2 && (toupper(*src2) < 'A' || toupper(*src2) > 'Z')) {
					if(ismbblead(*src2)) {
						src2 += 2;
						continue;
					}
					src2++;
				}
				src2++;
			} else if(*(src2 + 1) == '=') {
				src2 += 4;
			} else if(*(src2 + 1) == ')' || *(src2 + 1) == '!') {
				src2 += 3;
			} else {
				src2 += 2;
			}
		} else {
			*dest = *src2;
			dest++;
			src2++;
		}
	}
	
	free(src3);
	*dest = '\0';
	return dest2;
}


//=============================================================================
//	２バイト半角文字を半角に変換
//=============================================================================
char *zen2tohan(char *dest, const char *src)
{
	char *src2;
	char *src3;
	char *dest2;
	int32_t	len;
	static const char *codetable[] = {
		"!",		/*	8540 	*/
		"\"",		/*	8541 	*/
		"#",		/*	8542 	*/
		"$",		/*	8543 	*/
		"%",		/*	8544 	*/
		"&",		/*	8545 	*/
		"'",		/*	8546 	*/
		"(",		/*	8547 	*/
		")",		/*	8548 	*/
		"*",		/*	8549 	*/
		"+",		/*	854a 	*/
		",",		/*	854b 	*/
		"-",		/*	854c 	*/
		".",		/*	854d 	*/
		"/",		/*	854e 	*/
		"0",		/*	854f 	*/
		"1",		/*	8550 	*/
		"2",		/*	8551 	*/
		"3",		/*	8552 	*/
		"4",		/*	8553 	*/
		"5",		/*	8554 	*/
		"6",		/*	8555 	*/
		"7",		/*	8556 	*/
		"8",		/*	8557 	*/
		"9",		/*	8558 	*/
		":",		/*	8559 	*/
		";",		/*	855a 	*/
		"<",		/*	855b 	*/
		"=",		/*	855c 	*/
		">",		/*	855d 	*/
		"?",		/*	855e 	*/
		"@",		/*	855f 	*/
		"A",		/*	8560 	*/
		"B",		/*	8561 	*/
		"C",		/*	8562 	*/
		"D",		/*	8563 	*/
		"E",		/*	8564 	*/
		"F",		/*	8565 	*/
		"G",		/*	8566 	*/
		"H",		/*	8567 	*/
		"I",		/*	8568 	*/
		"J",		/*	8569 	*/
		"K",		/*	856a 	*/
		"L",		/*	856b 	*/
		"M",		/*	856c 	*/
		"N",		/*	856d 	*/
		"O",		/*	856e 	*/
		"P",		/*	856f 	*/
		"Q",		/*	8570 	*/
		"R",		/*	8571 	*/
		"S",		/*	8572 	*/
		"T",		/*	8573 	*/
		"U",		/*	8574 	*/
		"V",		/*	8575 	*/
		"W",		/*	8576 	*/
		"X",		/*	8577 	*/
		"Y",		/*	8578 	*/
		"Z",		/*	8579 	*/
		"[",		/*	857a 	*/
		"\\",		/*	857b 	*/
		"]",		/*	857c 	*/
		"^",		/*	857d 	*/
		"_",		/*	857e 	*/
		"",			/*	857f 	*/
		"`",		/*	8580 	*/
		"a",		/*	8581 	*/
		"b",		/*	8582 	*/
		"c",		/*	8583 	*/
		"d",		/*	8584 	*/
		"e",		/*	8585 	*/
		"f",		/*	8586 	*/
		"g",		/*	8587 	*/
		"h",		/*	8588 	*/
		"i",		/*	8589 	*/
		"j",		/*	858a 	*/
		"k",		/*	858b 	*/
		"l",		/*	858c 	*/
		"m",		/*	858d 	*/
		"n",		/*	858e 	*/
		"o",		/*	858f 	*/
		"p",		/*	8590 	*/
		"q",		/*	8591 	*/
		"r",		/*	8592 	*/
		"s",		/*	8593 	*/
		"t",		/*	8594 	*/
		"u",		/*	8595 	*/
		"v",		/*	8596 	*/
		"w",		/*	8597 	*/
		"x",		/*	8598 	*/
		"y",		/*	8599 	*/
		"z",		/*	859a 	*/
		"{",		/*	859b 	*/
		"|",		/*	859c 	*/
		"}",		/*	859d 	*/
		"\x85\x9e",	/*	859e 	*/
		"｡",		/*	859f 	*/
		"｢",		/*	85a0 	*/
		"｣",		/*	85a1 	*/
		"､",		/*	85a2 	*/
		"･",		/*	85a3 	*/
		"ｦ",		/*	85a4 	*/
		"ｧ",		/*	85a5 	*/
		"ｨ",		/*	85a6 	*/
		"ｩ",		/*	85a7 	*/
		"ｪ",		/*	85a8 	*/
		"ｫ",		/*	85a9 	*/
		"ｬ",		/*	85aa 	*/
		"ｭ",		/*	85ab 	*/
		"ｮ",		/*	85ac 	*/
		"ｯ",		/*	85ad 	*/
		"ｰ",		/*	85ae 	*/
		"ｱ",		/*	85af 	*/
		"ｲ",		/*	85b0 	*/
		"ｳ",		/*	85b1 	*/
		"ｴ",		/*	85b2 	*/
		"ｵ",		/*	85b3 	*/
		"ｶ",		/*	85b4 	*/
		"ｷ",		/*	85b5 	*/
		"ｸ",		/*	85b6 	*/
		"ｹ",		/*	85b7 	*/
		"ｺ",		/*	85b8 	*/
		"ｻ",		/*	85b9 	*/
		"ｼ",		/*	85ba 	*/
		"ｽ",		/*	85bb 	*/
		"ｾ",		/*	85bc 	*/
		"ｿ",		/*	85bd 	*/
		"ﾀ",		/*	85be 	*/
		"ﾁ",		/*	85bf 	*/
		"ﾂ",		/*	85c0 	*/
		"ﾃ",		/*	85c1 	*/
		"ﾄ",		/*	85c2 	*/
		"ﾅ",		/*	85c3 	*/
		"ﾆ",		/*	85c4 	*/
		"ﾇ",		/*	85c5 	*/
		"ﾈ",		/*	85c6 	*/
		"ﾉ",		/*	85c7 	*/
		"ﾊ",		/*	85c8 	*/
		"ﾋ",		/*	85c9 	*/
		"ﾌ",		/*	85ca 	*/
		"ﾍ",		/*	85cb 	*/
		"ﾎ",		/*	85cc 	*/
		"ﾏ",		/*	85cd 	*/
		"ﾐ",		/*	85ce 	*/
		"ﾑ",		/*	85cf 	*/
		"ﾒ",		/*	85d0 	*/
		"ﾓ",		/*	85d1 	*/
		"ﾔ",		/*	85d2 	*/
		"ﾕ",		/*	85d3 	*/
		"ﾖ",		/*	85d4 	*/
		"ﾗ",		/*	85d5 	*/
		"ﾘ",		/*	85d6 	*/
		"ﾙ",		/*	85d7 	*/
		"ﾚ",		/*	85d8 	*/
		"ﾛ",		/*	85d9 	*/
		"ﾜ",		/*	85da 	*/
		"ﾝ",		/*	85db 	*/
		"ﾞ",		/*	85dc 	*/
		"ﾟ",		/*	85dd 	*/
		"\x85\xde",	/*	85de 	*/
		"\x85\xdf",	/*	85df 	*/
		"ﾜ",		/*	85e0 	*/
		"ｶ",		/*	85e1 	*/
		"ｹ",		/*	85e2 	*/
		"ｳﾞ",		/*	85e3 	*/
		"ｶﾞ",		/*	85e4 	*/
		"ｷﾞ",		/*	85e5 	*/
		"ｸﾞ",		/*	85e6 	*/
		"ｹﾞ",		/*	85e7 	*/
		"ｺﾞ",		/*	85e8 	*/
		"ｻﾞ",		/*	85e9 	*/
		"ｼﾞ",		/*	85ea 	*/
		"ｽﾞ",		/*	85eb 	*/
		"ｾﾞ",		/*	85ec 	*/
		"ｿﾞ",		/*	85ed 	*/
		"ﾀﾞ",		/*	85ee 	*/
		"ﾁﾞ",		/*	85ef 	*/
		"ﾂﾞ",		/*	85f0 	*/
		"ﾃﾞ",		/*	85f1 	*/
		"ﾄﾞ",		/*	85f2 	*/
		"ﾊﾞ",		/*	85f3 	*/
		"ﾊﾟ",		/*	85f4 	*/
		"ﾋﾞ",		/*	85f5 	*/
		"ﾋﾟ",		/*	85f6 	*/
		"ﾌﾞ",		/*	85f7 	*/
		"ﾌﾟ",		/*	85f8 	*/
		"ﾍﾞ",		/*	85f9 	*/
		"ﾍﾟ",		/*	85fa 	*/
		"ﾎﾞ",		/*	85fb 	*/
		"ﾎﾟ"		/*	85fc 	*/
	};
	
	if((src2 = src3 = (char *)malloc(strlen(src) + 2)) == NULL) {
		return NULL;
	};
	
	strcpy(src2, src);
	src2[strlen(src2)+1] = '\0';		// 2バイト連続 '\0' にする
	
	dest2 = dest;
	do {
		if(ismbblead(*src2)) {		// 漢字１バイト目
			if(*(uint8_t *)src2 == 0x85 &&
					*(uint8_t *)(src2+1) >= 0x40 && *(uint8_t *)(src2+1) <= 0xfc) {	// 2バイト半角
				len = (int32_t)strlen(codetable[*(uint8_t *)(src2+1) - 0x40]);
				strncpy(dest, codetable[*(uint8_t *)(src2+1) - 0x40], len);
				src2 += 2;
				dest += len;
			} else {
				*dest = *src2;
				dest++;
				src2++;

				*dest = *src2;
				dest++;
				src2++;
			}
		} else {
			*dest = *src2;
			dest++;
			src2++;
		}
	}while(*src2 != '\0');
	
	free(src3);
	if(strlen(dest2) > 0) {
		if(*(dest - 1) != '\0') {
			*dest = '\0';
		}
	}
	return dest2;
}
