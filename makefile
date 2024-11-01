DED_FLAGS=-Wall -Wextra -Weffc++ -Wcast-align -Wcast-qual -Iinclude -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-security -Wformat=2 -Wignored-qualifiers -Winit-self -Winline -Wlogical-op -Wmain -Wmissing-declarations -Wno-missing-field-initializers -Wmissing-include-dirs -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wswitch-default -Wswitch-enum -Wtype-limits -Wundef -Wunreachable-code -Wwrite-strings -fexceptions -g -pipe -D_DEBUG -D_EJUDGE_CLIENT_SIDE -D_EJC

ASM_EXE_NAME=Assemblerer
PROC_EXE_NAME=Processor
dASM_EXE_NAME=disAssembler

com_build_dir=common/Build/
asm_build_dir=Assembler/Build/
prc_build_dir=Processor/Build/
dasm_build_dir=disAssembler/Build/

common_src_prefix=common/src/
asm_src_prefix=Assembler/src/
prc_src_prefix=Processor/src/
dasm_src_prefix=disAssembler/src/

LIB= -L Stack/StackLibrary -lStackFuncs

COM_SRC= $(addprefix $(common_src_prefix), SPUStructFuncs.cpp)
COM_OBJ= $(addprefix $(common_src_prefix), SPUStructFuncs.o)

ASM_SRC= $(addprefix $(asm_src_prefix), main.cpp Assembler.cpp AsmStructFuncs.cpp TextProcessing.cpp) $(COM_SRC)
ASM_OBJ= $(addprefix $(asm_build_dir), main.o Assembler.o AsmStructFuncs.o TextProcessing.o) $(COM_OBJ)

PRC_SRC= $(addprefix $(prc_src_prefix_src_prefix), main.cpp Run.cpp CommandsRead.cpp) $(COM_SRC)
PRC_OBJ= $(addprefix $(prc_build_dir),  main.o Run.o CommandsRead.o) $(COM_OBJ)

dASM_SRC= $(addprefix $(dasm_src_prefix), main.cpp disAssembler.cpp CommandsRead.cpp) $(COM_SRC)
dASM_OBJ= $(addprefix $(dasm_build_dir), main.o disAssembler.o CommandsRead.o) $(COM_OBJ)

all: prepare assembler processor disassembler


prepare:
	cd Stack && make lib

assembler: $(ASM_EXE_NAME)

$(ASM_EXE_NAME): $(ASM_OBJ) $(COM_OBJ)
	@echo "[LD] Linking"
	@g++ $(ASM_OBJ) $(COM_OBJ) ${DED_FLAGS} ${LIB} -o $(ASM_EXE_NAME) 

$(asm_build_dir)%.o: $(asm_src_prefix)%.cpp
	@echo "[CXX] $@"
	@g++ -c $^ ${DED_FLAGS} -o $@

$(com_build_dir)%.o: $(com_src_prefix)%.cpp
	@echo "[CXX] $@"
	@g++ -c $^ ${DED_FLAGS} -o $@

clean:
	rm -rf *.exe $(asm_build_dir)*.o $(prc_build_dir)*.o $(dasm_build_dir)*.o






