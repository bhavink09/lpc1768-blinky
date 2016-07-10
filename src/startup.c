/*
 * This is an ARM Cortex-M3 startup file for the NXP LPC1768.
 */
#include <LPC17xx.h>

// Dummy handler.
void Default_Handler (void) { while (1); }

// Weakly bind all interrupt vectors to the dummy handler.
void __attribute__((weak)) Reset_Handler(void);
void __attribute__((weak)) NMI_Handler(void);
void __attribute__((weak)) HardFault_Handler(void);
void __attribute__((weak)) MemManage_Handler(void);
void __attribute__((weak)) BusFault_Handler(void);
void __attribute__((weak)) UsageFault_Handler(void);
void __attribute__((weak)) SVC_Handler(void);
void __attribute__((weak)) DebugMon_Handler(void);
void __attribute__((weak)) PendSV_Handler(void);
void __attribute__((weak)) SysTick_Handler(void);
#pragma weak NMI_Handler        = Default_Handler
#pragma weak HardFault_Handler  = Default_Handler
#pragma weak MemManage_Handler  = Default_Handler
#pragma weak BusFault_Handler   = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler        = Default_Handler
#pragma weak DebugMon_Handler   = Default_Handler
#pragma weak PendSV_Handler     = Default_Handler
#pragma weak SysTick_Handler    = Default_Handler

#define ALIAS(f) __attribute__ ((weak, alias (#f)))

void WDT_IRQHandler(void) ALIAS(Default_Handler);
void TIMER0_IRQHandler(void) ALIAS(Default_Handler);
void TIMER1_IRQHandler(void) ALIAS(Default_Handler);
void TIMER2_IRQHandler(void) ALIAS(Default_Handler);
void TIMER3_IRQHandler(void) ALIAS(Default_Handler);
void UART0_IRQHandler(void) ALIAS(Default_Handler);
void UART1_IRQHandler(void) ALIAS(Default_Handler);
void UART2_IRQHandler(void) ALIAS(Default_Handler);
void UART3_IRQHandler(void) ALIAS(Default_Handler);
void PWM1_IRQHandler(void) ALIAS(Default_Handler);
void I2C0_IRQHandler(void) ALIAS(Default_Handler);
void I2C1_IRQHandler(void) ALIAS(Default_Handler);
void I2C2_IRQHandler(void) ALIAS(Default_Handler);
void SPI_IRQHandler(void) ALIAS(Default_Handler);
void SSP0_IRQHandler(void) ALIAS(Default_Handler);
void SSP1_IRQHandler(void) ALIAS(Default_Handler);
void PLL0_IRQHandler(void) ALIAS(Default_Handler);
void RTC_IRQHandler(void) ALIAS(Default_Handler);
void EINT0_IRQHandler(void) ALIAS(Default_Handler);
void EINT1_IRQHandler(void) ALIAS(Default_Handler);
void EINT2_IRQHandler(void) ALIAS(Default_Handler);
void EINT3_IRQHandler(void) ALIAS(Default_Handler);
void ADC_IRQHandler(void) ALIAS(Default_Handler);
void BOD_IRQHandler(void) ALIAS(Default_Handler);
void USB_IRQHandler(void) ALIAS(Default_Handler);
void CAN_IRQHandler(void) ALIAS(Default_Handler);
void DMA_IRQHandler(void) ALIAS(Default_Handler);
void I2S_IRQHandler(void) ALIAS(Default_Handler);
void ENET_IRQHandler(void) ALIAS(Default_Handler);
void RIT_IRQHandler(void) ALIAS(Default_Handler);
void MCPWM_IRQHandler(void) ALIAS(Default_Handler);
void QEI_IRQHandler(void) ALIAS(Default_Handler);
void PLL1_IRQHandler(void) ALIAS(Default_Handler);
void USBActivity_IRQHandler(void) ALIAS(Default_Handler);
void CANActivity_IRQHandler(void) ALIAS(Default_Handler);


