// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_LIB_DIF_DIF_CLKMGR_H_
#define OPENTITAN_SW_DEVICE_LIB_DIF_DIF_CLKMGR_H_

/**
 * @file
 * @brief <a href="/hw/ip/clkmgr/doc/">Clock manager</a> Device Interface
 * Functions
 */

#include <stdint.h>

#include "sw/device/lib/base/macros.h"
#include "sw/device/lib/base/mmio.h"
#include "sw/device/lib/dif/dif_base.h"

#include "sw/device/lib/dif/autogen/dif_clkmgr_autogen.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * An Index of a "Gateable" Clock.
 *
 * "Gateable" clocks are under full software control: they can be enabled and
 * disabled by software, which directly starts and stops the identified clock.
 */
typedef uint32_t dif_clkmgr_gateable_clock_t;

/**
 * An Index of a "Hintable" Clock.
 *
 * "Hintable" clocks are under partial software control: software can suggest
 * they are stopped, but the clock manager may delay stopping the peripheral, or
 * may ignore the request altogether.
 */
typedef uint32_t dif_clkmgr_hintable_clock_t;

/**
 * Check if a Gateable Clock is Enabled or Disabled.
 *
 * @param clkmgr Clock Manager Handle.
 * @param clock Gateable Clock ID.
 * @param[out] is_enabled whether the clock is enabled or not.
 * @returns The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_clkmgr_gateable_clock_get_enabled(
    const dif_clkmgr_t *clkmgr, dif_clkmgr_gateable_clock_t clock,
    bool *is_enabled);

/**
 * Enable or Disable a Gateable Clock.
 *
 * @param clkmgr Clock Manager Handle.
 * @param clock Gateable Clock ID.
 * @param new_state whether to enable or disable the clock.
 * @returns The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_clkmgr_gateable_clock_set_enabled(
    const dif_clkmgr_t *clkmgr, dif_clkmgr_gateable_clock_t clock,
    dif_toggle_t new_state);

/**
 * Check if a Hintable Clock is Enabled or Disabled.
 *
 * Hintable clocks are not under full software control, but this operation
 * accurately reflects the state of the current clock, regardless of any hint
 * requests made by software.
 *
 * To read what hint the software has given the hardware, use
 * #dif_clkmgr_hintable_clock_get_hint.
 *
 * @param clkmgr Clock Manager Handle.
 * @param clock Hintable Clock ID.
 * @param[out] is_enabled whether the clock is enabled or not.
 * @returns The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_clkmgr_hintable_clock_get_enabled(
    const dif_clkmgr_t *clkmgr, dif_clkmgr_hintable_clock_t clock,
    bool *is_enabled);

/**
 * Enable or Disable a Hintable Clock.
 *
 * This only sets a hint that the clock should be enabled or disabled. The clock
 * manager is in control of whether the clock should actually be enabled or
 * disabled.
 *
 * To read what hint the software has given the hardware, use
 * #dif_clkmgr_hintable_clock_get_hint. To read whether the clock is currently
 * enabled or disabled, use #dif_clkmgr_hintable_clock_get_enabled.
 *
 * @param clkmgr Clock Manager Handle.
 * @param clock Hintable Clock ID.
 * @param new_state whether to enable or disable the clock.
 * @returns The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_clkmgr_hintable_clock_set_hint(
    const dif_clkmgr_t *clkmgr, dif_clkmgr_hintable_clock_t clock,
    dif_toggle_t new_state);

/**
 * Read the current Hint for a Hintable Clock.
 *
 * Hintable clocks are not under full software control; this operation
 * accurately reflects the current software hint, not the current state of the
 * clock.
 *
 * To read whether the clock is currently enabled or disabled, use
 * #dif_clkmgr_hintable_clock_get_enabled.
 *
 * @param clkmgr Clock Manager Handle.
 * @param clock Hintable Clock ID.
 * @param[out] hinted_is_enabled the current software request (hint) for this
 * clock.
 * @returns The result of the operation.
 */
OT_WARN_UNUSED_RESULT
dif_result_t dif_clkmgr_hintable_clock_get_hint(
    const dif_clkmgr_t *clkmgr, dif_clkmgr_hintable_clock_t clock,
    bool *hinted_is_enabled);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // OPENTITAN_SW_DEVICE_LIB_DIF_DIF_CLKMGR_H_
