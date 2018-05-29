#include "graph.h"

void graph::bellman_fordM(int w){
    int dist[vertices];             //tablica odległości między wierzchołkami
    int trace[vertices];            //dodatkowa tabela poprzednio odwiedzonych wierzchołków dla danego(do odtworzenia ścieżki, a nie tylko wag)

    for(int i=0;i<vertices;i++){
        dist[i]=max;
        trace[i]=w;
    }

    dist[w]=0;                      //wierzchołek startowy ma odległość 0

    for(int x=1;x<vertices;x++){    //i-punkt startowy(x), i2-punkt docelowy(y)     x-wysokość,rząd y-szerokość,kolumna
        //relaksacja
        for(int i=0;i<vertices;i++){
            for(int i2=0;i2<vertices;i2++){
                if(i2==i||matrix[i][i2]==max)           //omija siebie i brak krawędzi
                    continue;
                if(dist[i2]>dist[i]+matrix[i][i2]){ //jeśli odległość od i2 jest większa niż suma odległości do i oraz między i i2, to
                    dist[i2]=dist[i]+matrix[i][i2]; //zmień odległość i2 na właśnie tą sumę(czyli, że znaleziono do danego punktu krótszą drogę)
                    trace[i2]=i;                    //no i poprzednik i2 to teraz i, bo to od niego tu przyszliśmy
                }
            }
        }
    }

    bellman_ford(dist,trace);
    return;
}

void graph::bellman_fordL(int w){
    int dist[vertices];             //tablica odległości między wierzchołkami
    int trace[vertices];            //dodatkowa tabela poprzednio odwiedzonych wierzchołków dla danego(do odtworzenia ścieżki, a nie tylko wag)

    for(int i=0;i<vertices;i++){
        dist[i]=max;
        trace[i]=w;
    }

    dist[w]=0;                      //wierzchołek startowy ma odległość 0

    for(int x=1;x<vertices;x++){    //i-punkt startowy, pointer->direct-punkt docelowy
        //relaksacja
        for(int i=0;i<vertices;i++){
            elementList *pointer=lists[i];
            while(pointer){
                if(pointer->direct==i){                  //omija siebie
                    pointer=pointer->next;
                    continue;
                }
                if(dist[pointer->direct]>dist[i]+pointer->weight){
                    dist[pointer->direct]=dist[i]+pointer->weight;
                    trace[pointer->direct]=i;
                }
                pointer=pointer->next;
            }
        }
    }

    bellman_ford(dist,trace);
    return;
}

void graph::bellman_ford(int *dist, int *trace){
    int x=(int)max/2;

    if(vertices>50){                //alternatywny sposób wyświetlania dla większych grafów
        cout<<endl;
        for(int i=0;i<vertices;i++){
            if(dist[i]>x)
                cout<<i<<"(-)[-] ";
            else
                cout<<i<<"("<<dist[i]<<")["<<trace[i]<<"] ";
        }
        cout<<endl;
        return;
    }

    cout<<"         ";
    for(int i=0;i<vertices;i++){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"dystans: ";
    for(int i=0;i<vertices;i++){
        if(dist[i]>x)
            cout<<"- ";         //niech nie wyświetla, jeśli gdzieś nie da się dojść
        else
            cout<<dist[i]<<" ";
    }
    cout<<endl;
    cout<<"trace:   ";
    for(int i=0;i<vertices;i++){
        cout<<trace[i]<<" ";
    }
    cout<<endl;
}
