DATA  SEGMENT
	  TABLE	DB 100 DUP('$')
	  STR DB 'Please enter a string:$'
DATA  ENDS
CODE  SEGMENT
	  ASSUME CS:CODE,DS:DATA
START:MOV AX,DATA
	  MOV DS,AX
	  LEA DX,STR
	  MOV AH,9
	  INT 21H
	  MOV SI,0
  LP1:MOV AH,1
	  INT 21H
	  CMP AL,13
	  JZ EXIT
	  MOV TABLE[SI],AL
	  INC SI
	  LOOP LP1
 EXIT:MOV TABLE[SI],'$'
      CALL FUNC
      ADD BX,30H
	  MOV DX,BX
	  MOV AH,2
	  INT 21H
	  MOV AH,4CH
	  INT 21H
FUNC PROC NEAR
	  MOV CX,SI
	  LEA SI,TABLE
  LP2:CMP BYTE PTR [SI],'C'
	  JNZ EXIT1
	  INC SI
	  CMP BYTE PTR [SI],'H'
	  JNZ EXIT2
	  INC SI
	  CMP BYTE PTR [SI],'A'
	  JNZ EXIT2
	  INC SI
	  CMP BYTE PTR [SI],'R'
	  JNZ EXIT2
	  INC BX
EXIT1:INC SI
EXIT2:CMP SI,CX
	  LOOPNZ LP2
	  RET
FUNC ENDP
CODE ENDS
END	START
