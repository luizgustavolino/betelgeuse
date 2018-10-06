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
LDFLAGS = -lz -lallegro -lallegro_image -lallegro_dialog

# Pasta onde fica o fonte do jogo e
# nome do executável final
SOURCE_FOLDER = ../../game
TARGET = beteugeuse

# Arquivos para compilação: tudo que é .c na pasta
# do jogo
OBJECTS = $(shell find $(SOURCE_FOLDER) -name '*.c')

# alvo default: gera o target, com o nome escolhido
# primeiro ele chama clean: apaga a versão antiga
# depois chama o target, que gera o executável
# depois copia os assets para a pasta local
all: clean $(TARGET) copy_assets

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

# diretriz para arquivos '.c' -> compilar e gerar o '.o'
# que vai para o LD
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

copy_assets:
	rsync -rpE ../../game/assets .

.PHONY: copy_assets

clean:
	rm -f $(TARGET)
	rm -rf assets
