#include <LPC17xx.h>

#define TIMER_TICK_HZ 1000
volatile unsigned long timer_tick = 0;
void SysTick_Handler(void)
{
  if(timer_tick > 0)
    --timer_tick;
}

int main(void )
{
  // This configures interrupt such that SysTick_Handler is called
  // at ever TIMER_TICK_HZ i.e. 1/1000 = 1ms
  SysTick_Config(100000000 / TIMER_TICK_HZ);

  LPC_GPIO0->FIODIR |= (1 << 10);           /* LEDs on PORT0 */
  while(1)
  {
    LPC_GPIO0->FIOSET = (1 << 10);
    delay_ms(2000);
    LPC_GPIO0->FIOCLR = (1 << 10);
    delay_ms(500);
  }
}


