#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;
        vector<char> namaVertex;

    public:
        Graph(int banyakTitik) {
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
            for (int i = 0; i < numberVertex; i++)
                namaVertex.push_back('A' + i);
        }

    void addEdge(int i, int j) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = 1;
            adjMatrix[j][i] = 1;
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    void printAdjMatrix() {
        cout << "  ";
        for (int i = 0; i < numberVertex; i++)
            cout << namaVertex[i] << " ";
        cout << endl;

        for (int i = 0; i < numberVertex; i++) {
            cout << namaVertex[i] << " ";
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfs(int startVertex) {
        if (startVertex < 0 || startVertex >= numberVertex) {
            cout << "Vertex awal tidak valid" << endl;
            return;
        }

        vector<bool> visited(numberVertex, false);
        queue<int> titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        cout << "Urutan BFS: ";
        while (!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();
            cout << namaVertex[currentVertex] << " ";

            for (int i = 0; i < numberVertex; i++) {
                if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph graphh(6);

    int jumlahEdge;
    cout << "Masukkan jumlah edge: ";
    cin >> jumlahEdge;

    for (int i = 0; i < jumlahEdge; i++) {
        char u, v;
        cout << "Edge ke-" << i + 1 << " (contoh: A B): ";
        cin >> u >> v;
        graphh.addEdge(u - 'A', v - 'A');
    }
    cout << endl;

    graphh.printAdjMatrix();
    cout << endl;

    char awal;
    cout << "Masukkan vertex awal (A-F): ";
    cin >> awal;

    graphh.bfs(awal - 'A');
    return 0;
}