#include "../headers/ADC.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/GlobalConfig.h"


// Possible overflow because of continous sampling? Page 828
// Instead of using another ADC we can use another sequencer (e.g sequence 2)

volatile unsigned int diff_result;
volatile unsigned int LDR_result;


/*
void ADC1_Initialize(void) // Potentiometer
{
  SYSCTL_RCGCADC_R |= (1 << 1);
	SYSCTL_RCGC2_R |= (1 << 3);
	GPIO_PORTD_DIR_R &= ~(1 << 1);   // Set PD1 as input
  GPIO_PORTD_AFSEL_R |= (1 << 1);  // Enable alternate function (ADC)
  GPIO_PORTD_DEN_R &= ~(1 << 1);   // Disable digital function
  GPIO_PORTD_AMSEL_R |= (1 << 1);  // Enable analog function
	
	ADC1_ACTSS_R &= ~(1 << 3);			 // Disable sample sequencer 3
	ADC1_EMUX_R |= (15 << 12);			 // Countinuously sample 
	ADC1_SSMUX3_R = 6;
	ADC1_SSCTL3_R |= (1 << 1) | (1 << 2);	// (1 << 2) Enables Interrupt, (1 << 1) marks as end of sequence
	ADC1_IM_R |= (1 << 3);
	ADC1_ACTSS_R |= (1 << 3);
	NVIC_EN1_R |= (1 << 19);              // Enable NVIC for ADC1SS3 (IRQ 51)
}

void ADC0_Initialize(void) //LDR
{
  SYSCTL_RCGCADC_R |= (1 << 0); 
	SYSCTL_RCGC2_R |= (1 << 3);

	GPIO_PORTD_DIR_R &= ~(1 << 0);   // Set PD0 as input
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

void ADC_InitBoth(void)
{
	ADC0_Initialize();
	ADC1_Initialize();
}

void ADC1_Handler(void)
	// ADC values range from 0 to 4095 with step size of 3.3v / 4095 = 0.0008v
	// To divide the range into 3 values (0 - 1365, 1366 - 2730, 2731 - 4095)
{
	if(ADC1_RIS_R & (1 << 3)){
		ADC1_ISC_R |= (1 << 3);
		diff_result = ADC1_SSFIFO3_R;		// variable diff_result stores the sampling result
		if(diff_result <= 1365){
			GameDiff = 1;
		}
		else if(diff_result > 1365 && diff_result <= 2730){
			GameDiff = 2;
		}
		else{
			GameDiff = 3;
		}
	}
}
*/


void ADC1_initialize(void){
	SYSCTL_RCGCADC_R |= (1 << 1);
	SYSCTL_RCGC2_R |= (1 << 3);
	
	GPIO_PORTD_DIR_R &= ~(1 << 1);   // Set PD1 as input
  GPIO_PORTD_AFSEL_R |= (1 << 1);  // Enable alternate function (ADC)
  GPIO_PORTD_DEN_R &= ~(1 << 1);   // Disable digital function
  GPIO_PORTD_AMSEL_R |= (1 << 1);  // Enable analog function
	
	GPIO_PORTD_DIR_R &= ~(1 << 0);   // Set PD0 as input
  GPIO_PORTD_AFSEL_R |= (1 << 0);  // Enable alternate function (ADC)
  GPIO_PORTD_DEN_R &= ~(1 << 0);   // Disable digital function
  GPIO_PORTD_AMSEL_R |= (1 << 0);  // Enable analog function
	
	// Initialization for Potentiometer
	ADC1_ACTSS_R &= ~(1 << 3);			 // Disable sample sequencer 3
	ADC1_EMUX_R |= (15 << 12);			 // Countinuously sample 
	ADC1_SSMUX3_R = 6;							 // ADC input 6 for PD1
	ADC1_SSCTL3_R |= (1 << 1) | (1 << 2);	// (1 << 2) Enables Interrupt, (1 << 1) marks as end of sequence
	ADC1_IM_R |= (1 << 3);
	ADC1_ACTSS_R |= (1 << 3);
	
	// Initialization for LDR
	ADC1_ACTSS_R &= ~(1 << 2);			 // Disable sample sequencer 2
	ADC1_EMUX_R |= (15 << 8);			   // Countinuously sample
	ADC1_SSMUX3_R = 7;							 // ADC input 7 for PD0
	ADC1_SSCTL3_R |= (1 << 1) | (1 << 2);	// (1 << 2) Enables Interrupt, (1 << 1) marks as end of sequence
	ADC1_IM_R |= (1 << 2);
	ADC1_ACTSS_R |= (1 << 2);
	
	NVIC_EN1_R |= (1 << 19) | (1 << 18);				 //  Enable NVIC for ADC1SS3 (IRQ 51), Enable NVIC for ADC1SS2 (IRQ 50)
	
	NVIC_PRI2_R = (NVIC_PRI2_R & ~0xE0000000) | (0 << 29); // Set priority 0 for ADC1 Sequencer 2 (IRQ 50)
	NVIC_PRI4_R = (NVIC_PRI4_R & ~0x000000E0) | (3 << 5);   // Set priority 3 for ADC1 Sequencer 3 (IRQ 51)

}

void ADC1Sequence3_Handler(void)
	// ADC values range from 0 to 4095 with step size of 3.3v / 4095 = 0.0008v
	// To divide the range into 3 values (0 - 1365, 1366 - 2730, 2731 - 4095)
{
	if(ADC1_RIS_R & (1 << 3)){
		ADC1_ISC_R |= (1 << 3);
		diff_result = ADC1_SSFIFO3_R;		// variable diff_result stores the sampling result
		if(diff_result <= 1365){
			GameDiff = 1;
		}
		else if(diff_result > 1365 && diff_result <= 2730){
			GameDiff = 2;
		}
		else{
			GameDiff = 3;
		}
	}
}

void ADC1Sequence2_Handler(void)
{
	if(ADC1_RIS_R & (1 << 2)){
		ADC1_ISC_R |= (1 << 2);
		LDR_result = ADC1_SSFIFO2_R;
		if(LDR_result >= LDR_Threshold){
			isLight = 1;
		}
		else{
			isLight = 0;
		}
	}
}