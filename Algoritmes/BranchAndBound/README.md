# Solució del Problema del Viatjant de Comerç (TSP) mitjançant Branch & Bound

## 📌 Introducció i Problema
El problema del Viatjant de Comerç (Traveling Salesperson Problem, TSP) és un dels dilemes clàssics d'optimització combinatòria de classe NP-dur. En aquesta implementació, es resol una variant aplicada sobre un graf arbitrari $G = (V, E)$ on un agent ha de trobar el camí de cost mínim que comença en un vèrtex origen $vv_0$, visita de manera obligatòria un conjunt de vèrtexs intermediaris $VV = \{vv_1, vv_2, \dots, vv_{n-2}\}$ i finalitza en un vèrtex destí $vv_{n-1}$.

L'espai de cerca d'aquesta problemàtica creix de forma factorial segons la quantitat de visites $N = |VV|$, donant un total de $(N-2)!$ possibles combinacions d'ordenació de visites. Per tal d'explorar eficientment aquest espai sense recórrer a una cerca exhaustiva ingènua, el projecte utilitza la tècnica de **Branch & Bound (Ramificació i Poda)** combinada amb un precàlcul dels camins mínims entre tots els vèrtexs de visita mitjançant l'algorisme de Dijkstra.

## 🧠 Algorismes i Implementacions

### 1. Branch & Bound 1: Cerca per Amplitud Prioritària (Sens Estimació Restant)
- **Descripció funcional:** Implementa una cerca de cost uniforme (Uniform-Cost Search). La funció d'estimació $H(\text{camí})$ s'estableix a $0.0$, de manera que la fita inferior d'un node ve donada exclusivament per la distància real acumulada $L(\text{camí})$. Selecciona sempre la solució parcial més curta de la cua amb prioritat (`std::priority_queue`). Tot i que garanteix la troballa de la solució òptima, no realitza estimacions de la distància restant per podar branques de manera anticipada.
- **Interfície:** 
  - **Entrada:** `graph` (`CGraph&`), `visits` (`CVisits&`)
  - **Sortida:** (`CTrack`) Objecte que conté la llista d'arestes (`std::list<CEdge*>`) que formen el camí de cost mínim que connecta totes les visites en l'ordre òptim.
- **Entorn i Dependències:** 
  - Estructura de dades `nodeConjelatBB` per a la representació dels estats parcials.
  - `std::priority_queue<nodeConjelatBB>` (Min-Heap) per a la gestió dels nodes actius.
  - Mòdul `DijkstraQueue` per al precàlcul de distàncies i camins mínims parell a parell.
  - Matriu d'adjacència de visites `estructura`.
- **Complexitat:** 
  - **Temporal:** $O(N! + N \cdot (|E| + |V| \log |V|))$, on $N = |V_{\text{visites}}|$. La fase preliminar executa Dijkstra $N$ vegades amb cost $O(N \cdot (|E| + |V| \log |V|))$. En el pitjor cas, la cerca expandeix $(N-2)!$ permutacions ja que la fita $H = 0$ no aporta informació d'orientació cap al destí.
  - **Espacial:** $O(N! \cdot N + N^2 \cdot K)$, degut a l'emmagatzematge potencial de tots els nodes parcials a la cua amb prioritat en el pitjor cas i la matriu de camins precalculada (on $K$ és la longitud mitjana dels camins en arestes).

### 2. Branch & Bound 2: Cota Inferior amb Estimació Estàtica
- **Descripció funcional:** Utilitza una heurística d'estimació basada en les distàncies mínimes d'eixida dels vèrtexs pendents de visitar. Durant la fase d'inicialització, es calcula per a cada vèrtex el seu cost mínim vers qualsevol altre vèrtex (`minims[i]`). La fita inferior es defineix com $F(\text{camí}) = L(\text{camí}) + H_2(\text{camí})$, on $H_2(\text{camí})$ és la suma dels costos mínims associats als vèrtexs no visitats. A mesura que la cerca avança, l'estimació $H_2$ s'actualitza de manera incremental restant el cost mínim del vèrtex acabat d'incorporar.
- **Interfície:** 
  - **Entrada:** `graph` (`CGraph&`), `visits` (`CVisits&`)
  - **Sortida:** (`CTrack`) Camí de cost mínim reconstruït amb les arestes originals del graf.
- **Entorn i Dependències:** Comparteix l'estructura modular de B&B 1, afegint el vector `minims` de distàncies mínimes per vèrtex i el vector `disMin` per al càlcul inicial de la fita inferior.
- **Complexitat:** 
  - **Temporal:** $O(N! + N \cdot (|E| + |V| \log |V|))$ en el pitjor cas teòric, però amb una reducció molt significativa del temps d'execució pràctic. L'heurística $H_2 > 0$ permet podar branques subòptimes d'un mode precoç.
  - **Espacial:** $O(b^d \cdot N + N^2 \cdot K)$, on $b$ és el factor de ramificació efectiu ($b < N$) i $d = N$ és la profunditat de l'arbre, requerint considerablement menys memòria a la cua de prioritat.

