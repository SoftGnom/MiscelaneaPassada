.586
.MODEL FLAT, C


; Funcions definides en C
printChar_C PROTO C, value:SDWORD
printInt_C PROTO C, value:SDWORD
clearscreen_C PROTO C
printMenu_C PROTO C
gotoxy_C PROTO C, value:SDWORD, value1: SDWORD
getch_C PROTO C
victory_C PROTO C
printBoard_C PROTO C, value: DWORD
initialPosition_C PROTO C


TECLA_S EQU 115   ;ASCII letra s es el 115


.data          
teclaSalir DB 0




.code   
   
;;Macros que guardan y recuperan de la pila los registros de proposito general de la arquitectura de 32 bits de Intel    
Push_all macro
	
	push eax
   	push ebx
    push ecx
    push edx
    push esi
    push edi
endm


Pop_all macro

	pop edi
   	pop esi
   	pop edx
   	pop ecx
   	pop ebx
   	pop eax
endm
   
   
public C posCurScreen, getMove, moveCursor, moveCursorContinuo, moveTile, playTile, playBlock
                         

extern C opc: SDWORD, row:SDWORD, col: BYTE, carac: BYTE, carac2: BYTE, puzzle: BYTE, indexMat: SDWORD, rowEmpty: SDWORD, colEmpty: BYTE, victory: SDWORD, moves: SDWORD
extern C rowScreen: SDWORD, colScreen: SDWORD, RowScreenIni: SDWORD, ColScreenIni: SDWORD
extern C rowIni: SDWORD, colIni: BYTE, indexMatIni: SDWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Situar el cursor en una fila i una columna de la pantalla
; en funció de la fila i columna indicats per les variables colScreen i rowScreen
; cridant a la funció gotoxy_C.
;
; Variables utilitzades: 
; Cap
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;gotoxy:
gotoxy proc
   push ebp
   mov  ebp, esp
   Push_all

   ; Quan cridem la funció gotoxy_C(int row_num, int col_num) des d'assemblador 
   ; els paràmetres s'han de passar per la pila
      
   mov eax, [colScreen]
   push eax
   mov eax, [rowScreen]
   push eax
   call gotoxy_C
   pop eax
   pop eax 
   
   Pop_all

   mov esp, ebp
   pop ebp
   ret
gotoxy endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Mostrar un caràcter, guardat a la variable carac
; en la pantalla en la posició on està  el cursor,  
; cridant a la funció printChar_C.
; 
; Variables utilitzades: 
; carac : variable on està emmagatzemat el caracter a treure per pantalla
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;printch:
printch proc
   push ebp
   mov  ebp, esp
   ;guardem l'estat dels registres del processador perqué
   ;les funcions de C no mantenen l'estat dels registres.
   
   
   Push_all
   

   ; Quan cridem la funció  printch_C(char c) des d'assemblador, 
   ; el paràmetre (carac) s'ha de passar per la pila.
 
   xor eax,eax
   mov  al, [carac]
   push eax 
   call printChar_C
 
   pop eax
   Pop_all

   mov esp, ebp
   pop ebp
   ret
printch endp
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Llegir un caràcter de teclat   
; cridant a la funció getch_C
; i deixar-lo a la variable carac2.
;
; Variables utilitzades: 
; carac2 : Variable on s'emmagatzema el caracter llegit
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;getch:
getch proc
   push ebp
   mov  ebp, esp
    
   ;push eax
   Push_all

   call getch_C
   
   mov [carac2],al
   
   ;pop eax
   Pop_all

   mov esp, ebp
   pop ebp
   ret
