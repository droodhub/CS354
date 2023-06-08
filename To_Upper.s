	.file	"To_Upper.s"
	.text
	.globl	To_Upper
	.type	To_Upper, @function

/* **********************
    Name:Andrew Sabee
    Wisc ID Number:908 098 6061
    Wisc Email:apmcavoy@wisc.edu
************************ */


To_Upper:

# C version
/* **********************
    void To_Upper(char array[])
    int i = 0; 
    while(array[i] != '\0'){
           if(array[i] <= 122 && array[i] >= 97)
                array[i] -= 32;
            i++;
    }

************************ */


# Memory Layout
/* ************************ 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -8(%rsp)  |  stores int i
        -16(%rsp) |  stores the base address of the char array passed to To_Upper
        %cl       |  stores the char we are currently looking at
        %rdi      |  stores base addr of array as passed to To_Upper
        %rax      |  stores i when we are working with it
************************ */


# Prologue
pushq %rbp
movq %rsp, %rbp

# Body of function
movq $0, -8(%rsp) #i counter variable
movq %rdi, -16(%rsp) #store array pointer in memory

.START_LOOP:
movq -16(%rsp), %rax #move base address into %rax
movsx -8(%rsp), %rdx #move i value into register to use + sign extend
movb (%rax, %rdx), %cl #move char at pointer into register
movzx %cl, %rcx #zero-extend the byte to clear out the rest of the register

cmpb $0, %cl
jz .END_OF_LOOP #if character = 0, string is done

movb (%rax, %rdx), %cl #make sure cl holds right value
cmpb $97, %cl #compare char in cl to 97
jl .MOVE #jump if less than 97, aka not a lowercase letter

movb (%rax, %rdx), %cl #make sure cl holds right value
cmpb $122, %cl #compare cl to 122
jg .MOVE #jump if greater than 122, aka not a lowercase letter

subb $32, %cl #change lowercase letter to uppercase

.MOVE:
movq -16(%rsp), %rax #move base address into rax
movsx -8(%rsp), %rdx #move i into rdx

movb %cl, (%rax, %rdx) #move cl char back into its original location, modification or not
inc %rdx #increment i

movq %rdx, -8(%rsp) #move incremented value to memory
jmp .START_LOOP #run loop again

.END_OF_LOOP:

# Epilogue
popq %rbp
    ret
