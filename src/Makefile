.PHONY: all install uninstall clean dvi dist tests cpplint cppcheck leaks gcov_report rebuild

CC = g++
LDFLAGS =  -Wall -Wextra -Werror -std=c++17  -std=c++17

GCOV_FLAG = -fprofile-arcs -ftest-coverage 

TARGET = tests
CFILES= tests.cpp model.cpp  model_object.cpp controller.cpp
OFILES=$(CFILES:.cpp=.o)

QDIR= SmartCalc
DDIR= SmartCalc_2.0

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

default: rebuild

rebuild: clean all

check: cpplint cppcheck gcov_report

all: $(TARGET) 

$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(GCOV_FLAG) $(OFILES) -o $(TARGET) $(LIBFLAGS)
	./$(TARGET)

%.o: %.cpp
	$(CC) -c $(LDFLAGS) $(GCOV_FLAG)  $<

gcov_report: $(TARGET)
	lcov --no-external -t "$(TARGET)" -o $(TARGET).info -c -d ./
	genhtml -o report $(TARGET).info
ifneq ($(OS), Linux)
	open report/index.html
endif

cpplint:
	cp ../materials/linters/.clang-format . 
	clang-format -i *.cpp *.h
	clang-format -n *.cpp *.h


cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --std=c++17 *.h *.cpp
	cppcheck --enable=all --force  --suppress=unusedFunction --suppress=missingInclude --suppress=unknownMacro:{} --suppress=unusedStructMember:{}  --suppress=unmatchedSuppression:{} --language=c++ --std=c++17 ./credit_calc/*.h ./credit_calc/*.cpp

clean:
	rm -f *.o *.a *.gcno *.gcda *.info a.out $(TARGET)
	rm -rf report/
	rm -f .clang-format
	rm -f qt/.clang-format
	rm -f credit_calc/.clang-format
	rm -rf build*
	rm -rf manual/

leaks:
ifeq ($(OS), Linux)
	CK_FORK=no valgrind  --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TARGET)
else
	CK_FORK=no leaks -atExit -- ./$(TARGET)
endif
# valgrind  --quiet

install:
	mkdir $(QDIR)
	cd $(QDIR); qmake ../qt/s21_smart_calc.pro
	cd $(QDIR); make
	cd $(QDIR); make clean
ifneq ($(OS), Linux)
	open SmartCalc 
endif	

uninstall: 
	rm -r $(QDIR)

dist:
	mkdir $(DDIR)
	cp *.cpp *.h Makefile $(DDIR)	
	cp -R qt $(DDIR)
	tar --totals -cvf $(DDIR).tar $(DDIR)
	rm -rf $(DDIR)

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html