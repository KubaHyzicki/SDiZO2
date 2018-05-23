#include "interface.h"

interface::interface(){
    gr=new graph();
    gr->fileLoad_toList();
    gr->fileLoad_toMatrix();
    while(mainLoop());
}

bool interface::mainLoop(){
    for(;;){
        cout<<messMain;
        cin>>input;
        switch(input){
        case 0:{
            return 0;
        }
        case 1:{
            cout<<endl;
            gr->showMatrix();
            cout<<endl;
            cout<<endl;
            return 1;
        }
        case 2:{
            cout<<endl;
            gr->showList();
            cout<<endl;
            return 1;
        }
        case 3:{
            int mode;
            cin>>mode;
            time.start();
            cout<<endl;
            noDirect(mode);
            cout<<endl;
            return 1;
        }
        case 4:{
            int mode;
            cin>>mode;
            time.start();
            kruskal(mode);
            break;
        }
        case 5:{
            int mode;
            cin>>mode;
            time.start();
            prim(mode);
            break;
        }
        case 6:{
            int mode;
            int w;
            cin>>mode;
            cin>>w;
            time.start();
            dijkstra(mode,w);
            break;
        }
        case 7:{
            int mode;
            int w;
            cin>>mode;
            cin>>w;
            time.start();
            bellman_ford(mode,w);
            break;
        }
        default:{
            continue;
        }
        }
        time.stop();
        return 1;
    }
}

void interface::noDirect(int mode){
    if(mode==1)
        gr->showMatrixNoDirect();
    if(mode==2)
        gr->showListNoDirect();
    getchar();
}

void interface::kruskal(int mode){
    if(mode==1)
        gr->kruskalM();
    if(mode==2)
        gr->kruskalL();
    cout<<"ciastko"<<endl;
    getchar();
}

void interface::prim(int mode){
    if(mode==1)
        gr->primM();
    if(mode==2)
        gr->primL();
    getchar();
}

void interface::dijkstra(int mode,int w){
    if(mode==1)
        gr->dijkstraM(w);
    if(mode==2)
        gr->dijkstraL(w);
    getchar();
}

void interface::bellman_ford(int mode, int w){
    if(mode==1)
        gr->bellman_fordM(w);
    if(mode==2)
        gr->bellman_fordL(w);
    getchar();
}
