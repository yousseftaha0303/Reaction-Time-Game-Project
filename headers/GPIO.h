#ifndef GPIO
#define GPIO
void PortE_Init(void);

void EnableInterrupts(void);
void WaitForInterrupt(void);
void GPIOE_Handler(void);

#endif 
