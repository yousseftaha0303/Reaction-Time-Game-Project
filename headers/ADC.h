#ifndef ADC
#define ADC

#include <stdint.h>

/*oid ADC1_Initialize(void);
void ADC0_Initialize(void);
void ADC_InitBoth(void);
void ADC1_Handler(void);
void ADC0_Handler(void);
*/
void ADC_Init(void);
uint16_t ADC_Read(void);
int ADC_GetDiff(void);
/*void ADC1Seq3_Handler(void);
void ADC1Seq2_Handler(void);*/


#endif