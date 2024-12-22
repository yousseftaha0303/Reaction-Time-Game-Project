#include "../headers/ADC.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/GlobalConfig.h"
#include "../headers/timer.h"
#include "../headers/Nokia5110.h"
#include <stdint.h>


// Possible overflow because of continous sampling? Page 828
// Instead of using another ADC we can use another sequencer (e.g sequence 2)

volatile unsigned int diff_result;
volatile unsigned int LDR_result;
volatile int adcdelay;


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


void ADC_Init(void) {
    SYSCTL_RCGCADC_R |= (1 << 0);             // Enable ADC0 clock
    SYSCTL_RCGCGPIO_R |= (1 << 4);            // Enable clock for Port E

    adcdelay = 0;
    adcdelay += 4;                               // Stabilization delay

    GPIO_PORTE_AFSEL_R |= (1 << 3);           // Enable alternate function on PE3
    GPIO_PORTE_DEN_R &= ~(1 << 3);            // Disable digital function on PE3
    GPIO_PORTE_AMSEL_R |= (1 << 3);           // Enable analog functionality on PE3

    ADC0_ACTSS_R &= ~(1 << 3);                // Disable Sample Sequencer 3
    ADC0_EMUX_R &= ~(0xF << 12);              // Configure as software trigger
    ADC0_SSMUX3_R = 0;                        // Set input channel to AIN0 (PE3)
    ADC0_SSCTL3_R = (1 << 1) | (1 << 2);      // Single-ended, end-of-sequence
    ADC0_ACTSS_R |= (1 << 3);                 // Enable Sample Sequencer 3
}

// Read ADC value using bitwise operations
uint16_t ADC_Read(void) {
    uint16_t result;
    ADC0_PSSI_R |= (1 << 3);                  // Initiate SS3
    while ((ADC0_RIS_R & (1 << 3)) == 0);     // Wait for conversion to complete
    result = ADC0_SSFIFO3_R & 0xFFF;          // Read 12-bit result
    ADC0_ISC_R |= (1 << 3);                   // Clear interrupt flag
    return result;
}

int ADC_GetDiff(void){
		uint16_t diff_result = ADC_Read();
		if(diff_result <= 1365){
			GameDiff = 1;
		}
		else if(diff_result > 1365 && diff_result <= 2730){
			GameDiff = 2;
		}
		else{
			GameDiff = 3;
		}
		return GameDiff;
}

/*void ADC1Seq3_Handler(void)
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

void ADC1Seq2_Handler(void)
{
	if(ADC1_RIS_R & (1 << 2)){
		ADC1_ISC_R |= (1 << 2);
		LDR_result = ADC1_SSFIFO2_R;
		if(LDR_result < LDR_Threshold){
			isDark = 1;
			Timer2_stop();
			Nokia5110_Clear();
			Nokia5110_ClearBuffer();
			Nokia5110_OutString("Stand in the light");
			attempt = 0;
			score = 0;
		}
		else if(isDark == 1){
			isDark = 0;
			Timer2_delay(HoldDelay * CyclesPerSec);
		}
	}
}*/