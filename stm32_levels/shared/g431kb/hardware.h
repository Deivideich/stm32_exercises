#ifndef HARDWARE_H
#define HARDWARE_H 

#include <stdint.h>

/* ========================================================================== */
/* 1. ABSOLUTE BASE ADDRESSES                                                 */
/* ========================================================================== */
#define PERIPH_BASE         0x40000000UL
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000UL) /* 0x40020000 */
#define AHB2PERIPH_BASE     (PERIPH_BASE + 0x08000000UL) /* 0x48000000 */

#define RCC_BASE            (AHB1PERIPH_BASE + 0x1000UL)  /* 0x40021000 */
#define GPIOB_BASE          (AHB2PERIPH_BASE + 0x0400UL)  /* 0x48000400 */

/* ========================================================================== */
/* 2. REGISTER MAP STRUCTURES                                                 */
/* ========================================================================== */

/* Clean structure for the Reset and Clock Control (RCC) block */
typedef struct {
    volatile uint32_t CR;          /* 0x00 */
    volatile uint32_t ICSCR;       /* 0x04 */
    volatile uint32_t CFGR;        /* 0x08 */
    volatile uint32_t PLLCFGR;     /* 0x0C */
    volatile uint32_t CIER;        /* 0x10 */
    volatile uint32_t CIFR;        /* 0x14 */
    volatile uint32_t CICR;        /* 0x18 */
    volatile uint32_t CRRCR;       /* 0x1C */
    volatile uint32_t AHB1RSTR;    /* 0x20 */
    volatile uint32_t AHB2RSTR;    /* 0x24 */
    volatile uint32_t AHB3RSTR;    /* 0x28 */
    volatile uint32_t RESERVED0;   /* 0x2C */
    volatile uint32_t APB1RSTR1;   /* 0x30 */
    volatile uint32_t APB1RSTR2;   /* 0x34 */
    volatile uint32_t APB2RSTR;    /* 0x38 */
    volatile uint32_t RESERVED1;   /* 0x3C */
    volatile uint32_t AHB1ENR;     /* 0x40 */
    volatile uint32_t RESERVED2;   /* 0x44 */
    volatile uint32_t RESERVED3;   /* 0x48 */
    volatile uint32_t AHB2ENR;     /* 0x4C <-- FORCED TO OFFSET 0x4C (19 * 4) */
} RCC_TypeDef;

/* Structure for the GPIO Port */
typedef struct {
    volatile uint32_t MODER;   /* 0x00 */
    volatile uint32_t OTYPER;  /* 0x04 */
    volatile uint32_t OSPEEDR; /* 0x08 */
    volatile uint32_t PUPDR;   /* 0x0C */
    volatile uint32_t IDR;     /* 0x10 */
    volatile uint32_t ODR;     /* 0x14 */
    volatile uint32_t BSRR;    /* 0x18 */
    volatile uint32_t LCKR;    /* 0x1C */
    volatile uint32_t AFRL;    /* 0x20 */
    volatile uint32_t AFRH;    /* 0x24 */
    volatile uint32_t BRR;     /* 0x28 */
} GPIO_TypeDef;

/* ========================================================================== */
/* 3. MAGIC POINTER INSTANTIATION                                             */
/* ========================================================================== */
#define RCC     ((RCC_TypeDef *)RCC_BASE)
#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)

#endif /* HARDWARE_H */