getch endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Posicionar el cursor a la pantalla, dins el tauler, en funció de
; les variables (row) fila (int) i (col) columna (char), a partir dels
; valors de les constants RowScreenIni i ColScreenIni.
; Primer cal convertir el char de la columna (A..D) a un número
; entre 0 i 3, i el int de la fila (1..4) a un número entre 0 i 3.
; Per calcular la posició del cursor a pantalla (rowScreen) i 
; (colScreen) utilitzar aquestes fórmules:
; rowScreen=rowScreenIni+(row*2)
; colScreen=colScreenIni+(col*4)
; Per a posicionar el cursor cridar a la subrutina gotoxy.
;
; Variables utilitzades:	
;	row       : fila per a accedir a la matriu sea
;	col       : columna per a accedir a la matriu sea
;	rowScreen : fila on volem posicionar el cursor a la pantalla.
;	colScreen : columna on volem posicionar el cursor a la pantalla.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;posCurScreen:
posCurScreen proc
    push ebp
	mov  ebp, esp
	Push_all
	mov eax, [row]
	dec eax
	shl eax, 1
	mov ebx, [rowScreenIni]
	add eax, ebx

	mov ecx, 0
	mov cl, [col]
	sub cl, 'A'
	shl cl, 2
	mov edx, [colScreenIni]
	add edx, ecx

	mov [rowScreen], eax
	mov [colScreen], edx

	call gotoxy
	Pop_all
	mov esp, ebp
	pop ebp
	ret

posCurScreen endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Llegir un caràcter de teclat   
; cridant a la subrutina getch
; Verificar que solament es pot introduir valors entre 'i' i 'l', 
; o les tecles espai 'm' o 's' i deixar-lo a la variable carac2.
; 
; Variables utilitzades: 
;	carac2 : Variable on s'emmagatzema el caràcter llegit
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;getMove:
getMove proc
   push ebp
   mov  ebp, esp
   Push_all
getMovebucle:
	call getch
	cmp [carac2], 's'
	je getMovefinal
	cmp [carac2], ' '
	je getMovefinal
	cmp [carac2], 'i'
	jl getMovebucle
	cmp [carac2], 'm'
	jg getMovebucle
getMovefinal:
	Pop_all
   mov esp, ebp
   pop ebp
   ret

getMove endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Calcular l'índex per a accedir a les matrius en assemblador.
; puzzle[row][col] en C, és [puzzle+indexMat] en assemblador.
; on indexMat = row*4 + col (col convertir a número).
;
; Variables utilitzades:	
;	row       : fila per a accedir a la matriu puzzle
;	col       : columna per a accedir a la matriu puzzle
;	indexMat  : índex per a accedir a la matriu puzzle
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;calcIndex: proc endp
calcIndex proc
	push ebp
	mov  ebp, esp
	push_all
	mov edx, 0
	mov eax, [row]
	dec eax
	shl eax, 2
	mov dl, [col]
	sub dl, 'A'
	add eax, edx
	mov [indexMat], eax
	pop_all
	mov esp, ebp
	pop ebp
	ret

calcIndex endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Actualitzar les variables (row) i (col) en funció de 
; la tecla premuda que tenim a la variable (carac2)
; (i: amunt, j:esquerra, k:avall, l:dreta).
; Comprovar que no sortim del taulell, (row) i (col) només poden 
; prendre els valors [1..4] i [A..D]. Si al fer el moviment es surt 
; del tauler, no fer el moviment.
; No posicionar el cursor a la pantalla, es fa a posCurScreenP1.
; 
; Variables utilitzades: 
;	carac2 : caràcter llegit de teclat
;          'i': amunt, 'j':esquerra, 'k':avall, 'l':dreta
;	row : fila del cursor a la matriu puzzle.
;	col : columna del cursor a la matriu puzzle.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveCursor: proc endp
moveCursor proc
   push ebp
   mov  ebp, esp 
   push_all
   cmp[carac2], 'm'
   je fi
   cmp[carac2], 's'
   je fi
   cmp[carac2], 'i'
   je moure_i
   cmp[carac2], 'j'
   je moure_j
   cmp[carac2], 'k'
   je moure_k
   cmp[carac2], 'l'
   je moure_l
   moure_l: cmp[col], 'D'
   je fi
   inc [col]
   jmp fi
   moure_i: cmp[row], 1
   je fi
   dec [row]
   jmp fi
   moure_j: cmp[col], 'A'
   je fi
   dec [col]
   jmp fi
   moure_k: cmp[row], 4
   je fi
   inc [row]
   jmp fi
   fi:
   pop_all
   mov esp, ebp
   pop ebp
   ret

