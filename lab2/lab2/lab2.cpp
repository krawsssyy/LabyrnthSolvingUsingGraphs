#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#define MAX_VAL 65537
using namespace std;

int minDistance(int dist[], bool sptSet[], int noNodes)
{
    int min = MAX_VAL;
    int min_index;
    for (int v = 1; v <= noNodes; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
int dijkstra(int** graph, int noNodes, int src, int dest)
{
    int* dist = new int[noNodes + 1];
    bool* sptSet = new bool[noNodes + 1];
    for (int i = 1; i <= noNodes; i++)
        dist[i] = MAX_VAL, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 1; count < noNodes; count++) {
        int u = minDistance(dist, sptSet, noNodes);
        sptSet[u] = true;
        for (int v = 1; v <= noNodes; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != MAX_VAL
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    delete[] sptSet;
    sptSet = NULL;
    int retVal = dist[dest];
    delete[] dist;
    dist = NULL;
    return retVal;
}

bool specCase(int** graph,int noNodes, int node) {
    bool okLeave = true;
    bool okArrive = true;
    for (int i = 1; i <= noNodes; i++) {
        if (graph[node][i])
            okLeave = false;
        if (graph[i][node])
            okArrive = false;
    }
    return (okLeave || okArrive);
}


void moore(int** graph, int noNodes, int src) {
    int* l = new int[noNodes + 1];
    int* p = new int[noNodes + 1];
    for (int i = 1; i <= noNodes; i++)
        l[i] = MAX_VAL, p[i] = -1;
    l[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= noNodes; i++) {
            if(graph[x][i])
                if (l[i] == MAX_VAL) {
                    p[i] = x;
                    l[i] = l[x] + 1;
                    q.push(i);
                }
        }
    }
    
    for (int i = 1; i <= noNodes; i++) {
        if (i != src) {
            if (l[i] != MAX_VAL) {
                string path = to_string(i) + ">-";
                int j = i;
                while (p[j] != -1) {
                    j = p[j];
                    if (j == src)
                        path += to_string(j);
                    else
                        path += to_string(j) + ">-";
                }
                reverse(path.begin(), path.end());
                cout << "Calea de la nodul sursa " << src << " la nodul " << i << " este : " << path << endl;
            }
            else
                cout << "Nu exista drum de la nodul sursa " << src << " la nodul " << i << "." << endl;
        }
    }
    delete[] p;
    p = NULL;
    delete[] l;
    l = NULL;
    return;
}

void BFS(int** graph, int noNodes, int src) {
    int* l = new int[noNodes + 1];
    int* p = new int[noNodes + 1];
    bool* visited = new bool[noNodes + 1];
    for (int i = 1; i <= noNodes; i++) {
        visited[i] = false;
        l[i] = MAX_VAL;
        p[i] = -1;
    }
    l[src] = 0;
    visited[src] = true;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= noNodes; i++) {
            if (graph[x][i] && !visited[i]) {
                visited[i] = true;
                l[i] = l[x] + 1;
                p[i] = x;
            }
        }
        visited[x] = true;
    }
    for (int i = 1; i <= noNodes; i++) {
        if (visited[i])
            cout << "Nodul " << i << " a fost descoperit. Distanta de la nodul sursa(" << src << ") este " << l[i] << "." << endl;
    }
    delete[] visited;
    visited = NULL;
    delete[] p;
    p = NULL;
    delete[] l;
    l = NULL;
    return;
}

void DFS_VISIT(int** graph, int noNodes, int currNode, int& time, int* d, int* f, int* p, bool* visited) {
    time++;
    d[currNode] = time;
    visited[currNode] = true;
    for (int k = 1; k <= noNodes; k++) {
        if (graph[currNode][k] && !visited[k])
            p[k] = currNode, DFS_VISIT(graph, noNodes, k, time, d, f, p, visited);
    }
    time++;
    f[currNode] = time;
}

