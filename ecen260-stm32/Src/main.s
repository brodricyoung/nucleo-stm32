	.text
	.global main
	.cpu cortex-m4
	.syntax unified

main:
    MOV R1, #1
    BL abs
inf: B inf



// This abs function returns the absolute value of a number
// Input Parameter: R1
// Return Parameter: R0
abs:
    PUSH {R2}
    MOV R2, #0
    MOV R0, R1
    CMP R2, R1
    BLT L1
    SUB R0, R2, R1
L1:
    POP {R2}
    BX LR



	.end
