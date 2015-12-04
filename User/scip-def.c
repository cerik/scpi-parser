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
 * @file   scpi-def.c
 * @date   Thu Nov 15 10:58:45 UTC 2012
 * 
 * @brief  SCPI Command Defination
 * 
 */
#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include "parser.h"
#include "utils.h"
#include "error.h"
#include "scpi.h"
#include "fifo.h"


#define SCPI_INPUT_BUFFER_LENGTH 100

//static fifo_t fifo;
static char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
static scpi_reg_val_t scpi_regs[SCPI_REG_COUNT];


static FLOAT32 gMatrix[5][5][5]={0.0};
//======================================================================
//                                                                     =
// Interface Function Decleration                                      =
//                                                                     =
//======================================================================

static INT32 SCPI_Error(scpi_t * context, INT16 err) {
    printf("**ERROR: %d, \"%s\"\r\n",(INT32) err, SCPI_ErrorTranslate(err));
    return err;
}

static INT32 SCPI_Write(scpi_t * context, const char * data, INT32 len) {
	INT32 i=0;
    while(i<len)
	{
		printf("%c",*data++);
		i++;
	}
    return i;
}

static scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    if (SCPI_CTRL_SRQ == ctrl) {
        printf("**SRQ: 0x%X (%d)\r\n", val, val);
    } else {
        printf("**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
    }
    return SCPI_RES_OK;
}

static scpi_result_t SCPI_Flush(scpi_t * context) {
    return SCPI_RES_OK;
}

static scpi_result_t SCPI_Reset(scpi_t * context) {
    printf("**Reset\r\n");
    return SCPI_RES_OK;
}

static scpi_result_t SCPI_Test(scpi_t * context) {
    return SCPI_RES_OK;
}

//======================================================================
//                                                                     =
// Command Decleration                                                 =
//                                                                     =
//======================================================================
#if 0
static scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context) {
    scpi_number_t param1, param2;
    char bf[15];
    // read first parameter if present
    if (SCPI_ParamNumber(context, &param1, FALSE)) {
        SCPI_NumberToStr(context, &param1, bf, 15);
        SCPI_ResultString(context,bf);
    }

    // read second paraeter if present
    if (SCPI_ParamNumber(context, &param2, FALSE)) {
        SCPI_NumberToStr(context, &param2, bf, 15);
        SCPI_ResultString(context,bf);
    }
    return SCPI_RES_OK;
}

//===================================================================
// Configure Command
//===================================================================
static scpi_result_t CFG_Frequency(scpi_t * context) {
    scpi_number_t param1;
    //char bf[15];
    // read first parameter if present
    if (SCPI_ParamNumber(context, &param1, FALSE)) {
        //SCPI_NumberToStr(context, &param1, bf, 15);
        //SCPI_ResultString(context,bf);
        return SCPI_RES_OK;
    }
    else
    {
        return SCPI_RES_ERR;
    }
}
static scpi_result_t CFG_FrequencyQ(scpi_t * context) {
    char bf[15];
    scpi_number_t param1;
    param1.value = 123 ;
    param1.type = SCPI_NUM_NUMBER;
    SCPI_NumberToStr(context, &param1, bf, 15);
    SCPI_ResultString(context,bf);
    return SCPI_RES_OK;
}


//===================================================================
// Device Measure Command
//===================================================================
static scpi_result_t DMM_CalibDbX(scpi_t * context,INT8 which)
{
    scpi_number_t param1, param2;
    char bf[15];
    // read first parameter if present
    if (SCPI_ParamNumber(context, &param1, FALSE)) {
    //  ABC[which][0]=param1.value;
        SCPI_NumberToStr(context, &param1, bf, 15);
        SCPI_ResultString(context,bf);
    }

    // read second paraeter if present
    if (SCPI_ParamNumber(context, &param2, FALSE)) {
    //  ABC[which][1]=param2.value;
        SCPI_NumberToStr(context, &param2, bf, 15);
        SCPI_ResultString(context,bf);
    }
    return SCPI_RES_OK;
}

static scpi_result_t DMM_CalibDbA(scpi_t * context)
{
    return DMM_CalibDbX(context,0);
}
static scpi_result_t DMM_CalibDbB(scpi_t * context)
{
    return DMM_CalibDbX(context,1);
}
static scpi_result_t DMM_CalibDbC(scpi_t * context)
{
    return DMM_CalibDbX(context,2);
}

static scpi_result_t DMM_CalibDbXQ(scpi_t * context,INT8 which)
{ 
    char bf[15];
    // read first parameter if present
    SCPI_ResultString(context,bf);

    // read second paraeter if present
    SCPI_ResultString(context,bf);
    return SCPI_RES_OK;
}
static scpi_result_t DMM_CalibDbAQ(scpi_t * context)
{
    return DMM_CalibDbXQ(context,0);
}
static scpi_result_t DMM_CalibDbBQ(scpi_t * context)
{
    return DMM_CalibDbXQ(context,1);
}
static scpi_result_t DMM_CalibDbCQ(scpi_t * context)
{
    return DMM_CalibDbXQ(context,2);
}

static scpi_result_t DMM_MeasRawVolt(scpi_t * context)
{
    //StartConversion(TRUE);
    //while(!IsCovsCompleted());
//    SCPI_ResultDouble(context,gAdState.PvCalc[0]);
//    SCPI_ResultDouble(context,gAdState.PvCalc[1]);
    return SCPI_RES_OK;
}

