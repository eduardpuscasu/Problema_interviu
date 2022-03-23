#include <iostream>
#include <vector>
#include <list>

using namespace std;


//facem legatura intre noduri
// legam atat a de b cat si b de a 
void add_edge(vector<int> data[], int src, int dest)
{
    data[src].push_back(dest);
    data[dest].push_back(src);
}




//BFS algo
bool BFS(vector<int> data[], int src, int dest, int v,
    int pred[], int dist[])
{
    //o coada in care punem nodurile ce vor urma sa fie verificate de algoritm
    list<int> queue;

    //in visited tinem toate valorile vizitate pentru a fi siguri ca nodurile nu se repeta
    bool* visited = new bool[v];

    //initializam array ul cu fals cat si cele doua matrice in care vom pune distanta de la nodul de care am plecat si predecesorul sau
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    //facem nodul curent true => este vizitat
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    //efectiv BFS
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < data[u].size(); i++) {
            if (visited[data[u][i]] == false) {
                visited[data[u][i]] = true;
                dist[data[u][i]] = dist[u] + 1;
                pred[data[u][i]] = u;
                queue.push_back(data[u][i]);

                //cand am gasit nodul pe care il cautam oprim functia
                if (data[u][i] == dest)
                    return true;
            }
        }
    }

    return false;
}

void printShortestDistance(vector<int> data[], int s,
    int dest, int v)
{
    //in pred tinem tinem nodul prin care am ajuns la nodul curent
    //in dist tinem distanta de la nodul s
    int* pred = new int[v];
    int* dist = new int[v];

    if (BFS(data, s, dest, v, pred, dist) == false) {
        cout << "Nu exista o cale intre cei doi";
        return;
    }

    //vectorul care retine cea mai scurta distanta
    vector<int> path;
    int aux = dest;
    path.push_back(aux);
    while (pred[aux] != -1) {
        path.push_back(pred[aux]);
        aux = pred[aux];
    }

    // cea mai scurta distanta se afla in dist
    cout << "Cea mai scurta cale este : "
        << dist[dest];

    // afisare cale
    cout << "\nCalea este ::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}


int main()
{
    //numarul de noduri
    int v = 12;

    //un array de vectori pentru fiecare punct
    vector<int>* data = new vector<int>[v];

    //aici este graful pe care am testat problema
    add_edge(data, 0, 2);
    add_edge(data, 0, 4);
    add_edge(data, 0, 5);
    add_edge(data, 1, 4);
    add_edge(data, 1, 5);
    add_edge(data, 2, 3);
    add_edge(data, 2, 4);
    add_edge(data, 3, 0);
    add_edge(data, 4, 5);
    add_edge(data, 6, 5);
    add_edge(data, 6, 0);
    add_edge(data, 7, 6);
    add_edge(data, 7, 1);
    add_edge(data, 8, 3);
    add_edge(data, 9, 10);
    add_edge(data, 9, 11);
    
    
    printShortestDistance(data, 2, 9, v);
    cout << endl;
    printShortestDistance(data, 7, 8, v);
    cout << endl;
    printShortestDistance(data, 11, 9, v);



    return 0;
}