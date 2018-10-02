# Compilador será o GCC
CC = gcc

# Flags do compilador:
#  -c: compilar, mas sem o linker ainda
#  -Wall: habilita todos warnings
#  -g: incluir informações extras de debug
#  -O2: otimizações no código, sem perda de performance
CFLAGS = -c -Wall -g -O2

# LD é o Linker, vamos utilizar o mesmo que
# o compiler. LD flags são as libs incluidas
LD = $(CC)
LDFLAGS = -lz

# Pasta onde fica o fonte do jogo e
# nome do executável final
SOURCE_FOLDER = ../../game
TARGET = beteugeuse

# Arquivos para compilação: tudo que é .c na pasta
# do jogo
OBJECTS = $(shell find $(SOURCE_FOLDER) -name '*.c')

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

# You don't even need to be explicit here,
# compiling C files is handled automagically by Make.
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(TARGET) $(OBJECTS)