/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics STM32F4-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_INVERTER
#define BOARD_NAME                  "NEPTUN_TTT_Resolver_panel"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F407xx

/*
 * IO pins assignments.
 */
#define GPIOA_CH_DIR                0U
#define GPIOA_CH_B                  1U
#define GPIOA_CURR_1                2U
#define GPIOA_CURR_2                3U
#define GPIOA_SPI1_CS               4U
#define GPIOA_SPI1_SCK              5U
#define GPIOA_SPI1_MISO             6U
#define GPIOA_SPI1_MOSI             7U
#define GPIOA_PIN8                  8U
#define GPIOA_TX1                   9U
#define GPIOA_RX1                   10U
#define GPIOA_PIN11                 11U
#define GPIOA_PIN12                 12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_CURR_3                0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_CH_NM                 5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                 10U
#define GPIOB_PIN11                 11U
#define GPIOB_SPI2_CS               12U
#define GPIOB_SPI2_SCK              13U
#define GPIOB_SPI2_MISO             14U
#define GPIOB_SPI2_MOSI             15U

#define GPIOC_NTC_U                 0U
#define GPIOC_NTC_V                 1U
#define GPIOC_NTC_W                 2U
#define GPIOC_MOTOR_PTC             3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_U_L                   6U
#define GPIOC_V_L                   7U
#define GPIOC_W_L                   8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_LOT                   8U
#define GPIOD_DOS                   9U
#define GPIOD_SD_B                  10U
#define GPIOD_PIN11                 11U
#define GPIOD_U_H                   12U
#define GPIOD_V_H                   13U
#define GPIOD_W_H                   14U
#define GPIOD_LED6                  15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_CH_A                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_RDVEL                 9U
#define GPIOE_SPI2_SAMPLE           10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_CH_DIR                PAL_LINE(GPIOA, 0U)
#define LINE_CH_B                  PAL_LINE(GPIOA, 1U)
#define LINE_CURR_1                PAL_LINE(GPIOA, 2U)
#define LINE_CURR_2                PAL_LINE(GPIOA, 3U)
#define LINE_SPI1_CS               PAL_LINE(GPIOA, 4U)
#define LINE_SPI1_SCK              PAL_LINE(GPIOA, 5U)
#define LINE_SPI1_MISO             PAL_LINE(GPIOA, 6U)
#define LINE_SPI1_MOSI             PAL_LINE(GPIOA, 7U)
#define LINE_TX1                   pAL_LINE(GPIOA, 9U)
#define LINE_RX1                   PAL_LINE(GPIOA, 10U)
#define LINE_SWDIO                 PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                 PAL_LINE(GPIOA, 14U)

#define LINE_CURR_3                 PAL_LINE(GPIOB, 0U)
#define LINE_CH_NM                  PAL_LINE(GPIOB, 5U)
#define LINE_SPI2_CS                PAL_LINE(GPIOB, 12U)
#define LINE_SPI2_SCK               PAL_LINE(GPIOB, 13U)
#define LINE_SPI2_MISO              PAL_LINE(GPIOB, 14U)
#define LINE_SPI2_MOSI              PAL_LINE(GPIOB, 15U)

#define LINE_NTC_U                  PAL_LINE(GPIOC, 0U)
#define LINE_NTC_V                  PAL_LINE(GPIOC, 1U)
#define LINE_NTC_W                  PAL_LINE(GPIOC, 2U)
#define LINE_MOTOR_PTC              PAL_LINE(GPIOC, 3U)
#define LINE_U_L                    PAL_LINE(GPIOC, 6U)
#define LINE_V_L                    PAL_LINE(GPIOC, 7U)
#define LINE_W_L                    PAL_LINE(GPIOC, 8U)

#define LINE_LOT                    PAL_LINE(GPIOD, 8U)
#define LINE_DOS                    PAL_LINE(GPIOD, 9U)
#define LINE_SD_B                   PAL_LINE(GPIOD, 10U)
#define LINE_U_H                    PAL_LINE(GPIOD, 12U)
#define LINE_V_H                    PAL_LINE(GPIOD, 13U)
#define LINE_W_H                    PAL_LINE(GPIOD, 14U)
#define LINE_LED6                   PAL_LINE(GPIOD, 15U)

