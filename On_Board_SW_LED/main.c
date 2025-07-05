#include <stdint.h>
#define RCC_AHB1ENR (*(volatile unsigned int *)0x40023830)
#define GPIOA_MODER (*(volatile unsigned int *)0x40020000)
#define GPIOA_ODR (*(volatile unsigned int *)0x40020014)
#define GPIOC_MODER (*(volatile uint32_t *)0x40020800)
#define GPIOC_IDR (*(volatile unsigned int *)0x40020810)
#define SW 13
void delay()
{
    for (volatile int i = 0; i < 500000; i++)
        ;
}

int main()
{
    RCC_AHB1ENR |= (1 << 0);  // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 2);  // Enable GPIOC clock
    GPIOA_MODER |= (1 << 10); // Set PA5 as output (MODER5 = 01)
    GPIOA_MODER &= ~(1 << 11);
    GPIOC_MODER &= ~(3 << 26); // clear 26&27 bits as input (MODER5 = 00)

    while (1)
    {
        if (!(GPIOC_IDR & (1 << SW)))
        {
            delay();
            GPIOA_ODR ^= (1 << 5); // Toggle LED at PA5
            delay();
        }
    }
}
