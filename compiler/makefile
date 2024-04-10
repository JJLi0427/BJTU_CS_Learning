CC = gcc
CFLAGS = -Wall -g
RM = rm -f
EXE =
SPACE = echo ""

ifeq ($(OS),Windows_NT)
	RM = del /Q
	EXE = .exe
	SPACE = @echo.
endif

%: %.c
	$(CC) $(CFLAGS) $< -o $@
	$(SPACE)
	./$@$(EXE)
	$(SPACE)
	$(RM) $@$(EXE)
	$(SPACE)

run2: exp1 exp2

run3: exp1 exp3

run4: exp1 exp4

run5: exp1 exp5

.PHONY: run2 run3 run4 run5
