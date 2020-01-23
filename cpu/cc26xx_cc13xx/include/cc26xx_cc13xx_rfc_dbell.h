/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc26xx_cc13xx_definitions
 * @{
 *
 * @file
 * @brief           CC26xx/CC13xx RFC_DBELL register definitions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26XX_CC13XX_RFC_DBELL_H
#define CC26XX_CC13XX_RFC_DBELL_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * RF Core Doorbell register
 */
typedef struct {
    reg32_t CMDR; /**< doorbell command register */
    reg32_t CMDSTA; /**< doorbell command status register */
    reg32_t RFHWIFG; /**< interrupt flags from rf hardware modules */
    reg32_t RFHWIEN; /**< interrupt enable for rf hardware modules */
    reg32_t RFCPEIFG; /**< interrupt flags for command and packet engine generated interrupts */
    reg32_t RFCPEIEN; /**< interrupt enable for command and packet engine generated interrupts */
    reg32_t RFCPEISL; /**< interrupt vector selection for command and packet engine generated interrupts */
    reg32_t RFACKIFG; /**< doorbell command acknowledgement interrupt flag */
    reg32_t SYSGPOCTL; /**< rf core general purpose output control */
} rfc_dbell_regs_t;

/**
 * @name RFC_DBELL registers fields values
 *
 * @{
 */
#define CMDR_DIR_CMD(id) (((id) << 16) | 1)
#define CMDR_DIR_CMD_2BYTE(id, par) (((id) << 16) | ((par) & 0xFFFC) | 1)

#define CMDSTA_RESULT_mask                 0x000000FF
#define CMDSTA_RESULT_PENDING              0x00
#define CMDSTA_RESULT_DONE                 0x01

#define RFHWIFG_RATCH7                     0x00080000
#define RFHWIFG_RATCH6                     0x00040000
#define RFHWIFG_RATCH5                     0x00020000
#define RFHWIFG_RATCH4                     0x00010000
#define RFHWIFG_RATCH3                     0x00008000
#define RFHWIFG_RATCH2                     0x00004000
#define RFHWIFG_RATCH1                     0x00002000
#define RFHWIFG_RATCH0                     0x00001000
#define RFHWIFG_RFESOFT2                   0x00000800
#define RFHWIFG_RFESOFT1                   0x00000400
#define RFHWIFG_RFESOFT0                   0x00000200
#define RFHWIFG_RFEDONE                    0x00000100
#define RFHWIFG_TRCTK                      0x00000040
#define RFHWIFG_MDMSOFT                    0x00000020
#define RFHWIFG_MDMOUT                     0x00000010
#define RFHWIFG_MDMIN                      0x00000008
#define RFHWIFG_MDMDONE                    0x00000004
#define RFHWIFG_FSCA                       0x00000002

#define RFHWIEN_RATCH7                     0x00080000
#define RFHWIEN_RATCH6                     0x00040000
#define RFHWIEN_RATCH5                     0x00020000
#define RFHWIEN_RATCH4                     0x00010000
#define RFHWIEN_RATCH3                     0x00008000
#define RFHWIEN_RATCH2                     0x00004000
#define RFHWIEN_RATCH1                     0x00002000
#define RFHWIEN_RATCH0                     0x00001000
#define RFHWIEN_RFESOFT2                   0x00000800
#define RFHWIEN_RFESOFT1                   0x00000400
#define RFHWIEN_RFESOFT0                   0x00000200
#define RFHWIEN_RFEDONE                    0x00000100
#define RFHWIEN_TRCTK                      0x00000040
#define RFHWIEN_MDMSOFT                    0x00000020
#define RFHWIEN_MDMOUT                     0x00000010
#define RFHWIEN_MDMIN                      0x00000008
#define RFHWIEN_MDMDONE                    0x00000004
#define RFHWIEN_FSCA                       0x00000002

#define RFCPEIFG_INTERNAL_ERROR            0x80000000
#define RFCPEIFG_BOOT_DONE                 0x40000000
#define RFCPEIFG_MODULES_UNLOCKED          0x20000000
#define RFCPEIFG_SYNTH_NO_LOCK             0x10000000
#define RFCPEIFG_IRQ27                     0x08000000
#define RFCPEIFG_RX_ABORTED                0x04000000
#define RFCPEIFG_RX_N_DATA_WRITTEN         0x02000000
#define RFCPEIFG_RX_DATA_WRITTEN           0x01000000
#define RFCPEIFG_RX_ENTRY_DONE             0x00800000
#define RFCPEIFG_RX_BUF_FULL               0x00400000
#define RFCPEIFG_RX_CTRL_ACK               0x00200000
#define RFCPEIFG_RX_CTRL                   0x00100000
#define RFCPEIFG_RX_EMPTY                  0x00080000
#define RFCPEIFG_RX_IGNORED                0x00040000
#define RFCPEIFG_RX_NOK                    0x00020000
#define RFCPEIFG_RX_OK                     0x00010000
#define RFCPEIFG_IRQ15                     0x00008000
#define RFCPEIFG_IRQ14                     0x00004000
#define RFCPEIFG_IRQ13                     0x00002000
#define RFCPEIFG_IRQ12                     0x00001000
#define RFCPEIFG_TX_BUFFER_CHANGED         0x00000800
#define RFCPEIFG_TX_ENTRY_DONE             0x00000400
#define RFCPEIFG_TX_RETRANS                0x00000200
#define RFCPEIFG_TX_CTRL_ACK_ACK           0x00000100
#define RFCPEIFG_TX_CTRL_ACK               0x00000080
#define RFCPEIFG_TX_CTRL                   0x00000040
#define RFCPEIFG_TX_ACK                    0x00000020
#define RFCPEIFG_TX_DONE                   0x00000010
#define RFCPEIFG_LAST_FG_COMMAND_DONE      0x00000008
#define RFCPEIFG_FG_COMMAND_DONE           0x00000004
#define RFCPEIFG_LAST_COMMAND_DONE         0x00000002
#define RFCPEIFG_COMMAND_DONE              0x00000001

#define RFCPEIEN_INTERNAL_ERROR            0x80000000
#define RFCPEIEN_BOOT_DONE                 0x40000000
#define RFCPEIEN_MODULES_UNLOCKED          0x20000000
#define RFCPEIEN_SYNTH_NO_LOCK             0x10000000
#define RFCPEIEN_IRQ27                     0x08000000
#define RFCPEIEN_RX_ABORTED                0x04000000
#define RFCPEIEN_RX_N_DATA_WRITTEN         0x02000000
#define RFCPEIEN_RX_DATA_WRITTEN           0x01000000
#define RFCPEIEN_RX_ENTRY_DONE             0x00800000
#define RFCPEIEN_RX_BUF_FULL               0x00400000
#define RFCPEIEN_RX_CTRL_ACK               0x00200000
#define RFCPEIEN_RX_CTRL                   0x00100000
#define RFCPEIEN_RX_EMPTY                  0x00080000
#define RFCPEIEN_RX_IGNORED                0x00040000
#define RFCPEIEN_RX_NOK                    0x00020000
#define RFCPEIEN_RX_OK                     0x00010000
#define RFCPEIEN_IRQ15                     0x00008000
#define RFCPEIEN_IRQ14                     0x00004000
#define RFCPEIEN_IRQ13                     0x00002000
#define RFCPEIEN_IRQ12                     0x00001000
#define RFCPEIEN_TX_BUFFER_CHANGED         0x00000800
#define RFCPEIEN_TX_ENTRY_DONE             0x00000400
#define RFCPEIEN_TX_RETRANS                0x00000200
#define RFCPEIEN_TX_CTRL_ACK_ACK           0x00000100
#define RFCPEIEN_TX_CTRL_ACK               0x00000080
#define RFCPEIEN_TX_CTRL                   0x00000040
#define RFCPEIEN_TX_ACK                    0x00000020
#define RFCPEIEN_TX_DONE                   0x00000010
#define RFCPEIEN_LAST_FG_COMMAND_DONE      0x00000008
#define RFCPEIEN_FG_COMMAND_DONE           0x00000004
#define RFCPEIEN_LAST_COMMAND_DONE         0x00000002
#define RFCPEIEN_COMMAND_DONE              0x00000001

#define RFCPEISL_INTERNAL_ERROR            0x80000000
#define RFCPEISL_INTERNAL_ERROR_CPE1       0x80000000
#define RFCPEISL_INTERNAL_ERROR_CPE0       0x00000000
#define RFCPEISL_BOOT_DONE                 0x40000000
#define RFCPEISL_BOOT_DONE_CPE1            0x40000000
#define RFCPEISL_BOOT_DONE_CPE0            0x00000000
#define RFCPEISL_MODULES_UNLOCKED          0x20000000
#define RFCPEISL_MODULES_UNLOCKED_CPE1     0x20000000
#define RFCPEISL_MODULES_UNLOCKED_CPE0     0x00000000
#define RFCPEISL_SYNTH_NO_LOCK             0x10000000
#define RFCPEISL_SYNTH_NO_LOCK_CPE1        0x10000000
#define RFCPEISL_SYNTH_NO_LOCK_CPE0        0x00000000
#define RFCPEISL_IRQ27                     0x08000000
#define RFCPEISL_IRQ27_CPE1                0x08000000
#define RFCPEISL_IRQ27_CPE0                0x00000000
#define RFCPEISL_RX_ABORTED                0x04000000
#define RFCPEISL_RX_ABORTED_CPE1           0x04000000
#define RFCPEISL_RX_ABORTED_CPE0           0x00000000
#define RFCPEISL_RX_N_DATA_WRITTEN         0x02000000
#define RFCPEISL_RX_N_DATA_WRITTEN_CPE1    0x02000000
#define RFCPEISL_RX_N_DATA_WRITTEN_CPE0    0x00000000
#define RFCPEISL_RX_DATA_WRITTEN           0x01000000
#define RFCPEISL_RX_DATA_WRITTEN_CPE1      0x01000000
#define RFCPEISL_RX_DATA_WRITTEN_CPE0      0x00000000
#define RFCPEISL_RX_ENTRY_DONE             0x00800000
#define RFCPEISL_RX_ENTRY_DONE_CPE1        0x00800000
#define RFCPEISL_RX_ENTRY_DONE_CPE0        0x00000000
#define RFCPEISL_RX_BUF_FULL               0x00400000
#define RFCPEISL_RX_BUF_FULL_CPE1          0x00400000
#define RFCPEISL_RX_BUF_FULL_CPE0          0x00000000
#define RFCPEISL_RX_CTRL_ACK               0x00200000
#define RFCPEISL_RX_CTRL_ACK_CPE1          0x00200000
#define RFCPEISL_RX_CTRL_ACK_CPE0          0x00000000
#define RFCPEISL_RX_CTRL                   0x00100000
#define RFCPEISL_RX_CTRL_CPE1              0x00100000
#define RFCPEISL_RX_CTRL_CPE0              0x00000000
#define RFCPEISL_RX_EMPTY                  0x00080000
#define RFCPEISL_RX_EMPTY_CPE1             0x00080000
#define RFCPEISL_RX_EMPTY_CPE0             0x00000000
#define RFCPEISL_RX_IGNORED                0x00040000
#define RFCPEISL_RX_IGNORED_CPE1           0x00040000
#define RFCPEISL_RX_IGNORED_CPE0           0x00000000
#define RFCPEISL_RX_NOK                    0x00020000
#define RFCPEISL_RX_NOK_CPE1               0x00020000
#define RFCPEISL_RX_NOK_CPE0               0x00000000
#define RFCPEISL_RX_OK                     0x00010000
#define RFCPEISL_RX_OK_CPE1                0x00010000
#define RFCPEISL_RX_OK_CPE0                0x00000000
#define RFCPEISL_IRQ15                     0x00008000
#define RFCPEISL_IRQ15_CPE1                0x00008000
#define RFCPEISL_IRQ15_CPE0                0x00000000
#define RFCPEISL_IRQ14                     0x00004000
#define RFCPEISL_IRQ14_CPE1                0x00004000
#define RFCPEISL_IRQ14_CPE0                0x00000000
#define RFCPEISL_IRQ13                     0x00002000
#define RFCPEISL_IRQ13_CPE1                0x00002000
#define RFCPEISL_IRQ13_CPE0                0x00000000
#define RFCPEISL_IRQ12                     0x00001000
#define RFCPEISL_IRQ12_CPE1                0x00001000
#define RFCPEISL_IRQ12_CPE0                0x00000000
#define RFCPEISL_TX_BUFFER_CHANGED         0x00000800
#define RFCPEISL_TX_BUFFER_CHANGED_CPE1    0x00000800
#define RFCPEISL_TX_BUFFER_CHANGED_CPE0    0x00000000
#define RFCPEISL_TX_ENTRY_DONE             0x00000400
#define RFCPEISL_TX_ENTRY_DONE_CPE1        0x00000400
#define RFCPEISL_TX_ENTRY_DONE_CPE0        0x00000000
#define RFCPEISL_TX_RETRANS                0x00000200
#define RFCPEISL_TX_RETRANS_CPE1           0x00000200
#define RFCPEISL_TX_RETRANS_CPE0           0x00000000
#define RFCPEISL_TX_CTRL_ACK_ACK           0x00000100
#define RFCPEISL_TX_CTRL_ACK_ACK_CPE1      0x00000100
#define RFCPEISL_TX_CTRL_ACK_ACK_CPE0      0x00000000
#define RFCPEISL_TX_CTRL_ACK               0x00000080
#define RFCPEISL_TX_CTRL_ACK_CPE1          0x00000080
#define RFCPEISL_TX_CTRL_ACK_CPE0          0x00000000
#define RFCPEISL_TX_CTRL                   0x00000040
#define RFCPEISL_TX_CTRL_CPE1              0x00000040
#define RFCPEISL_TX_CTRL_CPE0              0x00000000
#define RFCPEISL_TX_ACK                    0x00000020
#define RFCPEISL_TX_ACK_CPE1               0x00000020
#define RFCPEISL_TX_ACK_CPE0               0x00000000
#define RFCPEISL_TX_DONE                   0x00000010
#define RFCPEISL_TX_DONE_CPE1              0x00000010
#define RFCPEISL_TX_DONE_CPE0              0x00000000
#define RFCPEISL_LAST_FG_COMMAND_DONE      0x00000008
#define RFCPEISL_LAST_FG_COMMAND_DONE_CPE1 0x00000008
#define RFCPEISL_LAST_FG_COMMAND_DONE_CPE0 0x00000000
#define RFCPEISL_FG_COMMAND_DONE           0x00000004
#define RFCPEISL_FG_COMMAND_DONE_CPE1      0x00000004
#define RFCPEISL_FG_COMMAND_DONE_CPE0      0x00000000
#define RFCPEISL_LAST_COMMAND_DONE         0x00000002
#define RFCPEISL_LAST_COMMAND_DONE_CPE1    0x00000002
#define RFCPEISL_LAST_COMMAND_DONE_CPE0    0x00000000
#define RFCPEISL_COMMAND_DONE              0x00000001
#define RFCPEISL_COMMAND_DONE_CPE1         0x00000001
#define RFCPEISL_COMMAND_DONE_CPE0         0x00000000

#define RFACKIFG_ACKFLAG                   0x00000001

#define SYSGPOCTL_GPOCTL3_M                0x0000F000
#define SYSGPOCTL_GPOCTL3_RATGPO3          0x0000F000
#define SYSGPOCTL_GPOCTL3_RATGPO2          0x0000E000
#define SYSGPOCTL_GPOCTL3_RATGPO1          0x0000D000
#define SYSGPOCTL_GPOCTL3_RATGPO0          0x0000C000
#define SYSGPOCTL_GPOCTL3_RFEGPO3          0x0000B000
#define SYSGPOCTL_GPOCTL3_RFEGPO2          0x0000A000
#define SYSGPOCTL_GPOCTL3_RFEGPO1          0x00009000
#define SYSGPOCTL_GPOCTL3_RFEGPO0          0x00008000
#define SYSGPOCTL_GPOCTL3_MCEGPO3          0x00007000
#define SYSGPOCTL_GPOCTL3_MCEGPO2          0x00006000
#define SYSGPOCTL_GPOCTL3_MCEGPO1          0x00005000
#define SYSGPOCTL_GPOCTL3_MCEGPO0          0x00004000
#define SYSGPOCTL_GPOCTL3_CPEGPO3          0x00003000
#define SYSGPOCTL_GPOCTL3_CPEGPO2          0x00002000
#define SYSGPOCTL_GPOCTL3_CPEGPO1          0x00001000
#define SYSGPOCTL_GPOCTL3_CPEGPO0          0x00000000

#define SYSGPOCTL_GPOCTL2_M                0x00000F00
#define SYSGPOCTL_GPOCTL2_RATGPO3          0x00000F00
#define SYSGPOCTL_GPOCTL2_RATGPO2          0x00000E00
#define SYSGPOCTL_GPOCTL2_RATGPO1          0x00000D00
#define SYSGPOCTL_GPOCTL2_RATGPO0          0x00000C00
#define SYSGPOCTL_GPOCTL2_RFEGPO3          0x00000B00
#define SYSGPOCTL_GPOCTL2_RFEGPO2          0x00000A00
#define SYSGPOCTL_GPOCTL2_RFEGPO1          0x00000900
#define SYSGPOCTL_GPOCTL2_RFEGPO0          0x00000800
#define SYSGPOCTL_GPOCTL2_MCEGPO3          0x00000700
#define SYSGPOCTL_GPOCTL2_MCEGPO2          0x00000600
#define SYSGPOCTL_GPOCTL2_MCEGPO1          0x00000500
#define SYSGPOCTL_GPOCTL2_MCEGPO0          0x00000400
#define SYSGPOCTL_GPOCTL2_CPEGPO3          0x00000300
#define SYSGPOCTL_GPOCTL2_CPEGPO2          0x00000200
#define SYSGPOCTL_GPOCTL2_CPEGPO1          0x00000100
#define SYSGPOCTL_GPOCTL2_CPEGPO0          0x00000000

#define SYSGPOCTL_GPOCTL1_M                0x000000F0
#define SYSGPOCTL_GPOCTL1_RATGPO2          0x000000E0
#define SYSGPOCTL_GPOCTL1_RATGPO1          0x000000D0
#define SYSGPOCTL_GPOCTL1_RATGPO0          0x000000C0
#define SYSGPOCTL_GPOCTL1_RFEGPO3          0x000000B0
#define SYSGPOCTL_GPOCTL1_RFEGPO2          0x000000A0
#define SYSGPOCTL_GPOCTL1_RFEGPO1          0x00000090
#define SYSGPOCTL_GPOCTL1_RFEGPO0          0x00000080
#define SYSGPOCTL_GPOCTL1_MCEGPO3          0x00000070
#define SYSGPOCTL_GPOCTL1_MCEGPO2          0x00000060
#define SYSGPOCTL_GPOCTL1_MCEGPO1          0x00000050
#define SYSGPOCTL_GPOCTL1_MCEGPO0          0x00000040
#define SYSGPOCTL_GPOCTL1_CPEGPO3          0x00000030
#define SYSGPOCTL_GPOCTL1_CPEGPO2          0x00000020
#define SYSGPOCTL_GPOCTL1_CPEGPO1          0x00000010
#define SYSGPOCTL_GPOCTL1_CPEGPO0          0x00000000

#define SYSGPOCTL_GPOCTL0_M                0x0000000F
#define SYSGPOCTL_GPOCTL0_RATGPO3          0x0000000F
#define SYSGPOCTL_GPOCTL0_RATGPO2          0x0000000E
#define SYSGPOCTL_GPOCTL0_RATGPO1          0x0000000D
#define SYSGPOCTL_GPOCTL0_RATGPO0          0x0000000C
#define SYSGPOCTL_GPOCTL0_RFEGPO3          0x0000000B
#define SYSGPOCTL_GPOCTL0_RFEGPO2          0x0000000A
#define SYSGPOCTL_GPOCTL0_RFEGPO1          0x00000009
#define SYSGPOCTL_GPOCTL0_RFEGPO0          0x00000008
#define SYSGPOCTL_GPOCTL0_MCEGPO3          0x00000007
#define SYSGPOCTL_GPOCTL0_MCEGPO2          0x00000006
#define SYSGPOCTL_GPOCTL0_MCEGPO1          0x00000005
#define SYSGPOCTL_GPOCTL0_MCEGPO0          0x00000004
#define SYSGPOCTL_GPOCTL0_CPEGPO3          0x00000003
#define SYSGPOCTL_GPOCTL0_CPEGPO2          0x00000002
#define SYSGPOCTL_GPOCTL0_CPEGPO1          0x00000001
#define SYSGPOCTL_GPOCTL0_CPEGPO0          0x00000000
/** @} **/

/** @ingroup cpu_specific_peripheral_memory_map
  * @{
  */
#define RFC_DBELL_BASE        (PERIPH_BASE + 0x41000) /**< RFC_DBELL base address */
#define RFC_DBELL_NONBUF_BASE (PERIPH_NONBUF_BASE + 0x41000) /**< RFC_DBELL non-buffered base address */
/** @} */

#define RFC_DBELL             ((rfc_dbell_regs_t *) (RFC_DBELL_BASE)) /**< RFC_DBELL register bank */
#define RFC_DBELL_NONBUF      ((rfc_dbell_regs_t *) (RFC_DBELL_NONBUF_BASE)) /**< RFC_DBELL non-buffered register bank */

#ifdef __cplusplus
}
#endif

#endif /* CC26XX_CC13XX_RFC_DBELL_H */

/*@}*/
