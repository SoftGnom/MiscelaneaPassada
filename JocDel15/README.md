# Joc del 15


### 1. Descripció del Projecte

Aquest projecte implementa una versió del joc del 15 utilitzant el llenguatge Assembly per a l'arquitectura Intel x86. L'objectiu del joc és ordenar les peces dins d'un taulell de 4x4 a partir d'una posició inicial desordenada.

### 2. Objectius

Desenvolupar habilitats en programació en llenguatge Assembly.

Aplicar coneixements d'arquitectura de computadors i gestió de memòria.

Implementar algorismes d'interacció amb l'usuari per a la resolució del joc.


### 3. Requisits del Sistema

Entorn de desenvolupament: Microsoft Visual Studio 2019 Community

Arquitectura: Intel x86

Llenguatge: Assembly i C

### 4. Controls del Joc

i → Moure amunt

k → Moure avall

j → Moure esquerra

l → Moure dreta

m → Moure una fitxa

s → Sortir

### 6. Funcions Principals

📌 main_*.cpp

Els fitxers main_Basic.cpp, main_Mig.cpp i main_Avançat.cpp són els programes principals que gestionen la interacció de l'usuari i criden les funcions d'Assembly.

Exemples de crides a subrutines ASM:

posCurScreen(): Posiciona el cursor.

getMove(): Llegeix una tecla i valida el moviment.

moveCursor(): Mou el cursor segons la tecla premuda.

moveTile(): Mou una fitxa cap al forat.

playTile(): Implementa el moviment continu de fitxes.

playBlock(): Gestiona el moviment de blocs fins a la victòria.

📌 prac_Basic.asm

posCurScreen: Posiciona el cursor.

getMove: Llegeix una tecla i valida el moviment.

moveCursor: Mou el cursor segons la tecla premuda.

moveTile: Mou una fitxa cap al forat.

📌 prac_Mig.asm

playTile: Implementa el moviment continu de fitxes.

checkVictory: Comprova si s’ha guanyat el joc.

updateMovements: Actualitza el comptador de moviments.

📌 prac_Avançat.asm

moveBlock: Implementa el moviment de blocs de fitxes.

playBlock: Gestiona el moviment de blocs fins a la victòria.
