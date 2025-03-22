#include "BallTree.h"

bool operator>=(Coordinate c1, Coordinate c2)
{
    double epsilon = 0.0000001;
    return (c1.lat >= c2.lat - epsilon && c1.lat <= c2.lat + epsilon
        && c1.lon >= c2.lon - epsilon && c1.lon <= c2.lon + epsilon);
}

BallTree* BallTree::operator=(const BallTree*& t)
{
    BallTree* f = new BallTree();
    f->m_radi = t->m_radi;
    f->m_pivot = t->m_pivot;
    int i = 0;
    while (t->m_coordenades.size() > i)
    {
        f->m_coordenades.push_back(t->m_coordenades[i]);
    }

    f->m_root = t->m_root;
    f->m_left = t->m_left;
    f->m_right = t->m_right;

    return f;
}

double BallTree::calculaDistanciaLlunyana(const Coordinate& c, int& indexLluny)
{
    double mesLluny = -1;
    int i = 0;

    while (i < m_coordenades.size()) //calcular distancia dels nodes respecte el pivot
    {
        double distancia = Util::DistanciaHaversine(m_coordenades[i], c);
        if (distancia > mesLluny)
        {
            mesLluny = distancia; //guardar distancia del punt mes llunya al pivot
            indexLluny = i; //guardar index del punt mes llunya
        }
        i++;
    }

    return mesLluny;
}

std::vector<Coordinate> comprovarCoordenades(const std::vector<Coordinate>& coordenades) //provisional
{
    std::vector<Coordinate> c; //vector final de coordenades sense reptir

    bool b;

    c.push_back(coordenades[0]);
    for (int i = 1; i < (coordenades.size()); i++)
    {
        b = true;
        for (int j = 0; j < c.size(); j++)
        {
            if (coordenades[i] >= c[j])
                b = false;
        }
        if (b)
            c.push_back(coordenades[i]);
    }

    return c;
}
void BallTree::construirArbreRec(const std::vector<Coordinate>& coordenades) 
{
    std::vector<Coordinate>::const_iterator it = coordenades.begin();
    while (it != coordenades.end()) //creacio del vector de coordenades de l'arbre
    {
        m_coordenades.push_back(*it);
        it++;
    }

    //if (m_coordenades.size() > 4) //creacio arbre --> recursivitat
    //{
        m_pivot = Util::calcularPuntCentral(m_coordenades); //seleccio del pivot

        //Trobar punts mes llunyans
        int indexA = 0;
        m_radi = calculaDistanciaLlunyana(m_pivot, indexA);

        int indexB = 0;
        double distB = calculaDistanciaLlunyana(m_coordenades[indexA], indexB);

        //Agrupacio boles --> bucle comprovar distancies respecte A i B --> crear vectors de coordenades
        std::vector<Coordinate> cordA, cordB;

        for (int i = 0; i < m_coordenades.size(); i++)
        {
            if (Util::DistanciaHaversine(m_coordenades[i], m_coordenades[indexA]) < Util::DistanciaHaversine(m_coordenades[i], m_coordenades[indexB]))
                cordA.push_back(m_coordenades[i]);
            else
                cordB.push_back(m_coordenades[i]);
        }

        //CREAR BALLTREES FILLS
        if ((cordA.size() >= 1 && cordB.size() >= 1))//((cordA.size() >= 1 && cordB.size() > 1) || (cordA.size() > 1 && cordB.size() >= 1)) //arbre binari --> s'han de complir les dues condicions
        {
            m_right = new BallTree;
            m_right->m_root = this;
            m_right->construirArbreRec(cordA);

            m_left = new BallTree;
            m_left->m_root = this;
            m_left->construirArbreRec(cordB);
        }
    //}
}
void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    // TODO: Utilitza aquest metode per construir el teu BallTree
    // TODO: amb les coordenades que se us passen per parametre
    std::vector<Coordinate> c;
    m_root = this;
    c = comprovarCoordenades(coordenades);
    construirArbreRec(c);
    
}


//METODES RECURSIUS
void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    if (m_right != nullptr)
        m_right->inOrdre(out);

    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_left != nullptr)
        m_left->inOrdre(out);
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_right != nullptr)
        m_right->preOrdre(out);

    if (m_left != nullptr)
        m_left->preOrdre(out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2

    if (m_right != nullptr)
        m_right->postOrdre(out);

    if (m_left != nullptr)
        m_left->postOrdre(out);

    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);
    
}

                                                //PDI --> buscar node mes proper del balltree a aquestes coordenades
Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    
    //Calcular distancia punt central-PDI
    double D1 = Util::DistanciaHaversine(targetQuery, ball->m_pivot);

    //Calcular distancia punt central-Q
    double D2 = Util::DistanciaHaversine(Q, targetQuery);

    if ((D1 - ball->m_radi) >= D2)
        return Q; //actualitzar Q fins que sigui el punt mes proper
    else
    {
        if (ball->m_right == nullptr && ball->m_left == nullptr) //la bola es una fulla
        {
            double distancia = Util::DistanciaHaversine(targetQuery, Q); //distancia nodes arrel

            for (int i = 0; i < ball->m_coordenades.size(); i++) //comprovar distancia del PDI als punts de l'arrel
            {
                if (Util::DistanciaHaversine(targetQuery, ball->m_coordenades[i]) < distancia)
                {
                    distancia = Util::DistanciaHaversine(targetQuery, ball->m_coordenades[i]);
                    Q = ball->m_coordenades[i]; //actualitzacio de Q amb la coordenada mes propera al PDI
                }
            }

            if ((D1 - ball->m_radi) >= D2)
                return Q;
        }
        else //la bola NO es una fulla --> recursivitat
        {
            if (ball->m_left != nullptr && ball->m_right != nullptr)
            {
                double Da = Util::DistanciaHaversine(targetQuery, ball->m_left->m_pivot);
                double Db = Util::DistanciaHaversine(targetQuery, ball->m_right->m_pivot);

                if (Da < Db) //cercar dreta -> esquerra si Da < Db
                {
                    nodeMesProper(targetQuery, Q, ball->m_left);
                    nodeMesProper(targetQuery, Q, ball->m_right);
                    return Q;
                }

                else //cercar esquerra --> dreta
                {
                    nodeMesProper(targetQuery, Q, ball->m_right);
                    nodeMesProper(targetQuery, Q, ball->m_left);
                    return Q;
                }
            } 
        }
    }
}