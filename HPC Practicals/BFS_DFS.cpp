#include <iostream>
#include <omp.h>
#include <queue>
#include <vector>

using namespace std;

class Graph{
    int V; // No of vertices
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex)
    {
        vector<bool> visited(V, false);
        parallelDFSUtils(startVertex, visited);
    }

    void parallelDFSUtils(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int n = adj[v][i];
            if (!visited[n])
            {
                parallelDFSUtils(n, visited);
            }
        }
    }

    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i)
            {
                int n = adj[v][i];
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main()
{

    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "DFS Parallel: ";
    g.parallelDFS(0);
    cout << endl;

    cout << "BFS Parallel: ";
    g.parallelBFS(0);
    cout << endl;

    return 0;
}