moveCursor endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa el moviment continuo. 
;
; Variables utilitzades: 
;	carac2   : variable on s’emmagatzema el caràcter llegit
;	row      : Fila per a accedir a la matriu puzzle
;	col      : Columna per a accedir a la matriu puzzle
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveCursorContinuo: proc endp
moveCursorContinuo proc
	push ebp
	mov  ebp, esp
	push_all
	crida_moure:
	call getMove
	cmp [carac2], 'm'
	je sortir
	cmp [carac2], 's'
	je sortir
	call moveCursor
	call posCurScreen
	jmp crida_moure
	sortir:
	pop_all
	mov esp, ebp
	pop ebp
	ret

moveCursorContinuo endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Desplaçar una fitxa cap al forat. La fitxa ha desplaçar serà la que
; indiquin les variables (row) i (col) i primerament s'ha de comprovar
; si és una posició vàlida per ser desplaçada. Una posició vàlida vol
; dir que és contigua al forat, sense comptar diagonals. Si no és una
; posició vàlida no fer el moviment.
; També s'ha de desplaçar el forat cap a la casella que s'ha mogut. I
; incrementar la variable moves si el moviment ha estat vàlid.
;
; Variables utilitzades: 
;	carac2 : caràcter llegit de teclat
;          'i': amunt, 'j':esquerra, 'k':avall, 'l':dreta
;	row : fila del cursor a la matriu puzzle.
;	col : columna del cursor a la matriu puzzle.
;	rowEmpty : fila de la casella buida
;	colEmpty : columna de la casella buida
;	puzzle : matriu on es guarda l'estat del joc.
;   moves : enter que guarda el nombre de moviments fets.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveTile:
moveTile proc
	push ebp
	mov  ebp, esp

push_all
mov eax, [row]
mov ebx, 0
mov ecx, [rowEmpty]
mov edx, 0
mov bl, [col]
mov dl, [colEmpty]



sub eax, ecx
cmp eax, 1
je comprovacio_diagonal ;(moure amunt)
cmp eax, -1
je comprovacio_diagonal ;(moure avall)
cmp eax, 0
je comprovacio_horitzontal ;(moure esquerra-dreta)
jmp fi

comprovacio_diagonal: sub bl, dl
cmp bl, 0
je moure
jmp fi

comprovacio_horitzontal: sub bl, dl
cmp bl, 1
je moure
cmp bl, -1
je moure
jmp fi


moure: push row
mov eax, 0
mov al, col
push eax

call calcIndex
mov ESI, [indexMat] ;;guardar index original
mov [row], ecx ;;assignació de rowEmpty a row
mov [col], dl ;;...
call calcIndex
mov EDI, [indexMat] ;;guardar index buit

call posCurScreen
mov al, [puzzle+ESI]
mov [carac], al
mov [puzzle+ESI] ,' ' ;;posar el buit a la posicio original del vector
call printch
mov [puzzle+EDI], al ;;escriure el caracter a la posicio del vector de la buida
mov [carac], ' '

pop ebx
mov col, bl
mov colEmpty, bl
pop ebx
mov row, ebx
mov rowEmpty, ebx
call posCurScreen
call printch
inc moves

fi: pop_all


	mov esp, ebp
	pop ebp
	ret

