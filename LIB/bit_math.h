#ifndef _BITMATH_H_
#define _BITMATH_H_
/**************************************************************************/
/*                    Macros funcitons for Bit operations                 */
/**************************************************************************/
#define SET_BIT(_REG_ , _BIT_NUM_)        ((_REG_) |=  (1U<<(_BIT_NUM_)))
#define CLR_BIT(_REG_ , _BIT_NUM_)        ((_REG_) &= ~(1U<<(_BIT_NUM_)))
#define TOG_BIT(_REG_ , _BIT_NUM_)        ((_REG_) ^=  (1U<<(_BIT_NUM_)))
#define GET_BIT(_REG_ , _BIT_NUM_)        (((_REG_)>>  (_BIT_NUM_)) &1U ) 
#define SET_BITS(_REG_ , _VAL_)           ((_REG_) |=  (_VAL_))
#define CLR_BITS(_REG_ , _MSK_)           ((_REG_) &= ~(_MSK_))
#define TOG_BITS(_REG_ , _MSK_)           ((_REG_) ^=  (_MSK_))
#define GET_BITS(_REG_ , _MSK_)           ((_REG_)  &  (_MSK_))
#define CLR_ALL_BITS(_REG_)               ((_REG_)  = (0U))
#define SET_ALL_BITS(_REG_)               ((_REG_)  = ~((_REG_) & 0U))
#define TOG_ALL_BITS(_REG_)               ((_REG_)  = ~(_REG_))

#endif