RM = rm -f
EXE =
SPACE = echo ""

ifeq ($(OS),Windows_NT) # 识别操作系统
	RM = del /Q
	EXE = .exe
	SPACE = @echo.
endif

%: %.c # make exp_.c 只编译运行指定的exp_.c
	gcc -o $@ $<
	$(SPACE)
	./$@$(EXE)
	$(SPACE)
	$(RM) $@$(EXE)

run2: exp1.c exp2.c # make run2 顺序编译运行exp1.c和exp2.c
	gcc -o exp1 exp1.c
	gcc -o exp2 exp2.c
	$(SPACE)
	./exp1
	$(SPACE)
	./exp2
	$(SPACE)
	$(RM) exp1$(EXE)
	$(RM) exp2$(EXE)

run3: exp1.c exp3.c # make run3 顺序编译运行exp1.c和exp3.c
	gcc -o exp1 exp1.c
	gcc -o exp3 exp3.c
	$(SPACE)
	./exp1
	$(SPACE)
	./exp3
	$(SPACE)
	$(RM) exp1$(EXE)
	$(RM) exp3$(EXE)