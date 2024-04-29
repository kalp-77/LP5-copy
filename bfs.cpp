#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <omp.h>
#define int long long


using namespace std;
    
    int n = 10000;
    int m = 10000;
    vector<vector<int>> graph(n+1);
    
    void dfs(int node) {
        stack<int> s;
        s.push(node);
        vector<bool> vis(n,false);
        vis[node] = true;

        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            for (int child : graph[curr]) {
                if (!vis[child]) {
                    s.push(child);
                    vis[child] = true;
                }
            }
        }
    }

    void parallel_dfs(int node) {
        stack<int> s;
        vector<bool> vis(n,false);
        s.push(node);
        vis[node] = true;
        
            while (!s.empty()) {
                int curr = s.top();
                s.pop();

                #pragma omp parallel for
                for (int child : graph[curr]) {
                	if (!vis[child]) {
		          #pragma omp critical 
			   s.push(child);
			   vis[child] = true;
		            
		        }
                    
                }
                
            
        }
    }
    void bfs(int node) {
         queue<int> q;
        q.push(node);
        vector<bool> vis(n,false);
        vis[node] = true;

        while (!q.empty()) {
           int curr = q.front();
           q.pop();

            for (int child : graph[curr]) {
                if (!vis[child]) {
                    q.push(child);
                    vis[child] = true;
                }
            }
        }
    }

    void parallel_bfs(int node) {
        queue<int> q;
        vector<bool> vis(n,false);
       #pragma omp critical
        q.push(node);
        vis[node] = true;
            
        while (!q.empty()) {
               int curr = q.front();
               q.pop();
                #pragma omp parallel for
                for (int child : graph[curr]) {
                        if (!vis[child]) {
     			    	#pragma omp critical 
                                q.push(child);
                                vis[child] = true;
                        }
                }
        }
    }


signed main() {
    
    for (int i=0; i <n; i++) {
    	for(int j=0; j<m; j++){
    	    graph[i].push_back(j);
    	    graph[j].push_back(i);
 	}
     }
 

    double start = omp_get_wtime();
    dfs(0);
    double end = omp_get_wtime();
    double serialDfs = end - start;
    cout << "\nSerial DFS time: " << serialDfs << " seconds\n";


    start = omp_get_wtime();
    parallel_dfs(0);
    end = omp_get_wtime();
    double parallelDfs = end - start;
    cout << "Parallel DFS time: " << parallelDfs << " seconds\n";
    cout << "Speedup = " << serialDfs / parallelDfs << endl;
    cout<<endl;

    start = omp_get_wtime();
    bfs(0);
    end = omp_get_wtime();
    double serialBfs = end - start;
    cout << "Serial Bfs time: " << serialBfs << " seconds\n";
    

    start = omp_get_wtime();
    parallel_bfs(0);
    end = omp_get_wtime();
    double parallelBfs = end - start;
    cout << "Parallel Bfs time: " << parallelBfs << " seconds\n";
    cout << "Speedup = " << serialBfs / parallelBfs << endl;
    cout<<endl;

    return 0;
}