// Start of the stack (last RAM address; exported in the linker script)
extern void _sstack;
extern void vPortSVCHandler( void );
extern void xPortPendSVHandler( void );
void xPortSysTickHandler( void );

// The signature of Cortex-M3 interrupt handlers.
typedef void (* const Interrupt_Handler_P)(void);

// Interrupt vectors table
__attribute__ ((section(".cs3.interrupt_vector")))
Interrupt_Handler_P interrupt_vectors[] = {
  &_sstack,                     // the first  word contains  the initial
                                // stack pointer  the hardware  loads it
                                // to the  SP register before  the first
                                // instruction
  // Standard Cortex-M3 interrupts:
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  0,
  DebugMon_Handler,
  0,
  0,
  SysTick_Handler,
  // Vendor specific interrupts for LPC1768:
  WDT_IRQHandler,             // 16, 0x40 - WDT
  TIMER0_IRQHandler,            // 17, 0x44 - TIMER0
  TIMER1_IRQHandler,            // 18, 0x48 - TIMER1
  TIMER2_IRQHandler,            // 19, 0x4c - TIMER2
  TIMER3_IRQHandler,            // 20, 0x50 - TIMER3
  UART0_IRQHandler,           // 21, 0x54 - UART0
  UART1_IRQHandler,           // 22, 0x58 - UART1
  UART2_IRQHandler,           // 23, 0x5c - UART2
  UART3_IRQHandler,           // 24, 0x60 - UART3
  PWM1_IRQHandler,            // 25, 0x64 - PWM1
  I2C0_IRQHandler,            // 26, 0x68 - I2C0
  I2C1_IRQHandler,            // 27, 0x6c - I2C1
  I2C2_IRQHandler,            // 28, 0x70 - I2C2
  SPI_IRQHandler,             // 29, 0x74 - SPI
  SSP0_IRQHandler,            // 30, 0x78 - SSP0
  SSP1_IRQHandler,            // 31, 0x7c - SSP1
  PLL0_IRQHandler,            // 32, 0x80 - PLL0 (Main PLL)
  RTC_IRQHandler,             // 33, 0x84 - RTC
  EINT0_IRQHandler,           // 34, 0x88 - EINT0
  EINT1_IRQHandler,           // 35, 0x8c - EINT1
  EINT2_IRQHandler,           // 36, 0x90 - EINT2
  EINT3_IRQHandler,           // 37, 0x94 - EINT3
  ADC_IRQHandler,             // 38, 0x98 - ADC
  BOD_IRQHandler,             // 39, 0x9c - BOD
  USB_IRQHandler,             // 40, 0xA0 - USB
  CAN_IRQHandler,             // 41, 0xa4 - CAN
  DMA_IRQHandler,             // 42, 0xa8 - GP DMA
  I2S_IRQHandler,             // 43, 0xac - I2S
  ENET_IRQHandler,            // 44, 0xb0 - Ethernet.
  RIT_IRQHandler,             // 45, 0xb4 - RITINT
  MCPWM_IRQHandler,           // 46, 0xb8 - Motor Control PWM
  QEI_IRQHandler,             // 47, 0xbc - Quadrature Encoder
  PLL1_IRQHandler,            // 48, 0xc0 - PLL1 (USB PLL)
  USBActivity_IRQHandler,         // 49, 0xc4 - USB Activity interrupt to wakeup
  CANActivity_IRQHandler,         // 50, 0xc8 - CAN Activity interrupt to wakeup

};

extern int main (void);

extern uint32_t _etext, _sdata, _edata, __bss_start__, __bss_end__;

void
Reset_Handler(void)
{
  // Initialize clocks
  SystemInit ();
  uint32_t *s, *d;
  // Copy initialization data to RAM (.data section)
  s = &_etext;
  d = &_sdata;
  while (d < &_edata) *d++ = *s++;
  // Zero the remaining allocated RAM (.bss section)
  d = &__bss_start__;
  while (d < &__bss_end__)  *d++ = 0;
  // Everything is ready. Run the user program.
  main();
  while (1);
}
