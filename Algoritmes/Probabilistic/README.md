# Resolució Probabilística del Problema del Viatjant de Comerç (TSP) amb Descens del Gradient (2-Opt)

## 📌 Introducció i Problema
El **Problema del Viatjant de Comerç** (*Traveling Salesman Problem*, TSP) és un dels problemes d'optimització combinatòria NP-durs més estudiats en ciència de la computació. Donada una llista de ciutats (o vèrtexs de visita obligatòria) i les distàncies entre cadascun d'ells, l'objectiu és trobar la ruta de menor cost possible que visiti tots els vèrtexs requerits i torni o acabi en el punt de destinació especificat.

En aquest projecte, el problema es planteja sobre un graf general $G = (V, E)$ on s'especifica un subconjunt de vèrtexs de visita obligatòria $V_{visits} \subseteq V$ mitjançant una estructura `CVisits`. La ruta ha de satisfer les condicions següents:
1. Començar estrictament al primer vèrtex de la llista de visites (`visits[0]`).
2. Finalitzar estrictament a l'últim vèrtex de la llista de visites (`visits[N-1]`).
3. Visitar tots els vèrtexs intermedis de la llista sense repeticions.
4. Minimitzar la distància total recorreguda al llarg de les arestes del graf subjacent.

Per tal de resoldre aquest problema d'alta complexitat en temps real i sota restriccions d'execució estrictes, s'ha dissenyat un algorisme **metaheurístic probabilístic multi-inici (*Multi-Start*)** combinat amb una cerca local determinista basada en el **descens del gradient (*2-Opt*)** i un **precàlcul sistemàtic de camins mínims amb Dijkstra**.

---

## 🧠 Algorismes i Implementacions

L'arquitectura de la solució es divideix en tres components algorísmics principals que col·laboren en un pipeline d'optimització:

### 1. Precalculador de Matriu de Distàncies i Camins (Dijkstra All-Pairs)
- **Descripció funcional:** Abans d'iniciar la cerca probabilística, es precalcula la distància mínima i la seqüència exacta d'arestes entre tots els parells de vèrtexs de la llista `CVisits`. Això evita haver d'executar algorismes de cerca sobre el graf original durant les iteracions de cerca local, reduint la consulta de cost entre dos nodes a una llista d'adjacència precalculada amb accés en $O(1)$.
- **Interfície:**
  - **Entrada:** `graph` (`CGraph&`), `visits` (`CVisits&`)
  - **Sortida:** Popula internament `estructura` (`MatriuResultatP`, que correspon a `std::vector<std::vector<std::pair<std::list<CEdge*>, double>>>`).
