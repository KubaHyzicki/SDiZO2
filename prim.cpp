#include "graph.h"

void graph::primM(){
    vector<elementEdge*> T;                             //lista wybranych krawędzi
    vector<elementEdge*> allEdges;                      //lista krawędzi wychodzących z już wybranych wierzchołków
    int weightSum=0;

    //tablica z informacjami czy dany wierzchołek już był wybrany
    int usedVer[vertices];
    for(int i=0;i<vertices;i++)
        usedVer[i]=0;
    usedVer[0]=1;

                                                        //w-nr ostatnio wybranego wierzchołka
    for(int e=0,w=0;e<vertices-1;){                     //e-ilość wybranych już krawędzi
        //dodajemy krawędzie nowo wybranego wierzchołka do listy
        for(int i=0;i<vertices;i++){
            if(matrixNoDirect[w][i]==max)
                continue;
            if(w==i)
                continue;
            allEdges.push_back(new elementEdge);
            allEdges.back()->start=w;
            allEdges.back()->end=i;
            allEdges.back()->weight=matrixNoDirect[w][i];
        }

        //wyszukujemy krawędź o najmniejszej wadze
        int minWeiIt=0;                                 //minWeiIt-nr krawędzi o najmniejszej wadze na liście allEdges
        for(int i=0;i<(int)allEdges.size();i++)
            if(allEdges[i]->weight<=allEdges[minWeiIt]->weight){
                if(usedVer[allEdges[i]->end]==0)
                    minWeiIt=i;
                else
                    allEdges.erase(allEdges.begin()+i);
            }
        //dodajemy krawędź, zapisujemy użycie wierzchołka, usuwamy ją z listy przeszukiwanych krawędzi i ustawiamy ostatni wierzchołek
        T.push_back(allEdges[minWeiIt]);
        allEdges.erase(allEdges.begin()+minWeiIt);
        w=allEdges[minWeiIt]->end;
        usedVer[w]=1;
        weightSum+=T[e]->weight;
        e++;
    }

    prim(T,weightSum);
}

//void graph::primL(){
//    vector<elementEdge*> T;                             //lista wybranych krawędzi
//    vector<elementEdge*> allEdges;                      //lista krawędzi wychodzących z już wybranych wierzchołków
//    elementList *pointer;
//    int weightSum=0;

//    //tablica z informacjami czy dany wierzchołek już był wybrany
//    int usedVer[vertices];
//    for(int i=0;i<vertices;i++)
//        usedVer[i]=0;
//    usedVer[0]=1;

//                                                        //w-nr ostatnio wybranego wierzchołka
//    for(int e=0,w=0;e<vertices-1;){                     //e-ilość wybranych już krawędzi
//        //dodajemy krawędzie nowo wybranego wierzchołka do listy
//        pointer=listsNoDirect[w];
//        while(pointer){
//            allEdges.push_back(new elementEdge);
//            allEdges.back()->start=w;
//            allEdges.back()->end=pointer->direct;
//            allEdges.back()->weight=pointer->weight;
//            pointer=pointer->next;
//        }
//        //wyszukujemy krawędź o najmniejszej wadze
//        int minWeiIt=0;                                 //minWeiIt-nr krawędzi o najmniejszej wadze na liście allEdges
//        for(int i=0;i<(int)allEdges.size();i++)
//            if(allEdges[i]->weight<=allEdges[minWeiIt]->weight){
//                if(usedVer[allEdges[i]->end]==0)
//                    minWeiIt=i;
//                else
//                    allEdges.erase(allEdges.begin()+i);
//            }
//        //dodajemy krawędź, zapisujemy użycie wierzchołka, usuwamy ją z listy przeszukiwanych krawędzi i ustawiamy ostatni wierzchołek
//        T.push_back(allEdges[minWeiIt]);
//        allEdges.erase(allEdges.begin()+minWeiIt);
//        w=allEdges[minWeiIt]->end;
//        usedVer[w]=1;
//        weightSum+=T[e]->weight;
//        e++;
//    }

//    prim(T,weightSum);
//}

void graph::primL(){
    vector<elementEdge*> T;                             //lista wybranych krawędzi
    vector<elementEdge*> allEdges;                      //lista krawędzi wychodzących z już wybranych wierzchołków
    elementList *pointer;
    int weightSum=0;

    //tablica z informacjami czy dany wierzchołek już był wybrany
    int usedVer[vertices];
    for(int i=0;i<vertices;i++)
        usedVer[i]=0;
    usedVer[0]=1;


    for(int w=0;(int)T.size()<vertices-1;){                     //w-nr ostatnio wybranego wierzchołka
        //dodajemy krawędzie nowo wybranego wierzchołka do listy
        pointer=listsNoDirect[w];
        while(pointer){
            allEdges.push_back(new elementEdge);
            allEdges.back()->start=w;
            allEdges.back()->end=pointer->direct;
            allEdges.back()->weight=pointer->weight;
            pointer=pointer->next;
        }
        //wyszukujemy krawędź o najmniejszej wadze
        int minWeiIt=0;                                 //minWeiIt-nr krawędzi o najmniejszej wadze na liście allEdges
        for(int i=0;i<(int)allEdges.size();i++)
            if(allEdges[i]->weight<=allEdges[minWeiIt]->weight){
                if(usedVer[allEdges[i]->end]==0)
                    minWeiIt=i;
                else
                    allEdges.erase(allEdges.begin()+i);
            }
        //dodajemy krawędź, zapisujemy użycie wierzchołka, usuwamy ją z listy przeszukiwanych krawędzi i ustawiamy ostatni wierzchołek
        T.push_back(allEdges[minWeiIt]);
        allEdges.erase(allEdges.begin()+minWeiIt);
        w=allEdges[minWeiIt]->end;
        usedVer[w]=1;
        weightSum+=T.back()->weight;
    }

    prim(T,weightSum);
}

void graph::prim(vector<elementEdge*> list,int weightSum){
    for(int i=0;i<(int)list.size();i++){
        cout<<list[i]->start<<" "<<list[i]->end<<" ("<<list[i]->weight<<")"<<endl;
    }
    cout<<"sumaryczna waga="<<weightSum<<endl;
}
