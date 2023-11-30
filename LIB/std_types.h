/*-----------------------
-INCLUDES
------------------------*/
#include "stdint.h"

/*-----------------------
-MACROS
------------------------*/
#define SUCCESS     			  (0)
#define ERROR       			  (-1)
#define INVALID_INPUT 			(-2)
#define NULL 								((void *)0)
	
#ifndef TRUE
#define TRUE   							(1u)
#endif

#ifndef FALSE
#define FALSE  						  (0u)
#endif

/*-----------------------
-TYPEDEFS
------------------------*/
typedef unsigned char    boolean;
void debounce()
{
    for (uint16_t i = 0 ; i < 10000 ; i++)
        for(uint16_t j = 0 ; j < 100 ; j++)
            for (uint16_t k = 0 ; k < 2 ; k++);
}
/*-----------------------
-BIT OPERATIONS
------------------------*/

#define GET_BIT_STATUS(reg, bit_idx)  (0UL != ((reg)& (1UL<<(bit_idx))))

#define SET_BIT(reg, bit_idx)  (reg) |= (1UL << (bit_idx))

#define CLEAR_BIT(reg, bit_idx)  (reg) &= (~(1UL << (bit_idx)))