#define LINE_CH_A                   PAL_LINE(GPIOE, 5U)
#define LINE_RDVEL                  PAL_LINE(GPIOE, 9U)
#define LINE_SPI2_SAMPLE            PAL_LINE(GPIOE, 10U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)


/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 * All input with pull-up except:
 * PA0  - CH_DIR                    (input floating).
 * PA1  - CH_B                      (alternate 2).
 * PA2  - CURR_1                    (analog).
 * PA3  - CURR_2                    (analog).
 * PA4  - SPI1_CS                   (output pushpull).
 * PA5  - SPI1_SCK                  (alternate 5).
 * PA6  - SPI1_MISO                 (alternate 5).
 * PA7  - SPI1_MOSI                 (alternate 5).
 * PA9  - TX1                       (alternate 7).
 * PA10 - RX1                       (alternate 7).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_CH_DIR)        |  \
                                     PIN_MODE_ALTERNATE(GPIOA_CH_B)      |  \
                                     PIN_MODE_ANALOG(GPIOA_CURR_1)       |  \
                                     PIN_MODE_ANALOG(GPIOA_CURR_2)       |  \
                                     PIN_MODE_OUTPUT(GPIOA_SPI1_CS)      |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_SCK)  |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MOSI) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_TX1)       |  \
                                     PIN_MODE_ALTERNATE(GPIOA_RX1)       |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO)     |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_CH_DIR)    |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_CS)   |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO)     |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_CH_DIR)       |  \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_CS)      |  \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_SCK)     |  \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MISO)    |  \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MOSI)    |  \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO)        |  \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_CH_DIR)    |  \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO)     |  \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_CH_DIR)          |  \
                                     PIN_ODR_HIGH(GPIOA_SWDIO)           |  \
                                     PIN_ODR_HIGH(GPIOA_SWCLK))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_CH_B, 2)          |  \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 5)      |  \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5)     |  \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 5))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_TX1, 7)           |  \
                                     PIN_AFIO_AF(GPIOA_RX1, 7)           |  \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0)         |  \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0))

