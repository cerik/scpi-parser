/*-
 * Copyright (c) 2012-2013 Jan Breuer,
 *
 * All Rights Reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   scpi_utils.c
 * @date   Thu Nov 15 10:58:45 UTC 2012
 * 
 * @brief  Conversion routines and string manipulation routines
 * 
 * 
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "datatype.h"
#include "snprintf.h"


typedef enum {
    STATE_FIRST_WHITESPACE,
    STATE_TEXT_QUOTED,
    STATE_TEXT,
    STATE_LAST_WHITESPACE,
    STATE_COMMA,
    STATE_ERROR
}locate_text_states;

typedef struct {
    locate_text_states state;
    INT32 startIdx;
    INT32 stopIdx;
    UINT32 i;
}locate_text_nfa;

static UINT32 patternSeparatorShortPos(const char * pattern, UINT32 len);

/* just like strlen(3), but cap the number of bytes we count */
UINT32 strnlen(const char *s, UINT32 max) {
    const char *p;
    for(p = s; *p && max--; ++p);
    return(p - s);
}

#ifdef _MSC_VER
int strcasecmp(const char *s1,const char *s2)
{
   while  (toupper((unsigned char)*s1) == toupper((unsigned char)*s2++))
       if (*s1++ == '\0') return 0;
   return(toupper((unsigned char)*s1) - toupper((unsigned char)*--s2));
}

int strncasecmp(const char *s1, const char *s2, int n)
{
  while (--n >= 0 && toupper((unsigned char)*s1) == toupper((unsigned char)*s2++))
      if (*s1++ == '\0')  return 0;
  return(n < 0 ? 0 : toupper((unsigned char)*s1) - toupper((unsigned char)*--s2));
}

/**
 * Find the first occurrence in str of a character in set.
 * @param str
 * @param size
 * @param set
 * @return 
 */
const char * strnpbrk(const char *str, UINT32 size, const char *set) {
    const char *scanp;
    long c, sc;
    const char * strend = str + size;

    while ((strend != str) && ((c = *str++) != 0)) {
        for (scanp = set; (sc = *scanp++) != '\0';)
            if (sc == c)
                return ((char *) (str - 1));
    }
    return (NULL);
}

#endif

UINT8 char2hex(UINT8 ch) 
{ 
    if((ch>='0')&&(ch<='9')) 
        return ch-'0'; 
    else if((ch>='A')&&(ch<='F')) 
        return ch-'A' + 0x0A; 
    else if((ch>='a')&&(ch<='f')) 
        return ch - 'a' + 0x0A; 
    else 
        return ch; 
} 

/**
 * Converts signed 32b integer value to string
 * @param val   integer value
 * @param str   converted textual representation
 * @param len   string buffer length
 * @return number of bytes written to str (without '\0')
 */
UINT32 longToStr(INT32 val, char * str, UINT32 len) {
    UINT32 x = 1000000000L;
    INT8 digit;
    UINT32 pos = 0;

    if (val == 0) {
        if (pos < len) str[pos++] = '0';
    } else {
        if (val < 0) {
            val = -val;
            if (pos < len) str[pos++] = '-';
        }

        while ((val / x) == 0) {
            x /= 10;
        }

        do {
            digit = (UINT8) (val / x);
            if (pos < len) str[pos++] = digit + '0';
            val -= digit * x;
            x /= 10;
        } while (x && (pos < len));
    }

    if (pos < len) str[pos] = 0;
    return pos;
}

/**
 * Converts double value to string
 * @param val   double value
 * @param str   converted textual representation
 * @param len   string buffer length
 * @return number of bytes written to str (without '\0')
 */
UINT32 doubleToStr(double val, char * str, UINT32 len) {
    return snprintf(str, len, "%lg", val);
}

/**
 * Converts string to signed 32bit integer representation
 * @param str   string value
 * @param val   32bit integer result
 * @return      number of bytes used in string
 */
UINT32 strToLong(const char * str, INT32 * val) {
    char * endptr;
    *val = strtol(str, &endptr, 0);
    return endptr - str;
}

/**
 * Converts string to double representation
 * @param str   string value
 * @param val   double result
 * @return      number of bytes used in string
 */
UINT32 strToDouble(const char * str, double * val) {
    char * endptr;
    *val = strtod(str, &endptr);
    return endptr - str;
}

/**
 * Compare two strings with exact length
 * @param str1
 * @param len1
 * @param str2
 * @param len2
 * @return TRUE if len1==len2 and "len" characters of both strings are equal
 */