static scpi_result_t DMM_MeasTemperature(scpi_t * context)
{
    FLOAT32 T[3]={0,0,0};

    //while(!IsCovsCompleted());
    
    SCPI_ResultDouble(context,T[0]);
    SCPI_ResultDouble(context,T[1]);
    SCPI_ResultDouble(context,T[2]);
    return SCPI_RES_OK;
}
#endif

static scpi_result_t DMM_MatrixSave(scpi_t * context)
{
    return SCPI_RES_OK;
}

//===============================================================
// Configure system database
// normal_matrix[arg1][arg2][arg3]=arg4
// arg1 & arg2 is interger
// arg4 is float32.
static scpi_result_t CFG_MatrixQ(scpi_t *context)
{
    scpi_number_t param;
    UINT8 i,j,k;
    
    // read first parameter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        i = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }

    // read second paraeter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        j = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }

    // read third paraeter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        k = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }
	SCPI_ResultDouble(context,gMatrix[i][j][k]);
    return SCPI_RES_OK;
}

static scpi_result_t CFG_Matrix(scpi_t *context)
{
    scpi_number_t param;
    FLOAT32 value;
    UINT8 i,j,k;
    
    // read first parameter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        i = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }

    // read second paraeter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        j = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }

    // read third paraeter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        k = (UINT8)param.value;
    }else{
        return SCPI_RES_ERR;
    }

    // read fourth paraeter if present
    if (SCPI_ParamNumber(context, &param, FALSE)) {
        value =(FLOAT32) param.value;
    }else{
        return SCPI_RES_ERR;
    }
    gMatrix[i][j][k]=value;
    printf("%s:%d --->[%d][%d][%d]=%f\r\n",__FUNCTION__,__LINE__,i,j,k,gMatrix[i][j][k]);
    return SCPI_RES_OK;
}

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    {  "*CLS",SCPI_CoreCls},
    {  "*ESE",SCPI_CoreEse},
    { "*ESE?",SCPI_CoreEseQ},
    { "*ESR?",SCPI_CoreEsrQ},
    { "*IDN?",SCPI_CoreIdnQ},
    {  "*OPC",SCPI_CoreOpc},
    { "*OPC?",SCPI_CoreOpcQ},
    {  "*RST",SCPI_CoreRst},
    {  "*SRE",SCPI_CoreSre},
    { "*SRE?",SCPI_CoreSreQ},
    { "*STB?",SCPI_CoreStbQ},
    { "*TST?",SCPI_CoreTstQ},
    {  "*WAI",SCPI_CoreWai},

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {      "SYSTem:ERRor?",SCPI_SystemErrorNextQ},
    { "SYSTem:ERRor:NEXT?",SCPI_SystemErrorNextQ},
    {"SYSTem:ERRor:COUNt?",SCPI_SystemErrorCountQ},
    {    "SYSTem:VERSion?",SCPI_SystemVersionQ},

    {       "STATus:QUEStionable?",SCPI_StatusQuestionableEventQ},
    { "STATus:QUEStionable:EVENt?",SCPI_StatusQuestionableEventQ},
    { "STATus:QUEStionable:ENABle",SCPI_StatusQuestionableEnable},
    {"STATus:QUEStionable:ENABle?",SCPI_StatusQuestionableEnableQ},
    {              "STATus:PRESet",SCPI_StatusPreset,},

    /* CONF */
    {         "CONFigure:MATrix", CFG_Matrix},
    {         "CONFigure:MATrix?",CFG_MatrixQ},
    {           "CONFigure:SAVe", DMM_MatrixSave},

    /* MEAS */
  //{"MEASure:VOLTage:DC?",MEAS_MeasureVoltageDcQ,},
  //{       "MEASure:RAw?",MEAS_Raw,},
  //{       "MEASure:RGB?",MEAS_MeasureRgbReq,},
  //{       "MEASure:REG?",MEAS_MeasureRegReq,},
  //{     "MEASure:FLIck?",MEAS_FlickReq,},
  //{"MEASure:VOLTage:DC:RATio?",SCPI_StubQ,},
  //{      "MEASure:VOLTage:AC?",SCPI_StubQ,},
  //{      "MEASure:CURRent:DC?",SCPI_StubQ,},
  //{      "MEASure:CURRent:AC?",SCPI_StubQ,},
  //{      "MEASure:RESistance?",SCPI_StubQ,},
  //{     "MEASure:FRESistance?",SCPI_StubQ,},
  //{       "MEASure:FREQuency?",SCPI_StubQ,},
  //{          "MEASure:PERiod?",SCPI_StubQ,},
    SCPI_CMD_LIST_END
};

static scpi_interface_t scpi_interface = {
    SCPI_Error,
    SCPI_Write,
    SCPI_Control,
    SCPI_Flush,
    SCPI_Reset,
    SCPI_Test
};

static scpi_t scpi_context = {
    scpi_commands,               //cmdlist
    {//buffer
        SCPI_INPUT_BUFFER_LENGTH,//length
        0,                       //position
        scpi_input_buffer        //*data
    },
    {0,0,0},                     //paramlist
    &scpi_interface,             //interface
    0,                           //output_count
    0,                           //input_count
    FALSE,                       //cmd_error
    0,                           //error_queue
    scpi_regs,                   //registers
    scpi_units_def,              //units
    scpi_special_numbers_def,    //special_numbers
    0                            //user_context
};

int ScpiInput(const char * data, INT32 len)
{
    return SCPI_Input(&scpi_context, data, len); 
}

void InitSCPI(void)
{
    //fifo_init(&fifo);
    SCPI_Init(&scpi_context);
}