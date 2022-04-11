#include <stdio.h>

__asm int* hasher( char *a, int *array ){
	
	PUSH {r4, r5, r6, r7}

loop
	
	MOV r5, r1
	LDRB r3, [r0]
	CMP r3, #0
	BEQ returning
	
//--------------------
	CMP   r3, #'A'  			// compare with character 'A'
	BLT   not_cap_skip    // If lower than, then skip
	CMP		r3,	#'Z'				// compare with character 'Z'
	BGT		not_cap_skip		// If greater than, then skip
	
	SUB r2, r3, #'A'			// finding the offset and placing it in r2 (A: r2=0, B: r2=1 ....)
	MOV r7, #4						// placing 4 in r3 just for the multiplication
	MUL r2, r2, r7				// converting offset from bytes to words
	ADD r5, r5, r2				// increasing the pointer adding the offset
	LDR r4, [r5]					// placing the correct element acording to the pointer
	B loop_add				  	// returning
	
not_cap_skip						// moving here when the character is not a capital letter
	
	CMP   r3, #'0'  			// compare with character '0'
	BLT   not_num_skip		// If lower than, then skip
	CMP		r3,	#'9'    		// compare with character '9'
	BGT		not_num_skip		// If greater than, then skip
	
	SUB r3, r3, #'0'			// converting the character number to integer
	MOV r7, #-1						// placing -1 in r3 just for the multiplication
	MUL r4, r3, r7				// finding the opposite number
	B loop_add						// returning
	
not_num_skip						// moving here when the character is not a number nor a capital letter
	
	MOV r4, #0						// placing 0 as returning value
	
//----------------------
loop_add
	ADD r6, r6, r4
	ADD r0, r0, #1
	B loop

returning
	MOV r0, r1
	ADD r0, r0, #144
	STR r6, [r0]	
	POP {r4, r5, r6, r7}
	BX lr									// returning 
	
	
}

int main(){
	
	int* result;
	char a[]= "Xh34";
	int array[26] = {10,41,12,21,7,5,67,48,69,2,36,3,
    19,1,14,51,71,8,26,54,75,15,6,59,13,25};
	result= hasher(a, array);
	
		
	printf("=%d", *result);
	
	return 0;
}
