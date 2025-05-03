#ifndef Bit_Utilies
#define Bit_Utilies


#define GET_BIT(reg1,bit)   (((reg1)>>(bit))&1)
#define GET_REG(reg)        ((reg)&0xff)

#define SET(reg,val)        ((reg) |= (val))
#define SET_BIT(reg,bit)    ((reg) |= (1<<(bit)))

#define CLR(reg,val)        ((reg) &=~(val))
#define CLR_BIT(reg,bit)    ((reg) &=~(1<<(bit)))

#define MASK(reg, mask) ((reg) & (mask))

#define REV_MASK(reg, mask) ((reg) & ~(mask))

#endif
