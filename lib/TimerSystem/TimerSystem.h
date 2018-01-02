#ifndef FLOWMAIL_H
#define FLOWMAIL_H

#include "mbed.h"
#include <Config.h>

class TimerSystem {
	private:
	Ticker           _gateTimer;
	Callback<void()> _handlerFunc;

	public:
	TimerSystem();

	~TimerSystem();

	/** Stop the Gate Timer */
	void stop();

	/** Start the Gate Timer */
	void start();

	/** Set the handler for the Gate Timer */
	void handleGateTimer(Callback<void()> handler);
};

#endif
