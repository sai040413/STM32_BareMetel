
#include <stdint.h>

#define RCC_AHB1ENR   (*(volatile unsigned int*)0x40023830)
#define RCC_APB1ENR   (*(volatile unsigned int*)0x40023840)

#define GPIOA_MODER   (*(volatile unsigned int*)0x40020000)
#define GPIOA_OSPEEDR (*(volatile unsigned int*)0x40020008)
#define GPIOA_PUPDR   (*(volatile unsigned int*)0x4002000C)
#define GPIOA_AFRL    (*(volatile unsigned int*)0x40020020)

#define USART2_SR     (*(volatile unsigned int*)0x40004400)
#define USART2_DR     (*(volatile unsigned int*)0x40004404)
#define USART2_BRR    (*(volatile unsigned int*)0x40004408)
#define USART2_CR1    (*(volatile unsigned int*)0x4000440C)

void delay() {
    for (volatile int i = 0; i < 500000; i++);
}

void uart2_write(char ch) {
    while (!(USART2_SR & (1 << 7))); // Wait until TXE is set
    USART2_DR = ch;
}

int main() {
    // Enable GPIOA and USART2 clocks
    RCC_AHB1ENR |= (1 << 0);     // GPIOA
    RCC_APB1ENR |= (1 << 17);    // USART2

    // Set PA2 (TX) and PA3 (RX) to alternate function
    GPIOA_MODER &= ~(0xF << 4);   // Clear MODER2 and MODER3
    GPIOA_MODER |=  (0xA << 4);   // Set to AF mode

    // Set AF7 for USART2 (PA2 and PA3)
    GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12));
    GPIOA_AFRL |=  ((0x7 << 8) | (0x7 << 12));

    // Set output speed (optional)
    GPIOA_OSPEEDR |= (0xA << 4);  // Medium speed for PA2, PA3

    // Configure baud rate: assuming 16 MHz clock, 9600 baud
    USART2_BRR = 0x683;  // You may calculate based on your clock

    // USART settings: 8-bit, no parity, enable TX and RX
    USART2_CR1 &= ~(1 << 12);     // 8-bit data
    USART2_CR1 &= ~(1 << 10);     // No parity
    USART2_CR1 |= (1 << 3) | (1 << 2); // TE and RE
    USART2_CR1 |= (1 << 13);      // UE: USART enable

    // Send a message
    char *msg = "UART Tx testing...\r\n";
    while (*msg) {
        uart2_write(*msg++);
        delay();  
    }

   
}


// #include <stdint.h>

// // RCC
// #define RCC_AHB1ENR   (*(volatile uint32_t *)0x40023830)
// #define RCC_APB1ENR   (*(volatile uint32_t *)0x40023840)

// // GPIOA
// #define GPIOA_MODER   (*(volatile uint32_t *)0x40020000)
// #define GPIOA_AFRL    (*(volatile uint32_t *)0x40020020)

// // USART2
// #define USART2_SR     (*(volatile uint32_t *)0x40004400)
// #define USART2_DR     (*(volatile uint32_t *)0x40004404)
// #define USART2_BRR    (*(volatile uint32_t *)0x40004408)
// #define USART2_CR1    (*(volatile uint32_t *)0x4000440C)

// void uart2_init(void) {
//     // Enable GPIOA and USART2 clocks
//     RCC_AHB1ENR |= (1 << 0);   // GPIOA
//     RCC_APB1ENR |= (1 << 17);  // USART2

//     // PA2 (TX) and PA3 (RX) as Alternate Function (AF7)
//     GPIOA_MODER &= ~(0xF << 4);     // Clear MODER2 and MODER3
//     GPIOA_MODER |=  (0xA << 4);     // Set to AF mode (10)
//     GPIOA_AFRL  &= ~((0xF << 8) | (0xF << 12));  // Clear AFRL2 & AFRL3
//     GPIOA_AFRL  |=  ((0x7 << 8) | (0x7 << 12));  // AF7 for USART2

//     // Baud rate (assuming 16 MHz clock, 9600 baud)
//     USART2_BRR = 0x683;

//     // 8-bit, no parity, 1 stop, TE & RE, UE
//     USART2_CR1 = (1 << 3) | (1 << 2) | (1 << 13);
// }

// char uart2_read_char(void) {
//     while (!(USART2_SR & (1 << 5)));  // Wait until RXNE
//     return USART2_DR;
// }

// void uart2_write_char(char c) {
//     while (!(USART2_SR & (1 << 7)));    // Wait until TXE
//     USART2_DR = c;
// }

// int main(void) {
//     uart2_init();

//     while (1) {
        
//         uart2_write_char('A');         // Echo back
//     }
// }
