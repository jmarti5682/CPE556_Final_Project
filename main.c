#include "stm32u585xx.h"
#include <stdio.h>

void GPIO_Init(void)
{
	//enable the clock to GPIO H
	RCC -> AHB2ENR1 |= RCC_AHB2ENR1_GPIOHEN;

// Set PH4 and PH5 to Alternate Function mode (MODER = 10)
GPIOH->MODER &= ~((3 << (4*2)) | (3 << (5*2)));
GPIOH->MODER |=  ((2 << (4*2)) | (2 << (5*2)));

// Set alternate function AF4 for I2C (AFR[0] for pin < 8)
GPIOH->AFR[0] &= ~((0xF << (4*4)) | (0xF << (5*4)));
GPIOH->AFR[0] |=  ((4 << (4*4)) | (4 << (5*4)));

// Set output type to open-drain
GPIOH->OTYPER |= (1 << 4) | (1 << 5);

// Enable pull-up resistors (optional if external resistors are already present)
GPIOH->PUPDR &= ~((3 << (4*2)) | (3 << (5*2)));
GPIOH->PUPDR |=  ((1 << (4*2)) | (1 << (5*2)));
	
	
	
}


void delay(volatile uint32_t time) {
    while (time--) {
        for (volatile uint32_t i = 0; i < 1000; i++);
    }
}

int main(void) {
    // 1. Enable GPIOA clock
    RCC->AHB2ENR1 |= RCC_AHB2ENR1_GPIOAEN;

    // 2. Set PA5 as General Purpose Output (MODER = 01)
    GPIOA->MODER &= ~(3U << (5 * 2));   // Clear bits
    GPIOA->MODER |=  (1U << (5 * 2));   // Set to output mode

    // 3. Set output type to push-pull (default)
    GPIOA->OTYPER &= ~(1U << 5);

    // 4. Set speed to medium or high (optional)
    GPIOA->OSPEEDR |= (1U << (5 * 2));

    // 5. No pull-up, no pull-down
    GPIOA->PUPDR &= ~(3U << (5 * 2));

    while (1) {
        GPIOA->ODR ^= (1U << 5); // Toggle PA5
        delay(1000);
    }
}