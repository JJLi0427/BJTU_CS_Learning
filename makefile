all:run clean # make 编译并运行exp1.c和exp2.c, 然后清理生成文件

exp1:exp1.c # make exp1 只编译运行exp1.c
	gcc -o exp1 exp1.c
	@echo.
	./exp1

exp2:exp2.c # make exp2 只编译运行exp2.c
	gcc -o exp2 exp2.c
	@echo.
	./exp2

run: exp1.c exp2.c # make run 编译运行exp1.c和exp2.c
	gcc -o exp1 exp1.c
	gcc -o exp2 exp2.c
	@echo.
	./exp1
	@echo.
	./exp2
	@echo.

.PHONY: clean # make clean 清理生成文件
clean:
	del *.exe