# Envoltant Convexa 2D — Algorisme QuickHull (Divideix i Venceràs)

## 📌 Introducció i Problema

El problema de l'**Envoltant Convexa** (*Convex Hull*) en el pla bidimensional ($2	ext{D}$) consisteix a trobar el polígon convex mínim que envolta i inclou la totalitat d'un conjunt donat de $n$ punts. 

Un polígon és **convex** si el segment de recta que uneix qualsevol parell de punts situats a l'interior o a la frontera del polígon pertany integrament a l'envoltant. En termes geomètrics, tots els angles interiors dels seus vèrtexs són estrictament inferiors a $180^\circ$, i tots els vèrtexs que formen la frontera de l'envoltant convexa pertanyen estrictament al conjunt de punts d'entrada.

Aquest repositori inclou una implementació en C++ de l'algorisme **QuickHull**, basat en el paradigma de **Divideix i Venceràs** (*Divide and Conquer*), desenvolupat en el marc de l'assignatura d'Algorísmica de l'Escola d'Enginyeria (UAB) sobre l'entorn de treball `GraphApplication`.

---

## 🧠 Algorismes i Implementacions

### 1. Algorisme QuickHull (Divideix i Venceràs)

- **Descripció funcional:**  
  L'algorisme `QuickHull` aplica una estratègia anàloga a *QuickSort* per trobar recursivament els vèrtexs de l'envoltant convexa:
  1. **Inicialització:** Cerca els dos punts extrems en l'eix horizontal (el punt amb coordenada $X$ mínima, `minX`, i el punt amb $X$ màxima, `maxX`). Aquests dos punts estan garantits de formar part de l'envoltant convexa.
  2. **Partició inicial:** La línia recta que uneix `minX` i `maxX` divideix el conjunt de punts en dos subconjunts: la part superior (positiva) i la part inferior (negativa).
  3. **Pas recursiu (`QuickHullRec`):** Per a cada subconjunt, es troba el punt `mesLluny` que maximitza l'àrea del triangle format pels dos punts terminals del segment i ell mateix. Aquest punt és un nou vèrtex de l'envoltant convexa.
  4. **Descartat de punts interiors:** Tots els punts continguts a l'interior del triangle format es descarten automàticament. Els punts restants a l'exterior es divideixen en dos nous subconjunts respecte als costats del triangle, i es processen recursivament fins que no queden més punts exteriors.
  5. **Concatenació:** Es reconstrueix la llista ordenada de vèrtexs que formen el perímetre convex en sentit horari/antihorari.

- **Interfície:**  
  - **Entrada:** `graph` (`CGraph&`) — Referència a l'estructura del graf que conté la llista de vèrtexs/punts d'entrada (`std::list<CVertex>`).
  - **Sortida:** `CConvexHull` — Objecte resultat que conté la llista de punts ordenats (`std::vector<CVertex*>`) que delimiten l'envoltant convexa.

- **Entorn i Dependències:**  
  - Estructures de dades pròpies del framework: `CGraph`, `CVertex`, `CGPoint`, `CConvexHull`.
  - Llibreria estàndard de C++: `<vector>`, `<list>`, `<cmath>`, `<algorithm>`.

- **Complexitat:**  
  - **Temporal:** 
    - **Cas mitjà / millor cas:** $O(n \log n)$. A cada nivell de recursió es descarta un nombre significatiu de punts interiors al triangle i es divideix el problema en subproblemes de mida $n/2$.
    - **Pitjor cas:** $O(n^2)$. Ocorre quan tots o la majoria de punts estan distribuïts sobre una corba convexa, fent que la partició sigui extremadament desequilibrada (reduint només 1 punt per cada crida recursiva).
  - **Espacial:** $O(n)$. Requereix memòria addicional per emmagatzemar els vectors temporals de punts filtrats (`partPositiva`, `partNegativa`) en la llista de crides recursives de la pila (*call stack*), la qual té una profunditat de $O(\log n)$ en el cas mitjà i $O(n)$ en el pitjor cas.

---

### 2. Primitives Geomètriques de Suport (`PosicioRespeteRecta` i `AreaTriangle`)