void DFS(int** graph, int noNodes) {
    bool* visited = new bool[noNodes + 1];
    int* p = new int[noNodes + 1];
    int* d = new int[noNodes + 1];
    int* f = new int[noNodes + 1];
    for (int i = 1; i <= noNodes; i++) {
        visited[i] = false;
        p[i] = d[i] = f[i] = -1;

    }
    int time = 0;
    for (int i = 1; i <= noNodes; i++) {
        if (!visited[i])
            DFS_VISIT(graph, noNodes, i, time, d, f, p, visited);
    }
    for (int i = 1; i <= noNodes; i++)
        if (visited[i])
            cout << "Nodul " << i << " a fost vizitat. Descoperit la pasul : " << d[i] << ", explorat la pasul :" << f[i]  << endl;
    delete[] f;
    f = NULL;
    delete[] d;
    d = NULL;
    delete[] p;
    p = NULL;
    delete[] visited;
    visited = NULL;
    return;
}

bool inList(vector<int> v, int x) {
    for (int i = 0; i < v.size(); i++)
        if (v[i] == x)
            return true;
    return false;
}

void solveLabirinth(string FILENAME) {
    ifstream h(FILENAME);
    string line = "";
    int count = 0;
    vector<string> lab;
    while (getline(h, line)) {
        lab.push_back(line);
    }
    h.close();
    if (FILENAME == "labirint_cuvinte.txt") {
        int maxx = 0;
        for (int i = 0; i < lab.size(); i++)
            if (lab[i].length() > maxx)
                maxx = lab[i].length();
        for (int i = 0; i < lab.size(); i++)
            if (lab[i] == "") {
                string newStr = "";
                for (int j = 0; j < maxx; j++)
                    newStr += " ";
                lab[i] = newStr;
            }
    }
    int Sx, Sy, Fx, Fy;
    for (int i = 0; i < lab.size(); i++) {
        for (int j = 1; j < lab[i].length() - 1; j++) {
            if (lab[i][j] == ' ')
                count++;
            else if (lab[i][j] == 'S')
                Sx = i, Sy = j, count++;
            else if (lab[i][j] == 'F')
                Fx = i, Fy = j, count++;
        }
    }
    vector<pair<int, int>> list;
    list.push_back(make_pair(Sx, Sy));
    list.push_back(make_pair(Fx, Fy));
    for (int i = 0; i < lab.size(); i++) {
        for (int j = 1; j < lab[i].length() - 1; j++) {
            if (lab[i][j] == ' ')
                list.push_back(make_pair(i, j));
        }
    }
    vector<vector<int>> adjList(list.size());
    vector<int> currNeighs;
    for (int i = 0; i < lab.size(); i++) {
        for (int j = 1; j < lab[i].length() - 1; j++) {
            if (lab[i][j] != '1') {
                if (i != 0)
                    if (lab[i - 1][j] == ' ')
                        currNeighs.push_back(find(list.begin(), list.end(), make_pair(i - 1, j)) - list.begin());
                    else if (lab[i - 1][j] == 'S')
                            currNeighs.push_back(0);
                if (i != lab.size() - 1)
                    if (lab[i + 1][j] == ' ')
                        currNeighs.push_back(find(list.begin(), list.end(), make_pair(i + 1, j)) - list.begin());
                    else if (lab[i + 1][j] == 'F')
                        currNeighs.push_back(1);
                if (j != 1)
                    if (lab[i][j - 1] == ' ')
                        currNeighs.push_back(find(list.begin(), list.end(), make_pair(i, j - 1)) - list.begin());
                    else if (lab[i][j - 1] == 'S')
                        currNeighs.push_back(0);
                    else if (lab[i][j - 1] == 'F')
                        currNeighs.push_back(1);
                if (j != lab[i].length() - 1)
                    if (lab[i][j + 1] == ' ')
                        currNeighs.push_back(find(list.begin(), list.end(), make_pair(i, j + 1)) - list.begin());
                    else if (lab[i][j + 1] == 'S')
                        currNeighs.push_back(0);
                    else if (lab[i][j + 1] == 'F')
                        currNeighs.push_back(1);
                adjList[find(list.begin(), list.end(), make_pair(i, j)) - list.begin()] = currNeighs;
                currNeighs.clear();
            }
        }
    }
    int* l = new int[count];
    int* p = new int[count];
    for (int i = 0; i < count; i++)
        l[i] = MAX_VAL, p[i] = -1;
    l[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < adjList[x].size(); i++) {
            if (l[adjList[x][i]] == MAX_VAL) {
                p[adjList[x][i]] = x;
                l[adjList[x][i]] = l[x] + 1;
                q.push(adjList[x][i]);
                }
        }
    }
    int x = 1;
    if (p[x] != -1) {
        vector<int> pathNodes;
        while (p[x] != 0) {
            pathNodes.push_back(p[x]);
            x = p[x];
        }
        ofstream g("output_" + FILENAME);
        for (int i = 0; i < lab.size(); i++) {
            for (int j = 0; j < lab[i].length(); j++)
                if (lab[i][j] != 'S' && lab[i][j] != 'F' && inList(pathNodes, find(list.begin(), list.end(), make_pair(i, j)) - list.begin()))
                    g << "*";
                else
                    g << lab[i][j];
            g << endl;
        }
        g.close();
    }
    else
        cout << "Nu exista rezolvare!" << endl;
    delete[] p;
    p = NULL;
    delete[] l;
    l = NULL;
    return;
}

