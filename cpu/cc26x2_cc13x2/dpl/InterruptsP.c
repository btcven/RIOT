#include "cpu.h"
#include "vectors_cortexm.h"
#include "InterruptsP.h"

#include <inc/hw_ints.h>

dpl_handlers_t _dpl_handlers;

#define DISPATCH(isr)                \
    void isr(void)                 \
    {                                \
        if (_dpl_handlers.isr) {  \
            _dpl_handlers.isr();  \
        }                            \
        else {                       \
            dummy_handler_default(); \
        }                            \
        cortexm_isr_end();           \
    }

void default_isr_handler(void) {
    cortexm_isr_end();
}

void dpl_register_handler(uint32_t ui32Interrupt, void (*handler)(void))
{
    switch (ui32Interrupt) {
        case INT_NMI_FAULT:
        case INT_HARD_FAULT:
        case INT_MEMMANAGE_FAULT:
        case INT_BUS_FAULT:
        case INT_USAGE_FAULT:
        case INT_SVCALL:
        case INT_DEBUG:
        case INT_PENDSV:
        case INT_AON_GPIO_EDGE:
        case INT_UART0_COMB:
        case INT_GPT0A:
        case INT_GPT0B:
        case INT_GPT1A:
        case INT_GPT1B:
        case INT_GPT2A:
        case INT_GPT2B:
        case INT_GPT3A:
        case INT_GPT3B:
        case INT_UART1_COMB:
            core_panic(PANIC_GENERAL_ERROR, "reserved interrupt");
            break;

        case INT_SYSTICK:
            _dpl_handlers.isr_systick = handler;
            break;

        case INT_I2C_IRQ:
            _dpl_handlers.isr_i2c = handler;
            break;

        case INT_RFC_CPE_1:
            _dpl_handlers.isr_rfc_cpe1 = handler;
            break;

        case INT_PKA_IRQ:
            _dpl_handlers.isr_pka = handler;
            break;

        case INT_AON_RTC_COMB:
            _dpl_handlers.isr_aon_rtc = handler;
            break;

        case INT_AUX_SWEV0:
            _dpl_handlers.isr_aux0_aon = handler;
            break;

        case INT_SSI0_COMB:
            _dpl_handlers.isr_ssi0 = handler;
            break;

        case INT_SSI1_COMB:
            _dpl_handlers.isr_ssi1 = handler;
            break;

        case INT_RFC_CPE_0:
            _dpl_handlers.isr_rfc_cpe0 = handler;
            break;

        case INT_RFC_HW_COMB:
            _dpl_handlers.isr_rfc_hw = handler;
            break;

        case INT_RFC_CMD_ACK:
            _dpl_handlers.isr_rfc_cmd_ack = handler;
            break;

        case INT_I2S_IRQ:
            _dpl_handlers.isr_i2s = handler;
            break;

        case INT_AUX_SWEV1:
            _dpl_handlers.isr_aux1_aon = handler;
            break;

        case INT_WDT_IRQ:
            _dpl_handlers.isr_watchdog = handler;
            break;

        case INT_CRYPTO_RESULT_AVAIL_IRQ:
            _dpl_handlers.isr_crypto_res = handler;
            break;

        case INT_DMA_DONE_COMB:
            _dpl_handlers.isr_dma = handler;
            break;

        case INT_DMA_ERR:
            _dpl_handlers.isr_dmaerr = handler;
            break;

        case INT_FLASH:
            _dpl_handlers.isr_flash = handler;
            break;

        case INT_SWEV0:
            _dpl_handlers.isr_se0 = handler;
            break;

        case INT_AUX_COMB:
            _dpl_handlers.isr_aux_ce = handler;
            break;

        case INT_AON_PROG0:
            _dpl_handlers.isr_aon_prog = handler;
            break;

        case INT_PROG0:
            _dpl_handlers.isr_dyn_prog = handler;
            break;

        case INT_AUX_COMPA:
            _dpl_handlers.isr_comp = handler;
            break;

        case INT_AUX_ADC_IRQ:
            _dpl_handlers.isr_adc = handler;
            break;

        case INT_TRNG_IRQ:
            _dpl_handlers.isr_trng = handler;
            break;

        case INT_OSC_COMB:
            _dpl_handlers.isr_osc = handler;
            break;

        case INT_AUX_TIMER2_EV0:
            _dpl_handlers.isr_aux_timer2 = handler;
            break;

        case INT_BATMON_COMB:
            _dpl_handlers.isr_batmon = handler;
            break;

        default:
            break;
    }
}

