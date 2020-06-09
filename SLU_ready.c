/*******************************************************************************
* Copyright (C) 2020 TUSUR, FB
* File : 7361_vkd.c
* Compiler : gcc
* Version : 9.2.1
* Created File : 25.02.2020
* Last modified : 1.03.2020
*
* Support mail : voevodin111197@gmail.com
*
* Description : solving of linear equations system of the second order
* :
*******************************************************************************/
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "mstn_version.h"
#include "mstn_led.h"
#include "mstn_clk.h"
#include "mstn_usb.h"

#define AMMOUNT_OF_EQUATIONS 2
#define AMMOUNT_OF_COEFFICIENTS 3
#define AMMOUNT_OF_SOLUTIONS 2

//function calculates solutions of equation's system
void FindSolutions (float** matrix_ptr,	//matrix of coefficints (in)
		    float* solutions)	//array of solutions (out)
{
	float coef = -(matrix_ptr[0][0]/matrix_ptr[1][0]);
	matrix_ptr[0][1] += coef * matrix_ptr[1][1];
	matrix_ptr[0][2] += coef * matrix_ptr[1][2];
	solutions[1] = matrix_ptr[0][2]/matrix_ptr[0][1];
	solutions[0] = (matrix_ptr[1][2] - matrix_ptr[1][1]*solutions[1])/matrix_ptr[1][0];
}

//function prints solutions
void PrintSolutions(float* solutions)//array of solutions(in)
{
	printf("Solutions:");
	printf("\n");
	printf("X1 = ");
	printf("%f", solutions[0]);
	printf("\n");
	printf("X2 = ");
	printf("%f", solutions[1]);
	printf("\n");
}

int main()
{
        while(USB_GetStatus() != PERMITTED);
	float** matrix_ptr = (float**)malloc(sizeof(float*)*AMMOUNT_OF_EQUATIONS);//2-dimensional arra of coefficients of equation's system
	for (int8_t i = 0; i < AMMOUNT_OF_EQUATIONS; i++)
	{
		matrix_ptr[i] = (float*)malloc(sizeof(float)*AMMOUNT_OF_COEFFICIENTS);
	}
	float* solutions = (float*)malloc(sizeof(float)*AMMOUNT_OF_SOLUTIONS);//array of 2 solutions
        matrix_ptr[0][0] = 1;
        matrix_ptr[0][1] = 2;
        matrix_ptr[0][2] = 3;
        matrix_ptr[1][0] = 4;
        matrix_ptr[1][1] = 5;
        matrix_ptr[1][2] = 6;
        
	FindSolutions(matrix_ptr, solutions);//calculate solutions
	PrintSolutions(solutions);//print solutions
	free(matrix_ptr);
	free(solutions);
        while(1)
        {
                //blinking green led
                LED_SetGreenState(TURN_ON);
                Delay(2000);
                LED_SetGreenState(TURN_OFF);
                Delay(2000);
        };
	return 0;
}
