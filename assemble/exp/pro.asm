;8255的四个端口
IOY0 EQU 280H
MY8255_A EQU IOY0+00H
MY8255_B EQU IOY0+01H
MY8255_C EQU IOY0+02H
MY8255_MODE EQU IOY0+03H

;8254的四个端口
IOY1 EQU 288H
MY8254_C0 EQU IOY1+00H
MY8254_C1 EQU IOY1+01H
MY8254_C2 EQU IOY1+02H
MY8254_MODE EQU IOY1+03H

;ADC0809的四个端口
IOY2 EQU 290H
ADC0809 EQU IOY2+00H

;数据段定义
DATA SEGMENT
    ALPHATABLE DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH
    ;数码管字型码
    STR0 DB 'The voltmeter starts working! ',0ah,0dh, '$'
    STR1 DB 'Volts too high!', 0ah,0dh, '$'
    STR2 DB 'Volts too low!', 0ah,0dh, '$'
    STR3 DB 'safe!',0ah,0dh, '$'
    RESS DB 4 DUP(?)
DATA ENDS

STACK1 SEGMENT STACK
    DW 256 DUP(?)
STACK1 ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK1

;主程序部�?
START: 
    MOV AX,DATA;初始化寄存器
    MOV DS,AX
    MOV DX,MY8255_MODE;8255初始化
    MOV AL,10000000B;方式命令: ABC都为0方式且都为输出
    OUT DX,AL

    mov DX, MY8255_A
    mov AL, 0FFH
    out DX, AL

    MOV DX,OFFSET STR0   ;系统开始工作 显示提示信息
    MOV AH,09H
    INT 21H

START1:
    MOV DX, MY8254_MODE
    mov al, 00010000B
    out DX, AL

    ;mov DX, MY8254_C0
    ;mov al, 0FH
    ;out DX, AL

    MOV DX,ADC0809  ;0809的初始化
    MOV AL,0        ;送给0809任意值 启动芯片
    OUT DX,AL

    ;MOV CL,AL
    MOV DX,ADC0809
    IN AL,DX    
    MOV CL,AL       ;读取转换结果存入CL

START2:
    CALL TRANSFORM  ;调用AD转换
    mov bx, 0FH



lppp:

    CALL ALARM      ;调用报警检测

    DEC bx
    cmp bx,0
    jnz lppp

    MOV AH,01H
    INT 16H         ;检测是否有键盘输入
    JNE QUIT        ;按下任意键退出
    JMP START1      ;不退出则重新启动电压转换
QUIT: 
    MOV AH,4CH      ;退出程序
    INT 21H

;电压转换
TRANSFORM PROC NEAR
CHANGE:
    
    MOV SI,OFFSET RESS
    MOV AL,CL
    MOV BL,33H      ;ADC结果范围00H~0FFH, 0~255
                    ;应该除以51(255/51=5), 让量程缩小为0~5V
                    ;同时保留余数, 进而保留精确度

    MOV AH,00H      ;屏蔽高四位AX/BL用不上AH
    DIV BL          
    MOV [SI],AL  ;结果存入RESS及后续地址
    MOV CH,AL       ;CH用于判断是否电压过高
    
    MOV AL,AH       ;对除法的余数进行操作
    MOV BL,10
    MUL BL          ;余数扩大十倍
    MOV BL,33H      ;余数看作55为单位 仍然需要除以51得到该位上的结果
    DIV BL
    MOV [SI+1],AL   ;存入第一位小数
    MOV CL, AL      ;CL用于判断是否电压过低
    
    MOV AL,AH       ;重复扩大余数-除法-保存结果的过高
    MOV BL,10
    MUL BL    
    MOV BL,33H
    DIV BL
    MOV [SI+2],AL   ;存入第二位小数

    MOV AL,AH
    MOV BL,10
    MUL BL    
    MOV BL,33H
    DIV BL
    MOV [SI+3],AL ;2003H存入第三位小数 用于约分
    RET
TRANSFORM ENDP

ALARM PROC NEAR         ;电压报警
    push BX

    CMP CH,4
    JNB OE_
    cmp CH, 0
    JZ OL_
    JMP NORMAL
OE_:
    MOV CL, 0FFH
    CALL XIANG
    JMP WAIT1
