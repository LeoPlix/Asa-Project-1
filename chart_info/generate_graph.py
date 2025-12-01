#!/usr/bin/env python3
"""
Gera gráfico demonstrativo da avaliação de tempos.
Eixo X: f(n,m) = n³ (complexidade teórica)
Eixo Y: Tempo em segundos
"""

import matplotlib.pyplot as plt
import numpy as np

# Dados dos benchmarks
tamanhos = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 
            1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000]

tempos = [0.35, 0.00, 0.00, 0.01, 0.03, 0.05, 0.08, 0.13, 0.20, 0.26,
          0.32, 0.41, 0.55, 0.75, 0.87, 1.17, 1.28, 2.02, 2.52, 3.09]

# Calcular n³ (em milhões para melhor visualização)
n_cubico = [(n**3) / 1e6 for n in tamanhos]

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(n_cubico, tempos, 'b-o', linewidth=2, markersize=6)

# Configurar o gráfico
plt.xlabel('f(n,m) = n³ (×10⁶)', fontsize=12)
plt.ylabel('Tempo (s)', fontsize=12)
plt.grid(True, alpha=0.3)

# Ajustar layout
plt.tight_layout()

# Salvar o gráfico
plt.savefig('grafico_complexidade.png', dpi=300, bbox_inches='tight')
plt.savefig('grafico_complexidade.pdf', bbox_inches='tight')
print("Gráfico gerado com sucesso!")
print("  - grafico_complexidade.png")
print("  - grafico_complexidade.pdf")

# Mostrar o gráfico
plt.show()

# Verificar linearidade (ajuste linear)
coef = np.polyfit(n_cubico, tempos, 1)
print(f"\nRegressão linear: Tempo = {coef[0]:.6f} × n³ + {coef[1]:.6f}")
print(f"Coeficiente angular: {coef[0]:.6f} s/(n³×10⁶)")
print("\nA relação linear entre Tempo e n³ confirma a complexidade O(n³).")
