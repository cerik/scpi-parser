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
 * @file   scpi_parser.h
 * @date   Thu Nov 15 10:58:45 UTC 2012
 * 
 * @brief  SCPI parser implementation
 * 
 * 
 */

#ifndef SCPI_PARSER_H
#define	SCPI_PARSER_H

#include "types.h"
#include "debug.h"

#ifdef  __cplusplus
extern "C" {
#endif

    void SCPI_Init(scpi_t * context);

    int SCPI_Input(scpi_t * context, const char * data, UINT32 len);
    int SCPI_Parse(scpi_t * context, const char * data, UINT32 len);


    UINT32 SCPI_ResultString(scpi_t * context, const char * data);
    UINT32 SCPI_ResultInt(scpi_t * context, INT32 val);
    UINT32 SCPI_ResultDouble(scpi_t * context, double val);
    UINT32 SCPI_ResultText(scpi_t * context, const char * data);

    boolean SCPI_ParamInt(scpi_t * context, INT32 * value, boolean mandatory);
    boolean SCPI_ParamDouble(scpi_t * context, double * value, boolean mandatory);
    boolean SCPI_ParamString(scpi_t * context, const char ** value, UINT32 * len, boolean mandatory);
    boolean SCPI_ParamText(scpi_t * context, const char ** value, UINT32 * len, boolean mandatory);    


#ifdef	__cplusplus
}
#endif

#endif	/* SCPI_PARSER_H */