OL_:
    cmp CL, 5
    JNB NORMAL
    MOV CL, 0
    CALL XIANG
    JMP WAIT1

NORMAL:             ;正常显示
    MOV DX,OFFSET STR3
    MOV AH,09H
    INT 21H


    MOV DX,MY8255_C     ;8255的C口输出控制数码管
    MOV AL,00000001B    ;低电平控制该位置的数码管可亮
    OUT DX, AL
    MOV DI, [SI]        ;个位数字
    AND DI, 0FFH
    MOV BX, OFFSET ALPHATABLE
    MOV AL, [BX][DI]
    
    OR AL, 10000000B    ;点亮小数点

    MOV DX,MY8255_B     
    OUT DX,AL;数码管输出数
    CALL DELAY

    MOV DX,MY8255_C     ;8255的C口输出控制数码管
    MOV AL,00000010B    ;低电平控制该位置的数码管可亮
    OUT DX,AL
    MOV DI, [SI+1]      ;1位小数
    AND DI, 0FFH
    MOV BX, OFFSET ALPHATABLE
    MOV AL, [BX][DI]

    MOV DX,MY8255_B     
    OUT DX, AL
    CALL DELAY

    MOV DX,MY8255_C     ;8255的C口输出控制数码管
    MOV AL,00000100B    ;低电平控制该位置的数码管可亮
    OUT DX,AL
    MOV DI, [SI+2]      ;2位小数
    AND DI, 0FFH
    MOV BX, OFFSET ALPHATABLE
    MOV AL, [BX][DI]

    CALL DELAY
    ;CALL DELAY

    MOV DX, MY8255_B     
    OUT DX, AL

WAIT1:
    ;CALL DELAY
    pop bx
    RET

ALARM ENDP

XIANG PROC              ;蜂鸣器报警和提示信息显示



    MOV DX,MY8254_MODE  ;8254初始化
    MOV AL,00110110B    ;0号计数器, 读双字节, 3方式工作
    OUT DX,AL

PLAY:

    MOV AX,1000H        ;可改变频率
    MOV DX,MY8254_C0
    OUT DX,AL
    MOV AL,AH
    OUT DX,AL
    ;CALL DELAY

    CMP CL, 0
    JZ OVER_DOWN

OVER_UP:                ;提示电压过高

    MOV DX, OFFSET STR1
    mov AH, 9
    int 21H


    MOV DX,MY8255_C     ;8255的C口输出控制数码管
    MOV AL,00000001B    ;低电平控制该位置的数码管可亮
    ;XOR AL, AL
    OUT DX,AL

    MOV AL,10111111B    ;从B口输出字型代码
    MOV DX,MY8255_B     
    OUT DX,AL
    CALL DELAY
    
    MOV DX,MY8255_C     ;同上, 从C口输出点亮数码管的位码
    MOV AL,00000010B
    OUT DX,AL
    MOV AL,01111001B    ;从B口输出字型代码
    MOV DX,MY8255_B
    OUT DX,AL
    CALL DELAY
    RET

OVER_DOWN:              ;提示电压过低

    MOV DX, OFFSET STR2
    mov AH, 9
    int 21H

    MOV DX,MY8255_C     ;8255的C口输出控制数码管
    MOV AL,00000001B    ;低电平控制该位置的数码管可亮
    OUT DX,AL
    MOV AL,10111111B    ;从B口输出字型代码 字母LO
    MOV DX,MY8255_B     
    OUT DX,AL
    CALL DELAY
    
    MOV DX,MY8255_C     ;同上, 从C口输出点亮数码管的位码
    MOV AL,00000010B
    OUT DX,AL
    MOV AL,00111000B    ;从B口输出字型代码 字母EO
    MOV DX,MY8255_B
    OUT DX,AL
    ;CALL DELAY


    CALL DELAY
    RET
XIANG ENDP

DELAY PROC   ;延时
    PUSH CX
    PUSH AX
    MOV CX,04H
D1: 
    MOV AX,0FFFFH
D2: 
    DEC AX
    JNZ D2
    LOOP D1
    POP AX
    POP CX
    RET
DELAY ENDP
CLEAR:      ;清空显示数字
    MOV DX,MY8255_B         
    MOV AL,00H
    OUT DX,AL
    RET
CODE ENDS
END START