/*
 * GPIOB setup:
 * All input with pull-up except:
 * PB0  - CURR_3                    (analog).
 * PB5  - CH_NM                     (alternate 2).
 * PB12 - SPI2_CS                   (output pushpull maximum).
 * PB13 - SPI2_SCK                  (alternate 5).
 * PB14 - SPI2_MISO                 (alternate 5).
 * PB15 - SPI2_MOSI                 (alternate 5).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_CH_NM)    |  \
                                     PIN_MODE_OUTPUT(GPIOB_SPI2_CS)     |  \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI2_SCK) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI2_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI2_MOSI))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_SPI2_CS))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_SPI2_CS)     |  \
                                     PIN_OSPEED_HIGH(GPIOB_SPI2_SCK)    |  \
                                     PIN_OSPEED_HIGH(GPIOB_SPI2_MISO)   |  \
                                     PIN_OSPEED_HIGH(GPIOB_SPI2_MOSI))
#define VAL_GPIOB_PUPDR             0xFFFFFFFF
#define VAL_GPIOB_ODR               0xFFFFFFFF
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_CH_NM, 2))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_SPI2_SCK, 5)     |  \
                                     PIN_AFIO_AF(GPIOB_SPI2_MISO, 5)    |  \
                                     PIN_AFIO_AF(GPIOB_SPI2_MOSI, 5))

/*
 * GPIOC setup:
 * All input with pull-up except:
 * PC0  - NTC_U                    (analog).
 * PC1  - NTC_V                    (analog).
 * PC2  - NTC_W                    (analog).
 * PC3  - MOTOR_PTC                (analog).
 * PC6  - GPIOC_U_L                (alternate 3).
 * PC7  - GPIOC_V_L                (alternate 3).
 * PC8  - GPIOC_W_L                (alternate 3).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_U_L)          | \
                                     PIN_MODE_ALTERNATE(GPIOC_V_L)          | \
                                     PIN_MODE_ALTERNATE(GPIOC_W_L))
#define VAL_GPIOC_OTYPER            0x00000000
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_U_L)             | \
                                     PIN_OSPEED_HIGH(GPIOC_V_L)             | \
                                     PIN_OSPEED_HIGH(GPIOC_W_L))
#define VAL_GPIOC_PUPDR             0xFFFFFFFF
#define VAL_GPIOC_ODR               0xFFFFFFFF
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_U_L, 3)              | \
                                     PIN_AFIO_AF(GPIOC_V_L, 3))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_W_L, 3))


/*
 * GPIOD setup:
 * All input with pull-up except:
 * PD8  - LOT                       (input floating).
 * PD9  - DOS                       (input floating).
 * PD10 - SD_B                      (output pushpull).
 * PD12 - GPIOD_U_H                 (alternate 2).
 * PD13 - GPIOD_V_H                 (alternate 2).
 * PD14 - GPIOD_W_H                 (alternate 2).
 * PD15 - GPIOD_LED6                (output pushpull).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_U_H)          | \
                                     PIN_MODE_ALTERNATE(GPIOD_V_H)          | \
                                     PIN_MODE_ALTERNATE(GPIOD_W_H)          | \
                                     PIN_MODE_OUTPUT(GPIOD_LED6))

#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_LED6))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_U_H)             | \
                                     PIN_OSPEED_HIGH(GPIOD_V_H)             | \
                                     PIN_OSPEED_HIGH(GPIOD_W_H)             | \
                                     PIN_OSPEED_HIGH(GPIOD_LED6))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_LED6))
#define VAL_GPIOD_ODR               (PIN_ODR_LOW(GPIOD_LED6))
#define VAL_GPIOD_AFRL              0x00000000
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_U_H, 2)             | \
                                     PIN_AFIO_AF(GPIOD_V_H, 2)             | \
                                     PIN_AFIO_AF(GPIOD_W_H, 2))

/*
 * GPIOE setup:
 * All input with pull-up except:
 * PE5  - CH_A                      (alternate 3).
 * PE9  - RDVEL                     (alternate 3).
 * PE10 - SPI2_SAMPLE               (output pushpull maximum).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_CH_A)           | \
                                     PIN_MODE_OUTPUT(GPIOE_SPI2_SAMPLE))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_SPI2_SAMPLE))
#define VAL_GPIOE_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOE_PUPDR             0xFFFFFFFF
#define VAL_GPIOE_ODR               0xFFFFFFFF
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_CH_A, 3))
#define VAL_GPIOE_AFRH              0x00000000

/*
 * GPIOF setup:
 * All input with pull-up except:
 */
#define VAL_GPIOF_MODER             0x00000000
#define VAL_GPIOF_OTYPER            0x00000000
#define VAL_GPIOF_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOF_PUPDR             0xFFFFFFFF
#define VAL_GPIOF_ODR               0xFFFFFFFF
#define VAL_GPIOF_AFRL              0x00000000
#define VAL_GPIOF_AFRH              0x00000000

/*
 * GPIOG setup:
 * All input with pull-up except:
 */
#define VAL_GPIOG_MODER             0x00000000
#define VAL_GPIOG_OTYPER            0x00000000
#define VAL_GPIOG_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOG_PUPDR             0xFFFFFFFF
#define VAL_GPIOG_ODR               0xFFFFFFFF
#define VAL_GPIOG_AFRL              0x00000000
#define VAL_GPIOG_AFRH              0x00000000

/*
 * Port H setup.
 * All input with pull-up except:
 * PH0 - OSC_IN                     (input floating).
 * PH1 - OSC_OUT                    (input floating).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN)       | \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN)   | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN)      | \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN)   | \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN)         | \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT))
#define VAL_GPIOH_AFRL              0x00000000
#define VAL_GPIOH_AFRH              0x00000000

/*
 * GPIOI setup:
 * All input with pull-up except:
 */
#define VAL_GPIOI_MODER             0x00000000
#define VAL_GPIOI_OTYPER            0x00000000
#define VAL_GPIOI_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOI_PUPDR             0xFFFFFFFF
#define VAL_GPIOI_ODR               0xFFFFFFFF
#define VAL_GPIOI_AFRL              0x00000000
#define VAL_GPIOI_AFRH              0x00000000


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
