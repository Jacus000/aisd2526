import matplotlib.pyplot as plt
import numpy as np

# Wartości d
d_values = [2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 32, 64, 100, 256, 512, 1000, 2000, 4000, 8000, 12000, 16000]

# Tabela wartości czasu (ms) - wpisz tutaj swoje wartości
# Każda wartość odpowiada wartości d z powyższej listy
czas_ms = [
    # Wpisz wartości czasu w milisekundach dla każdej wartości d:
    14.7185,
    10.7372,
    7.4389,
    7.2914,
    6.2177,
    5.9405    ,
    6.4306    ,
    5.5669   ,
    6.0064  ,
    4.6837  ,
    2.9971  ,
    3.0425  ,
    3.0975 ,
    3.1939  ,
    3.8884  ,
    3.8741,
    2.73,
    2.8782,
    2.6568,
    2.8647,
    3.0797
]

# Tworzenie wykresu
plt.figure(figsize=(12, 6))
plt.plot(d_values, czas_ms, marker='o', linestyle='-', markersize=6)
plt.xlabel('wartość d', fontsize=12)
plt.ylabel('czas (ms)', fontsize=12)
plt.title('Wykres czasu wykonania w zależności od wartości d', fontsize=14)
plt.grid(True, alpha=0.3)
plt.xticks(rotation=45, ha='right')

# Ustawienie skali logarytmicznej dla lepszej czytelności (opcjonalne)
plt.xscale('log')
# plt.yscale('log')  # Odkomentuj jeśli potrzebujesz skali logarytmicznej na osi Y

plt.tight_layout()

# Zapisanie wykresu do pliku
plt.savefig('wykres.png', dpi=300, bbox_inches='tight')
print("Wykres zapisany jako 'wykres.png'")

plt.show()
