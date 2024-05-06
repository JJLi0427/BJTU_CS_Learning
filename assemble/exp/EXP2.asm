DATA  SEGMENT
      BUFF DB -37, 28, -115, -2, 98, -100, 93, 120, 56, -99
      MAX DB ?
      MIN DB ?
DATA  ENDS

CODE  SEGMENT
      ASSUME CS:CODE,DS:DATA
START:
      MOV AX,DATA
      MOV DS,AX
      LEA SI,BUFF
      MOV AL,[SI]
      MOV AH,[SI]
      INC SI
      MOV CX,9
   LP:CMP AL,[SI]
      JG N1
      MOV AL,[SI]
      JMP N2
   N1:CMP AH,[SI]
      JL N2
      MOV AH,[SI]
   N2:INC SI
      LOOP LP
      MOV MIN,AL
      MOV MAX,AH
      MOV AH,4CH
      INT 21H
CODE ENDS
END START