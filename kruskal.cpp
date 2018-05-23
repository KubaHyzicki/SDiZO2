#include "graph.h"

void graph::kruskalM(){
    elementEdge **L;
    L=new elementEdge * [edgesNoDirect];
    int n=0;
    for(int i=0;i<vertices;i++){
        for(int i2=0;i2<vertices;i2++){
            if(matrixNoDirect[i][i2]!=max){
                L[n]=new elementEdge;
                L[n]->start=i;
                L[n]->end=i2;
                L[n]->weight=matrixNoDirect[i][i2];
                n++;
            }
        }
    }
    kruskal(L,n);
//    for(int i=0;i<n;i++)
//        delete [] L[i];
//    delete []L;
}

void graph::kruskalL(){
    elementEdge **L;
    L=new elementEdge * [edgesNoDirect];
    elementList *pointer;
    int n=0;
    for(int i=0;i<vertices;i++){
        pointer=listsNoDirect[i];
        while(pointer){
            L[n]=new elementEdge;
            L[n]->start=i;
            L[n]->end=pointer->direct;
            L[n]->weight=pointer->weight;
            pointer=pointer->next;
            n++;
        }
    }
    kruskal(L,n);
//    for(int i=0;i<n;i++)
//        delete [] L[i];
//    delete []L;
}

void graph::kruskal(elementEdge **list, int n){
    int weightSum=0;
    elementEdge **L=list;
    elementEdge **T=new elementEdge *[vertices-1];      //założenie, że każde drzewo minimalne będzie miało tyle krawędzi ile ilość wierzchołków-1...chyba słuszne, nie?
    elementEdge *pointer;

    //sortowanie listy kubełkowo według wag
    for(int i=0;i<n-1;i++){
        for(int i2=0;i2<n-1;i2++){
            if(L[i2]->weight>L[i2+1]->weight){
                pointer=L[i2];
                L[i2]=L[i2+1];
                L[i2+1]=pointer;
            }
        }
    }

//    for(int i=0;i<n;i++){
//        cout<<L[i]->start<<" "<<L[i]->end<<" ("<<L[i]->weight<<")"<<endl;
//    }
//    cout<<endl<<endl;

    //tabela z przyporządkowaniem wierzchołków do osobnych drzew
    int usedVer[vertices];
    for(int i=0;i<vertices;i++)
        usedVer[i]=i;           //inicjacja numerami osobnych jednoelementowych(póki co) drzew

    //wybieranie krawędzi
    int e=0;
    for(int i=0;i<n;i++){
        if(L[i]->start==L[i]->end){    //ten algotytm siada dla wierzchołka wskazującego na siebie
            continue;
        }
        if(usedVer[L[i]->start]!=usedVer[L[i]->end]){ //jeśli nie należą do tego samego drzewa
            T[e++]=L[i];                    //przepisujemy krawędź
            weightSum+=L[i]->weight;
            int old=usedVer[L[i]->end];
            for(int k=0;k<vertices;k++){    //łączymy drzewa wierzchołków
                if(usedVer[k]==old)
                    usedVer[k]=usedVer[L[i]->start];
            }
        }
    }

    //wyświetlenie wybranych krawędzi:
    for(int i=0;i<e;i++){
        cout<<T[i]->start<<" "<<T[i]->end<<" ("<<T[i]->weight<<")"<<endl;
    }
    cout<<"sumaryczna waga="<<weightSum<<endl;
//    for(int i=0;i<n;i++)
//        delete [] L[i];
//    delete []L;
//    for(int i=0;i<n;i++)
//        delete [] T[i];
//    delete []T;
}
