#include "graph.h"

class table{
public:
    int size;
    elementEdge *tab;

    table(){
        size=0;
    }

    void push(elementEdge *el){
//        elementEdge *el=new elementEdge;
        if(size==0){
            tab=new elementEdge[1];
            tab[size++]=*el;
            return;
        }

        elementEdge *temp=new elementEdge[size+1];
        for(int i=0;i<size;i++)
            temp[i]=tab[i];
        temp[size++]=*el;
        delete []tab;
        tab=temp;
        return;
    }

    void remove(int pos){
        if(size==1){
            delete []tab;
            size--;
            return;
        }

        elementEdge *temp=new elementEdge[size-1];
        int iter=0;
        while(iter<pos){
            temp[iter]=tab[iter];
            iter++;
        }
        size--;
        while(iter<size){
            temp[iter]=tab[iter+1];
            iter++;
        }
        delete []tab;
        tab=temp;
        return;
    }
    
    elementEdge *back(){
        return &tab[size-1];
    }

    elementEdge *at(int pos){
        return &tab[pos];
    }

    int searchMin(){
        int pos=0;
        for(int i=0;i<size;i++){
            if(tab[i].weight<tab[pos].weight)
                pos=i;
        }
        return pos;
    }

    int getSize(){
        return size;
    }

    void print(){
        if(size==0){
            cout<<"brakElementów"<<endl;
            return;
        }
        for(int i=0;i<size;i++)
            cout<<tab[i].start<<" "<<tab[i].end<<" ("<<tab[i].weight<<")"<<endl;
    }

    int getSumWeight(){
        int sumWeight=0;
        for(int i=0;i<size;i++)
            sumWeight+=tab[i].weight;
        return sumWeight;
    }
};

void graph::primM(){
    table T;                                            //lista wybranych krawędzi
    table allEdges;                                     //lista krawędzi wychodzących z już wybranych wierzchołków

    //tablica z informacjami czy dany wierzchołek już był wybrany
    int usedVer[vertices];
    for(int i=0;i<vertices;i++)
        usedVer[i]=0;
    usedVer[0]=1;


    for(int w=0;T.getSize()<vertices-1;){               //w-nr ostatnio wybranego wierzchołka
        //dodajemy krawędzie nowo wybranego wierzchołka do listy
        for(int i=0;i<vertices;i++){
            if(matrixNoDirect[w][i]==max)
                continue;
            if(w==i)
                continue;
            allEdges.push(new elementEdge);
            allEdges.back()->start=w;
            allEdges.back()->end=i;
            allEdges.back()->weight=matrixNoDirect[w][i];
        }

        //wyszukujemy krawędź o najmniejszej wadze
        int minWeiIt=0;                                 //minWeiIt-nr krawędzi o najmniejszej wadze na liście allEdges
        while(true){
            minWeiIt=allEdges.searchMin();
            if(usedVer[allEdges.at(minWeiIt)->end]==1){
                allEdges.remove(minWeiIt);
                continue;
            }
            else
                break;
        }

        //dodajemy krawędź, zapisujemy użycie wierzchołka, usuwamy ją z listy przeszukiwanych krawędzi i ustawiamy ostatni wierzchołek
        T.push(allEdges.at(minWeiIt));
        w=allEdges.at(minWeiIt)->end;
        usedVer[w]=1;
        allEdges.remove(minWeiIt);
    }


    T.print();
    cout<<"sumWeight="<<T.getSumWeight()<<endl;
}

void graph::primL(){
    table T;                                            //lista wybranych krawędzi
    table allEdges;                                     //lista krawędzi wychodzących z już wybranych wierzchołków

    //tablica z informacjami czy dany wierzchołek już był wybrany
    int usedVer[vertices];
    for(int i=0;i<vertices;i++)
        usedVer[i]=0;
    usedVer[0]=1;

    elementList *pointer;
    for(int w=0;T.getSize()<vertices-1;){               //w-nr ostatnio wybranego wierzchołka
        //dodajemy krawędzie nowo wybranego wierzchołka do listy
        pointer=listsNoDirect[w];
        while(pointer){
            if(w==pointer->direct){
                pointer=pointer->next;
                continue;
            }
            allEdges.push(new elementEdge);
            allEdges.back()->start=w;
            allEdges.back()->end=pointer->direct;
            allEdges.back()->weight=pointer->weight;
            pointer=pointer->next;
        }

        //wyszukujemy krawędź o najmniejszej wadze
        int minWeiIt=0;                                 //minWeiIt-nr krawędzi o najmniejszej wadze na liście allEdges
        while(true){
            minWeiIt=allEdges.searchMin();
            if(usedVer[allEdges.at(minWeiIt)->end]==1){
                allEdges.remove(minWeiIt);
                continue;
            }
            else
                break;
        }

        //dodajemy krawędź, zapisujemy użycie wierzchołka, usuwamy ją z listy przeszukiwanych krawędzi i ustawiamy ostatni wierzchołek
        T.push(allEdges.at(minWeiIt));
        w=allEdges.at(minWeiIt)->end;
        usedVer[w]=1;
        allEdges.remove(minWeiIt);
    }


    T.print();
    cout<<"sumWeight="<<T.getSumWeight()<<endl;
}
