CXX = g++
LDFLAGS = -lpthread
RM = rm -f
EXE =
SPACE = echo ""

ifeq ($(OS),Windows_NT)
	RM = del /Q
	EXE = .exe
	SPACE = @echo.
endif

%: %.cpp
	$(CXX) -o $@ $< $(LDFLAGS)
	$(SPACE)
	./$@$(EXE)
	$(SPACE)
	$(RM) $@$(EXE)