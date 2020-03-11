#ifndef DPL_INTERRUPTSP_H
#define DPL_INTERRUPTSP_H

typedef struct {
    void (*isr_systick)(void);
    void (*isr_i2c)(void);
    void (*isr_rfc_cpe1)(void);
    void (*isr_pka)(void);
    void (*isr_aon_rtc)(void);
    void (*isr_aux0_aon)(void);
    void (*isr_ssi0)(void);
    void (*isr_ssi1)(void);
    void (*isr_rfc_cpe0)(void);
    void (*isr_rfc_hw)(void);
    void (*isr_rfc_cmd_ack)(void);
    void (*isr_i2s)(void);
    void (*isr_aux1_aon)(void);
    void (*isr_watchdog)(void);
    void (*isr_crypto_res)(void);
    void (*isr_dma)(void);
    void (*isr_dmaerr)(void);
    void (*isr_flash)(void);
    void (*isr_se0)(void);
    void (*isr_aux_ce)(void);
    void (*isr_aon_prog)(void);
    void (*isr_dyn_prog)(void);
    void (*isr_comp)(void);
    void (*isr_adc)(void);
    void (*isr_trng)(void);
#ifdef CPU_VARIANT_X2
    void (*isr_osc)(void);
    void (*isr_aux_timer2)(void);
    void (*isr_batmon)(void);
#endif // CPU_VARIANT_X2
} dpl_handlers_t;

void dpl_register_handler(uint32_t ui32Interrupt, void (*handler)(void));
void dpl_unregister_handler(uint32_t ui32Interrupt);

#endif /* DPL_INTERRUPTSP_H */