void dpl_unregister_handler(uint32_t ui32Interrupt)
{
    switch (ui32Interrupt) {
        case INT_NMI_FAULT:
        case INT_HARD_FAULT:
        case INT_MEMMANAGE_FAULT:
        case INT_BUS_FAULT:
        case INT_USAGE_FAULT:
        case INT_SVCALL:
        case INT_DEBUG:
        case INT_PENDSV:
        case INT_AON_GPIO_EDGE:
        case INT_UART0_COMB:
        case INT_GPT0A:
        case INT_GPT0B:
        case INT_GPT1A:
        case INT_GPT1B:
        case INT_GPT2A:
        case INT_GPT2B:
        case INT_GPT3A:
        case INT_GPT3B:
        case INT_UART1_COMB:
            core_panic(PANIC_GENERAL_ERROR, "reserved interrupt");
            break;

        case INT_SYSTICK:
            _dpl_handlers.isr_systick = default_isr_handler;
            break;

        case INT_I2C_IRQ:
            _dpl_handlers.isr_i2c = default_isr_handler;
            break;

        case INT_RFC_CPE_1:
            _dpl_handlers.isr_rfc_cpe1 = default_isr_handler;
            break;

        case INT_PKA_IRQ:
            _dpl_handlers.isr_pka = default_isr_handler;
            break;

        case INT_AON_RTC_COMB:
            _dpl_handlers.isr_aon_rtc = default_isr_handler;
            break;

        case INT_AUX_SWEV0:
            _dpl_handlers.isr_aux0_aon = default_isr_handler;
            break;

        case INT_SSI0_COMB:
            _dpl_handlers.isr_ssi0 = default_isr_handler;
            break;

        case INT_SSI1_COMB:
            _dpl_handlers.isr_ssi1 = default_isr_handler;
            break;

        case INT_RFC_CPE_0:
            _dpl_handlers.isr_rfc_cpe0 = default_isr_handler;
            break;

        case INT_RFC_HW_COMB:
            _dpl_handlers.isr_rfc_hw = default_isr_handler;
            break;

        case INT_RFC_CMD_ACK:
            _dpl_handlers.isr_rfc_cmd_ack = default_isr_handler;
            break;

        case INT_I2S_IRQ:
            _dpl_handlers.isr_i2s = default_isr_handler;
            break;

        case INT_AUX_SWEV1:
            _dpl_handlers.isr_aux1_aon = default_isr_handler;
            break;

        case INT_WDT_IRQ:
            _dpl_handlers.isr_watchdog = default_isr_handler;
            break;

        case INT_CRYPTO_RESULT_AVAIL_IRQ:
            _dpl_handlers.isr_crypto_res = default_isr_handler;
            break;

        case INT_DMA_DONE_COMB:
            _dpl_handlers.isr_dma = default_isr_handler;
            break;

        case INT_DMA_ERR:
            _dpl_handlers.isr_dmaerr = default_isr_handler;
            break;

        case INT_FLASH:
            _dpl_handlers.isr_flash = default_isr_handler;
            break;

        case INT_SWEV0:
            _dpl_handlers.isr_se0 = default_isr_handler;
            break;

        case INT_AUX_COMB:
            _dpl_handlers.isr_aux_ce = default_isr_handler;
            break;

        case INT_AON_PROG0:
            _dpl_handlers.isr_aon_prog = default_isr_handler;
            break;

        case INT_PROG0:
            _dpl_handlers.isr_dyn_prog = default_isr_handler;
            break;

        case INT_AUX_COMPA:
            _dpl_handlers.isr_comp = default_isr_handler;
            break;

        case INT_AUX_ADC_IRQ:
            _dpl_handlers.isr_adc = default_isr_handler;
            break;

        case INT_TRNG_IRQ:
            _dpl_handlers.isr_trng = default_isr_handler;
            break;

        case INT_OSC_COMB:
            _dpl_handlers.isr_osc = default_isr_handler;
            break;

        case INT_AUX_TIMER2_EV0:
            _dpl_handlers.isr_aux_timer2 = default_isr_handler;
            break;

        case INT_BATMON_COMB:
            _dpl_handlers.isr_batmon = default_isr_handler;
            break;

        default:
            break;
    }
}

DISPATCH(isr_systick)
DISPATCH(isr_i2c)
DISPATCH(isr_rfc_cpe1)
DISPATCH(isr_pka)
DISPATCH(isr_aon_rtc)
DISPATCH(isr_aux0_aon)
DISPATCH(isr_ssi0)
DISPATCH(isr_ssi1)
DISPATCH(isr_rfc_cpe0)
DISPATCH(isr_rfc_hw)
DISPATCH(isr_rfc_cmd_ack)
DISPATCH(isr_i2s)
DISPATCH(isr_aux1_aon)
DISPATCH(isr_watchdog)
DISPATCH(isr_crypto_res)
DISPATCH(isr_dma)
DISPATCH(isr_dmaerr)
DISPATCH(isr_flash)
DISPATCH(isr_se0)
DISPATCH(isr_aux_ce)
DISPATCH(isr_aon_prog)
DISPATCH(isr_dyn_prog)
DISPATCH(isr_comp)
DISPATCH(isr_adc)
DISPATCH(isr_trng)
#ifdef CPU_VARIANT_X2
DISPATCH(isr_osc)
DISPATCH(isr_aux_timer2)
DISPATCH(isr_batmon)
#endif /* CPU_VARIANT_X2 */
