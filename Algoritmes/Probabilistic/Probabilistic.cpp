#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 
#include <random>
#include <chrono>

// SalesmanTrackProbabilistic ==================================================





using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;



std::pair<double, std::vector<int>> GenerarCamiAleatori(int n, MatriuResultatP& estructura) {

    std::pair<double, std::vector<int>> ret(0.0, std::vector<int>(n, 0));
    std::vector<bool> visitat(n, false);

    ret.first = 0;

    // set node inicial
    ret.second[0] = 0;
    visitat[0] = true;

    // set node final
    ret.second[n - 1] = (n - 1);
    visitat[n - 1] = true;

    // Construïm el camí
    for (int pas = 1; pas < (n - 1); ++pas) {

        int actual = ret.second[pas - 1];
        std::vector<std::pair<int, double>> opcions;
        double sumaInverses = 0;

        // Busquem opcions no visitats
        for (int i = 1; i < n - 1; ++i) {
            if (!visitat[i]) {
                double d = estructura[actual][i].second;

                // Corretjir errors i definir pes
                double pes;
                if (d <= 0) pes = 100.0;
                else if (d >= std::numeric_limits<double>::max()) pes = 0;
                else pes = 1.0 / (d * d * d * d);

                opcions.push_back({ i, pes });
                sumaInverses += pes;

            }
        }

        // escollir el correcte i buscar-lo
        double llindar = ((double)rand() / RAND_MAX) * sumaInverses;

        double acumulat = 0;
        int triat = -1;

        for (auto& opcio : opcions) {
            acumulat += opcio.second;
            if (acumulat >= llindar) {
                triat = opcio.first;
                break;
            }
        }


        // Actualitzem el camí i l'estat
        ret.first += estructura[actual][triat].second;
        ret.second[pas] = triat;
        visitat[triat] = true;
    }

    ret.first += estructura[ret.second[n - 2]][ret.second[n - 1]].second;

    return ret;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització 
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            
            i++;
        }
    }
    
    // Escalat cúbic consolidat: (600 * std::pow(NUM_NODES, 3))
    long long tempsTotal = static_cast<long long>(100 * std::pow(NUM_NODES, 3));

    // Amplada consolidada: (base * 1.5 * 1.5) = base * 2.25
    double pAmplada = 0.225;

    // CÀLCULS DERIVATS
    // L'amplada defineix quants intents nous fem
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));

    std::pair<double, std::vector<int>> millo(std::numeric_limits<double>::max(), std::vector<int>(NUM_NODES, true));
    std::pair<double, std::vector<int>> actual(0.0, std::vector<int>(NUM_NODES, 0));

    if (NUM_NODES > 3) {

        // Dins de SalesmanTrackProbabilistic, per a cada intent (nCercas):
        for (int i_intent = 0; i_intent < nCercas; i_intent++) {
            // 1. Generar solució inicial (Greedy o Aleatòria) [cite: 24, 25, 26]
            actual = GenerarCamiAleatori(NUM_NODES, estructura);

            // 2. Descens del Gradient Sistemàtic [cite: 61]
            bool milloraAconseguida = true;
            while (milloraAconseguida) {
                milloraAconseguida = false;

                // Bucle sistemàtic extret de l'enunciat 
                for (int i = 1; i < (int)NUM_NODES - 2; ++i) {
                    for (int j = i + 1; j < (int)NUM_NODES - 1; ++j) {

                        // Càlcul ràpid de l'estalvi amb la matriu precalculada [cite: 43, 44]
                        double costActual = estructura[actual.second[i - 1]][actual.second[i]].second +
                            estructura[actual.second[j]][actual.second[j + 1]].second;

                        double costNou = estructura[actual.second[i - 1]][actual.second[j]].second +
                            estructura[actual.second[i]][actual.second[j + 1]].second;

                        if (costNou < costActual) {
                            // Si millora, fem l'intercanvi (2-Opt: invertir el segment) [cite: 29, 65]
                            std::reverse(actual.second.begin() + i, actual.second.begin() + j + 1);
                            actual.first = actual.first - costActual + costNou;

                            milloraAconseguida = true; // Hem de repetir el descens [cite: 66]
                        }
                    }
                }
            }

            // Guardar si és la millor global de tots els intents [cite: 55]
            if (actual.first < millo.first) {
                millo.first = actual.first;
                for (int k = 0; k < NUM_NODES; k++) millo.second[k] = actual.second[k];
            }
        }


        
    }
    else {//fer algo amb el 4?

        millo.second[0] = 0;
        millo.first = 0;

        for (int i = 1; i < NUM_NODES; ++i) {
            millo.second[i] = i;
            millo.first += estructura[millo.second[i - 1]][i].second;
        }
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.second[i - 1];
        int desti = millo.second[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}

/*
* V2 - Nota: 5.2
*  

struct nodeConjelatP {
    int node;             // L'índex del node (0, 1, 2...)
    double cost;   // El cost del salt anterior comparat amb el camí total
    double perduaInici;      // (costAresta - costMinim amb el mateix node de Inici)
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;



std::pair<double, std::vector<nodeConjelatP>> GenerarCamiAleatori(int n, MatriuResultatP& estructura, const std::vector<double>& min) {

    nodeConjelatP P = {
        0,    //node
        0.0,  //percentCost
        0.0,  //perduaInici
    };

    std::pair<double, std::vector<nodeConjelatP>> ret(0.0, std::vector<nodeConjelatP>(n, P));
    std::vector<bool> visitat(n, false);

    ret.first = 0;

    // set node inicial
    ret.second[0].node = 0;
    ret.second[0].perduaInici = 0;
    ret.second[0].cost = 0;
    visitat[0] = true;

    // set node final
    ret.second[n - 1].node = (n - 1);
    visitat[n - 1] = true;

    // Construïm el camí
    for (int pas = 1; pas < (n - 1); ++pas) {

        int actual = ret.second[pas - 1].node;
        std::vector<std::pair<int, double>> opcions;
        double sumaInverses = 0;

        // Busquem opcions no visitats
        for (int i = 1; i < n - 1; ++i) {
            if (!visitat[i]) {
                double d = estructura[actual][i].second;

                // Corretjir errors i definir pes
                double pes;
                if (d <= 0) pes = 100.0;
                else if (d >= std::numeric_limits<double>::max()) pes = 0;//pes = 0.0001;// el que farem es si es max es infinit i si es infinit no es una opcio
                else pes = 1.0 / std::pow(d, 4); // else pes = 1.0 / (d * d);

                opcions.push_back({ i, pes });
                sumaInverses += pes;

            }
        }

        // escollir el correcte i buscar-lo
        double llindar = ((double)rand() / RAND_MAX) * sumaInverses;

        double acumulat = 0;
        int triat = -1;

        for (auto& opcio : opcions) {
            acumulat += opcio.second;
            if (acumulat >= llindar) {
                triat = opcio.first;
                break;
            }
        }


        // Actualitzem el camí i l'estat
        ret.first += estructura[actual][triat].second;
        ret.second[pas].node = triat;
        ret.second[pas].cost = estructura[actual][triat].second;
        ret.second[pas].perduaInici = ret.second[pas].cost - min[pas];
        visitat[triat] = true;
    }

    ret.first += estructura[ret.second[n - 2].node][ret.second[n - 1].node].second;

    return ret;
}


bool MilloraCami(int n, std::pair<double, std::vector<nodeConjelatP>>& camiActual, MatriuResultatP& estructura, const std::vector<double>& minimsPrecalculats) {

    // Calcul dels pesos
    double sumaPesos = 0;
    for (int k = 1; k < n - 1; ++k) {
        //sumaPesos += camiActual.second[k].perduaInici * camiActual.second[k].cost;
        double p = std::pow(camiActual.second[k].perduaInici, 2) * camiActual.second[k].cost;
        sumaPesos += p + 0.1; // El +0.1 assegura que fins i tot els nodes "bons" puguin ser moguts
    }
    if (sumaPesos <= 1e-6) return false; // El camí ja és molt bo


    auto triarPosicio = [&](double suma, int no) {// (no < 0) -> desactivat
        double llindar = ((double)rand() / RAND_MAX) * suma;
        double acumulat = 0;
        for (int k = 1; k < n - 1; ++k) {
            if (k != no) {
                acumulat += camiActual.second[k].perduaInici * camiActual.second[k].cost;
                if (acumulat >= llindar) return k;
            }
            else {
                acumulat += camiActual.second[k].perduaInici * camiActual.second[k].cost;
            }
        }
        return n - 2;
        };

    // Triem "i" i "j"
    int i = triarPosicio(sumaPesos, -1);
    int j;
    int __ = 0;
    do {
        j = triarPosicio(sumaPesos, i);
        __++;
    } while (i == j && __ < 10);
    if (__ >= 10) return false;
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }



    // 3. Càlcul de costos per al 2-Opt (Inversió de segment)
    // Arestes de connexió
    double costAbans = estructura[camiActual.second[i - 1].node][camiActual.second[i].node].second
        + estructura[camiActual.second[j].node][camiActual.second[j + 1].node].second;


    double costDespres = estructura[camiActual.second[i - 1].node][camiActual.second[j].node].second
        + estructura[camiActual.second[i].node][camiActual.second[j + 1].node].second;


    double novaDist = camiActual.first - costAbans + costDespres;

    // Verifiquem per si realitzem el cambi 
    if (novaDist < camiActual.first && costDespres < 1e15) {

        std::reverse(camiActual.second.begin() + i, camiActual.second.begin() + j + 1);

        camiActual.first = novaDist;

        // RECALCULEM els sensors (//TODO:es mes facil que intentar reaprofitar com a maxim la 1/2 de les dades)
        for (int k = i; k <= j + 1; ++k) {
            int u = camiActual.second[k - 1].node;
            int v = camiActual.second[k].node;
            double nouCost = estructura[u][v].second;

            camiActual.second[k].cost = nouCost;
            camiActual.second[k].perduaInici = std::max(0.0, nouCost - minimsPrecalculats[u]);
        }
        return true;
    }
    else {
        return false;
    }
}

CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització 
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }

    // Escalat cúbic consolidat: (500 * n^3) * 2 = 1000 * n^3
    long long tempsTotal = static_cast<long long>(600 * std::pow(NUM_NODES, 3));

    // Amplada consolidada: (base * 1.5 * 1.5) = base * 2.25
    double pAmplada = 0.225;

    // CÀLCULS DERIVATS
    // L'amplada defineix quants intents nous fem
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));

    // La profunditat és el que sobra del temps dividit entre cada cerca
    int nPasosPerCerca = static_cast<int>(tempsTotal / nCercas);


    nodeConjelatP P = {
        0,    //node
        0.0,  //percentCost
        0.0,  //perduaInici
    };

    std::pair<double, std::vector<int>> millo(std::numeric_limits<double>::max(), std::vector<int>(NUM_NODES, true));
    std::pair<double, std::vector<nodeConjelatP>> actual(0.0, std::vector<nodeConjelatP>(NUM_NODES, P));

    if (NUM_NODES > 3) {


        for (int i = 0; i < nCercas; i++) {
            actual.first = 0;

            actual = GenerarCamiAleatori(NUM_NODES, estructura, minims);

            if (actual.first < millo.first) {

                for (int i = 0; i < NUM_NODES; i++) {
                    millo.second[i] = actual.second[i].node;
                }

                millo.first = actual.first;
            }
            for (int j = 0; j < nPasosPerCerca;) {
                for (; j < 10; j++) {
                    MilloraCami(NUM_NODES, actual, estructura, minims);
                }
                if (actual.first < millo.first) {
                    millo.first = actual.first;
                    for (int k = 0; k < NUM_NODES; k++) {
                        millo.second[k] = actual.second[k].node;
                    }
                }
            }
        }
    }
    else {//fer algo amb el 4?

        millo.second[0] = 0;
        millo.first = 0;

        for (int i = 1; i < NUM_NODES; ++i) {
            millo.second[i] = i;
            millo.first += estructura[millo.second[i - 1]][i].second;
        }
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.second[i - 1];
        int desti = millo.second[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}*/

/*
* V1.9 - Nota 4.8
* 

struct nodeConjelatP {
    int node;             // L'índex del node (0, 1, 2...)
    double cost;   // El cost del salt anterior comparat amb el camí total
    double perduaInici;      // (costAresta - costMinim amb el mateix node de Inici)
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;



std::pair<double, std::vector<nodeConjelatP>> GenerarCamiAleatori(int n, MatriuResultatP& estructura, const std::vector<double>& min) {

    nodeConjelatP P = {
        0,    //node
        0.0,  //percentCost
        0.0,  //perduaInici
    };

    std::pair<double, std::vector<nodeConjelatP>> ret(0.0, std::vector<nodeConjelatP>(n, P));
    std::vector<bool> visitat(n, false);

    ret.first = 0;

    // set node inicial
    ret.second[0].node = 0;
    ret.second[0].perduaInici = 0;
    ret.second[0].cost = 0;
    visitat[0] = true;

    // set node final
    ret.second[n - 1].node = (n - 1);
    visitat[n - 1] = true;

    // Construïm el camí
    for (int pas = 1; pas < (n - 1); ++pas) {

        int actual = ret.second[pas-1].node;
        std::vector<std::pair<int, double>> opcions;
        double sumaInverses = 0;

        // Busquem opcions no visitats
        for (int i = 1; i < n - 1; ++i) {
            if (!visitat[i]) {
                double d = estructura[actual][i].second;

                // Corretjir errors i definir pes
                double pes;
                if (d <= 0) pes = 100.0;
                else if (d >= std::numeric_limits<double>::max()) pes = 0;//pes = 0.0001;// el que farem es si es max es infinit i si es infinit no es una opcio
                else pes = 1.0 / std::pow(d, 4); // else pes = 1.0 / (d * d);

                opcions.push_back({ i, pes });
                sumaInverses += pes;

            }
        }

        // escollir el correcte i buscar-lo
        double llindar = ((double)rand() / RAND_MAX) * sumaInverses;

        double acumulat = 0;
        int triat = -1;

        for (auto& opcio : opcions) {
            acumulat += opcio.second;
            if (acumulat >= llindar) {
                triat = opcio.first;
                break;
            }
        }


        // Actualitzem el camí i l'estat
        ret.first += estructura[actual][triat].second;
        ret.second[pas].node=triat;
        ret.second[pas].cost = estructura[actual][triat].second;
        ret.second[pas].perduaInici = ret.second[pas].cost - min[pas];
        visitat[triat] = true;
    }

    ret.first += estructura[ret.second[n-2].node][ret.second[n - 1].node].second;

    return ret;
}


bool MilloraCami(int n, std::pair<double, std::vector<nodeConjelatP>>& camiActual, MatriuResultatP& estructura, const std::vector<double>& minimsPrecalculats) {

    // Calcul dels pesos
    double sumaPesos = 0;
    for (int k = 1; k < n - 1; ++k) {
        //sumaPesos += camiActual.second[k].perduaInici * camiActual.second[k].cost;
        double p = std::pow(camiActual.second[k].perduaInici, 2) * camiActual.second[k].cost;
        sumaPesos += p + 0.1; // El +0.1 assegura que fins i tot els nodes "bons" puguin ser moguts
    }
    if (sumaPesos <= 1e-6) return false; // El camí ja és molt bo


    auto triarPosicio = [&](double suma, int no) {// (no < 0) -> desactivat
        double llindar = ((double)rand() / RAND_MAX) * suma;
        double acumulat = 0;
        for (int k = 1; k < n - 1; ++k) {
            if (k != no) {
                acumulat += camiActual.second[k].perduaInici * camiActual.second[k].cost;
                if (acumulat >= llindar) return k;
            }
            else {
                acumulat += camiActual.second[k].perduaInici * camiActual.second[k].cost;
            }
        }
        return n - 2;
    };

    // Triem "i" i "j"
    int i = triarPosicio(sumaPesos, -1);
    int j;
    int __= 0;
    do {
        j = triarPosicio(sumaPesos, i);
        __++;
    } while (i == j && __<10);
    if (__ >= 10) return false;
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }



    // 3. Càlcul de costos per al 2-Opt (Inversió de segment)
    // Arestes de connexió
    double costAbans = estructura[camiActual.second[i - 1].node][camiActual.second[i].node].second
        + estructura[camiActual.second[j].node][camiActual.second[j + 1].node].second;

    /* // no existeixen arestes unidirecionals
    // Cost intern
    double costInternAbans = 0;
    for (int k = i; k < j; ++k)
        costInternAbans += estructura[camiActual.second[k].node][camiActual.second[k + 1].node].second;
     *//*

double costDespres = estructura[camiActual.second[i - 1].node][camiActual.second[j].node].second
+ estructura[camiActual.second[i].node][camiActual.second[j + 1].node].second;

/* // no existeixen arestes unidirecionals
double costInternDespres = 0;
for (int k = i; k < j; ++k)
    costInternDespres += estructura[camiActual.second[k].node][camiActual.second[k + 1].node].second;
*//*

double novaDist = camiActual.first - costAbans + costDespres;

// Verifiquem per si realitzem el cambi 
if (novaDist < camiActual.first && costDespres < 1e15) {

    std::reverse(camiActual.second.begin() + i, camiActual.second.begin() + j + 1);

    camiActual.first = novaDist;

    // RECALCULEM els sensors (//TODO:es mes facil que intentar reaprofitar com a maxim la 1/2 de les dades)
    for (int k = i; k <= j + 1; ++k) {
        int u = camiActual.second[k - 1].node;
        int v = camiActual.second[k].node;
        double nouCost = estructura[u][v].second;

        camiActual.second[k].cost = nouCost;
        camiActual.second[k].perduaInici = std::max(0.0, nouCost - minimsPrecalculats[u]);
    }
    return true;
}
else {
    return false;
}
}

CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització 
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }

    /*
    // input
    int tempsTotal = 100000*(NUM_NODES - 3);//500  //100000 Millo:50000         // El teu pressupost fix d'iteracions (maxim 2M)
    double pAmplada = 0.06;//0.07 //0.006 Millo:0.006          // Quin % de l'esforç dediquem a obrir noves branques

    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca
    */
    /*
    // Escalat quadràtic
    long long tempsTotal = static_cast<long long>(100 * std::pow(NUM_NODES, 4));

    // Augmentem l'amplada per a problemes grans per no quedar-nos atrapats en un sol camí dolent
    double pAmplada = (NUM_NODES < 20) ? 0.10 : 0.03;

    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca
    *//*
    // Escalat cúbic: prou fort per a 100 nodes, però no explota
    long long tempsTotal = static_cast<long long>(500 * std::pow(NUM_NODES, 3));
    tempsTotal = tempsTotal * 2;
    // Seguretat absoluta per no passar-se del temps de l'examen
    //if (NUM_NODES > 50 && tempsTotal > 10000000) tempsTotal = 10000000;
    //if (NUM_NODES > 80 && tempsTotal > 15000000) tempsTotal = 15000000;

    // Augmentem l'amplada per a problemes grans per no quedar-nos atrapats en un sol camí dolent
    double pAmplada = (NUM_NODES < 20) ? 0.10 : 0.03;
    pAmplada = pAmplada * 1.5;
    pAmplada = pAmplada * 1.5;
    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca


    nodeConjelatP P = {
        0,    //node
        0.0,  //percentCost
        0.0,  //perduaInici
    };

    std::pair<double, std::vector<int>> millo(std::numeric_limits<double>::max(), std::vector<int>(NUM_NODES, true));
    std::pair<double, std::vector<nodeConjelatP>> actual(0.0, std::vector<nodeConjelatP>(NUM_NODES, P));

    if (NUM_NODES > 3) {

        for (int i = 0; i < nCercas; i++) {
            actual.first = 0;

            actual = GenerarCamiAleatori(NUM_NODES, estructura, minims);

            if (actual.first < millo.first) {

                for (int i = 0; i < NUM_NODES; i++) {
                    millo.second[i] = actual.second[i].node;
                }

                millo.first = actual.first;
            }

            /*
            for (int j = 0; j < nPasosPerCerca; j++) {
                if (MilloraCami(NUM_NODES, actual, estructura, minims)) {

                    for (int i = 0; i < NUM_NODES; i++) {
                        millo.second[i] = actual.second[i].node;
                    }

                    millo.first = actual.first;
                }

            }
            //*//*
            //*
            for (int j = 0; j < nPasosPerCerca;) {
                for (; j < 5; j++) {
                    MilloraCami(NUM_NODES, actual, estructura, minims);
                }
                if (actual.first < millo.first) {
                    millo.first = actual.first;
                    for (int k = 0; k < NUM_NODES; k++) {
                        millo.second[k] = actual.second[k].node;
                    }
                }
            }
            //*//*
        }
    }
    else {//fer algo amb el 4?

        millo.second[0] = 0;
        millo.first = 0;

        for (int i = 1; i < NUM_NODES; ++i) {
            millo.second[i] = i;
            millo.first += estructura[millo.second[i - 1]][i].second;
        }
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.second[i - 1];
        int desti = millo.second[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}
*/

/*
* V1.5 - upgrate generar cami
* 
struct nodeConjelatP
{
    std::vector<int> m_camiActual;
    double m_distacia;
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;



std::vector<int> GenerarCamiAleatori(int n, double& distanciaRetorn, MatriuResultatP& estructura) {

    std::vector<int> ret(n);
    std::vector<bool> visitat(n, false);

    distanciaRetorn = 0;

    // set node inicial
    ret[0] = 0;
    visitat[0] = true;

    // set node final
    ret[n - 1] = (n - 1);
    visitat[n - 1] = true;

    // Construïm el camí
    for (int pas = 1; pas < (n - 1); ++pas) {

        int actual = ret[pas-1];
        std::vector<std::pair<int, double>> opcions;
        double sumaInverses = 0;

        // Busquem opcions no visitats
        for (int i = 1; i < n - 1; ++i) {
            if (!visitat[i]) {
                double d = estructura[actual][i].second;

                // Corretjir errors i definir pes
                double pes;
                if (d <= 0) pes = 100.0;
                else if (d >= std::numeric_limits<double>::max()) pes = 0;//pes = 0.0001;// el que farem es si es max es infinit i si es infinit no es una opcio
                else pes = 1.0 / (d * d);

                opcions.push_back({ i, pes });
                sumaInverses += pes;
            }
        }

        // escollir el correcte i buscar-lo
        double llindar = ((double)rand() / RAND_MAX) * sumaInverses;

        double acumulat = 0;
        int triat = -1;

        for (auto& opcio : opcions) {
            acumulat += opcio.second;
            if (acumulat >= llindar) {
                triat = opcio.first;
                break;
            }
        }

        // Seguretat: si per temes de decimals no ha triat ningú, agafem el darrer
        if (triat == -1) triat = opcions.back().first;

        // Actualitzem el camí i l'estat
        distanciaRetorn += estructura[actual][triat].second;
        ret[pas]=triat;
        visitat[triat] = true;
    }

    distanciaRetorn += estructura[ret[n-2]][ret[n - 1]].second;

    return ret;
}

bool Intercambi(int n, std::vector<int>& cami, double& distanciaActual, MatriuResultatP& estructura) {

    int i;
    int j;

    do {
        i = rand() % (n - 2) + 1;
        j = rand() % (n - 2) + 1;
    } while (i == j);
    double distDec;
    double distInc;
    double novaDist;

    if (abs(i - j) == 1) {
        int _1r = std::min(i, j);
        int _2n = std::max(i, j);

        // Provem l'intercanvi
        distDec = estructura[cami[_1r - 1]][cami[_1r]].second
            + estructura[cami[_1r]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_2n + 1]].second;

        distInc = estructura[cami[_1r - 1]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_1r]].second;
        +estructura[cami[_1r]][cami[_2n + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }
    else {
        // Provem l'intercanvi
        distDec = estructura[cami[j - 1]][cami[j]].second
            + estructura[cami[j]][cami[j + 1]].second;
        distDec += estructura[cami[i - 1]][cami[i]].second
            + estructura[cami[i]][cami[i + 1]].second;

        distInc = estructura[cami[j - 1]][cami[i]].second
            + estructura[cami[i]][cami[j + 1]].second;
        distInc += estructura[cami[i - 1]][cami[j]].second
            + estructura[cami[j]][cami[i + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }


    if (novaDist > 0 && novaDist < distanciaActual) {
        std::swap(cami[i], cami[j]); // Millora acceptada
        distanciaActual = novaDist;
        return true;
    }

    return false;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }


    // input
    int tempsTotal = 100000*(NUM_NODES - 3);//500  //100000 Millo:50000         // El teu pressupost fix d'iteracions (maxim 2M)
    double pAmplada = 0.06;//0.07 //0.006 Millo:0.006          // Quin % de l'esforç dediquem a obrir noves branques

    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca


    double distanciaActual;

    nodeConjelatP millo = {
        std::vector<int>(NUM_NODES),         // m_camiActual;
        std::numeric_limits<double>::max()   // m_distacia;
    };

    if (NUM_NODES > 3) {

        for (int i = 0; i < nCercas; i++) {
            distanciaActual = 0;

            std::vector<int> cami=GenerarCamiAleatori(NUM_NODES, distanciaActual, estructura);

            if (distanciaActual < millo.m_distacia) {
                millo.m_camiActual = cami;
                millo.m_distacia = distanciaActual;
            }

            for (int j = 0; j < nPasosPerCerca; j++) {
                if (Intercambi(NUM_NODES, cami, distanciaActual, estructura)) {
                    millo.m_camiActual = cami;
                    millo.m_distacia = distanciaActual;
                }
            }
        }
    }
    else {//fer algo amb el 4?

        millo.m_camiActual[0] = 0;
        millo.m_distacia = 0;

        for (int i = 1; i < NUM_NODES; ++i) {
            millo.m_camiActual[i] = i;
            millo.m_distacia += estructura[millo.m_camiActual[i - 1]][i].second;
        }
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.m_camiActual[i - 1];
        int desti = millo.m_camiActual[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}

*/

/*
* V1 - Nota: 1.8 - 2
* 

struct nodeConjelatP
{
    std::vector<int> m_camiActual;
    double m_distacia;
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;


void GenerarCamiAleatori(std::vector<int>& cami, double& distanciaActual, MatriuResultatP& estructura) {

    distanciaActual = 0;

    if (cami.size() > 2) {
        std::shuffle(cami.begin() + 1, cami.end() - 1, std::default_random_engine(std::random_device{}()));
    }

    for (size_t i = 1; i < cami.size(); ++i) {
        distanciaActual += estructura[cami[i - 1]][cami[i]].second;
    }
}

bool Intercambi(int n,std::vector<int>& cami, double& distanciaActual, MatriuResultatP& estructura) {

    int i;
    int j;

    do {
        i = rand() % (n - 2) + 1;
        j = rand() % (n - 2) + 1;
    } while(i == j);
    double distDec;
    double distInc;
    double novaDist;

    if (abs(i - j) == 1) {
        int _1r = std::min(i, j);
        int _2n = std::max(i, j);

        // Provem l'intercanvi
        distDec = estructura[cami[_1r - 1]][cami[_1r]].second
            + estructura[cami[_1r]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_2n + 1]].second;

        distInc = estructura[cami[_1r - 1]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_1r]].second;
            + estructura[cami[_1r]][cami[_2n + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }
    else {
        // Provem l'intercanvi
        distDec = estructura[cami[j - 1]][cami[j]].second
            + estructura[cami[j]][cami[j + 1]].second;
        distDec += estructura[cami[i - 1]][cami[i]].second
            + estructura[cami[i]][cami[i + 1]].second;

        distInc = estructura[cami[j - 1]][cami[i]].second
            + estructura[cami[i]][cami[j + 1]].second;
        distInc += estructura[cami[i - 1]][cami[j]].second
            + estructura[cami[j]][cami[i + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }


    if (novaDist > 0 && novaDist < distanciaActual) {
        std::swap(cami[i], cami[j]); // Millora acceptada
        distanciaActual = novaDist;
        return true;
    }

    return false;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }

    // input
    int tempsTotal = 50000;//500  //100000 Millo:50000         // El teu pressupost fix d'iteracions (maxim 2M)
    double pAmplada = 0.006;//0.07 //0.006 Millo:0.006          // Quin % de l'esforç dediquem a obrir noves branques

    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca

    double distanciaActual;

    nodeConjelatP millo = {
        std::vector<int>(NUM_NODES),         // m_camiActual;
        std::numeric_limits<double>::max()   // m_distacia;
    };

    std::vector<int> camiPlantilla(NUM_NODES);
    for (int i = 0; i < NUM_NODES; ++i) {
        camiPlantilla[i] = i;
    }


    if (NUM_NODES>3) {
        std::vector<int> cami;

        for (int i = 0; i < nCercas; i++) {
            int j = 0;
            cami = camiPlantilla;
            distanciaActual = 0;
            do {
                GenerarCamiAleatori(cami, distanciaActual, estructura);// tornar a executar si no es lo suficient ment bo
                j++;
            } while (distanciaActual > millo.m_distacia && j < nPasosPerCerca);
            if (distanciaActual < millo.m_distacia) {
                millo.m_camiActual = cami;
                millo.m_distacia = distanciaActual;
            }
            for (; j < nPasosPerCerca; j++) {
                if (Intercambi(NUM_NODES, cami, distanciaActual, estructura)) {// els bons anar mes fons?->no perque si no es bo no el executes
                    millo.m_camiActual = cami;
                    millo.m_distacia = distanciaActual;
                }
            }

            //*
            for(int l = 0; i < intents; l++){
                camiCerca = cami;
                for (; j < (nPasosPerCerca / intents); j++) {
                    if (Intercambi(NUM_NODES, camiCerca, distanciaActual, estructura)) {// els bons anar mes fons?->no perque si no es bo no el executes
                        millo.m_camiActual = camiCerca;
                        millo.m_distacia = distanciaActual;
                    }
                }
            }
            //*//*
        }
    }
    else {
        distanciaActual = 0;

        for (size_t i = 1; i < camiPlantilla.size(); ++i) {
            distanciaActual += estructura[camiPlantilla[i - 1]][camiPlantilla[i]].second;
        }

        millo.m_camiActual = camiPlantilla;
        millo.m_distacia = distanciaActual;
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.m_camiActual[i - 1];
        int desti = millo.m_camiActual[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}
*/


/*
* V0.5 - estructura inicial no comprovat
* 

struct nodeConjelatP
{
    std::vector<int> m_camiActual;
    double m_distacia;
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;


void GenerarCamiAleatori(std::vector<int>& cami, double& distanciaActual, MatriuResultatP estructura) {

    distanciaActual = 0;

    if (cami.size() > 2) {
        std::shuffle(cami.begin() + 1, cami.end() - 1, std::default_random_engine(std::random_device{}()));
    }

    for (size_t i = 1; i < cami.size(); ++i) {
        distanciaActual += estructura[cami[i - 1]][cami[i]].second;
    }
}

bool Intercambi(int n,std::vector<int>& cami, double& distanciaActual, MatriuResultatP estructura) {

    int i;
    int j;

    do {
        i = rand() % (n - 2) + 1;
        j = rand() % (n - 2) + 1;
    } while(i == j);

    // Provem l'intercanvi
    double distDec  = estructura[cami[j - 1]][cami[j]].second + estructura[cami[j]][cami[j - 1]].second;
           distDec += estructura[cami[i - 1]][cami[i]].second + estructura[cami[i]][cami[i - 1]].second;

    double distInc  = estructura[cami[j - 1]][cami[i]].second + estructura[cami[i]][cami[j - 1]].second;
           distInc += estructura[cami[i - 1]][cami[j]].second + estructura[cami[j]][cami[i - 1]].second;

    double novaDist = distanciaActual + distInc - distDec;

    if (novaDist > 0 && novaDist < distanciaActual) {
        std::swap(cami[i], cami[j]); // Millora acceptada
        distanciaActual = novaDist;
        return true;
    }

    return false;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }


    int temps = , percentatgePasos = ;// input
    int nCercas = temps*(1- percentatgePasos), nPasosPerCerca = temps * (percentatgePasos);// valors

    double distanciaActual;

    nodeConjelatP millo = {
        std::vector<int>(NUM_NODES),         // m_camiActual;
        std::numeric_limits<double>::max()   // m_distacia;
    };

    std::vector<int> camiPlantilla(NUM_NODES);
    for (int i = 0; i < NUM_NODES; ++i) {
        camiPlantilla[i] = i;
    }

    std::vector<int> cami;

    for (int i = 0; i < nCercas; i++) {
        cami = camiPlantilla;
        distanciaActual = 0;
        GenerarCamiAleatori(cami, distanciaActual, estructura);
        if (distanciaActual < millo.m_distacia) {
            millo.m_camiActual = cami;
            millo.m_distacia = distanciaActual;
        }
        for (int j = 0; j < nPasosPerCerca; j++) {
            if (Intercambi(NUM_NODES, cami, distanciaActual, estructura)) {
                millo.m_camiActual = cami;
                millo.m_distacia = distanciaActual;
            }
        }
    }



    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.m_camiActual[i - 1];
        int desti = millo.m_camiActual[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}
*/

/*
* V0
CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
	return CTrack(&graph);
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
struct nodeConjelatP
{
    std::vector<int> m_camiActual;
    double m_distacia;
};


using InfoConnexioP = std::pair<std::list<CEdge*>, double>;
using MatriuResultatP = std::vector<std::vector<InfoConnexioP>>;


void GenerarCamiAleatori(std::vector<int>& cami, double& distanciaActual, MatriuResultatP& estructura) {

    distanciaActual = 0;

    if (cami.size() > 2) {
        std::shuffle(cami.begin() + 1, cami.end() - 1, std::default_random_engine(std::random_device{}()));
    }

    for (size_t i = 1; i < cami.size(); ++i) {
        distanciaActual += estructura[cami[i - 1]][cami[i]].second;
    }
}

bool Intercambi(int n, std::vector<int>& cami, double& distanciaActual, MatriuResultatP& estructura) {

    int i;
    int j;

    do {
        i = rand() % (n - 2) + 1;
        j = rand() % (n - 2) + 1;
    } while (i == j);
    double distDec;
    double distInc;
    double novaDist;

    if (abs(i - j) == 1) {
        int _1r = std::min(i, j);
        int _2n = std::max(i, j);

        // Provem l'intercanvi
        distDec = estructura[cami[_1r - 1]][cami[_1r]].second
            + estructura[cami[_1r]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_2n + 1]].second;

        distInc = estructura[cami[_1r - 1]][cami[_2n]].second
            + estructura[cami[_2n]][cami[_1r]].second;
        +estructura[cami[_1r]][cami[_2n + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }
    else {
        // Provem l'intercanvi
        distDec = estructura[cami[j - 1]][cami[j]].second
            + estructura[cami[j]][cami[j + 1]].second;
        distDec += estructura[cami[i - 1]][cami[i]].second
            + estructura[cami[i]][cami[i + 1]].second;

        distInc = estructura[cami[j - 1]][cami[i]].second
            + estructura[cami[i]][cami[j + 1]].second;
        distInc += estructura[cami[i - 1]][cami[j]].second
            + estructura[cami[j]][cami[i + 1]].second;

        novaDist = distanciaActual + distInc - distDec;
    }


    if (novaDist > 0 && novaDist < distanciaActual) {
        std::swap(cami[i], cami[j]); // Millora acceptada
        distanciaActual = novaDist;
        return true;
    }

    return false;
}


CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
    const size_t NUM_NODES = visits.m_Vertices.size();


    // Inicialització
    MatriuResultatP estructura(NUM_NODES, std::vector<InfoConnexioP>(NUM_NODES, { {}, 0.0 }));
    std::vector<double> minims(NUM_NODES);
    if (true) {
        int i = 0;
        for (CVertex* it : visits.m_Vertices) {
            double min = std::numeric_limits<double>::max();
            DijkstraQueue(graph, it);
            int j = 0;
            for (auto it1 : visits.m_Vertices) {
                if (it == it1) {
                    estructura[i][j].second = std::numeric_limits<double>::infinity();
                }
                else {
                    CVertex* node = it1;
                    if (min > node->m_DijkstraDistance) min = node->m_DijkstraDistance;
                    estructura[i][j].second = node->m_DijkstraDistance;
                    while (node->m_Name != it->m_Name) {
                        estructura[i][j].first.push_front(node->m_pDijkstraPrevious);
                        node = node->m_pDijkstraPrevious->m_pOrigin;
                    }
                }
                j++;
            }
            minims[i] = min;
            i++;
        }
    }

    // input
    int tempsTotal = 50000;//500  //100000 Millo:50000         // El teu pressupost fix d'iteracions (maxim 2M)
    double pAmplada = 0.006;//0.07 //0.006 Millo:0.006          // Quin % de l'esforç dediquem a obrir noves branques

    // CALCULS DERIVATS
    int nCercas = static_cast<int>(std::max(1.0, tempsTotal * pAmplada));                           // L'amplada defineix quants intents nous fem
    int nPasosPerCerca = static_cast<int>(std::floor(static_cast<double>(tempsTotal) / nCercas));   // La profunditat és el que sobra del temps dividit entre cada cerca

    double distanciaActual;

    nodeConjelatP millo = {
        std::vector<int>(NUM_NODES),         // m_camiActual;
        std::numeric_limits<double>::max()   // m_distacia;
    };

    std::vector<int> camiPlantilla(NUM_NODES);
    for (int i = 0; i < NUM_NODES; ++i) {
        camiPlantilla[i] = i;
    }


    if (NUM_NODES > 3) {
        std::vector<int> cami;

        for (int i = 0; i < nCercas; i++) {
            int j = 0;
            cami = camiPlantilla;
            distanciaActual = 0;
            do {
                GenerarCamiAleatori(cami, distanciaActual, estructura);// tornar a executar si no es lo suficient ment bo
                j++;
            } while (distanciaActual > millo.m_distacia && j < nPasosPerCerca);
            if (distanciaActual < millo.m_distacia) {
                millo.m_camiActual = cami;
                millo.m_distacia = distanciaActual;
            }
            for (; j < nPasosPerCerca; j++) {
                if (Intercambi(NUM_NODES, cami, distanciaActual, estructura)) {// els bons anar mes fons?->no perque si no es bo no el executes
                    millo.m_camiActual = cami;
                    millo.m_distacia = distanciaActual;
                }
            }

            //*
            for (int l = 0; i < intents; l++) {
                camiCerca = cami;
                for (; j < (nPasosPerCerca / intents); j++) {
                    if (Intercambi(NUM_NODES, camiCerca, distanciaActual, estructura)) {// els bons anar mes fons?->no perque si no es bo no el executes
                        millo.m_camiActual = camiCerca;
                        millo.m_distacia = distanciaActual;
                    }
                }
            }
            // 
            */ 
            /*
        }
    }
    else {
        distanciaActual = 0;

        for (size_t i = 1; i < camiPlantilla.size(); ++i) {
            distanciaActual += estructura[camiPlantilla[i - 1]][camiPlantilla[i]].second;
        }

        millo.m_camiActual = camiPlantilla;
        millo.m_distacia = distanciaActual;
    }


    CTrack ret(&graph);
    for (int i = 1; i < NUM_NODES; i++) {
        int origen = millo.m_camiActual[i - 1];
        int desti = millo.m_camiActual[i];

        for (CEdge* aresta : estructura[origen][desti].first) {
            ret.m_Edges.push_back(aresta);
        }
    }

    return ret;
}
//* */