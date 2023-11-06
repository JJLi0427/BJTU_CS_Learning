RM = rm -f
EXE =
SPACE = echo ""

ifeq ($(OS),Windows_NT) # 识别操作系统
	RM = del /Q
	EXE = .exe
	SPACE = @echo.
endif

%: %.c # make _.c 只编译运行指定的_.c
	gcc -o $@ $<
	$(SPACE)
	./$@$(EXE)
	$(SPACE)
	$(RM) $@$(EXE)

all: exp1.c exp2.c # make 顺序编译运行exp1.c和exp2.c
	gcc -o exp1 exp1.c
	gcc -o exp2 exp2.c
	$(SPACE)
	./exp1
	$(SPACE)
	./exp2
	$(SPACE)
	$(RM) *$(EXE)