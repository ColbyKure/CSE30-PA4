/*
 * Filename: revHash.s
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file hods the revhash function that returns an int
 * Date: May 26 2018
 * Sources of Help: piazza, notes
 */

	.cpu	cortex-a53		@ version of pi
	.syntax	unified			@ modern ARM syntax

	.equ	FP_OFFSET, 4
	.equ	LOCAL_SPACE, 8
	.equ	PARAM_SPACE, 8
	.equ	HASH_OFF, -8
	.equ	I_OFF, -12
	.equ	STR_OFF, -16

	.global	revHash			@ global function

	.text				@ start coding section
	.align	2			@ align 4 offset 

/*
 * Function Name: revHash()
 * Function Prototype: int revHash(char const * str)
 * Description: This function will make the hash key for a string.
 * Parameters:
 * 	str - char * - holds the string to hash 
 * Side Effects: none 
 * Error Conditions: none 
 * Return Value: returns the hash of the string
 * 
 * Registers used: 
 * 	r0 - arg 1 and hash variable - return and arg 1
 * 	r1 - i - counter for loop
 * 	r3 - paceholder register
 *
 * Local variables: 
 * 	hash - fp-8 - integer value to return 
 * 	i - fp-12 - counter for loop 
 */

revHash:
	@ prologue
	push	{fp, lr}		@ save registers
	add	fp, sp, FP_OFFSET	@ set fp

	@ save locals
	sub	sp, sp, LOCAL_SPACE	@ set sp 
	ldr	r3, =HashStartVal
	ldr	r3, [r3]		@ get const val 
	str	r3, [fp, HASH_OFF]	@ store hash
	mov	r3, 0
	str	r3, [fp, I_OFF]		@ store i

	@ save params
	sub	sp, sp, PARAM_SPACE
	str	r0, [fp, STR_OFF]

	@ start code
	ldr	r0, [fp, STR_OFF]	@ load str
	cmp	r0, 0
	beq	end_for			@ if str is NULL

	ldr	r0, [fp, STR_OFF]
	bl	strlen			@ call strlen

	sub	r0, r0, 1		@ i = strlen(str) - 1
	str	r0, [fp, I_OFF]		@ i = strLen
	cmp	r0, 0			@ cosmetic
	blt	end_for

for_loop:
	ldr	r0, [fp, HASH_OFF]	
	ldr	r3, =HashPrime
	ldr	r3, [r3]		@ load HASH_PRIME const value
	mul	r0, r0, r3		@ hash = hash * HASH_PRIME

	@ get str[i]
	ldr	r3, [fp, STR_OFF]
	ldr	r1, [fp, I_OFF]
	add	r3, r3, r1		@ str = str + i
	ldrsb	r3, [r3]		@ *str

	add	r0, r0, r3		@ hash = hash + str[i]
	str	r0, [fp, HASH_OFF]

	ldr	r1, [fp, I_OFF]
	sub	r1, r1, 1
	str	r1, [fp, I_OFF]		@ i--

	cmp	r1, 0			@ i >= 0
	bge	for_loop
end_for:

	ldr	r0, [fp, HASH_OFF]
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}	
