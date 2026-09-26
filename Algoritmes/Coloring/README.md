# Coloració de Grafs mitjançant Cerca amb Enrere (Backtracking)

## 📌 Introducció i Problema
El problema de la coloració de grafs (*Graph Coloring Problem*) és un problema d'optimització combinatòria clàssic classificat com a NP-complet. Donat un graf no dirigit $G = (V, E)$ i un nombre màxim de colors disponibles $K$ (`m_MaxColors`), l'objectiu consisteix a assignar una etiqueta de color $c(v) \in \{0, 1, \dots, K-1\}$ a cada vèrtix $v \in V$ de manera que cap parell de vèrtixs adjacents comparteixi el mateix color:

$$\forall (u, v) \in E, \quad c(u) \neq c(v)$$

En l'àmbit de l'enginyeria de programari i la gestió de projectes, aquest problema modela directament la planificació de tasques amb dependències i restriccions de recursos simultanis, l'assignació de registres en compiladors i la planificació de freqüències en xarxes de telecomunicacions.

Aquest repositori ofereix una implementació optimitzada en C++20 dissenyada per resoldre el problema de $K$-coloració mitjançant tècniques de cerca exhaustiva amb enrere (*Backtracking*), posant especial èmfasi en l'eficiència temporal, la reducció d'overhead de memòria al *heap* i la gestió rigorosa de casos límit.

---

## 🧠 Algorismes i Implementacions

### 1. Coloració per Cerca amb Enrere Optimitzada (`ColoringBacktracking`)
- **Descripció funcional:** Implementa un algorisme de cerca en profunditat (DFS) amb enrere (*Backtracking*) que explora l'espai d'estats d'assignacions de colors. Per tal de maximitzar el rendiment en execució, l'algorisme evita la reassignació dinàmica de memòria durant la recursió mitjançant la preassignació d'una matriu d'accessibilitat de colors 2D (`colorsAcesibles`) de mida $|V| 	imes K$. Per a cada vèrtix, l'algorisme examina els vèrtixs adjacents ja acolorits, inhabilita els colors en ús i provi iterativament les opcions disponibles. Si s'arriba a un punt sense sortida, l'algorisme fa *backtracking*, restableix el color del vèrtix a `-1`, restaura el seu domini de colors disponibles i retrocedeix en l'arbre d'exploració.
- **Interfície:**
  - **Entrada:** `graph` (`CGraph&`) — Referència mutable al graf d'entrada que conté la llista de vèrtixs (`m_Vertices`) i el límit de colors permessos (`m_MaxColors`).
  - **Sortida:** `bool` — Retorna `true` si s'ha trobat una $K$-coloració vàlida per a tot el graf; `false` si el graf no és $K$-acolorible. Com a efecte secundari, actualitza el camp `m_Color` de cada vèrtix amb l'índex del color assignat.
- **Entorn i Dependències:**
  - Classes del domini: `CGraph`, `CVertex`, `CEdge`.
  - Llibreria estàndard de C++ (`<vector>`, `<list>`, `<iterator>`).
- **Complexitat:**
  - **Temporal:** $O(K^{|V|})$ en el pitjor dels casos, on $K = 	ext{m\_MaxColors}$ i $|V|$ és el nombre de vèrtixs. Tanmateix, la poda activa d'estats invàlids en revisar la veïnatge redueix significativament l'espai de cerca efectiu a $O(K^d)$, on $d \ll |V|$ és la profunditat màxima de branques no vàlides.
  - **Espacial:** $O(|V| \cdot K + |V|)$, on $|V| \cdot K$ és l'espai reservat per la matriu booleana `colorsAcesibles` i $O(|V|)$ correspon a la profunditat màxima de la pila de crides recursives (*call stack*).