boolean compareStr(const char * str1, UINT32 len1, const char * str2, UINT32 len2) {
    if (len1 != len2) {
        return FALSE;
    }

    if (SCPI_strncasecmp(str1, str2, len2) == 0) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Test locate text state, if it is correct final state
 */
static boolean isFinalState(locate_text_states state) {
    return (
        ((state) == STATE_COMMA)
        || ((state) == STATE_LAST_WHITESPACE)
        || ((state) == STATE_TEXT) ||
        ((state) == STATE_FIRST_WHITESPACE)
    );
}

/**
 * Perform locateText automaton to search string pattern
 * @param nfa stores automaton state
 * @param c current char processed
 */
static boolean locateTextAutomaton(locate_text_nfa * nfa, unsigned char c) {
    switch(nfa->state) {
        /* first state locating only white spaces */
        case STATE_FIRST_WHITESPACE:
            if(isspace(c)) {
                nfa->startIdx = nfa->stopIdx = nfa->i + 1;
            } else if (c == ',') {
                nfa->state = STATE_COMMA;
            } else if (c == '"') {
                nfa->startIdx = nfa->i + 1;
                nfa->state = STATE_TEXT_QUOTED;
            } else {
                nfa->startIdx = nfa->i;
                nfa->stopIdx = nfa->i + 1;
                nfa->state = STATE_TEXT;
            }
            break;
        /* state locating any text inside "" */
        case STATE_TEXT_QUOTED:
            if(c == '"') {
                nfa->state = STATE_LAST_WHITESPACE;
                nfa->stopIdx = nfa->i;
            }
            break;
        /* locate text ignoring quotes */
        case STATE_TEXT:
            if (c == ',') {
                nfa->state = STATE_COMMA;
            } else if (!isspace(c)) {
                nfa->stopIdx = nfa->i + 1;
            }
            break;
        /* locating text after last quote */
        case STATE_LAST_WHITESPACE:
            if (c == ',') {
                nfa->state = STATE_COMMA;
            } else if (!isspace(c)) {
                nfa->state = STATE_ERROR;
            }
            break;

        default:
            break;
    }

    /* if it is terminating state, break from for loop */
    if ((nfa->state == STATE_COMMA) || (nfa->state == STATE_ERROR)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * Locate text in string. Text is separated by two ""
 *   example: "text", next parameter
 *   regexp: ^[ \t\r\n]*"([^"]*)"[ \t\r\n]*,?
 *   regexp: ^[ \t\r\n]*([^,]*)[ \t\r\n]*,?
 * @param str1 string to be searched
 * @param len1 length of string
 * @param str2 result
 * @param len2 length of result
 * @return string str1 contains text and str2 was set
 */
boolean locateText(const char * str1, UINT32 len1, const char ** str2, UINT32 * len2) {
    locate_text_nfa nfa;
    nfa.state = STATE_FIRST_WHITESPACE;
    nfa.startIdx = 0;
    nfa.stopIdx = 0;

    for (nfa.i = 0; nfa.i < len1; nfa.i++) {
        if(FALSE == locateTextAutomaton(&nfa, str1[nfa.i])) {
            break;
        }
    }

    if (isFinalState(nfa.state)) {

        if (str2) {
            *str2 = &str1[nfa.startIdx];
        }

        if (len2) {
            *len2 = nfa.stopIdx - nfa.startIdx;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * Perform locateStr automaton to search string pattern
 * @param nfa stores automaton state
 * @param c current char processed
 */
static boolean locateStrAutomaton(locate_text_nfa * nfa, unsigned char c) {
    switch(nfa->state) {
        /* first state locating only white spaces */
        case STATE_FIRST_WHITESPACE:
            if(isspace(c)) {
                nfa->startIdx = nfa->stopIdx = nfa->i + 1;
            } else if (c == ',') {
                nfa->state = STATE_COMMA;
            } else {
                nfa->startIdx = nfa->i;
                nfa->stopIdx = nfa->i + 1;
                nfa->state = STATE_TEXT;
            }
            break;
        /* locate text ignoring quotes */
        case STATE_TEXT:
            if (c == ',') {
                nfa->state = STATE_COMMA;
            } else if (!isspace(c)) {
                nfa->stopIdx = nfa->i + 1;
            }
            break;

        default:
            break;            
    }

    /* if it is terminating state, break from for loop */
    if ((nfa->state == STATE_COMMA) || (nfa->state == STATE_ERROR)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * Locate string in string.
 *   regexp: ^[ \t\r\n]*([^,]*)[ \t\r\n]*,?
 * @param str1 string to be searched
 * @param len1 length of string
 * @param str2 result
 * @param len2 length of result
 * @return string str1 contains text and str2 was set
 */
boolean locateStr(const char * str1, UINT32 len1, const char ** str2, UINT32 * len2) {
    locate_text_nfa nfa;
    nfa.state = STATE_FIRST_WHITESPACE;
    nfa.startIdx = 0;
    nfa.stopIdx = 0;

    for (nfa.i = 0; nfa.i < len1; nfa.i++) {
        if(FALSE == locateStrAutomaton(&nfa, str1[nfa.i])) {
            break;
        }
    }

    if (isFinalState(nfa.state)) {

        if (str2) {
            *str2 = &str1[nfa.startIdx];
        }

        if (len2) {
            *len2 = nfa.stopIdx - nfa.startIdx;
        }
        return TRUE;
    }
    return FALSE;
}


/**
 * Count white spaces from the beggining
 * @param cmd - command
 * @param len - max search length
 * @return number of white spaces
 */
UINT32 skipWhitespace(const char * cmd, UINT32 len) {
    UINT32 i;
    for (i = 0; i < len; i++) {
        if (!isspace((unsigned char)cmd[i])) {
            return i;
        }
    }
    return len;
}

/**
 * Pattern is composed from upper case an lower case letters. This function
 * search the first lowercase letter
 * @param pattern
 * @param len - max search length
 * @return position of separator or len
 */
UINT32 patternSeparatorShortPos(const char * pattern, UINT32 len) {
    UINT32 i;
    for (i = 0; (i < len) && pattern[i]; i++) {
        if (islower((unsigned char)pattern[i])) {
            return i;
        }
    }
    return i;
}

/**
 * Match pattern and str. Pattern is in format UPPERCASElowercase
 * @param pattern
 * @param pattern_len
 * @param str
 * @param str_len
 * @return 
 */
boolean matchPattern(const char * pattern, UINT32 pattern_len, const char * str, UINT32 str_len) {
    int pattern_sep_pos_short = patternSeparatorShortPos(pattern, pattern_len);
    return compareStr(pattern, pattern_len, str, str_len) ||
            compareStr(pattern, pattern_sep_pos_short, str, str_len);
}


/**
 * Compose command from previsou command anc current command
 * 
 * @param ptr_prev pointer to previous command
 * @param len_prev length of previous command
 * @param pptr pointer to pointer of current command
 * @param plen pointer to length of current command
 * 
 * ptr_prev and ptr should be in the same memory buffer
 * 
 * Function will add part of previous command prior to ptr_prev
 * 
 * char * cmd = "meas:volt:dc?;ac?"
 * char * ptr_prev = cmd;
 * size_t len_prev = 13;
 * char * ptr = cmd + 14;
 * size_t len = 3;
 * 
 * composeCompoundCommand(ptr_prev, len_prev, &ptr, &len);
 * 
 * after calling this
 *  
 */
boolean composeCompoundCommand(char * ptr_prev, UINT32 len_prev,
                               char ** pptr, UINT32 * plen) {
    char * ptr;
    UINT32 len;
    UINT32 i;

    /* Invalid input */
    if (pptr == NULL || plen == NULL)
        return FALSE;

    /* no previous command - nothing to do*/
    if (ptr_prev == NULL || len_prev == 0)
        return TRUE;
       
    ptr = *pptr;
    len = *plen;
    
    /* No current command */
    if (len == 0 || ptr == NULL)
        return FALSE;
    
    /* Common command or command root - nothing to do */
    if (ptr[0] == '*' || ptr[0] == ':')
        return TRUE;
        
    /* Previsou command was common command - nothing to do */
    if (ptr_prev[0] == '*')
        return TRUE;
        
    /* Find last occurence of ':' */
    for (i = len_prev; i > 0; i--) {
        if (ptr_prev[i-1] == ':') {
            break;
        }
    }
    
    /* Previous command was simple command - nothing to do*/
    if (i == 0)
        return TRUE;
    
    ptr -= i;
    len += i;
    memmove(ptr, ptr_prev, i);
    *plen = len;
    *pptr = ptr;
    return TRUE;
}

#if !HAVE_STRNLEN
/* use FreeBSD strnlen */

/*-
 * Copyright (c) 2009 David Schultz <das@FreeBSD.org>
 * All rights reserved.
 */
UINT32 BSD_strnlen(const char *s, UINT32 maxlen)
{
    UINT32 len;

    for (len = 0; len < maxlen; len++, s++) {
        if (!*s)
            break;
    }
    return (len);
}
#endif

#if !HAVE_STRNCASECMP && !HAVE_STRNICMP
int OUR_strncasecmp(const char *s1, const char *s2, UINT32 n) {
    unsigned char c1, c2;

    for(; n != 0; n--) {
        c1 = tolower((unsigned char)*s1++);
        c2 = tolower((unsigned char)*s2++);
        if (c1 != c2) {
            return c1 - c2;
        }
        if (c1 = '\0') {
            return 0;
        }
    }
    return 0;
}
#endif