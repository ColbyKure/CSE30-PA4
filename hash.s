/*
 * Filename: hash.s
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file hods the has h function thatreturns an int
 * Date: May 14 2018
 * Sources of Help: piazza, notes
 */

	.cpu	cortex-a53		@ version of pi
	.syntax	unified			@ modern ARM syntax

	.equ	FP_OFFSET, 4		
	.equ	LOCAL_SPACE, 16		
	.equ	PARAM_SPACE, 8
	.equ	HASH_OFF, -8
	.equ	STRLEN_OFF, -12
	.equ	I_OFF, -16
	.equ	STR_OFF, -24

	.global hash			@ global function

	.text				@ start coding section
	.align	2			@ align 4 offset 

/*
 * Function Name: hash()
 * Function Prototype: int hash(char const * str);
 * Description: This function will make the hash key for a string.
 * Parameters:
 * 	str - char * - holds the string to hash 
 * Side Effects: none 
 * Error Conditions: none 
 * Return Value: returns the hash of the string
 * 
 * Registers used: 
 * 	r0 - arg 1 - arg 1 holdser and return address
 * 	r1 - local - strlen - holds length of arg 1, str
 * 	r1 - local - holder for loop counter, i 
 * 	r3 - temp val - used to load and store value or constants
 * 
 * Local variables: 
 * 	hash - fp-8 -- hash value to return eventually
 * 	strLen - fp-12 -- length of string
 * 	i - fp-16 - counter for loop
 */

hash:
	@ prologue
	push	{fp, lr}		@ save registers
	add	fp, sp, FP_OFFSET	@ set fp

	@ save locals
	sub	sp, sp, LOCAL_SPACE	@ set sp 
	ldr	r3, =HashStartVal
	ldr	r3, [r3]		@ get const val 
	str	r3, [fp, HASH_OFF]	@ store hash
	mov	r3, 0
	str	r3, [fp, STRLEN_OFF]	@ store strlen
	mov	r3, 0
	str	r3, [fp, I_OFF]		@ store i

	@ save params
	sub	sp, sp, PARAM_SPACE
	str	r0, [fp, STR_OFF]

	@ start code
	ldr	r0, [fp, STR_OFF]	@ load str
	cmp	r0, 0
	beq	end_for			@ if str == NULL

	bl	strlen			@ call strlen
	str	r0, [fp, STRLEN_OFF]	@ save val

	ldr	r0, [fp, I_OFF]		@ load i
	ldr	r1, [fp, STRLEN_OFF]
	cmp	r0, r1			@ cmp i and strLen
	bge	end_for
for_loop:
	ldr	r0, [fp, HASH_OFF]
	ldr	r3, =HashPrime
	ldr	r3, [r3]
	mul	r0, r0, r3		@ hash = hash * HASH_PRIME

	ldr	r3, [fp, STR_OFF]
	ldr	r1, [fp, I_OFF]
	add	r3, r3, r1		@ str = str + i
	ldrb	r3, [r3]		@ *str

	add	r0, r0, r3		@ hash = hash + str[i]
	str	r0, [fp, HASH_OFF]

	ldr	r1, [fp, I_OFF]
	add	r1, r1, 1
	str	r1, [fp, I_OFF]		@ i++

	ldr	r3, [fp, STRLEN_OFF]
	cmp	r1, r3			@ i < strlen
	blt	for_loop
end_for:

	ldr	r0, [fp, HASH_OFF]
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}	
