#include "file.h"
#include "point.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>
using namespace std;
using namespace Imagine;

// --- fileListe ---

fileListe::fileListe() {}

fileListe::~fileListe() {} // pas de tableau dynamique a desallouer

bool fileListe::empty() const {
    return L.empty();
}

void fileListe::push(point p) {
    L.push_back(p);
}

point fileListe::pop() {
    point p = L.front();
    L.pop_front();
    return p;
}

// --- fileTableau ---

// Constructeurs
fileTableau::fileTableau() {
    //t = new point[257*257]; // cas ou un grand nombre d'elements est alloue
    t = new point[1]; // cas ou un unique element est alloue au depart
    //t = (point *)malloc(sizeof(point) * 1);
    first = 0;
    last = 0;
    size = 1;
}

// Destructeur
fileTableau::~fileTableau() {
    delete[] t;
}

// La file d'attente est-elle vide?
bool fileTableau::empty() const {
    if(first == last)
        return true;
    return false;
}

// Un nouveau client arrive
void fileTableau::push(point p) {
    // cas ou il y a un grand nombre d'elements
    /*t[last] = p;
    last += 1;*/

    // cas ou un seul element est alloue au depart

    // ajout de l'element
    t[last] = p; // affectation du nouveau client dans t
    last += 1; // decalage de l'indice last

    if(last >= size) // circularite de last (last revient au debut)
        last = 0;

    if(first == last) { // tableau trop petit
        point* t_c = new point[size]; // tableau auxiliaire de meme taille que t

        for(int i=first;i<size+first;i++)
            t_c[i-first] = t[i%size]; // l'element de tete du nouveau tableau est celui de first

        t = new point[2*size]; // on alloue un tableau 2 fois plus grand
        for(int i=0; i<size;i++)
            t[i] = t_c[i];
        delete[] t_c; // on desalloue t_c

        first = 0; // first est de nouveau au debut du nouveau tableau
        last = size; // on ramene le curseur de fin sur la position de la premiere case vide du nouveau tableau
        size = 2*size; // on double la taille du tableau
    }
}

// Sert le premier client
point fileTableau::pop() {
    point p = t[first]; // recuperation du premier client
    first += 1; // on avance l'indice debut d'une case

    if(first >= size) // circularite de l'indice first (retour au debut)
        first = 0;
    return p;
}
