/*
 * button.c

 *  Created on: May 9, 2026
 *      Author: deivideich
 */

#include "button.h"
#include "main.h"

static GPIO_PinState raw_state;
static GPIO_PinState last_raw_state;
static GPIO_PinState debounced_state;
static button_event_t pending_event = BTN_EVENT_NONE;
static uint32_t debounce_start_time = 100; //ms
static uint32_t min_total_time_for_stable_stat;

void button_update(void){
	// read usr input
	raw_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);
	// compare previous state vs current state to determine if a transition happened
	if (raw_state != last_raw_state){
		// If there was a change in the state then reset the timer
		debounce_timer_reset();
	}
	// In case the state is the same as the previous one, keep track on time
	else{
		// Evaluate if the raw state has been present for more than the min_waiting_time for debounced state
		if(get_state_timer() >= debounce_start_time){
			// In case the raw_state is DIFFERENT from the debounced state, assume an EVENT happened. Otherwise,
			// assume the state is continuous even if the waiting time condition was true
			if(raw_state != debounced_state){
				// If the raw_state and debounced state are different, then it means that the button state changed and has been
				// stable for more than the necessary waiting time
				// Because these conditions are true, it means that now the raw_state has officially become the new debounced state
				debounced_state = raw_state;
				// Now the debounced state is evaluated to see if the button was pressed or released
				if (debounced_state == GPIO_PIN_SET){
					pending_event = BTN_EVENT_PRESSED;
				}
				else{
					pending_event = BTN_EVENT_RELEASED;
				}
			}
		}
	}

	last_raw_state = raw_state;


};

button_event_t button_get_event(void){
	// This function returns the event that just happened, and resets the event to let it be determined
	//when a new change in state is registered
	button_event_t event_copy = pending_event;

	pending_event = BTN_EVENT_NONE;
	return event_copy;
}

void button_init(void){
	// Initialize previous_state as the current usr input to avoid state change false positives
	last_raw_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);
	debounced_state = last_raw_state;
	pending_event = BTN_EVENT_NONE;
	debounce_timer_reset();
}

// In case a new event happens, and if the state changed before the stabilization timer happened, then
// reset the debounce timer to allow the new satte to be processed
void debounce_timer_reset(void){
	min_total_time_for_stable_stat = HAL_GetTick();
}

// Evaluate the current time ct - min_time. In case CR - MIN_TIME >= wait then the state is consdered stable
uint32_t get_state_timer(void){
	return HAL_GetTick() - min_total_time_for_stable_stat;
}
