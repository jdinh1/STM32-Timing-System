#include "mbed.h"
#include <string>
#include <TimerSystem.h>
#include <Config.h>

void _set_timers_values();
void _serialRX();
void _process_rx_buffer();
void _clear_rx_buffer();
void _notify_update_false();
void _notify_update_true();
void _notify_cycle_finish();
void handleGateTimer();
void init();
void reset();

Serial device(SERIAL_TX, SERIAL_RX);
/* ================================================================
*	 GLOBAL VARIABLES
*  ================================================================
*/
string            buff   = "";
string            backup = "";
char              buffer[40];
int               bytesReceived = 0;
volatile uint64_t protocol      = 0;
volatile uint64_t timer_on      = 0;
volatile uint64_t timer_off     = 0;
volatile int      nCycles       = 0;
volatile uint64_t cycleCount    = 0;
volatile uint64_t gateHitCount  = 0;
volatile uint64_t onCounter     = 0;
volatile uint64_t offCounter    = 0;
volatile bool     updated       = true;
volatile bool     cycleOn       = true;

TimerSystem timer;
DigitalOut  led(LED2);

/* ================================================================
*	 MAIN
*  ================================================================
*/
int main() {
	init();

	wait(1);
	timer.handleGateTimer(callback(&handleGateTimer));
	timer.start();

	while (1) {

		if (cycleOn) {
			led = 1;
		} else {
			led = 0;
		}
		_notify_cycle_finish();
		if (strchr(buffer, ';') != 0) {
			_process_rx_buffer();
			bytesReceived = 0;
		}

#ifdef _DEBUG_
		device.printf("Data - %c\n", buffer);
		device.printf("Backup - %s\n", backup.c_str());
		device.printf("Protocol - %llu\n", protocol);
		//device.printf("updated - %d\n", updated);
		device.printf("Cycles - %d\n", nCycles);
		device.printf("On - %llu\n", timer_on);
		device.printf("Off - %llu\n", timer_off);
#endif
	}
}

/* ================================================================
*	 METHODS
*  ================================================================
*/
void init() {
	led = 1;
	device.baud(9600);
	device.attach(&_serialRX, Serial::RxIrq);
}

void _serialRX() {
	while ((device.readable())) {
		buffer[bytesReceived] = device.getc();
		bytesReceived++;
		if ((bytesReceived == 40) || (buffer[bytesReceived - 1] == '\n')) {
			buffer[bytesReceived] = 0; // append a null
		}
	}
}

void _process_rx_buffer() {
	switch (buffer[0]) {
		case '1':
			timer.stop();
			_set_timers_values();
			timer.start();
			break;
		case '2':
			break;
		case '3':
			break;
	}
}

void _set_timers_values() {
	if (strlen(buffer) > 0) {
		char *token;
		token     = strtok(buffer, ",;");
		protocol  = atoi(token);
		token     = strtok(NULL, ",;");
		nCycles   = atoi(token);
		token     = strtok(NULL, ",;");
		timer_on  = (uint64_t)(Config::GATE_TIMER_1_SECONDS * atoi(token));
		token     = strtok(NULL, ",;");
		timer_off = (uint64_t)(Config::GATE_TIMER_1_SECONDS * atoi(token));
		reset();
		updated = true;
	} else {
		updated = false;
	}
}

void _notify_update_false() {
	device.printf("0");
}

void _notify_update_true() {
	device.printf("1");
}

void _notify_cycle_finish() {
	device.printf("2;%llu\n", cycleCount);
}

void _clear_rx_buffer() {
	buff.clear();
}

void handleGateTimer() {
	gateHitCount++;

	if (cycleCount < nCycles) {
		if (cycleOn == true) {
			onCounter++;
			if (onCounter % timer_on == 0) {
				cycleOn = false;
			}
		} else {
			offCounter++;
			if (offCounter % timer_off == 0) {

				cycleCount++;
				cycleOn    = true;
				onCounter  = 0;
				offCounter = 0;
			}
		}
	}
}

void reset() {
	cycleCount   = 0;
	gateHitCount = 0;
	onCounter    = 0;
	offCounter   = 0;
	cycleOn      = true;
}