### 3. Branch & Bound 3: Cota Inferior Dinàmica i Poda Optimitzada
- **Descripció funcional:** Variant optimitzada de Ramificació i Poda dissenyada per maximitzar la capacitat de poda ajustant la fita inferior. Aquesta implementació avalua el cost restant $H_3(\text{camí})$ considerant l'estat actual del recorregut i aplicant mecanismes de seguretat que recalculen la suma de costos sobre els vèrtexs no visitats. Això evita subestimacions errònies i maximitza el retall de branques que superin la cota superior actualment coneguda.
- **Interfície:** 
  - **Entrada:** `graph` (`CGraph&`), `visits` (`CVisits&`)
  - **Sortida:** (`CTrack`) Camí d'arestes de $G$ que connecta l'origen, totes les visites intermediàries i el destí amb el menor cost total.
- **Entorn i Dependències:** Manté l'arquitectura unificada basant-se en `SalesmanTrackBranchAndBoundGeneric` i `nodeConjelatBB`, utilitzant estructures de seguiment d'estat (`m_utilitzat`) i la matriu de Dijkstra `estructura`.
- **Complexitat:** 
  - **Temporal:** $O(N! + N \cdot (|E| + |V| \log |V|))$ en el pitjor cas, presentant la millor eficiència en temps d'execució degut a un menor nombre de nodes generats i explorats.
  - **Espacial:** $O(b^d \cdot N + N^2 \cdot K)$, registrant el consum de memòria més contingut per a la cua de prioritat.

## ⚖️ Comparativa de Solucions

| Algorisme / Variant | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| **Branch & Bound 1** | $O(N! + N(|E| + |V|\log |V|))$ | $O(N! \cdot N + N^2 K)$ | Implementació directa i de referència. Ideal per a un nombre molt reduït de vèrtexs ($N \le 5$) on el càlcul d'heurístiques no compensa la sobrecàrrega. |
| **Branch & Bound 2** | $O(N! + N(|E| + |V|\log |V|))$ | $O(b^d \cdot N + N^2 K)$ | Gran equilibri entre cost de càlcul per node i reducció de l'espai de cerca. Ideal per a grafs mitjans amb costos d'eixida homogenis. |
| **Branch & Bound 3** | $O(N! + N(|E| + |V|\log |V|))$ | $O(b^d \cdot N + N^2 K)$ | Poda més eficient i ràpida convergència. Ideal per a instàncies complexes on minimitzar la mida màxima de la cua de prioritat és prioritari. |

## 💡 Decisions de Disseny i Casos Límit

- **Justificació tècnica:**
  - **Arquitectura Modular Genèrica:** S'ha dissenyat la funció `SalesmanTrackBranchAndBoundGeneric` que centralitza la lògica de cerca, la gestió de la cua amb prioritat i la reconstrucció final del camí. Això evita la duplicació de codi i facilita l'avaluació de diferents heurístiques (`nivell = 1, 2, 3`).
  - **Reducció del Graf mitjançant Dijkstra (APSP):** En lloc d'explorar l'arbre de cerca directament sobre les arestes del graf original $G$, es redueix el problema a un graf complet de $N$ vèrtexs de visita. Els camins mínims i les seqüències d'arestes (`CEdge*`) es precalculen un sol cop a la matriu `estructura`.
  - **Min-Heap mitjançant Sobrecàrrega d'Operadors:** Es sobrecarrega l'operador `<` a l'estructura `nodeConjelatBB` per convertir la `std::priority_queue` per defecte (Max-Heap) en un Min-Heap basat en `m_fitaInferior`, garantint que el següent node a expandir sigui sempre el que té menor cost estimat.
  - **Poda Activa per Cota Superior:** Es manté una variable `cotaSuperior` inicialitzada al valor màxim (`std::numeric_limits<double>::max()`). Si un node extret té $F(\text{node}) \ge \text{cotaSuperior}$, es descarta immediatament.

- **Casos límit gestionats:**
  - **Preservació del Destí Final:** Per evitar finalitzar el recorregut abans d'haver visitat tots els vèrtexs requerits, el bucle de ramificació imposa la restricció `if ((i == (NUM_NODES - 1)) && (nodeMenor.m_seguentPosCami < i)) continue;`. Això impedeix transicions prematures cap al vèrtex final.
  - **Nodes Inaccessibles o Distàncies Infinites:** Si no existeix camí entre dos vèrtexs de visita, Dijkstra assigna cost `infinity`. La condició `(distacia + estimacio) < cotaSuperior` descarta automàticament l'afegiment de branques invàlides a la cua.
  - **Recàlcul de Consistència d'Estimacions:** Quan el descompte incremental de l'estimació heurística produeix un valor negatiu degut a imprecisions numèriques de tipus `double`, el codi recalcula iterativament la suma real dels costos mínims dels vèrtexs pendents (`sumaH`), assegurant que $H \ge 0$.
  - **Reconstrucció d'Arestes Originals:** En finalitzar la cerca, la solució conté la seqüència d'índexs de visites. Es concatenen de forma ordenada totes les arestes individuals emmagatzemades en `estructura[origen][desti].first` per retornar un objecte `CTrack` coherent i complet.
