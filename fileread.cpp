#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

struct graphEdge{
    int start;
    int end;
    int weight;
};

class fileread {
public:
    //plik
    string filepath="/home/kuba/Qt/SDiZO2/data";
    fstream file;
    //graf:
    int edges;
    int vertices;
    int start;
    int end;
    graphEdge *tabEdges;


    fileread(){
        this->file_read_graph();
    }

//    ~fileread(){
//        delete [] tabEdges;
//    }

    fileread(string filepath){
        this->filepath=filepath;
        this->file_read_graph();
//        file.open(filepath,ios::in);
//        cout<<file.is_open()<<endl;
    }

    bool file_read_line(ifstream &file, int tab[], int size)
    {
        string s;
        getline(file, s);

        if(file.fail() || s.empty())
        return(false);

        istringstream in_ss(s);

        for(int i = 0; i < size; i++)
        {
        in_ss >> tab[i];
        if(in_ss.fail())
        return(false);
        }
        return(true);
    }

    void file_read_graph(){
        ifstream file;
        int tab[4];
        file.open(filepath.c_str());

        if(file.is_open()){
            if(file_read_line(file, tab, 4)){
                edges = tab[0];
                vertices = tab[1];
                start = tab[2];
                end = tab[3];
                tabEdges=new graphEdge[edges];
                for(int i = 0; i < edges; i++)
                if(file_read_line(file, tab, 3)){
                    tabEdges[i].start = tab[0];
                    tabEdges[i].end = tab[1];
                    tabEdges[i].weight = tab[2];
                }
                else{
                    cout << "File error - READ EDGE(Reading line error)" << endl;
                    break;
                }
            }
            else
                cout << "File error - READ INFO(Reading line error)" << endl;
            file.close();
        }
        else
            cout << "File error - OPEN" << endl;
    }
};
