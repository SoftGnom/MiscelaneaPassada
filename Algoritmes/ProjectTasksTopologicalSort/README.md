# Ordenació Topològica i Detecció de Cicles en Grafs de Tasques (Algorisme Greedy de Kahn)

## 📌 Introducció i Problema
En l'àmbit de l'enginyeria de programari i la gestió de projectes, una estructura de dades comuna és el graf dirigit de tasques amb dependències de precedència. Cada projecte està compost per un conjunt de tasques (`CProTask`), on determinades tasques requereixen la finalització prèvia d'altres (`m_Previous`) abans de poder iniciar-se, generant al seu torn restriccions sobre les tasques posteriors (`m_Next`).

El problema consisteix a trobar una seqüència d'execució vàlida —una **ordenació topològica**— que garanteixi que cap tasca s'iniciï abans que les seves dependències hagin finalitzat. A més, en entorns de dades reals poden existir dependències circulars o cícliques (ex. la tasca A depèn de B i la tasca B depèn de A). El codi desenvolupat té com a objectiu extreure l'ordre topològic executable de manera *greedy* i, simultàniament, detectar i aïllar totes les tasques que formen part o depenen de cicles (`m_Cyclic`).

## 🧠 Algorismes i Implementacions

### 1. ProjectTaskTopologicalSortGreedy (Algorisme de Kahn Modificat)
- **Descripció funcional:** Implementa una variant iterativa i greedy de l'algorisme de Kahn per a l'ordenació topològica. Primer, calcula el grau d'entrada (*in-degree*) de cada node a partir de la mida de la llista `m_Previous` i l'emmagatzema a `m_Valor`. A continuació, recorre iterativament el conjunt de tasques seleccionant aquelles que tenen `m_Valor == 0` (sense dependències pendents). En processar una tasca, s'afegeix a la llista d'ordre topològic (`ret.m_Order`), es redueix en 1 el comptador de dependències de les seves tasques següents (`m_Next`), i es marca com a processada (`m_Valor = -1`). L'algorisme es repeteix fins que no es poden desbloquejar més tasques. Finalment, qualsevol tasca que mantingui `m_Valor > 0` s'identifica com a bloquejada per dependència cíclica i s'afegeix a `ret.m_Cyclic`.
- **Interfície:** 
  - **Entrada:** `project` (`CProjectTasks&`) - Referència a l'objecte contenidor del projecte que inclou la llista de tasques `m_Tasks`.
  - **Sortida:** `CTopologicalOrder` - Objecte que conté la llista de tasques ordenades (`m_Order`) i la llista de tasques afectades per cicles (`m_Cyclic`).
- **Entorn i Dependències:** Utilitza les estructures de dades C++ `CProjectTasks`, `CProTask` (camps `m_Valor`, `m_Previous`, `m_Next`) i `CTopologicalOrder`.
- **Complexitat:** 
  - **Temporal:** $O(|V|^2 + |E|)$, on $|V|$ és el nombre de tasques i $|E|$ el nombre d'arcs de dependència. En el pitjor cas (un graf lineal), el bucle intern recorre la llista de $V$ tasques durant $V$ iteracions primàries ($O(|V|^2)$), mentre que l'actualització dels comptadors veïns realitza un total de $|E|$ decrements.
  - **Espacial:** $O(|V|)$ per emmagatzemar els estat dels comptadors temporals i les llistes resultat (`m_Order` i `m_Cyclic`).

### 2. ProjectTaskTopologicalSortRecursive (Estructura de Resolució Recursiva / DFS)
- **Descripció funcional:** Proporciona la interfície base i l'esquelet funcional per a un enfocament d'ordenació topològica basat en el recorregut en profunditat (DFS - *Depth-First Search*). Aquesta variant serveix com a punt d'entrada per a resolucions recursives on l'ordre es determina post-visita dels successors del graf, gestionant els cicles mitjançant piles d'execució i marcatge d'estats de visita (no visitat, en procés, visitat).
- **Interfície:** 
  - **Entrada:** `project` (`CProjectTasks&`) - Referència a la llista de tasques del projecte.
  - **Sortida:** `CTopologicalOrder` - Instància del resultat de l'ordenació topològica.
- **Entorn i Dependències:** Classes C++ `CProjectTasks` i `CTopologicalOrder`.
- **Complexitat:** 
  - **Temporal:** $O(1)$ en l'estat actual d'interfície base (o $O(|V| + |E|)$ quan s'implementa la cerca DFS completa de recorregut lineal).
  - **Espacial:** $O(1)$ auxiliar (o $O(|V|)$ per la pila de crides recursives i la traça d'estats de nodes en una implementació DFS plena).

## ⚖️ Comparativa de Solucions

| Algorisme / Variant | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| `ProjectTaskTopologicalSortGreedy` | $O(|V|^2 + |E|)$ | $O(|V|)$ | Robustesa i simplicitat iterativa. No depèn de la pila de crides del sistema, evita desbordaments de memòria (*stack overflow*) i aïlla de manera determinista les tasques atrapades en dependències cícliques. |
| `ProjectTaskTopologicalSortRecursive` | $O(1)$ / $O(|V| + |E|)$ | $O(1)$ / $O(|V|)$ | Model d'abstracció recursiva tipus DFS. Ideal per a validacions conceptuals o grafs acíclics de profunditat moderada on es requereix un temps de recorregut lineal $O(|V| + |E|)$. |

## 💡 Decisions de Disseny i Casos Límit

- **Justificació tècnica:**
  - L'elecció de l'algorisme de Kahn modificat (`ProjectTaskTopologicalSortGreedy`) respon a la necessitat de tractar projectes reals on poden existir errors de definició de tasques (cicles de dependència). A diferència d'un algorisme topològic tradicional que fallaria o entraria en bucle infinit, l'enfocament greedy decrementa l'in-degree progressivament. Quan cap node té `in-degree == 0`, l'algorisme s'atura de forma segura i classifica la resta de nodescom a cíclics (`m_Valor > 0`), oferint un diagnòstic clar.
- **Casos límit gestionats:**
  - **Projecte buit ($|V| = 0$):** La funció retorna immediatament una estructura `CTopologicalOrder` buida sense executar cap iteració.
  - **Graf acíclic dirigit (DAG perfecte):** Totes les tasques es redueixen a `m_Valor == 0` de manera progressiva, completant `m_Order` amb les $|V|$ tasques i deixant `m_Cyclic` completament buida.
  - **Cicles complets (Grafs no resolibles):** Si totes les tasques depenen entre si en un cicle tancat, cap tasca tindrà inicialment `m_Valor == 0`. El bucle `while` finalitza immediatament i totes les tasques es classifiquen a `m_Cyclic`.
  - **Cicles parcials amb components acíclics:** L'algorisme resol primer totes les tasques no afectades pel cicle (afegint-les a `m_Order`) i aïlla únicament les tasques directament o indirectament bloquejades pel cicle a `m_Cyclic`.
