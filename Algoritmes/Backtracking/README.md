# Optimització de Rutes del Viatjant de Comerç (TSP) amb Visites Obligatòries: Backtracking Pur vs. Backtracking-Greedy

## 📌 Introducció i Problema
El problema del Viatjant de Comerç amb visites intermèdies obligatòries (*Traveling Salesperson Problem with Mandatory Visits*) és un problema d'optimització combinatòria basat en la teoria de grafs. Donat un graf dirigit i ponderat $G = (V, E)$, un vèrtex d'origen $V_o$, un vèrtex de destí $V_d$ i un conjunt de vèrtexs de visita obligatòria $V_{visits} = \{V_o, V_1, V_2, \dots, V_d\}$, l'objectiu consisteix a trobar el camí de cost (longitud) mínim que comenci a $V_o$, finalitzi a $V_d$ i passi per tots els vèrtexs entremitjos.

A diferència del cas simple (on no es permet repetir cap vèrtex en tot el recorregut), en escenaris complexos amb visites obligatòries pot ser necessari transitar més d'una vegada per un mateix vèrtex per tal de connectar diferents trams de la ruta de manera òptima. No obstant això, dins d'un mateix tram o camí no es poden repetir arestes en el mateix sentit.

Aquest projecte desenvolupa dues solucions algorísmiques en C++ per resoldre el problema:
1. **Backtracking Pur sobre Arestes (`SalesmanTrackBacktracking`):** Exploració recursiva de l'espai d'estats directament sobre l'estructura d'arestes del graf, amb poda per cota superior (*Branch and Bound*).
2. **Backtracking-Greedy Híbrid (`SalesmanTrackBacktrackingGreedy`):** Abstracció del graf mitjançant la precomputació dels camins mínims entre totes les visites utilitzant l'algorisme de Dijkstra, seguida d'una cerca per backtracking de la millor permutació d'itinerari.

---

## 🧠 Algorismes i Implementacions

### 1. Backtracking Pur sobre Arestes (`SalesmanTrackBacktracking`)

- **Descripció funcional:**  
  Explora l'espai de cerca transitant aresta per aresta directament sobre la topologia del graf. Per tal de permetre la reutilització de vèrtexs entre diferents trams de visites però evitar bucles infinits, l'algorisme marca les arestes utilitzades (`m_valor = true`) i manté un seguiment dels vèrtexs visitats.  
  Utilitza una estratègia de ramificació i poda (*Branch and Bound*) descartant immediatament qualsevol branca la distància acumulada de la qual superi la longitud de la millor solució trobada fins al moment (`prob.m_long >= prob.m_longMillo`). Una ruta és acceptada com a solució vàlida només quan s'assoleix el node destí havent marcat prèviament com a visitats tots els nodes continguts a `visits`.

- **Interfície:** 
  - **Entrada:** `graph` *(CGraph&)* — Referència al graf de la xarxa de transport o topologia.
  - **Entrada:** `visits` *(CVisits&)* — Llista ordenada de vèrtexs de pas obligatori (incloent l'origen i el destí).
  - **Sortida:** *(CTrack)* Objecte que conté la seqüència ordenada d'arestes (`m_Edges`) que formen el camí òptim trobat.

- **Entorn i Dependències:**
  - `CGraph`, `CVertex`, `CEdge`: Estructures de dades orientades a objectes per a la representació de grafs dirigits i ponderats.
  - `CVisits`, `CTrack`: Classes auxiliars per gestionar llistes de nodes de visita i rutes resultants.
  - `DefProblemaSTB`: Estructura d'estat global utilitzada per encapsular el context de cerca recursiva (`m_Arestes`, `m_solucio`, `m_longMillo`, `m_long`).

- **Complexitat:**
  - **Temporal:** $O(|E|!)$ en el pitjor cas. La cerca explora combinacions d'arestes no utilitzades, generant un arbre d'exploració amb un factor de ramificació acotat pel grau de sortida màxim $\Delta$ i una profunditat màxima proporcional al nombre d'arestes $|E|$. L'aplicació de la poda (*Branch and Bound*) redueix significativament l'efecte exponencial en grafs reals.
  - **Espacial:** $O(|V| + |E|)$ degut a la pila de crides recursives (profunditat acotada per $|E|$) i al manteniment dels marcadors d'estat a les estructures del graf.

---

### 2. Backtracking-Greedy Híbrid (`SalesmanTrackBacktrackingGreedy`)

- **Descripció funcional:**  
  Descompon el problema en dues fases aprofitant la propietat de subestructura òptima dels camins entre visites:
  1. **Fase d'Abstracció (Dijkstra APSP parcial):** Executa l'algorisme de Dijkstra prenent com a origen cadascun dels $N_v$ vèrtexs a visitar ($N_v = |V_{visits}|$). Es construeix una matriu de distàncies i camins `estructura[i][j]` on cada cel·la emmagatzema la distància mínima i la llista d'arestes precomputada entre la visita $i$ i la visita $j$.
  2. **Fase d'Optimització de Permutacions (Backtracking):** Explora l'espai de cerca de les $(N_v - 2)!$ permutacions possibles per a l'ordre de les visites intermèdies (mantenint fixos l'origen $0$ i el destí $N_v-1$). Aplica poda immediata quan la distància acumulada supera la millor distància trobada (`distAcumulada >= g_millorDistancia`).
  3. **Fase de Reconstrucció:** Concatena les llistes d'arestes dels camins precomputats d'acord amb la millor permutació d'índexs trobada.

