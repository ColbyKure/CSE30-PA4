/* 
 * File: isInRange.s
 * Author: Colby Kure 
 * Userid: cs30xdc
 * Description: This function will chack to see if the first parameter is
 *	is in the range of the last 2 paramters.
 * Date: 4/17/18
 * Sources of help: notes:
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of pis 
	.syntax	unified		@ modern ARM syntax

	.equ	FP_OFFSET, 4	@ set fp to base of saved registers

	.global	isInRange	@ isInRnage is global function

	.text			@ start text section 
	.align	2		@ align at 4 offset 

/*
 * Function name: isInRange()
 * Prototype: isInRange(long value, long minRange, long maxRange)
 * Description: Checks if value is in a certain range 
 * Paramters: 	value - the value to chack
 *		minRange - lower bound
 *		maxRange - upper bound
 * Side Effects: None
 * Error Condition: minRange is greater than maxRange and -1 is returned
 * Return Value: 0 for not in range, 1 for in range, -1 for error 
 *
 * Registers used:
 *	
 *	r0 - arg 1 - value 
 *	r1 - arg 2 - minRange
 *	r2 - arg 3 - maxRange
 */

isInRange:
	@ Standard Prologue
	push	{fp, lr}		@ save registers fp anf lr on stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of sved registers 

	cmp	r1, r2			@ branch if minRange < maxRange
	blt	no_err			

	mov	r0, -1			@ set return val to -1 and return
	b	return

no_err:
	cmp	r0, r1			@ no error; compaer value and min
	blt	not_in_range

	cmp	r0, r2			@ compare value and max
	bge	not_in_range

	mov	r0, 1			@ return 1 if in range 
	b	return

not_in_range:
	mov	r0, 0			@ return 0 if not in range

return:
	@ Standard Epilogue
	sub	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp and lr into pc
