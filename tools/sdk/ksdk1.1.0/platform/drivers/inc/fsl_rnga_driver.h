/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_RNGA_DRIVER_H__
#define __FSL_RNGA_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_rnga_hal.h"
/*! 
 * @addtogroup rnga_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Table of base addresses for RNGA instances. */
extern const uint32_t g_rngaBaseAddr[];

/*! @brief Table to save RNGA IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_rngaIrqId[HW_RNG_INSTANCE_COUNT];

/*! 
 * @brief Data structure for the RNGA initialization
 *
 * This structure is used when initializing the RNGA by calling the the rnga_init function.
 * It contains all RNGA configurations.
 */
typedef struct _rnga_user_config
{
   bool isIntMasked; /*!< Mask the triggering of error interrupt */
   bool highAssuranceEnable; /*!< Enable notification of security violations */  
} rnga_user_config_t;


/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the RNGA.
 *
 * This function initializes the RNGA. When called, the RNGA
 * runs immediately according to the specifications in the configuration.
 *
 * @param instance, RNGA instance ID
 * @param config, pointer to initialize configuration structure
 * @return RNGA status
 */
rnga_status_t RNGA_DRV_Init(uint32_t instance, const rnga_user_config_t *config);


/*!
 * @brief Shuts down the RNGA.
 *
 * This function shuts down the RNGA.
 *
 * @param instance, RNGA instance ID
 */
void RNGA_DRV_Deinit(uint32_t instance);


/*!
 * @brief Sets the RNGA in normal mode or sleep mode.
 *
 * This function sets the RNGA in sleep mode or normal mode.
 *
 * @param instance, RNGA instance ID
 * @param mode, normal mode or sleep mode
 */
static inline void RNGA_DRV_SetMode(uint32_t instance, rnga_mode_t mode)
{
    RNGA_HAL_SetWorkModeCmd(g_rngaBaseAddr[instance], mode);
}


/*!
 * @brief Gets the RNGA working mode.
 *
 * This function gets the RNGA working mode.
 *
 * @param instance, RNGA instance ID
 * @return normal mode or sleep mode
 */
static inline rnga_mode_t RNGA_DRV_GetMode(uint32_t instance)
{
    return RNGA_HAL_GetWorkMode(g_rngaBaseAddr[instance]);
}


/*!
 * @brief Gets random data.
 *
 * This function gets random data from the RNGA.
 *
 * @param instance, RNGA instance ID
 * @param data, pointer address used to store random data
 * @return one random data
 */
static inline rnga_status_t RNGA_DRV_GetRandomData(uint32_t instance, uint32_t *data)
{
    return RNGA_HAL_GetRandomData(g_rngaBaseAddr[instance], data);
}


/*!
 * @brief Feeds the RNGA module.
 *
 * This function inputs an entropy value that the RNGA uses to seed its
 * pseudo-random algorithm.
 *
 * @param instance, RNGA instance ID
 * @param seed, input seed value
 */
static inline void RNGA_DRV_Seed(uint32_t instance, uint32_t seed)
{
    RNGA_HAL_WriteSeed(g_rngaBaseAddr[instance],seed);
}

/*!
 * @brief RNGA interrupt handler.
 *
 * This function handles the error interrupt caused by the RNGA underflow.
 *
 * @param instance, RNGA instance ID
 */
void RNGA_DRV_IRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_RNGA_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

