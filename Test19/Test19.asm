ORG 0H

AJMP MAIN
ORG 100H
MAIN:
MOV A,#0FEH
LOOP:
RL A
MOV P1,A
LCALL DELAY1
LJMP LOOP

DELAY1:
MOV R0,#200
LOOP2:
MOV R1,#100
LOOP1:
DJNZ R1,LOOP1
DJNZ R0,LOOP2
RET

END