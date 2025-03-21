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
; Situar el cursor en una fila i una columna de la pantalla
; en funci� de la fila i columna indicats per les variables colScreen i rowScreen
; cridant a la funci� gotoxy_C.
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

   ; Quan cridem la funci� gotoxy_C(int row_num, int col_num) des d'assemblador 
   ; els par�metres s'han de passar per la pila
      
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
; Mostrar un car�cter, guardat a la variable carac
; en la pantalla en la posici� on est� el cursor,  
; cridant a la funci� printChar_C.
; 
; Variables utilitzades: 
; carac : variable on est� emmagatzemat el caracter a treure per pantalla
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;printch:
printch proc
   push ebp
   mov  ebp, esp
   ;guardem l'estat dels registres del processador perqu�
   ;les funcions de C no mantenen l'estat dels registres.
   
   
   Push_all
   

   ; Quan cridem la funci�  printch_C(char c) des d'assemblador, 
   ; el par�metre (carac) s'ha de passar per la pila.
 
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
; Llegir un car�cter de teclat   
; cridant a la funci� getch_C
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
; Posicionar el cursor a la pantalla, dins el tauler, en funci� de
; les variables (row) fila (int) i (col) columna (char), a partir dels
; valors de les constants RowScreenIni i ColScreenIni.
; Primer cal convertir el char de la columna (A..D) a un n�mero
; entre 0 i 3, i el int de la fila (1..4) a un n�mero entre 0 i 3.
; Per calcular la posici� del cursor a pantalla (rowScreen) i 
; (colScreen) utilitzar aquestes f�rmules:
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


	mov esp, ebp
	pop ebp
	ret

posCurScreen endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Llegir un car�cter de teclat   
; cridant a la subrutina getch
; Verificar que solament es pot introduir valors entre 'i' i 'l', 
; o les tecles espai 'm' o 's' i deixar-lo a la variable carac2.
; 
; Variables utilitzades: 
;	carac2 : Variable on s'emmagatzema el car�cter llegit
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;getMove:
getMove proc
   push ebp
   mov  ebp, esp


   mov esp, ebp
   pop ebp
   ret

getMove endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Calcular l'�ndex per a accedir a les matrius en assemblador.
; puzzle[row][col] en C, �s [puzzle+indexMat] en assemblador.
; on indexMat = row*4 + col (col convertir a n�mero).
;
; Variables utilitzades:	
;	row       : fila per a accedir a la matriu puzzle
;	col       : columna per a accedir a la matriu puzzle
;	indexMat  : �ndex per a accedir a la matriu puzzle
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;calcIndex: proc endp
calcIndex proc
	push ebp
	mov  ebp, esp
	

	mov esp, ebp
	pop ebp
	ret

calcIndex endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Actualitzar les variables (row) i (col) en funci� de 
; la tecla premuda que tenim a la variable (carac2)
; (i: amunt, j:esquerra, k:avall, l:dreta).
; Comprovar que no sortim del taulell, (row) i (col) nom�s poden 
; prendre els valors [1..4] i [A..D]. Si al fer el moviment es surt 
; del tauler, no fer el moviment.
; No posicionar el cursor a la pantalla, es fa a posCurScreenP1.
; 
; Variables utilitzades: 
;	carac2 : car�cter llegit de teclat
;          'i': amunt, 'j':esquerra, 'k':avall, 'l':dreta
;	row : fila del cursor a la matriu puzzle.
;	col : columna del cursor a la matriu puzzle.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveCursor: proc endp
moveCursor proc
   push ebp
   mov  ebp, esp 


   mov esp, ebp
   pop ebp
   ret

moveCursor endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa el moviment continuo. 
;
; Variables utilitzades: 
;	carac2   : variable on s�emmagatzema el car�cter llegit
;	row      : Fila per a accedir a la matriu puzzle
;	col      : Columna per a accedir a la matriu puzzle
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;moveCursorContinuo: proc endp
moveCursorContinuo proc
	push ebp
	mov  ebp, esp


	mov esp, ebp
	pop ebp
	ret

moveCursorContinuo endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Despla�ar una fitxa cap al forat. La fitxa ha despla�ar ser� la que
; indiquin les variables (row) i (col) i primerament s'ha de comprovar
; si �s una posici� v�lida per ser despla�ada. Una posici� v�lida vol
; dir que �s contigua al forat, sense comptar diagonals. Si no �s una
; posici� v�lida no fer el moviment.
; Tamb� s'ha de despla�ar el forat cap a la casella que s'ha mogut. I
; incrementar la variable moves si el moviment ha estat v�lid.
;
; Variables utilitzades: 
;	carac2 : car�cter llegit de teclat
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
;	carac2   : variable on s�emmagatzema el car�cter llegit
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;playTile:
playTile proc
	push ebp
	mov  ebp, esp


	mov esp, ebp
	pop ebp
	ret

playTile endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
; Comprovar si s'ha guanyat el joc. Es considera una vict�ria si totes
; les lletres estan ordenades i el forat est� al final.
;
; Si es compleixen les condicions de vict�ria, cridar a la funci� victory_C,
; que s'encarrega d'imprimir el missatge de vict�ria per pantalla.
;
; Variables utilitzades: 
; puzzle : matriu on es guarda l'estat del joc.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;checkVictory:
checkVictory proc
	push ebp
	mov  ebp, esp


	mov esp, ebp
	pop ebp
	ret

checkVictory endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
; Actualitzar el nombre de moviments realitzats, �s a dir, imprimir el 
; nou valor de la variable moves.
; Imprimir el nou valor a la posici� indicada (rowScreen = 3, colScreen = 57), 
; per� s'ha d'imprimir amb dues xifres (amb un zero davant si �s menor a 10).
; Per poder dividir saber les dues xifres del n�mero us recomanem usar la 
; instrucci� div.
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


	mov esp, ebp
	pop ebp
	ret

updateMovements endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Despla�ar una fitxa o un bloc de fitxes cap al forat. 
; L'inici del bloc de fitxes a despla�ar l'indicaran les variables 
; (row) i (col). I el final quedar� impl�cit pel forat. S'ha de 
; comprovar que el bloc de fitxes estigui tot el "l�nea" i acabi 
; en el forat. Si nom�s es tracta d'una fitxa nom�s s'ha de comprovar 
; que estigui contigua al forat, no diagonalment.
; Al moure el bloc cap a direcci� el forat, el forat es desplac� a la
; fitxa inicial i el bloc es despla�ar� una posici� cap on estava el 
; forat. En el cas d'una sola fitxa, nom�s s'han d'intercanviar el
; forat i la fitxa.
; Si les condicions no es compleixen no es far� cap moviment.
; S'ha d'incrementar la variable moves si el moviment ha estat v�lid,
; sempre s'incrementa nom�s en un els moviments encara que es moguin
; m�s d'una fitxa.
;
; Variables utilitzades: 
;   carac2 : car�cter llegit de teclat
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
;	carac2   : variable on s�emmagatzema el car�cter llegit
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;playBlock:
playBlock proc
	push ebp
	mov  ebp, esp


	mov esp, ebp
	pop ebp
	ret

playBlock endp

END