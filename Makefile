# Makefile para Projeto ASA 2025/2026

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall
LDFLAGS = -lm

# Alvos
TARGET = asaProjeto
GERADOR = gerador_p1

# Ficheiros fonte
SRC = asaProjeto.cpp
GERADOR_SRC = gerador_p1.cpp

# Alvo padrão
all: $(TARGET) $(GERADOR)

# Compilar o programa principal
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Compilar o gerador
$(GERADOR): $(GERADOR_SRC)
	$(CXX) $(CXXFLAGS) $(GERADOR_SRC) -o $(GERADOR)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Testar com os exemplos do enunciado
test: $(TARGET)
	@echo "=== Teste Exemplo 1 ==="
	@echo "3\n10 5 12\nABA" | ./$(TARGET)
	@echo "\n=== Teste Exemplo 2 ==="
	@echo "9\n4 2 7 3 5 1 2 8 3\nANBPAPBNA" | ./$(TARGET)

# Limpar ficheiros compilados
clean:
	rm -f $(TARGET) $(GERADOR) *.out *.o

# Limpar tudo incluindo ficheiros temporários
distclean: clean
	rm -f *~ *.swp

# Recompilar tudo
rebuild: clean all

.PHONY: all run test clean distclean rebuild