moveTile endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa el moviment continuo de fitxes. S'ha
; d'utilitzar la tecla 'm' per moure una fitxa i la tecla 's' per
; sortir del joc. 
;
; Variables utilitzades: 
;	carac2   : variable on s’emmagatzema el caràcter llegit
;   victory  : sortir del bule si hi ha victoria (1)
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;playTile:
playTile proc
	push ebp
	mov  ebp, esp
	push_all
	bucleSortir: cmp [carac2], 's'
	je fi
	cmp [carac2], 'm'
	jne cursor
	call moveTile
	call updateMovements
	call checkVictory
	cmp [victory], 1
	je fi
	cursor: call moveCursorContinuo
	jmp bucleSortir
	fi: mov [carac2], ' '


	pop_all
	mov esp, ebp
	pop ebp
	ret

playTile endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
; Comprovar si s'ha guanyat el joc. Es considera una victòria si totes
; les lletres estan ordenades i el forat està al final.
;
; Si es compleixen les condicions de victòria, cridar a la funció victory_C,
; que s'encarrega d'imprimir el missatge de victòria per pantalla.
;
; Variables utilitzades: 
; puzzle : matriu on es guarda l'estat del joc.
; victory: 0 si no s'ha guanyat, i l'heu de posar a 1 si hi ha victoria
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;checkVictory:
checkVictory proc
	push ebp
	mov  ebp, esp
	push_all

	mov al, 'A'
	mov ESI, 0
	inici_CV: cmp ESI, 15
	jge fi_CV
	cmp al, [puzzle+ESI]
	jne  Nfi_CV

	inc ESI
	inc al
	jmp inici_CV
	fi_CV: mov [victory],1
	call victory_C
	Nfi_CV:




	pop_all
	mov esp, ebp
	pop ebp
	ret

checkVictory endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
; Actualitzar el nombre de moviments realitzats, és a dir, imprimir el 
; nou valor de la variable moves.
; Imprimir el nou valor a la posició indicada (rowScreen = 3, colScreen = 57), 
; però s'ha d'imprimir amb dues xifres (amb un zero davant si és menor a 10).
; Per poder dividir saber les dues xifres del número us recomanem usar la 
; instrucció div.
;
; Variables utilitzades: 
; rowScreen : Fila de la pantalla
; colScreen : Columna de la pantalla
; moves : Comptador de moviments
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;updateMovements:
updateMovements proc
	push ebp
	mov  ebp, esp
	push_all
	mov [rowScreen], 2
	mov[colScreen], 58
	call gotoxy
	mov eax, moves
	mov ebx, 10
	mov edx, 0
	div ebx
	add eax, '0'
	add edx, '0'
	mov [carac], al
	call printch
	mov [carac], dl
	call printch
	call posCurScreen

	pop_all
	mov esp, ebp
	pop ebp
	ret

updateMovements endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Desplaçar una fitxa o un bloc de fitxes cap al forat. 
; L'inici del bloc de fitxes a desplaçar l'indicaran les variables 
; (row) i (col). I el final quedarà implícit pel forat. S'ha de 
; comprovar que el bloc de fitxes estigui tot el "línea" i acabi 
; en el forat. Si només es tracta d'una fitxa només s'ha de comprovar 
; que estigui contigua al forat, no diagonalment.
; Al moure el bloc cap a direcció el forat, el forat es desplacà a la
; fitxa inicial i el bloc es desplaçarà una posició cap on estava el 
; forat. En el cas d'una sola fitxa, només s'han d'intercanviar el
; forat i la fitxa.
; Si les condicions no es compleixen no es farà cap moviment.
; S'ha d'incrementar la variable moves si el moviment ha estat vàlid,
; sempre s'incrementa només en un els moviments encara que es moguin
; més d'una fitxa.
;
; Variables utilitzades: 
;   carac2 : caràcter llegit de teclat
;          'i': amunt, 'j':esquerra, 'k':avall, 'l':dreta
;   row : fila del cursor a la matriu puzzle.
;   col : columna del cursor a la matriu puzzle.
;   rowEmpty : fila de la casella buida
;   colEmpty : columna de la casella buida
;   puzzle : matriu on es guarda l'estat del joc.
;   moves : enter que guarda el nombre de moviments fets.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveBlock:
moveBlock proc
	push ebp
	mov  ebp, esp

	push_all
