	.text
	.global main
	.cpu cortex-m4
	.syntax unified

main:
	MOV R1, #42

inf: B inf
