#pragma once

/**
 * @file lpm.h
 * @brief 触摸唤醒和低功耗模式控制接口。
 * @details 无操作达到超时后降低 CPU 频率并关闭背光，GPIO 中断负责唤醒。
 */

/** @file lpm.h @brief 触摸唤醒和低功耗模式控制接口。 */

/** @brief 初始化低功耗任务、触摸中断和唤醒相关 GPIO。 */
void lpm_init(void);

/** @brief 初始化低功耗任务、触摸中断和唤醒 GPIO。 */
/** @brief 使能低功耗策略。 */
void lpm_enable(void);

/** @brief 使能低功耗策略并创建后台监测任务。 */
/** @brief 禁用低功耗策略并恢复正常运行。 */
void lpm_disable(void);

/** @brief 禁用低功耗策略、移除中断并恢复正常运行状态。 */
