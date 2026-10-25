// Declare a C structure using the '__attribute__((packed))' attribute to map memory precisely
#ifndef CUSTOM_PACKED_STRUCT_H
#define CUSTOM_PACKED_STRUCT_H
#include <stdint.h>

typedef struct __attribute__((packed)) custom_struct_packed_s { 
    uint8_t sensor_data;       
    uint16_t sensor_address;   
    uint32_t calibration_val;  
} custom_struct_packed_t;            


typedef struct custom_struct_s {
    uint8_t sensor_data;
    uint16_t sensor_address;
    uint32_t calibration_val;
} custom_struct_t;

#endif /* CUSTOM_PACKED_STRUCT_H */
