```
ISI 1 k., 1-1, Arnas Martinkus
```
<h1 align="center" id="title">Studentų pažymių skaičiavimas</h1>

<h2>Projekto screenshot:</h2>

![Screenshot 2024-04-24 202446](https://github.com/ArnasIc3/Objektinis-programavimas/assets/149010264/c41931d3-a27a-45d2-995a-d52612d964e4)

<h2>🛠️ Setup:</h2>

<p>1. Download VSCode:</p>

```
https://code.visualstudio.com
```

<p>2. Download CMake and other needed programs:</p>

```
https://cmake.org/download/
```

```
TDM-GCC 64+32 BIT: https://jmeubank.github.io/tdm-gcc/articles/2021-05/10.3.0-release
```

```
NINJA-BUILD: https://github.com/ninja-build/ninja/releases/v1.12.0
```

<p>3. Setup:</p>

```
Install CMake.exe file. (MAKE SURE TO ADD PATH TO ALL USERS)
```

```
Insert ninja into this directorty: C:\Program Files\CMake\bin
```

```
Run TDM-GCC.
```

```
CREATE -> MinGW -w64/TDM64 (32-BIT AND 64-BIT)
```

```
Instalation directory: C:\TDM-GCC-64
```

```
Complete the instalation.
```

<p>4. Extensions in VSCode:</p>

```
CMake Tools
```

```
C/C++ Extension Pack
```

<p>5. DONE</p>

<h2>❗Visų release'ų aprašymai: </h2>
<p> v.pradine - vardų, pavardžių, pažymių ir egzamino įvedimas ranka. 
  Galutinio vidurkio skaičiavimas formule: 0.4*vidurkis + 0.6*egzaminas.
  Medianos kaip galutinės išvedimo elemento pasirinkimas.</p>
<p> v0.1 - veikia su iš anksto nežinomu n skačiumi studentų.
Sukurti du failai: vienas su C masyvų, kitas naudojant vector container'į.
Pridėtas atsitiktinių vardų, pavardžių, pažymių generacija.</p>
<p> v0.2 - skaitymas iš failo kursiokai.txt.
Rūšiavimas pagal pasirinktą elementą: vardą, pavardę ar galutinį pažymį.
Atliktas testavimas su iš anksto sugeneruotais failais.</p>
<p> v0.3 - pataisyta ir tikslingai naudojamas struct.
Implementuoti header ir cpp failai.
Išimčių valdymas su try catch funkcija.</p>
<p> v0.4 - failų generavimas nuo 1000 - 100000 su šabloniniais vardais ir pavardėm.
Surušiuota studentus į dvi grupes: galvočiai ir nuskriaustukai. Atlikta spartos analizė.
Pridėtas menu, sumažintas main.cpp failo ilgis. </p>
<p> v1.0 - realizuota naudojant tris skirtingus konteinerius (trys skirtingi folder'iai).
Bandyta optimizuoti rūšiavimą ir dvi grupes t.y. galvočiai ir nuskriaustukai.
Realizuotos 3 strategijos: 
    1 - orginalioji padalinant į dvi grupes skaitant nuo failo.
    2 - vargšiukų išrašymas į kitą failą ir kitus paliekant orginaliame faile. 
    3 - taikant algoritmus pagreitintas veikimas.
Sūkurtas CMakelists.txt failas kuris leidžia sukompeliuoti tinkamai kodą per VSCode ir buvo pereita prie šio IDE.
</p>

<h1>💣 1.0 TESTAVIMAI: </h1>
<p>Testavimai atliekami ant:</p>

```
AMD Ryzen 5 5600H 3.30GHz
```
```
16GB 3200MHz
```
```
NVIDIA GeForce RTX 3050 Laptop GPU
```
## Su VECTOR konteineriu:
### Vector 1-a strategija: ###

|Dydis|Sorting|Output|
|---|---|---|
|1000|0.004|0.005| 
|10000|0.03|0.034| 
|100000|0.3|0.336| 
|1000000|3.646|3.434| 
|10000000|34.906|33.046| 

### Vector 2-a strategija: ###

| Dydis | Sorting | Output |
| --- | --- | --- |
| 1000 | 0.004 | 0.002 | 
| 10000 | 0.029 | 0.017 | 
| 100000 | 0.282 | 0.282 | 
| 1000000 | 2.924 | 1.741 | 
| 10000000 | 30.025 | 16.998 | 

### Vector 3-a strategija: ###

| Dydis | Read | Sorting | Output |
| --- | --- | --- | --- |
| 1000 | 0.003 | 0.0000 | 0.007 |
| 10000 | 0.04 | 0.012 | 0.3 |
| 100000 | 0.3 | 0.095 | 3.211 |
| 1000000 | 3.211 | 0.268 | 0.997 |
| 10000000 | 31.96 | 3.445 | 9.752 | 



## Su LIST konteineriu:

### List 1-a strategija: ###

| Dydis | Sorting | Output |
| --- | --- | --- |
| 1000 | 0.008 | 0.004 | 
| 10000 | 0.046 | 0.034 | 
| 100000 | 0.677 | 0.378 | 
| 1000000 | 6.826 |  3.602 | 
| 10000000 | 68.091 | 35.743 | 

### List 2-a strategija: ###

| Dydis | Sorting | Output |
| --- | --- |  --- |
| 1000 | 0.003 | 0.002 | 
| 10000 | 0.033 | 0.017 | 
| 100000 | 0.294 | 0.17 | 
| 1000000 | 2.958 | 1.72 | 
| 10000000 | 28.89 | 17.443 | 

### List 3-a strategija: ###

| Dydis | Read | Sorting | Output |
| --- | --- |  ---  | --- |
| 1000 | 0.003 | 0.0000 | 0.001 |
| 10000 | 0.03 | 0.004 | 0.01 |
| 100000 | 0.297 | 0.034 | 0.095 |
| 1000000 | 3.163 | 0.371 | 0.997 |
| 10000000 | 32.308 | 3.697 | 10.305 | 


## Su DEQUE konteineriu:
### Deque 1-a strategija: ###

| Dydis | Sorting | Output |
| --- | --- |  --- |
| 1000 | 0.009 | 0.005 | 
| 10000 | 0.066 | 0.034 | 
| 100000 | 0.656 | 0.344 | 
| 1000000 | 6.79 |  3.506 | 
| 10000000 | 66.599 | 34.606 | 

### Deque 2-a strategija: ###

| Dydis | Sorting | Output |
| --- | --- | --- |
| 1000 | 0.003 | 0.002 | 
| 10000 | 0.032 | 0.017 | 
| 100000 | 0.285 | 0.174 | 
| 1000000 | 2.978 | 1.688 | 
| 10000000 | 29.647 | 17.286 | 

### Deque 3-a strategija: ###

| Dydis | Read | Sorting | Output |
| --- | --- |  ---  | --- |
| 1000 | 0.004 | 0.0000 | 0.001 |
| 10000 | 0.032 | 0.001 | 0.01 |
| 100000 | 0.305 | 0.029 | 0.107 |
| 1000000 | 3.182 | 0.266 | 0.989 |
| 10000000 | 35.24 | 3.309 | 10.751 | 
