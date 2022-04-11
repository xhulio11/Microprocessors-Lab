#include <stdio.h>

__asm int hasher( char a, int *array ){
	
	CMP   r0, #'A'  			// compare with character 'A'
	BLT   not_cap_skip    // If lower than, then skip
	CMP		r0,	#'Z'				// compare with character 'Z'
	BGT		not_cap_skip		// If greater than, then skip
	
	SUB r2, r0, #'A'			// finding the offset and placing it in r2 (A: r2=0, B: r2=1 ....)
	MOV r3, #4						// placing 4 in r3 just for the multiplication
	MUL r2, r2, r3				// converting offset from bytes to words
	ADD r1, r1, r2				// increasing the pointer adding the offset
	LDR r0, [r1]					// placing the correct element acording to the pointer
	BX 	lr								// returning
	
not_cap_skip						// moving here when the character is not a capital letter
	
	CMP   r0, #'0'  			// compare with character '0'
	BLT   not_num_skip		// If lower than, then skip
	CMP		r0,	#'9'    		// compare with character '9'
	BGT		not_num_skip		// If greater than, then skip
	
	SUB r0, r0, #'0'			// converting the character number to integer
	MOV r3, #-1						// placing -1 in r3 just for the multiplication
	MUL r0, r0, r3				// finding the opposite number
	BX 	lr								// returning
	
not_num_skip						// moving here when the character is not a number nor a capital letter
	
	MOV r0, #0						// placing 0 as returning value
	BX lr									// returning
	
}

int main(){
	
	int result=0, hash, i;
	char a[]= "Xh345LAWaw000A3";
	int array[26] = {10,41,12,21,7,5,67,48,69,2,36,3,
    19,1,14,51,71,8,26,54,75,15,6,59,13,25};
	int size= sizeof(a)/sizeof(char);
	
	for(i=0; i<size-1; i++){
		hash= hasher(a[i], array);
		result = result + hash;
		if(i!=0 && hash>=0) printf("+");
		printf("%d", hash);
	}
		
	printf("=%d", result);
	
	return 0;
}