### 2. Mòdul d'Interfície Probabilística i Nombre Cromàtic (`ColoringProbabilistic` / `ChromaticNumberBacktracking`)
- **Descripció funcional:** Defineix les interfícies d'extensió per a futurs algorismes d'aproximació i cerca heurística probabilística (ex. algorismes tipus Monte Carlo o Las Vegas) i per al càlcul del nombre cromàtic exacti $\chi(G)$ (el valor mínim de $K$ que admet coloració). Actualment actuen com a contractes de programació i punts d'entrada per a l'avaluació comparativa.
- **Interfície:**
  - **Entrada:** `graph` (`CGraph&`) — Referència al graf a analitzar.
  - **Sortida:** `bool` / `int` — Retorna la viabilitat de la coloració o el valor del nombre cromàtic $\chi(G)$.
- **Entorn i Dependències:** Classes de grafs, `<random>`, `<chrono>`.
- **Complexitat:**
  - **Temporal:** $O(1)$ en l'estat d'interfície actual.
  - **Espacial:** $O(1)$.

---

## ⚖️ Comparativa de Solucions

| Algorisme / Variant | Complexitat Temporal | Complexitat Espacial | Punt fort / Cas d'ús ideal |
|---|---|---|---|
| **Backtracking Optimitzat** (`ColoringBacktracking`) | $O(K^{|V|})$ | $O(|V| \cdot K + |V|)$ | Solució exacta determinista. Ideal per a grafs de mida petita o mitjana, o grafs amb fortes restriccions on es requereix un certificat exacte de colorabilitat. |
| **Aproximació Probabilística** (`ColoringProbabilistic` - *Extensió*) | $O(|V| + |E|)$ *(teòric)* | $O(|V|)$ | Solució aproximada ràpida. Ideal per a grafs d'escala massiva on la cerca exhaustiva és inabordable computacionalment. |

---

## 💡 Decisions de Disseny i Casos Límit

### Justificació tècnica:
1. **Preassignació de Matriu d'Accessibilitat de Colors:**
   En les primeres iteracions del disseny (com es pot observar en les variants arxivades V1–V3), es creava un vector local de booleans `std::vector<bool>` a cada nivell recursiu. Això provocava milions d'assignacions i desassignacions dinàmiques de memòria al *heap* per segon. En la versió final, es preassigna una única matriu `std::vector<std::vector<bool>>` de mida $|V| 	imes K$ abans d'iniciar la recursió. Quan l'algorisme fa *backtracking*, restaura els valors booleans a `true` directament, assolint una eficiència temporal un ordre de magnitud superior i complint els requeriments d'execució més exigents.

2. **Indexació $O(1)$ via `m_valor`:**
   Abans d'iniciar el *backtracking*, l'algorisme fa un recorregut lineal $O(|V|)$ per inicialitzar l'atribut `m_valor` de cada vèrtix amb una seqüència d'enters consecutius $0, 1, \dots, |V|-1$. Això permet mapejar immediatament cada iterador de la llista de vèrtixs amb el seu corresponent registre a la matriu de dominis de colors en temps constant $O(1)$.

3. **Invariabilitat i Neteja d'Estat:**
   Abans de qualsevol exploració, es garanteix que tots els camps `m_Color` estan inicialitzats a `-1` (no acolorit). Això assegura que execucions successives de la funció sobre el mateix objecte graf no pateixin de contaminació d'estat (*state leakage*).

### Casos límit gestionats:
- **Grafs buits (`|V| = 0`):** L'algorisme avalua `graph.m_Vertices.size() > 0`. Si el graf no conté cap vèrtix, la funció retorna `true` immediatament, evitant desreferències d'iteradors nuls o operacions d'inicialització invàlides.
- **Grafs desconnectats o sense arestes ($|E| = 0$):** Cada vèrtix rep el primer color disponible (`color = 0`) en temps lineal $O(|V|)$, ja que la comprovació d'arestes adjacents finalitza immediatament sense cap restricció.
- **Nombre de colors insuficient ($K < \chi(G)$):** Si $K$ és inferior al nombre cromàtic del graf, l'algorisme explora exhaustivament totes les branques admeses, restaura tots els vèrtixs a `m_Color = -1` i retorna `false` de manera totalment segura sense modificar l'estat intern del graf.
- **Vèrtixs aïllats o de grau zero:** S'acoloreixen correctament amb el color $0$ en la seva tornada d'exploració, sense afectar la disponibilitat de colors dels veïns.