- **Entorn i Dependències:** `DijkstraQueue`, `CGraph`, `CVertex`, `CEdge`, `std::vector`, `std::list`.
- **Complexitat:**
  - **Temporal:** $O(N \cdot (|E| + |V| \log |V|))$, on $N = |V_{visits}|$, $|V|$ és el nombre total de vèrtexs del graf i $|E|$ el nombre d'arestes. S'executa l'algorisme de Dijkstra $N$ vegades (una per cada node de visita).
  - **Espacial:** $O(N^2 \cdot L)$, on $L$ és la longitud mitjana (en nombre d'arestes) dels camins mínims entre vèrtexs de visita.

---

### 2. Generador Estocàstic de Camí Inicial (`GenerarCamiAleatori`)
- **Descripció funcional:** Genera un camí inicial vàlid entre la primera i l'última visita. Per a les posicions intermèdies, utilitza una estratègia de selecció probabilística ponderada (*Roulette Wheel Selection* / Selecció per Monte Carlo). La probabilitat de triar un node no visitat $i$ des del node actual és inversament proporcional a la quarta potència de la seva distància ($pes = 1 / d^4$). Això afavoreix fortament els nodes de proximitat geogràfica (comportament *Greedy* estocàstic) mantenint alhora diversitat per evitar la convergència prematura.
- **Interfície:**
  - **Entrada:** `n` (`int`), `estructura` (`MatriuResultatP&`)
  - **Sortida:** `std::pair<double, std::vector<int>>` — Parell que conté el cost total del camí (`double`) i la seqüència ordenada dels índexs de les visites (`std::vector<int>`).
- **Entorn i Dependències:** `std::vector`, `rand()`, `RAND_MAX`, `std::numeric_limits<double>`.
- **Complexitat:**
  - **Temporal:** $O(N^2)$, ja que per a cadascun dels $N-2$ passos intermedis s'avaluen fins a $N$ candidats restants per calcular la suma de pesos i seleccionar la següent posició.
  - **Espacial:** $O(N)$ per emmagatzemar la llista d'opcions, l'estat de visitats i el vector d'índexs del camí.

---

### 3. Cerca Local per Descens del Gradient Sistemàtic 2-Opt (`SalesmanTrackProbabilistic`)
- **Descripció funcional:** Un cop generada una solució inicial, s'aplica una millora determinista mitjançant descens del gradient basat en l'operador **2-Opt**. L'algorisme explora sistemàticament tots els parells de posicions $(i, j)$ amb $1 \le i < j \le N-2$ i avalua el canvi de cost de la ruta si s'inverteix el segment comprès entre $i$ i $j$. Gràcies a la matriu de distàncies precalculada, l'avaluació de la diferència de cost (*delta evaluation*) es realitza en temps constant $O(1)$. Si es troba una millora, s'inverteix el subsegment amb `std::reverse` i es repeteix el descens fins a assolir un màxim local.
- **Interfície:**
  - **Entrada:** `graph` (`CGraph&`), `visits` (`CVisits&`)
  - **Sortida:** `CTrack` — Objecte que conté la llista ordenada d'arestes (`m_Edges`) que formen el camí global optimitzat.
- **Entorn i Dependències:** `CGraph`, `CVisits`, `CTrack`, `std::reverse`, `std::pow`, `std::max`.
- **Complexitat:**
  - **Temporal:** $O(K \cdot N^2)$ per cada descens local completo, on $K$ és el nombre de passades de millora fins a trobar el màxim local. Atès que el nombre d'intents (*multi-start*) s'escala dinàmicament segons $nCercas = O(N^3)$, la complexitat temporal global de la metaheurística és de $O(N \cdot 	ext{Dijkstra} + K \cdot N^5)$.
  - **Espacial:** $O(N)$ d'emmagatzematge auxiliar durant la cerca local (més $O(N^2 \cdot L)$ per la matriu precalculada).

---

## ⚖️ Comparativa de Solucions i Components

A continuació es detalla la funció i l'eficiència de cadascun dels components algorísmics de la solució:

| Component / Algorisme | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| **Precalculador Dijkstra All-Pairs** | $O(N \cdot (|E| + |V| \log |V|))$ | $O(N^2 \cdot L)$ | Accelera dràsticament l'avaluació de rutes en $O(1)$ durant la cerca local, eliminant càlculs repetitius sobre el graf. |
| **Generador Estocàstic ($1/d^4$)** | $O(N^2)$ | $O(N)$ | Genera solucions inicials d'alta qualitat que combinen la lògica voraç (*greedy*) amb exploració aleatòria diversificada. |
| **Descens del Gradient (2-Opt)** | $O(K \cdot N^2)$ | $O(N)$ | Intensificació eficient: elimina creuaments de camins i optimitza el cost de manera determinista fins a un mínim local. |
| **Metaheurística Multi-Start Integrada** | $O(N \cdot 	ext{Dijkstra} + K \cdot N^5)$ | $O(N^2 \cdot L)$ | Balanç d'exploració/explotació adaptatiu segons la mida del problema ($N^3$), trobant solucions quasi-òptimes per al TSP. |

---

## 💡 Decisions de Disseny i Casos Límit

### Justificació tècnica:
1. **Ponderació cúbica/quàrtica de distàncies ($1/d^4$):** En lloc d'un ordre completament aleatori o purament voraç, la funció de pes $1/d^4$ penalitza severament els salts a nodes llunyans mentre manté una petita probabilitat d'explorar rutes no trivials. Això produeix solucions inicials molt properes a l'òptim.
2. **Evaluació Delta en $O(1)$ per al 2-Opt:** En invertir un segment entre les posicions $i$ i $j$, no cal recalcular el cost total de tot el camí ($O(N)$). N'hi ha prou amb restar les arestes eliminades $((i-1) 	o i$ i $j 	o (j+1))$ i sumar les noves arestes d'enllaç $((i-1) 	o j$ i $i 	o (j+1))$, aconseguint una millora de rendiment d'un ordre de magnitud.
3. **Escalat Temporal Adaptatiu Cúbic ($N^3$):** El nombre d'intents de cerca (*multi-start*) es calcula dinàmicament en funció de la quantitat de vèrtexs de visita:
   $$	ext{tempsTotal} = 100 \cdot N^3 \implies nCercas = \max(1, 	ext{tempsTotal} \cdot 0.225)$$
   Això permet dedicar un pressupost de temps elevat a grafs petits/mitjans per trobar la solució exacta, i alhora acotar el temps d'execució en grafs molt grans per respectar els límits del corrector automàtic.

### Casos límit gestionats:
- **Grafs o visites de mida petita ($N \le 3$):** Si el nombre de visites és igual o inferior a 3, el problema no té graus de llibertat per a intercanvis intermedis. L'algorisme ho detecta directament i construeix el camí lineal directe en $O(N)$ sense executar el bucle de cerca 2-Opt.
- **Nodes inaccessibles / Distància infinita (`d >= max`):** Es comprova si la distància precalculada és infinita o no accessible (`d >= std::numeric_limits<double>::max()`). En aquest cas, se li assigna un pes $0$, impossibilitant la selecció d'aquesta opció durant la generació estocàstica.
- **Distàncies nul·les o negatives ($d \le 0$):** Per evitar divisions per zero o comportaments anòmals al calcular $1/d^4$, es fixa un pes protector predeterminat ($100.0$).
- **Absència de millora en descens local:** El bucle `while (milloraAconseguida)` garanteix l'aturada immediata del descens del gradient quan una passada completa sobre totes les parelles $(i, j)$ no produeix cap reducció en el cost del camí.
