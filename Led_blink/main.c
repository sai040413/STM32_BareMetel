#define RCC_AHB1ENR   (*(volatile unsigned int*)0x40023830)
#define GPIOA_MODER   (*(volatile unsigned int*)0x40020000)
#define GPIOA_ODR     (*(volatile unsigned int*)0x40020014)

void delay() {
    for (volatile int i = 0; i < 500000; i++);
}

int main() {
    RCC_AHB1ENR |= (1 << 0);         // Enable GPIOA clock
    GPIOA_MODER |= (1 << 10);        // Set PA5 as output (MODER5 = 01)
    GPIOA_MODER &= ~(1 << 11);

    while (1) {
        GPIOA_ODR ^= (1 << 5);       // Toggle PA5
        delay();
    }
}

