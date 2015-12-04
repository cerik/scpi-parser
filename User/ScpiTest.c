// ScpiTest.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <time.h>
#include "scpi-interface.h"

char gTstCmd1[]={"CONFigure:MATrix 1,2,2,1.2;MAT? 1,2,2;MAT 1,2,2,2.1;MAT? 1,2,2;\r"};

int main(int argc, char* argv[])
{
    clock_t start,end;
    
    start = clock();
    printf("start:%d\n",start);
    
	InitSCPI();
	ScpiInput(gTstCmd1,sizeof(gTstCmd1)-1);
    end = clock();
    printf("end:%d\n",end);
	getchar();
	return 0;
}
