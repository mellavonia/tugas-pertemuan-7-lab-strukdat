#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;
        vector<char> namaVertex;
        vector<int> jarak;
        vector<int> prev;

    public:
        Graph(int banyakTitik) {
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
            for (int i = 0; i < numberVertex; i++)
                namaVertex.push_back('A' + i);
        }

    void addEdge(int i, int j, int bobot) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = bobot;
            adjMatrix[j][i] = bobot;
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    void dijkstra(int sumber) {
        jarak.assign(numberVertex, INT_MAX);
        prev.assign(numberVertex, -1);
        vector<bool> selesai(numberVertex, false);
        jarak[sumber] = 0;

        for (int k = 0; k < numberVertex; k++) {
            int u = -1;
            for (int i = 0; i < numberVertex; i++) {
                if (!selesai[i] && jarak[i] != INT_MAX && (u == -1 || jarak[i] < jarak[u]))
                    u = i;
            }
            if (u == -1) break;
            selesai[u] = true;

            for (int v = 0; v < numberVertex; v++) {
                if (adjMatrix[u][v] > 0 && jarak[u] + adjMatrix[u][v] < jarak[v]) {
                    jarak[v] = jarak[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    void tampilRute(int tujuan) {
        if (prev[tujuan] != -1) {
            tampilRute(prev[tujuan]);
            cout << " -> ";
        }
        cout << namaVertex[tujuan];
    }

    void tampilSemuaRute(int sumber) {
        dijkstra(sumber);
        cout << "Rute terpendek dari " << namaVertex[sumber] << " ke semua lokasi:" << endl;

        for (int i = 0; i < numberVertex; i++) {
            if (i == sumber) continue;

            cout << "  ";
            if (jarak[i] == INT_MAX) {
                cout << namaVertex[i] << " : tidak terjangkau";
            } else {
                tampilRute(i);
                cout << " (total " << jarak[i] << " km)";
            }
            cout << endl;
        }
    }

    void rekomendasiRute(int asal, int tujuan) {
        if (asal < 0 || asal >= numberVertex || tujuan < 0 || tujuan >= numberVertex) {
            cout << "Lokasi tidak valid" << endl;
            return;
        }

        dijkstra(asal);
        cout << "\nRekomendasi rute tercepat: ";

        if (jarak[tujuan] == INT_MAX) {
            cout << "tidak ada rute" << endl;
            return;
        }

        tampilRute(tujuan);
        cout << "\nTotal jarak: " << jarak[tujuan] << " km" << endl;
    }
};

int main() {
    Graph graphh(6);

    graphh.addEdge(0, 1, 4);
    graphh.addEdge(1, 2, 1);
    graphh.addEdge(2, 3, 8);
    graphh.addEdge(3, 4, 2);
    graphh.addEdge(4, 5, 3);
    graphh.addEdge(0, 2, 2);
    graphh.addEdge(1, 3, 5);
    graphh.addEdge(2, 4, 6);
    graphh.addEdge(3, 5, 4);
    graphh.addEdge(1, 4, 3);

    graphh.tampilSemuaRute(0);

    char asal, tujuan;
    cout << "\nMasukkan lokasi awal (A-F): ";
    cin >> asal;
    cout << "Masukkan lokasi tujuan (A-F): ";
    cin >> tujuan;

    graphh.rekomendasiRute(asal - 'A', tujuan - 'A');
    return 0;
}