- **Interfície:** 
  - **Entrada:** `graph` *(CGraph&)* — Referència al graf base de la xarxa.
  - **Entrada:** `visits` *(CVisits&)* — Llista de vèrtexs de pas obligatori.
  - **Sortida:** *(CTrack)* Ruta completa concatenada amb la seqüència d'arestes de cost mínim.

- **Entorn i Dependències:**
  - `DijkstraQueue(graph, vertex)`: Funció d'algorisme de Dijkstra per calcular distàncies mínimes des d'un node origen utilitzant cua de prioritat.
  - `MatriuResultat` (`std::vector<std::vector<InfoConnexio>>`): Matriu $N_v \times N_v$ que emmagatzema parells de (llista d'arestes, distància).
  - `g_millorDistancia`, `g_millorCami`: Variables globals/d'estat per gestionar el seguiment de la millor solució durant el backtracking de permutacions.

- **Complexitat:**
  - **Temporal:** $O(N_v \cdot (|E| + |V| \log |V|) + (N_v - 2)!)$, on $N_v = |V_{visits}|$. El terme $N_v \cdot (|E| + |V| \log |V|)$ correspon a les $N_v$ execucions de Dijkstra amb cua de prioritat, i $(N_v - 2)!$ és el límit superior de les permutacions avaluades pel backtracking. Quan $N_v \ll |V|$, aquesta variant és ordres de magnitud més ràpida que el Backtracking pur.
  - **Espacial:** $O(N_v^2 \cdot L + |V|)$, on $L$ és la longitud mitjana en arestes dels camins mínims entre visites, degut a la matriu de camins precalculats i a les estructures d'estat de Dijkstra.

---

## ⚖️ Comparativa de Solucions

| Algorisme / Variant | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| **Backtracking Pur sobre Arestes** | $O(|E|!)$ *(pitjor cas)* | $O(|V| + |E|)$ | Grafs molt petits o topologies altament canviants on es requereix exploració d'estats primitius sense precalculs de camins. |
| **Backtracking-Greedy (Híbrid Dijkstra)** | $O(N_v \cdot (|E| + |V| \log |V|) + (N_v - 2)!)$ | $O(N_v^2 \cdot L + |V|)$ | Grafs grans amb un nombre moderat de visites ($N_v \le 15$). Maximitza el rendiment reduint la cerca a permutacions de camins mínims. |

---

## 💡 Decisions de Disseny i Casos Límit

- **Justificació tècnica:**
  - **Abstracció del Graf mitjançant Dijkstra:** L'enfocament pur treballa directament sobre la topologia física del graf, la qual cosa provoca ineficiències quan la distància entre visites és gran. La decisió de dissenyar el model Híbrid redueix l'espai d'estats d'un graf d'arestes complex a un **graf complet d'abstracció de visites**, on cada aresta abstracta representa un camí mínim precomputat.
  - **Tècnica de Poda (Branch & Bound):** En ambdós algorismes s'aplica poda per cota superior estricta (`distAcumulada >= millorDistancia`). Això redueix dràsticament l'arbre d'exploració evitant branques no subòptimes.
  - **Reconstrucció lineal de rutes:** A la variant Híbrida, la reconstrucció dels camins precalculats es fa mitjançant `push_front` recorrent els punters de predecessor de Dijkstra (`m_pDijkstraPrevious`), garantint un temps de reconstrucció lineal $O(L)$ per tram.

- **Casos límit gestionats:**
  - **Absència de visites intermèdies ($N_v = 2$):** Ambdós algorismes gestionen correctament la cerca entre origen i destí directe. A la variant Híbrida, la cerca de permutacions intermèdies es nolieja i es retorna el camí directe calculat per Dijkstra.
  - **Grafs desconnectats / Visites inabastables:** Si una visita no és accessible des d'una altra, `m_DijkstraDistance` pren valor infinit (`std::numeric_limits<double>::infinity()`). La poda per cota superior invalida immediatament la branca evitant bucles o excepcions de memòria.
  - **Nodos repetits entre trams:** El Backtracking pur valida el conjunt de visites mitjançant la verificació de l'estat booleà `m_valor` a tots els vèrtexs de la llista de visites abans d'acceptar una solució al node destí.