mov eax, [row]
mov ebx, 0
mov ecx, [rowEmpty]
mov edx, 0
mov bl, [col]
mov dl, [colEmpty]



sub ebx, edx
mov edx, 0
sub eax, ecx
mov ecx, 0
cmp eax, 0
je comprovacio_horitzontal ;(moure esquerra-dreta)

cmp eax,1
jge comprovacio_diagonal_block_1 ;; comprovaacio adalt
cmp eax, -1
jle comprovacio_diagonal_block_2 ;; comprovacio abaix
jmp fi

comprovacio_diagonal_block_1:
mov edx, 1
jmp comprovacio_diagonal_block

comprovacio_diagonal_block_2: 
mov edx, -1

comprovacio_diagonal_block:
cmp bl, 0 ;; comprova q no esta a la diagonal
je moure
jmp fi

comprovacio_horitzontal: ;;tots els casos hortizontals
cmp bl, 1
jge comprovacio_horitzontal_block_1 ;; comprovacio dreta
cmp bl, -1
jle comprovacio_horitzontal_block_2 ;; comprovacio esquerra
jmp fi

comprovacio_horitzontal_block_1:
mov ecx, 1
jmp moure
comprovacio_horitzontal_block_2:
mov ecx, -1
jmp moure

moure:

cmp eax, 0
je assignacioColumna

assignacioFila: mov ESI, eax ;;diferencia de files
mov eax, 0
jmp moureBloc

assignacioColumna: mov ESI, ebx ;;diferencia de columnes
mov ebx, 0


;;assignar a ESI la diferencia entre files o columnes +-1
moureBloc: cmp ESI, 0
je final
mov eax, [rowEmpty]
mov [row], eax
mov al, [colEmpty]
mov [col], al
cmp edx, 1
je bucle_amunt
cmp edx, -1
je bucle_abaix
cmp ecx, 1
je bucle_dreta
cmp ecx, -1
je bucle_esquerra
jmp fi


bucle_amunt:
cmp ESI, 0
je final
mov eax, row
add eax, 1
mov [row], eax
call moveTile
dec moves
dec ESI
jmp bucle_amunt

bucle_abaix:
cmp ESI, 0
je final
mov eax, row
sub eax, 1
mov [row], eax
call moveTile
dec moves
inc ESI
jmp bucle_abaix

bucle_dreta:
cmp ESI, 0
je final
mov al, col
add eax, 1
mov [col], al
call moveTile
dec moves
dec ESI
jmp bucle_dreta

bucle_esquerra:
cmp ESI, 0
je final
mov al, col
add eax, -1
mov [col], al
call moveTile
dec moves
inc ESI
jmp bucle_esquerra

final:inc moves
fi: 
	pop_all


	mov esp, ebp
	pop ebp
	ret


	mov esp, ebp
	pop ebp
	ret

moveBlock endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa el moviment continuo de blocs. S'ha
; d'utilitzar la tecla 'm' per moure una fitxa i la tecla 's' per
; sortir del joc. 
;
; Variables utilitzades: 
;	carac2   : variable on s’emmagatzema el caràcter llegit
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;playBlock:
playBlock proc
	push ebp
	mov  ebp, esp

	push_all
	bucleSortir: cmp [carac2], 's'
	je fi
	cmp [carac2], 'm'
	jne cursor
	call moveBlock
	call updateMovements
	call checkVictory
	cmp [victory], 1
	je fi
	cursor: call moveCursorContinuo
	jmp bucleSortir
	fi: mov [carac2], ' '


	pop_all

	mov esp, ebp
	pop ebp
	ret

playBlock endp

END