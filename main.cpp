/**
-----------------------------------------------------------------------------------
Laboratoire : 10 - Graphe
@file       main.cpp
@author     Loïc Dessaules, Doran Kayoumi, Gabrielle Thurnherr
@date       15/06/2019
@brief      Permet de trouver la séquence de résolution en partant d'un sommet spécifique du jeu Taquin 3x3
            https://ocuisenaire.github.io/ASD1-Labs/taquin/
@remark1    Pour que notre programme puisse résoudre le taquin 4x4, il faudrait seulement changer la méthode de stockage
            d'un Sommet, car nous aurions des nombres de 2 chiffres. Cela sera donc plus représentable aussi facilement dans
            une string. Il faudrait stocker un Sommet par exemple dans un array. Et donc adaptée les fonctions qui utilise des
            Sommets. Mais la logique des fonctions a bien été décomposées et ne devrai pas changer.
@remark2    Le but labo était de trouver la séquence de résolution du taquin 3x3 et non 4x4, c'est pour cela que nous avons
            décider d'utiliser un type string pour représenter un Sommet, car c'est plus simple et moins lourd.
Compilateur MinGW-gcc 6.3.0
**/

#include <iostream>
#include <queue>
#include <map>
#include <stack>

using namespace std;

typedef string Sommet;

const Sommet SOMMET_OBJECTIF = "012345678";
const size_t GRILLE_MAX_LIGNE = 3;
const size_t GRILLE_MAX_COL = 3;

/**
 * Effectue un parcours en largeur du graphe défini par des Sommets
 * @param Sommet sommet Notre sommet de départ
 */
void parcoursLargueur(Sommet sommet);

/**
 * Permet de récupérer un sommet voisin par rapport à un sommet donné
 * @param sommetInitiale Le Sommet initiale pour lequel nous voulons son voisin
 * @param zeroPos La position du zero dans le sommet initiale
 * @param posEchange La position avec laquelle nous voulons echanger le zero
 * @return Le Sommet voisin
 */
Sommet recupererVoisin(Sommet sommetInitiale, size_t zeroPos, size_t posEchange);

/**
 * Permet de récupérer tous les sommets voisins par rapport à un sommet donné
 * @param sommet  Le sommet pour lequel nous voulons tous ses voisins
 * @return Un Vector contenant tous les voisins de notre sommet
 */
vector<Sommet> recupererVoisins(const Sommet& sommet);

/**
 * Traite le sommet en cours et affiche la séquence de résolution si l'on a trouver le sommet objectif
 * @param sommetDepart Notre sommet de départ (initiale)
 * @param sommet Notre sommet courant
 * @param mapTraite La map contenant les sommets / sommets parents
 */
void traiter(const Sommet& sommetDepart, Sommet& sommet, const map<Sommet, Sommet>& mapTraite);


int main() {
    Sommet sommetDepart;
    cout << "Veuillez entrer la séquence de départ sans espaces : ";
    cin >> sommetDepart;
    parcoursLargueur(sommetDepart);

    return EXIT_SUCCESS;
}


void parcoursLargueur(Sommet sommet){
    const Sommet sommetDepart = sommet;

    queue<Sommet> queueATraiter;
    map<Sommet, Sommet> mapMarque;
    // Push au depart le sommet recu dans la file et le marque (insérer = marquer car met dedans que si n'est pas déjà dedans)
    queueATraiter.push(sommet);
    mapMarque.insert(make_pair(sommet, sommet)); // 1er sommet n'a pas de parent, on met lui-meme comme parent

    while(!queueATraiter.empty()){
        // On récupère le prochain sommet de la file et le traite
        sommet = queueATraiter.front();
        queueATraiter.pop();
        traiter(sommetDepart, sommet, mapMarque);
        // On récupère les sommets voisins et parcours
        vector<Sommet> voisins = recupererVoisins(sommet);
        for(size_t i = 0; i < voisins.size(); ++i){
            // On marque le sommet en cours et l'ajoute dans le queue, si il n'est pas déjà marqué
            if(!mapMarque.count(voisins[i])){
                queueATraiter.push(voisins[i]);
                mapMarque.insert(make_pair(voisins[i], sommet));
            }
        }
    }
}

Sommet recupererVoisin(Sommet sommetInitiale, size_t zeroPos, size_t posEchange){
    std::swap(sommetInitiale[zeroPos], sommetInitiale[posEchange]);
    return sommetInitiale;
}

vector<Sommet> recupererVoisins(const Sommet& sommet){
    vector<Sommet> voisins;
    size_t zeroPos = sommet.find('0'); // Position du zero [0-X]
    size_t zeroLigne = zeroPos / GRILLE_MAX_LIGNE + 1;  // Ligne ou se trouve le zero [1-x]
    size_t zeroCol = zeroPos % GRILLE_MAX_COL+ 1;  // Colonne ou se trouve le zero [1-x]

    // Le zero est pas sur la 1ere colonne => on peut échanger avec le chiffre à sa gauche
    if(zeroCol != 1){
        voisins.push_back(recupererVoisin(sommet, zeroPos, zeroPos - 1));
    }
    // Le zero est pas sur la dernière colonne => on peut échanger avec le chiffre à sa droite
    if(zeroCol != GRILLE_MAX_COL){
        voisins.push_back(recupererVoisin(sommet, zeroPos, zeroPos + 1));
    }
    // Le zero est pas sur la 1ere ligne => on peut échanger avec le chiffre du dessus
    if(zeroLigne != 1){
        voisins.push_back(recupererVoisin(sommet, zeroPos, zeroPos - GRILLE_MAX_LIGNE));
    }
    // Le zero est pas sur la dernière colonne => on peut échanger avec le chiffre du dessous
    if(zeroLigne != GRILLE_MAX_LIGNE){
        voisins.push_back(recupererVoisin(sommet, zeroPos, zeroPos + GRILLE_MAX_LIGNE));
    }

    return voisins;
}

void traiter(const Sommet& sommetDepart, Sommet& sommetCourant, const map<Sommet, Sommet>& mapTraite){
    // On regarde si on a atteint le sommet objectif
    if(sommetCourant == SOMMET_OBJECTIF){
        // On ajoute dans une pile la position du 0 dans le parent du sommet courant, et on remonte juqu'au sommet
        // initiale grace a note mapTraite qui contient tout les sommets / sommets parents parcouru
        stack<size_t> pileFinal;
        Sommet parent = sommetCourant;
        while(parent != sommetDepart){
            pileFinal.push(parent.find('0'));
            parent = mapTraite.find(sommetCourant)->second;
            sommetCourant = parent;
        }

        cout << "Séquence de résolution : ";

        // La séquence de résolution est la position du zero dans chaque parent, on va donc dépiler notre pile
        while(!pileFinal.empty()){
            cout << pileFinal.top() << " ";
            pileFinal.pop();
        }

    }
}