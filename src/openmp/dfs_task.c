#include <stdio.h>
#include <omp.h>

#define N 6

int graph[N][N] = {
    {0,1,1,0,0,0},
    {1,0,0,1,1,0},
    {1,0,0,0,0,1},
    {0,1,0,0,0,0},
    {0,1,0,0,0,0},
    {0,0,1,0,0,0}
};

int visited[N] = {0};

void dfs(int v) {

    int already_visited = 0;

    #pragma omp critical
    {
        if (visited[v]) {
            already_visited = 1;
        } else {
            visited[v] = 1;
            printf("Visited %d by thread %d\n",
                   v, omp_get_thread_num());
        }
    }

    if (already_visited) return;

    // Explore neighbors
    for (int i = 0; i < N; i++) {
        if (graph[v][i]) {
            #pragma omp task
            dfs(i);
        }
    }

    // Wait for all child tasks
    #pragma omp taskwait
}

int main() {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            dfs(0);
        }
    }

    return 0;
}