void menu() {
    cout << "1.Algoritmul lui Moore cu un varf sursa" << endl;
    cout << "2.Generati inchiderea tranzitiva" << endl;
    cout << "3.Rezolvati labirint" << endl;
    cout << "4.Afisati arborele descoperit de BFS" << endl;
    cout << "5.Afisati padurea descoperita de DFS" << endl;
    cout << "6.Iesire" << endl;
    cout << "Optiune: ";
}

int main()
{
    ifstream f("graf.txt");
    string line = "";
    getline(f, line);
    int noNodes = stoi(line);
    int** adjMatrix = new int* [noNodes + 1];
    for (int i = 0; i <= noNodes; i++)
        adjMatrix[i] = new int[noNodes + 1];
    for (int i = 1; i <= noNodes; i++)
        for (int j = 1; j <= noNodes; j++)
            adjMatrix[i][j] = 0;
    while (getline(f, line)) {
        int node1 = stoi(line.substr(0, line.find(' ')));
        int node2 = stoi(line.substr(line.find(' '), line.length() - 1));
        adjMatrix[node1][node2] = 1;
    }
    f.close();
    int opt = 0;
    menu();
    cin >> opt;
    while (opt != 6) {
        if (opt == 1) {
            cout << "Introduceti nod sursa : ";
            int nodS; cin >> nodS;
            moore(adjMatrix, noNodes, nodS);
            
        }
        else if (opt == 2) {
            int d;
            for (int i = 1; i <= noNodes; i++)
            {
                for (int j = 1; j <= noNodes; j++)
                {
                    if (i == j)
                        cout << "1 ";
                    else {
                        if ((d = dijkstra(adjMatrix, noNodes, i, j)) != MAX_VAL)
                            cout << "1 ";
                        else
                            cout << "0 ";
                    }
                }
                cout << endl;
            }
        }
        else if (opt == 3) {
            cout << "Introduceti numele fisierului din care sa se incarce labirintul: ";
            string fn = ""; cin >> fn;
            solveLabirinth(fn);
        }
        else if (opt == 4) {
            cout << "Introduceti nod sursa : ";
            int nodS; cin >> nodS;
            BFS(adjMatrix, noNodes, nodS);
        }
        else if (opt == 5) {
            DFS(adjMatrix, noNodes);
        }
        else  {
            cout << "Optiune gresita!Reincercati." << endl;
        }
        menu();
        cin >> opt;
    }
    for (int i = 0; i < noNodes + 1; i++)
        delete[] adjMatrix[i], adjMatrix[i] = NULL;
    delete[] adjMatrix;
    adjMatrix = NULL;
    return 0;
    
}
