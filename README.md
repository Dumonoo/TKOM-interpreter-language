# TKOM Interpreter JĘZYKA WALUTOWEGO

## Wymagania:
* gcc version 9.4.0
* cmake version 3.23.0
* połączenie z siecią - do pobrania bibliotek do testowania

**CPP STANDARD 23**
## Budowanie:
```bash
    cd tkom-interpreter-jezyka-walutowego
    mkdir build
    cd build/
    cmake ../CMakeLists.txt
    cmake .
    make
```
Lub za pomocą rozszerzenia w vscode - o wiele szybsze

## Uruchamianie
Po zbudowaniu!
W folderze z plikiem wykonywalnym: tkom-interpreter
```bash
    cd build/
    ./tkom-interpreter nazwa_pliku_do_interpretacji [nazwa glownej funkcji] [opcjonalny plik konfiguracyjny]
```

## Testowanie - Unit testy
Po zbudowaniu!
```bash
    cd build/
    ctest
```