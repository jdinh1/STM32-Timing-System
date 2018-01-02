#include "TimerSystem.h"

TimerSystem::TimerSystem() {
}

TimerSystem::~TimerSystem() {
}

void TimerSystem::start() {
	_gateTimer.attach(this->_handlerFunc, Config::GATE_TIMER_PERIOD);
}

void TimerSystem::stop() {
	_gateTimer.detach();
}

void TimerSystem::handleGateTimer(Callback<void()> handler) {
	this->_handlerFunc = handler;
}
