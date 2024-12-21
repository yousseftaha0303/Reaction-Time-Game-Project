#ifndef GPIO
#define GPIO

void PortB_Init(void);
void PortF_Init(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void GPIOB_Handler(void);


#endif 
