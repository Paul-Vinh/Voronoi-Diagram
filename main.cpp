// Imagine++ project
// Project:  File
// Author: Paul-Vinh LÊ


/* Pourquoi un algorithme recursif ne fonctionnerait pas ici ?

Ici, d'une case du tableau dépend 4 voisins donc si on supprime cette case du tableau, on ne pourra plus y revenir et donc dépiler
le tas alloué a la recursivité.
*/

#include "file.h"
#include "point.h"
#include<iostream>
#include<ctime>
#include<random>

using namespace Imagine;
using namespace std;

// Mettre en commentaire une et une seule des deux lignes suivantes
// typedef fileListe file; // utilisation de la file provenant de la librairie std
typedef fileTableau file; // utilisation d'un tableau circulaire

const int n=256;

// Essayer d'ajouter un point dans la file et de le colorer, s'il est dans la
// zone de l'image et qu'il n'a pas deja ete explore.
void add(file& f, bool t[n][n], int x, int y, Color c) {
    if(t[x][y] == false && x >= 0 && x <= n-1 && y >= 0 && y <= n-1) { // point non explore et dans zone image consideree
        point p;
        p.c = c;
        p.x = x, p.y = y;
        t[x][y] = true; // point qui devient explore
        drawPoint(x,y,c); // point dessine dans la fenetre
        f.push(p);
    }
}

int main() {
    srand((unsigned int)time(0)); // initialisation pour tirage aleatoire
    file f; // File vide
    bool t[n][n] = {false};  // Tableau des points deja vus
    const int nb_coul = 9; // nombre de couleurs total
    Color coul[nb_coul] = {RED, BLUE, PURPLE, GREEN, YELLOW, ORANGE, BLACK, CYAN, MAGENTA};  // Tableau de couleurs

    cout << "Entrez 1 pour distance 1, 0 pour distance max" << endl;
    int d1; // choix de la distance adoptee
    cin >> d1;

    openWindow(n,n);
    cout << "Clics pour ajouter des points, clic droit pour terminer" << endl;

    int clic = 0;

    while(clic != 3) { // boucle pour designation des points
        int x0, y0;
        clic = getMouse(x0,y0);

        if(clic == 1) { // clic gauche
            int i = (rand()%(nb_coul+1)); // tirage parmi les 9 couleurs
            add(f,t,x0,y0,coul[i]); // ajout du point dans la file
        }
    }

    while(! f.empty()) { // Croissance
        point p0 = f.pop(); // suppression du premier element de la file

        add(f,t,p0.x-1,p0.y,p0.c); // voisin a gauche
        add(f,t,p0.x+1,p0.y,p0.c); // voisin a droite
        add(f,t,p0.x,p0.y-1,p0.c); // voisin en haut
        add(f,t,p0.x,p0.y+1,p0.c); // voisin en bas*/

        if(d1 == 0) { // norme infinie (4 voisins supplementaires)
            add(f,t,p0.x-1,p0.y-1,p0.c); // voisin en haut a gauche
            add(f,t,p0.x+1,p0.y-1,p0.c); // voisin en haut a droite
            add(f,t,p0.x-1,p0.y+1,p0.c); // voisin en bas a gauche
            add(f,t,p0.x+1,p0.y+1,p0.c); // voisin en bas a droite
        }
    }

    endGraphics();
    return 0;
}
