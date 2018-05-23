#include "graph.h"

void graph::dijkstraM(int w){
    int dist[vertices];             //tablica odległości między wierzchołkami
    int trace[vertices];            //dodatkowa tabela poprzednio odwiedzonych wierzchołków dla danego(do odtworzenia ścieżki, a nie tylko wag)
    vector <int> Q;                 //niewykorzystane wierzchołki grafu
    for(int i=0;i<vertices;i++){
        dist[i]=max;                //inicjalizujemy odległości na nieskończoność
        trace[i]=w;                 //inicjalizujemy tablicę śledzącą trasę do wierzchołka wierzchołkiem startowym(zakładam, że do każdego będzie się dało finalnie dostać)
        Q.push_back(i);             //inicjalizujemy po prostu wszystkie nr wierzchołków
    }
    dist[w]=0;                      //wierzchołek startowy ma odległość 0

    while(!Q.empty()){
        //szukanie minimalnej odległości
        int minID=0;             //nr w tabeli wierzchołków z wierzchołkiem o minimalnej odległości od obecnego
        for(int i=0;i<(int)Q.size();i++)
            if(dist[Q[i]]<dist[Q[minID]])
                minID=i;
        //aktualizowanie tabeli odległości(sąsiadów minimalnego wierzchołka)
        for(int i=0;i<vertices;i++){ //w macierzy trzeba przejść ją całą, bo dla każdego punktu jest tylko lista wchodzących(nie wychodzących) krawędzi
            if(matrix[Q[minID]][i]!=max){        //jeśli znaleziono dojście do nowego wierzchołka
                if(i!=Q[minID]){                //i jeśli to nie jest pętla własna(dodatkowy warunek na zmienną startową-nie potrafię rozgryźć dlaczego unika schwytania przez łapanie pętli własnej)
                   if(dist[i]>dist[Q[minID]]+matrix[Q[minID]][i]){   //(wikipedia mówi o tym "relaksacja")
                        dist[i]=dist[Q[minID]]+matrix[Q[minID]][i];     //to aktualizujemy jego odległość=całkowita odległość do ostatniego W+odległość między ostatnim, a tym
                        trace[i]=Q[minID];
                    }
                }
            }
        }

        Q.erase(Q.begin()+minID);   //usuwamy wierzchołek
    }

    dijkstra(dist,trace);
}

void graph::dijkstraL(int w){
    int dist[vertices];             //tablica odległości między wierzchołkami
    int trace[vertices];            //dodatkowa tabela poprzednio odwiedzonych wierzchołków dla danego(do odtworzenia ścieżki, a nie tylko wag)
    vector <int> Q;                 //niewykorzystane wierzchołki grafu
    for(int i=0;i<vertices;i++){
        dist[i]=max;                //inicjalizujemy odległości na nieskończoność
        trace[i]=w;                 //inicjalizujemy tablicę śledzącą trasę do wierzchołka wierzchołkiem startowym(zakładam, że do każdego będzie się dało finalnie dostać)
        Q.push_back(i);             //inicjalizujemy po prostu wszystkie nr wierzchołków
    }
    dist[w]=0;                      //wierzchołek startowy ma odległość 0

    while(!Q.empty()){
        //szukanie minimalnej odległości
        int minID=0;             //nr w tabeli wierzchołków z wierzchołkiem o minimalnej odległości od obecnego
        for(int i=0;i<(int)Q.size();i++)
            if(dist[Q[i]]<dist[Q[minID]])
                minID=i;
        //aktualizowanie tabeli odległości(sąsiadów minimalnego wierzchołka)
        elementList *pointer=lists[Q[minID]];
        while(pointer){     //automatycznie zapewniamy, że znaleziono dojście do nowego wierzchołka
            if(pointer->direct==Q[minID])   //jeśli to nie jest pętla własna
                continue;
            if(dist[pointer->direct]>dist[Q[minID]]+pointer->weight){   //(wikipedia mówi o tym "relaksacja")
                dist[pointer->direct]=dist[Q[minID]]+pointer->weight;
                trace[pointer->direct]=Q[minID];
            }
            pointer=pointer->next;
        }

        Q.erase(Q.begin()+minID);   //usuwamy wierzchołek
     }

    dijkstra(dist,trace);
}

void graph::dijkstra(int *dist, int *trace){
    int x=(int)max/2;
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
