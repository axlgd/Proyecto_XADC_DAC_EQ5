/*
 * main.c
 *
 *  Created on: 25/05/2023
 *      Author: luis-
 */

/*** Libraries ***/
#include "xparameters.h"	// System related parameters (produced by Vitis based on the provided XSA or HDF)
#include "xgpio.h"			// BSP of the Xilinx AXI GPIO Controller
#include "sleep.h"			// Time based functions
#include <xil_types.h>
#include <xsysmon.h>
#include <stdio.h>


/*** Hardware Instances ***/
XGpio GPIO;
XSysMon xadc;
XSysMon_Config *xadc_config;


int status;
u16 ADC_out;
int main()
{
	XGpio_Initialize(&GPIO, XPAR_AXI_GPIO_0_DEVICE_ID);
	xadc_config = XSysMon_LookupConfig(XPAR_SYSMON_0_DEVICE_ID);
	XSysMon_CfgInitialize(&xadc, xadc_config, xadc_config->BaseAddress);


	while(1)
	{
		ADC_out = XSysMon_GetAdcData(&xadc, XSM_CH_VPVN);
	    XGpio_DiscreteWrite(&GPIO, 1, ADC_out);
		usleep(1000);

		printf("Voltage = %.2f\r\n",(ADC_out)/65535.0);
		usleep(1000);
	}
}















