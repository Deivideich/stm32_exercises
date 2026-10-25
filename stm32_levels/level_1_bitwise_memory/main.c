#include "hardware.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void bitwise_operations(void) {
    // Initialize an arbitrary 32 bit register
    volatile uint32_t register_sim = 0x00000000U;

    // Exercise 1: Manually calculate a binary and hexadecimal mask to isolate a specific bit
    volatile uint32_t calculated_hexadecimal_mask = 0x100U; // 256 in decimal, 100000000 in binary
    volatile uint32_t calculated_binary_mask = (1U << 1); //0x00000010 mask in binary;
    register_sim |= calculated_binary_mask; //register_sim is now 00000010 in binary  
    register_sim |= calculated_hexadecimal_mask; //register sim is now 1000000010, or 0x00000102
    
    // Exercise 2: Apply the logical AND (&) operation to clear (set to 0) a register bit without altering the others.
    register_sim &= ~(1U << 8); //register sim is now 00000010 

    // Exercise 3: Apply the logical OR (|) operation to activate (set to 1) a configuration bit.
    register_sim |= (1U << 5); //register sim is now 01000010
    
    // Exercise 4: Combine the NOT (~) operator with AND (&) to safely turn off a specific bit.
    register_sim &= ~(1U << 1);

    // Exercise 5: Apply the XOR (^) operator to accurately toggle a status bit.
    register_sim ^= (1U << 1);

    // Exercise 6: Use logical left shifts (<<) to position a multi-bit value within a register field.
    register_sim = 3U; // 0x00000011 which is 3 in binary
    #define TIMER_MODE_SHIFT 12U // bit displacement value
    uint32_t mode_value = 5U; // 0x05 or 00000101

    register_sim |= (mode_value << TIMER_MODE_SHIFT); // 101000000000011
    
    // Exercise 7: Use logical right shifts (>>) to extract and read a multi-bit field from a register
    uint32_t register_extract = 0;
    uint32_t bitfield = 31U;
    register_extract = (register_sim >> TIMER_MODE_SHIFT) & bitfield; //register extract = 00101
    (void)register_extract;
    // Exercise 8: Design a compound mask with shifts to clear and then write a multi-bit configuration field.
    register_sim = 0x53F9F314; //random value 
    uint32_t sensor_mask = 63U; //assume 6bit config field for a sensor config mask
    uint32_t init_config_sensor = 25U; //random config sensor initialization mask
    #define MOCK_SENSOR_BITFIELD_READ_AND_RESET_SHIFT 10U
    register_sim = (~(sensor_mask << MOCK_SENSOR_BITFIELD_READ_AND_RESET_SHIFT) & register_sim) | (init_config_sensor << MOCK_SENSOR_BITFIELD_READ_AND_RESET_SHIFT);
}


int main(void) {

    bitwise_operations();
    uint32_t fake_random_sensor_register = 0x8304BFD3;
    uint32_t timer_shift = 8U;
    uint32_t fake_dynamic_value_mask = 15U; //0b1111
    uint32_t counter = 0;
    uint32_t limit_mask = 15U; // for some random reason, even if the val for our fake perihperal is 4-bit sized, lets assume that the counter only
    // needs access to the first 3 bits and the last bit is only a configuration or reset bit 
    uint32_t status_flag = 0;
    uint32_t status_flag_mask = 1U;
    uint32_t status_flag_inner_shift = timer_shift + 3U;// After moving 8U, move another 3 shifts to check for the flag mask sized bit 
    fake_random_sensor_register = ~(fake_dynamic_value_mask << timer_shift) & fake_random_sensor_register; //sets bits from random register to 000

    while (1) {

        // Exercise 9: Implement a synchronous polling read by analyzing a status flag using an AND mask.
        status_flag = (fake_random_sensor_register >> status_flag_inner_shift) & status_flag_mask;
        counter = counter + 1;
        counter = counter & limit_mask;
        fake_random_sensor_register = ~(fake_dynamic_value_mask << timer_shift) & fake_random_sensor_register;
        fake_random_sensor_register = (counter << timer_shift) | fake_random_sensor_register; 
        (void)status_flag;
    }

    return 0;
}