- **Descripció funcional:**  
  Mòdul d'operacions matemàtiques en $2	ext{D}$ utilitzat per determinar l'orientació espacial i la distància relativa de punts respecte a segments de recta:
  - `PosicioRespeteRecta`: Calcula el signe del producte creuat entre el vector director del segment $AB$ i el vector $BC$. Determina si un punt $C$ es troba a l'esquerra (resultat $> 0$), a la dreta (resultat $< 0$) o col·lineal (resultat $= 0$) respecte al segment orientat $AB$.
  - `AreaTriangle`: Calcula l'àrea absoluta del triangle compost pels vèrtexs $A$, $B$ i $C$. Atès que la base $AB$ és fixa, l'àrea és directament proporcional a la distància perpendicular del punt $C$ a la recta $AB$, permetent identificar el punt més allunyat d'un segment en temps constant.

- **Interfície:**  
  - **Entrada (`PosicioRespeteRecta`):** `rectaPuntA` (`CGPoint&`), `rectaPuntB` (`CGPoint&`), `puntEvaluar` (`CGPoint&`).
  - **Sortida (`PosicioRespeteRecta`):** `double` — Valor escalar amb signe que indica la posició relativa.
  - **Entrada (`AreaTriangle`):** `a` (`CGPoint&`), `b` (`CGPoint&`), `c` (`CGPoint`).
  - **Sortida (`AreaTriangle`):** `double` — Valor real positiu que representa l'àrea del triangle.

- **Entorn i Dependències:**  
  - Estrutura de dades `CGPoint` (coordenades reals `m_X`, `m_Y`).
  - Funció estàndard `std::abs` de `<cmath>`.

- **Complexitat:**  
  - **Temporal:** $O(1)$. Consisteix en un conjunt reduït d'operacions aritmètiques bàsiques (multiplicacions, substractions i divisions) d'execució immediata.
  - **Espacial:** $O(1)$. Ús de memòria constant sense assignació dinàmica.

---

## ⚖️ Comparativa de Solucions

| Algorisme / Variant | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| **QuickHull (Divideix i Venceràs)** | Mitjà: $O(n \log n)$<br>Pitjor cas: $O(n^2)$ | Mitjà: $O(n)$<br>Pitjor cas: $O(n)$ | Ideal per a conjunts de punts distribuïts aleatòriament en $2	ext{D}$ on molts punts queden a l'interior i es poden descartar ràpidament. |
| **Primitives Geomètriques (`PosicioRespeteRecta` / `AreaTriangle`)** | $O(1)$ | $O(1)$ | Operacions geomètriques de baix nivell extremadament ràpides i directes per a orientació de punts i distàncies. |

---

## 💡 Decisions de Disseny i Casos Límit

### Justificació tècnica
- **Elecció de punts extrems en X:** L'elecció dels punts amb coordenada $X$ mínima i màxima garanteix que la recta divisòria inicial creui tot el conjunt de dades. A més, aquests dos punts tenen la certesa matemàtica de formar part de l'envoltant convexa.
- **Criteri d'àrea màxima:** Maximitzar l'àrea del triangle $ABC$ permet trobar de forma eficient el punt més allunyat del segment $AB$. Això maximitza la quantitat de punts interiors que queden coberts pel triangle $ABC$ i que, per tant, es poden descartar en la següent fase recursiva.
- **Concatenació estructurada:** La funció recursiva `QuickHullRec` manté l'ordre estricte de la llista de perímetre en afegir primer els vèrtexs de la part esquerra/positiva, després el punt central `mesLluny` i finalment la part dreta/negativa.

### Casos límit gestionats
- **Conjunt buit ($N = 0$):** L'algorisme ho detecta mitjançant el control de mida de vèrtexs i retorna un objecte `CConvexHull` buit sense realitzar càlculs.
- **Un sol punt ($N = 1$):** Es retorna directament el punt com a únic integrant de l'envoltant convexa.
- **Dos punts ($N = 2$):** 
  - Si els dos punts són coincidents (mateixes coordenades $X$ i $Y$), es retorna només un d'ells per evitar duplicitats.
  - Si són diferents, es retornen tots dos punts formant el segment base.
- **Punts col·lineals:** La condició estricta `posPositiva > 0` i `posNegativa > 0` descarta automàticament els punts col·lineals sobre els segments (on `PosicioRespeteRecta` és $0$), assegurant que només s'incloguin com a vèrtexs els punts extrems del polígon.
- **Punts interiors al triangle:** Queden exclosos de les futures crides recursives en comprovar que no estan a l'esquerra de cap dels nous segments formats (`AC` o `CB`).
