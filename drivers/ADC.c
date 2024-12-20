#include "./headers/ADC.h"
#include "./headers/tm4c123gh6pm.h"

void ADC1_Init(void)
{
  SYSCTL_RCGCADC_R |= (1 << 1);
	SYSCTL_RCGC2_R |= (1 << 3);
	GPIO_PORTD_DIR_R &= ~(1 << 1);   // Set PD1 as input
  GPIO_PORTD_AFSEL_R |= (1 << 1);  // Enable alternate function (ADC)
  GPIO_PORTD_DEN_R &= ~(1 << 1);   // Disable digital function
  GPIO_PORTD_AMSEL_R |= (1 << 1);  // Enable analog function
	
	ADC1_ACTSS_R &= ~(1 << 3);
	ADC1_EMUX_R |= (15 << 12);
	ADC1_SSMUX3_R = 6;
	ADC1_SSCTL3_R |= (1 << 1);
	ADC1_IM_R |= (1 << 3);
	ADC1_ACTSS_R |= (1 << 3);
}

void ADC0_Init(void) 
{
  SYSCTL_RCGCADC_R |= (1 << 0); 
	SYSCTL_RCGC2_R |= (1 << 3);
	GPIO_PORTD_AFSEL_R |= (1 << 0);
	GPIO_PORTD_DIR_R &= ~(1 << 0);   // Set PD1 as input
  GPIO_PORTD_AFSEL_R |= (1 << 0);  // Enable alternate function (ADC)
  GPIO_PORTD_DEN_R &= ~(1 << 0);   // Disable digital function
  GPIO_PORTD_AMSEL_R |= (1 << 0);  // Enable analog function
	
	ADC0_ACTSS_R &= ~(1 << 3);
	ADC0_EMUX_R |= (15 << 12);
	ADC0_SSMUX3_R = 7;
	ADC0_SSCTL3_R |= (1 << 1);
	ADC0_IM_R |= (1 << 3);
	ADC0_ACTSS_R |= (1 << 3);
}

void ADC_Init(void)
{
	ADC0_Init();
	ADC1_Init();
}