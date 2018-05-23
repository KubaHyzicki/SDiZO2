#include "graph.h"


graph::graph(){
    data=fileread();
    edges=data.edges;
    vertices=data.vertices;
    start=data.start;
    end=data.end;
}

graph::graph(string filename){
    data=fileread(filename);
    edges=data.edges;
    vertices=data.vertices;
    start=data.start;
    end=data.end;
    cout<<"ciastko"<<endl;
}

graph::~graph(){
    for(int i=0;i<vertices;i++){
        delete [] matrix[i];
        delete [] matrixNoDirect[i];
        delete [] lists[i];
        delete [] listsNoDirect[i];
    }
    delete [] matrixNoDirect;
    delete [] matrix;
    delete [] lists;
    delete [] listsNoDirect;
}

void graph::fileLoad_toMatrix(){
    //tworzenie
    matrix=new int * [vertices];
    for(int i=0;i<vertices;i++){
        matrix[i]=new int [vertices];
        for(int i2=0;i2<vertices;i2++){
            matrix[i][i2]=max;
        }
    }
    //ładowanie krawędzi
    for(int i=0;i<edges;i++)
        matrix[data.tabEdges[i].start][data.tabEdges[i].end]=data.tabEdges[i].weight;


    //ładowanie krawędzi do macierzy bez kierunków
    matrixNoDirect=new int * [vertices];
    for(int i=0;i<vertices;i++){
        matrixNoDirect[i]=new int [vertices];
        for(int i2=0;i2<vertices;i2++){
            matrixNoDirect[i][i2]=max;
        }
    }
    for(int i=0;i<edges;i++){
        if(matrixNoDirect[data.tabEdges[i].start][data.tabEdges[i].end]>data.tabEdges[i].weight)
            matrixNoDirect[data.tabEdges[i].start][data.tabEdges[i].end]=data.tabEdges[i].weight;
        if(matrixNoDirect[data.tabEdges[i].end][data.tabEdges[i].start]>data.tabEdges[i].weight)
            matrixNoDirect[data.tabEdges[i].end][data.tabEdges[i].start]=data.tabEdges[i].weight;
    }
    edgesNoDirect=0;
    for(int i=0;i<vertices;i++){
        for(int i2=0;i2<vertices;i2++){
            if(matrixNoDirect[i][i2]!=max)
                edgesNoDirect++;
        }
    }
}

void graph::fileLoad_toList(){
    elementList *pointer=NULL;
    //tworzenie
    lists=new elementList * [vertices];
    for(int i=0;i<vertices;i++)
        lists[i]=NULL;
    //ładowanie krawędzi
    for(int i=0;i<edges;i++){
        pointer=new elementList;
        pointer->next=lists[data.tabEdges[i].start];    //zachowujemy obecny(bądź nie) element w tabeli
        pointer->weight=data.tabEdges[i].weight;
        pointer->direct=data.tabEdges[i].end;
        lists[data.tabEdges[i].start]=pointer;          //nadpisujemy wskaźnik tabeli nowym
    }


    //ładowanie krawędzi do tablicy list bez kierunków
    pointer=NULL;
    listsNoDirect=new elementList * [vertices];
    for(int i=0;i<vertices;i++)
        listsNoDirect[i]=NULL;

    elementList *pointer2=NULL;
    for(int i=0;i<vertices;i++){
        pointer=lists[i];
        while(pointer){
            //tworzenie oryginalnej krawędzi
            pointer2=new elementList;
            pointer2->next=listsNoDirect[i];
            pointer2->weight=pointer->weight;
            pointer2->direct=pointer->direct;
            listsNoDirect[i]=pointer2;
            //tworzenie krawędzi o przeciwnym kierunku
            if(pointer->direct!=i){         //nie chcemy powtórek krawędzi, które wskazują na siebie same o tej samej wadze
                pointer2=new elementList;
                pointer2->next=listsNoDirect[pointer->direct];
                pointer2->weight=pointer->weight;
                pointer2->direct=i;
                listsNoDirect[pointer->direct]=pointer2;
            }
            //następny pointer
            pointer=pointer->next;
        }
    }
    edgesNoDirect=0;
    for(int i=0;i<vertices;i++){
        pointer=listsNoDirect[i];
        while(pointer){
            edgesNoDirect++;
            pointer=pointer->next;
        }
    }
}

void graph::showMatrix(){
    //oprawa graficzna
    cout<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<i<<" ";
    cout<<endl<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<"--";
    cout<<endl;

    //faktyczne wyświetlanie macierzy
    for(int i=0;i<vertices;i++){
        cout<<i<<"|";
        for(int i2=0;i2<vertices;i2++)
            if(matrix[i][i2]==max)
                cout<<"x ";
            else
                cout<<matrix[i][i2]<<" ";
        cout<<"|"<<endl;
    }

    //oprawa graficzna
    cout<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<"--";
    cout<<endl;
}

void graph::showList(){
    elementList *pointer=NULL;
    for(int i=0;i<vertices;i++){
        cout<<i<<":";
        pointer=lists[i];
        while(pointer){
            cout<<pointer->direct<<"("<<pointer->weight<<")"<<" ";
            pointer=pointer->next;
        }
        cout<<endl;
    }
}

void graph::showFileData(){
    cout<<data.edges<<" "<<data.vertices<<" "<<data.start<<" "<<data.end<<endl;
    for(int i=0;i<data.edges;i++)
        cout<<data.tabEdges[i].start<<" "<<data.tabEdges[i].end<<" "<<data.tabEdges[i].weight<<endl;
}

void graph::showMatrixNoDirect(){
    //oprawa graficzna
    cout<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<i<<" ";
    cout<<endl<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<"--";
    cout<<endl;

    //faktyczne wyświetlanie macierzy
    for(int i=0;i<vertices;i++){
        cout<<i<<"|";
        for(int i2=0;i2<vertices;i2++)
            if(matrixNoDirect[i][i2]==max)
                cout<<"x ";
            else
                cout<<matrixNoDirect[i][i2]<<" ";
        cout<<"|"<<endl;
    }

    //oprawa graficzna
    cout<<"  ";
    for(int i=0;i<vertices;i++)
        cout<<"--";
    cout<<endl;
}

void graph::showListNoDirect(){
    elementList *pointer=NULL;
    for(int i=0;i<vertices;i++){
        cout<<i<<":";
        pointer=listsNoDirect[i];
        while(pointer){
            cout<<pointer->direct<<"("<<pointer->weight<<")"<<" ";
            pointer=pointer->next;
        }
        cout<<endl;
    }
}
