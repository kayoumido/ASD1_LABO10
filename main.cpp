#include <iostream>
#include <queue>
#include <map>
#include <stack>

/*
 * TODO list
 * - CONTAINEURS : - Une Queue qui stock les noeuds à traité (on ajoute au fur et a mesure les voisins)
 *                 - Un Array qui stock ce qui a été visité, par qui => v[10] = 11 le noeud 10 a été visité par 11
 *                 - Un Map qui stock la clé (string de la séquence) avec une valeur qui est le noeud associé à la clé
 *                 => par exemple on a un voisin qui est "1324058976" si cette valeur existe dans notre Map, et son noeud
 *                    associé (valeur de la clé "1324058976") est 10, on sait qu'il a déjà été visité donc on va pas le revisiter
 *
 * - Parcours en largeur qui prend en param
 */

using namespace std;

typedef string Sommet;
Sommet sommetDepart = "754236108";
Sommet sommetObjectif = "012345678";


void parcoursLargueur(Sommet sommet);
vector<Sommet> chercherVoisins(const Sommet& sommet);
void traiter(Sommet& sommet, const map<Sommet, Sommet>& mapTraite);

int main() {

    parcoursLargueur(sommetDepart);

    return EXIT_SUCCESS;
}


void parcoursLargueur(Sommet sommet){
    queue<Sommet> queueATraiter;
    queueATraiter.push(sommet);

    map<Sommet, Sommet> mapMarque;
    mapMarque.insert(make_pair(sommet, sommet));

    while(!queueATraiter.empty()){
        // On récupère un sommet dans la file
        sommet = queueATraiter.front();
        queueATraiter.pop();
        traiter(sommet, mapMarque);
        // On récupère les sommets voisins et parcours
        vector<Sommet> voisins = chercherVoisins(sommet);
        for(size_t i = 0; i < voisins.size(); ++i){
            // On marque le sommet en cours et l'ajoute dans le queue, si il n'est pas déjà marqué
            if(!mapMarque.count(voisins[i])){
                queueATraiter.push(voisins[i]);
                mapMarque.insert(make_pair(voisins[i], sommet));
            }
        }
    }
}

vector<Sommet> chercherVoisins(const Sommet& sommet){
    vector<Sommet> voisins;
    size_t zeroPos = sommet.find('0');
    Sommet sommetInitiale = sommet;
    switch (zeroPos){
        case 0:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[1]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[3]);
            voisins.push_back(sommetInitiale);
            break;
        case 1:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[0]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[2]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[4]);
            voisins.push_back(sommetInitiale);
            break;
        case 2:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[1]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[5]);
            voisins.push_back(sommetInitiale);
            break;
        case 3:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[0]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[4]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[6]);
            voisins.push_back(sommetInitiale);
            break;
        case 4:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[1]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[3]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[5]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[7]);
            voisins.push_back(sommetInitiale);
            break;
        case 5:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[2]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[4]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[8]);
            voisins.push_back(sommetInitiale);
        case 6:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[3]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[7]);
            voisins.push_back(sommetInitiale);
            break;
        case 7:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[4]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[6]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[8]);
            voisins.push_back(sommetInitiale);
        case 8:
            std::swap(sommetInitiale[zeroPos], sommetInitiale[5]);
            voisins.push_back(sommetInitiale);
            sommetInitiale = sommet;
            std::swap(sommetInitiale[zeroPos], sommetInitiale[7]);
            voisins.push_back(sommetInitiale);
        default:
            break;
    }

    return voisins;
}

void traiter(Sommet& sommet, const map<Sommet, Sommet>& mapTraite){
    if(sommet == sommetObjectif){
        stack<size_t > pileFinal;

        Sommet parent = sommet;
        while(parent != sommetDepart){
            pileFinal.push(parent.find('0'));
            parent = mapTraite.find(sommet)->second;
            sommet = parent;
        }

        while(!pileFinal.empty()){
            cout << pileFinal.top() << " ";
            pileFinal.pop();
        }

    }
}