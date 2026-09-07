#pragma once

/** @file lpm.h @brief 触摸唤醒和低功耗模式控制接口。 */

/** @brief 初始化低功耗任务、触摸中断和唤醒相关 GPIO。 */
void lpm_init(void);
/** @brief 使能低功耗策略。 */
void lpm_enable(void);
/** @brief 禁用低功耗策略并恢复正常运行。 */
void lpm_disable(void);
