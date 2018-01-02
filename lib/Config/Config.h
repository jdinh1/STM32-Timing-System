#ifndef S6CONFIG_H
#define S6CONFIG_H

#include "mbed.h"

namespace Config {
	const extern double   GATE_TIMER_PERIOD;
	const extern uint64_t GATE_TIMER_1_SECONDS;
	const extern uint64_t GATE_TIMER_2_SECONDS;
	const extern uint64_t GATE_TIMER_4_SECONDS;
	const extern uint64_t GATE_TIMER_8_SECONDS;
	const extern uint64_t GATE_TIMER_16_SECONDS;
	const extern uint64_t GATE_TIMER_30_SECONDS;
	const extern uint64_t GATE_TIMER_32_SECONDS;
} // namespace Config

#endif
