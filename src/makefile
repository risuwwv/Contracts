
COMMON_RELEASE= -march=native -O3 -DNDEBUG

COMMON=-std=c++14 -Werror -Wshadow

CLANG_COMMONS=$(COMMON) -Wno-c++98-compat -Wno-used-but-marked-unused -Wno-padded

CLANG_RELEASE=$(COMMON_RELEASE) $(CLANG_COMMONS)

GCC_COMMONS=$(COMMON) -Wall -Wpedantic -Wextra -Wshadow -Wabi -Wcomment -Wcast-align -Wcast-qual -Wchar-subscripts -Wctor-dtor-privacy -Wdisabled-optimization -Weffc++ -Wempty-body -Wfloat-equal -Wformat-nonliteral \
-Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wmissing-declarations -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs \
-Wmissing-noreturn -Wodr -Wold-style-cast -Woverlength-strings -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wsign-compare -Wsign-conversion -Wsign-promo \
-Wstack-protector -Wswitch-default -Wswitch-enum -Wtype-limits -Wundef -Wunreachable-code -Wunused-parameter -Wvariadic-macros -Wwrite-strings \
-pedantic-errors -Wno-unused -Wno-error=inline -Wformat=2 -Wstrict-aliasing=2 -Wuseless-cast -Wzero-as-null-pointer-constant -Wlogical-op -Wnoexcept \
-Wstrict-null-sentinel -fdiagnostics-color=always -Wno-missing-declarations

GCC_RELEASE=$(COMMON_RELEASE) $(GCC_COMMONS) -flto -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno 

CLANG_DEBUG=-g -O0 $(CLANG_COMMONS)
GCC_DEBUG= -g -O0 $(GCC_COMMONS)

#compiler choice
ifeq ($(compiler),gcc)
	ifeq ($(mode),debug)
		FLAGS=$(GCC_DEBUG)
	else
		FLAGS=$(GCC_RELEASE)
	endif
	CC=g++
else
	ifeq ($(mode),debug)
		FLAGS=$(CLANG_DEBUG)
	else
		FLAGS=$(CLANG_RELEASE)
	endif
	CC=clang++
endif

#windows extension
ifdef SystemRoot
	TARGET_EXT=.exe
endif

ifeq ($(checks),true)
CHECKS = -DCHECK_CONDITIONS
endif

all:
	$(CC) -o test$(TARGET_EXT) test.cpp $(FLAGS) $(CHECKS)	

help:
	@echo Supported compilers are "clang" and "gcc"
	@echo Supported modes are "release" and "debug"
	@echo Set "checks" to true to enable the checks.
	@echo example: "make mode=release compiler=gcc checks=true"
	@echo example: "make mode=debug compiler=clang checks=true"
	
clean:
	del test.exe 2> nul	