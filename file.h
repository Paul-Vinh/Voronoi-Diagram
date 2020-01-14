#pragma once
#include "point.h"
#include <list>

class fileListe {
    std::list<point> L;
public:
    fileListe();
    ~fileListe();
    bool empty() const;
    void push(point p);
    point pop();
};

class fileTableau {
    point* t;       // Tableau des valeurs
    int size;       // Taille du tableau
    // Indices: - first: celui qui va etre servi, 
    //          - last: place libre pour le prochain arrivant
    int first,last;
public:
    fileTableau();
    ~fileTableau();
    bool empty() const;
    void push(point p);
    point pop();
};
