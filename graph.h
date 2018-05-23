#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>

#include "fileread.cpp"

using namespace std;

struct elementList{
    elementList *next=NULL;
    int weight;
    int direct;
};

struct elementEdge{
    int weight;
    int start;
    int end;
};

struct elementVertice{
    int vertice;
    int dist;

    bool operator < (const elementVertice& el) const {
        return dist<el.dist;
    }
};

class graph{
public:
    const int max=147483647;//max nie może być nieskończonością(za duży), bo przy algorytmach przekręca licznik i się staje ujemny-sypie program
    int **matrix;
    elementList **lists;
    //wersje macierzy i tablicy list do tworzenia drzewa mst, czyli z brakiem kierunków krawędzi
    int **matrixNoDirect;
    elementList **listsNoDirect;
    fileread data;
    int edges;
    int vertices;
    int edgesNoDirect;
    int start;
    int end;
    string ciastko="ciastko";

    graph();

    ~graph();

    graph(string filename);

    void fileLoad_toMatrix();

    void fileLoad_toList();

    void showMatrix();
    void showMatrixNoDirect();

    void showList();
    void showListNoDirect();

    void showFileData();

    void kruskalM();            //kruskal dla tablicy list
    void kruskalL();            //kruskal dla tablicy list

    void primM();               //prim dla tablicy list
    void primL();               //prim dla tablicy list

    void dijkstraM(int w);      //dijkstra dla tablicy list(argumentem jest nr wierzchołka)
    void dijkstraL(int w);      //dijkstra dla tablicy list(argumentem jest nr wierzchołka)

    void bellman_fordM(int w);  //bellman_ford dla tablicy list(argumentem jest nr wierzchołka)
    void bellman_fordL(int w);  //bellman_ford dla tablicy list(argumentem jest nr wierzchołka)

private:    //wspólne części algorytmów dla obu reprezentacji
    void kruskal(elementEdge **list, int n);
    void prim(vector<elementEdge*> list,int weightSum);
    void dijkstra(int *dist, int *trace);
    void bellman_ford(int *dist, int *trace);

};
#endif // GRAPH_H
