#ifndef INTERFACE_H
#define INTERFACE_H

#include "graph.h"
#include "linuxtime.h"

using namespace std;

class interface{
public:
    linuxtime time;
    int input;
    graph *gr;
    string messMain="0-exit\n"
                "1-wyświetl macierz\n"
                "2-wyświetl tablicę list\n"
                "3-wyświetl graf w postaci nieskierowanej(1-dla macierzy,2-dla tablicy list)\n"
                "4-kruskal(1-dla macierzy,2-dla tablicy list(NIE DZIAŁA W INTERFACE))\n"
                "5-prim(1-dla macierzy,2-dla tablicy list)\n"
                "6-dijkstra(1-dla macierzy,2-dla tablicy list no i nr wierzchołka)\n"
                "7-bellman-ford(1-dla macierzy,2-dla tablicy list no i nr wierzchołka)\n";
    interface();

    bool mainLoop();

    void noDirect(int mode);

    void kruskal(int mode);

    void prim(int mode);

    void dijkstra(int mode,int w);

    void bellman_ford(int mode, int w);

};

#endif // INTERFACE_H
