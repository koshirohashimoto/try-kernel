/*
 *** Common library function definition
 */

#ifndef SYSLIB_H
#define SYSLIB_H

/* Input from 32bit register */
static inline UW in_w(UW adr)
{
    return *(_UW*)adr;
}

/* Output to 32bit register */
static inline void out_w(UW adr, UW data)
{
    *(_UW*)adr = data;
}

/* Output to 32bit register (bit clear) */
#define OP_CLR      0x3000
static inline void clr_w(UW adr, UW data)
{
    *(_UW*)(adr + OP_CLR) = data;
}

/* Output to 32bit register (bit set) */
#define OP_SET       0x2000
static inline void set_w(UW adr, UW data)
{
    *(_UW*)(adr + OP_SET) = data;
}

/* Output to 32bit register (bit XOR) */
#define OP_XOR      0x1000
static inline void xset_w(UW adr, UW data)
{
    *(_UW*)(adr + OP_XOR) = data;
}

/* Inline function for PRIMASK register */
static inline void set_primask( INT pm )
{
    __asm__ volatile("msr primask, %0":: "r"(pm));
}

static inline UW get_primask( void )
{
    UW  pm;
    __asm__ volatile("mrs %0, primask": "=r"(pm));
    return pm;
}

/* Macro for Disable Interrupt */
#define	DI(intsts)	(intsts=get_primask(), set_primask(1))

/* Macro for Enable Interrupt */
#define	EI(intsts)	(set_primask(intsts))

/* Serial com for debugging */
void tm_com_init(void);
UINT tm_putstring(char *str);

#endif  /* STYLIB_H */
