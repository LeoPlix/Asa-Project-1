#!/bin/bash

# Script para gerar instâncias e medir tempos de execução
# Complexidade esperada: O(n^3)

# Compilar os programas
echo "Compilando programas..."
cd ..
make clean
make all
cd chart_info

if [ ! -f "../protein_chain" ] || [ ! -f "../generator" ]; then
    echo "Erro: Falha na compilação"
    exit 1
fi

echo ""
echo "Gerando instâncias e medindo tempos de execução..."
echo ""

# Criar diretório para as instâncias
mkdir -p instances

# Tamanhos das instâncias (mais de 10, tamanho incremental)
sizes=(100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000)

# Cabeçalho da tabela
printf "%-10s | %-15s | %-15s\n" "Tamanho" "Tempo (s)" "Tempo (ms)"
printf "%-10s-+-%-15s-+-%-15s\n" "----------" "---------------" "---------------"

# Arquivo para salvar resultados
results_file="benchmark_results.txt"
echo "Resultados do Benchmark - $(date)" > $results_file
echo "" >> $results_file
printf "%-10s | %-15s | %-15s\n" "Tamanho" "Tempo (s)" "Tempo (ms)" >> $results_file
printf "%-10s-+-%-15s-+-%-15s\n" "----------" "---------------" "---------------" >> $results_file

for n in "${sizes[@]}"; do
    # Gerar instância
    instance_file="instances/instance_${n}.txt"
    ../generator $n 100 42 > $instance_file
    
    # Medir tempo de execução usando /usr/bin/time
    time_output=$( { /usr/bin/time -p ../protein_chain < $instance_file > /dev/null; } 2>&1 )
    
    # Extrair tempo real
    elapsed=$(echo "$time_output" | grep "real" | awk '{print $2}')
    elapsed_ms=$(echo "$elapsed * 1000" | bc 2>/dev/null || awk "BEGIN {print $elapsed * 1000}")
    
    # Imprimir resultado
    printf "%-10d | %-15s | %-15s\n" $n "$elapsed" "$elapsed_ms"
    printf "%-10d | %-15s | %-15s\n" $n "$elapsed" "$elapsed_ms" >> $results_file
done

echo ""
echo "Resultados salvos em: $results_file"
echo "Instâncias geradas em: instances/"
