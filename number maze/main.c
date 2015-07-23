#include<stdlib.h>
#include<stdio.h>

#include "listEph.h"
#include "queue.h"

#define MAX 100
typedef list *graph;

//transfer the input to a graph so we can apply BFS
graph input_to_graph(char** board, int n, int m){
    graph g = malloc(sizeof(*g) * m * n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(board[i][j] != 'G'){
                g[i*m+j] = NULL;
                
                int num_of_step = board[i][j] - '0';
                //check if we can go right
                if(j + num_of_step < m){
                    list_cons(i * m + j + num_of_step, &g[i*m+j]);
                }
                
                //check if we can go left
                if(j - num_of_step >= 0){
                    list_cons(i * m + j - num_of_step, &g[i*m+j]);
                }
                
                //check if we can go down
                if(i + num_of_step < n){
                    list_cons(i * m + j + num_of_step * m, &g[i*m+j]);
                }
                
                //check if we can go up
                if(i - num_of_step >= 0){
                    list_cons(i * m + j - num_of_step * m, &g[i*m+j]);
                }
            }
        }
    }
    return g;
}

//this function is for the shortest path using BFS
void graph_BFS(graph g, int n, int m, int start, int finish) {
    int visited[n];
    int parent[n];
    char path[n];
    int count = 0;
    
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    
    queue q = malloc(sizeof(*q));
    queue_init(q);
    queue_enqueue(q, start);
    while(!queue_isempty(q)){
        int current = queue_dequeue(q);
        if (current == finish) {
            int u = finish;
            while (u != start) {
                int step = parent[u] - u;
                if(step > 0 && step < m){
                    path[count] = 'L';
                }
                if(step >= m){
                    path[count] = 'U';
                }
                if(step < 0 && step > -m){
                    path[count] = 'R';
                }
                if(step <= -m){
                    path[count] = 'D';
                }
                u = parent[u];
                count++;
            }
            for (int k = count-1; k >= 0; k--) {
                printf("%c", path[k]);
            }
            return;
        }
        list neighbors = g[current];
        while (neighbors != NULL) {
            if(!visited[neighbors->x]){
                visited[neighbors->x] = 1;
                queue_enqueue(q, neighbors->x);
                parent[neighbors->x] = current;
                
            }
            neighbors = neighbors->next;
        }
    }
}

//this function is for printing all possible ways to reach 'G', using recursion
void all_solutions(char **board,int m, int n, int i, int j, int visited[][MAX], char result[], int t){
    //has reached the GOAL
    if(board[i][j] == 'G'){
        i = 0; j = 0;
        int cost = 0;
        for(int k = 0; k < t; k++){
            cost += board[i][j] - '0';
            switch(result[k]){
                case 'R':
                    j += board[i][j] - '0';
                    break;
                case 'L':
                    j -= board[i][j] - '0';
                    break;
                case 'D':
                    i += board[i][j] - '0';
                    break;
                case 'U':
                    i -= board[i][j] - '0';
                    break;
                default:
                    break;
            }
            printf("%c", result[k]);
        }
        printf("\n");
        return;
    }
    
    //check if we can go right
    int num_of_step = board[i][j] - '0';
    if(j + num_of_step < m && !visited[i][j+num_of_step]){
        result[t] = 'R';
        visited[i][j+num_of_step] = 1;
        all_solutions(board, m, n, i, j+num_of_step, visited, result, t+1);
        visited[i][j+num_of_step] = 0;
    }
    
    //check if we can go left
    if(j - num_of_step >= 0 && !visited[i][j-num_of_step]){
        result[t] ='L';
        visited[i][j-num_of_step] = 1;
        all_solutions(board, m,n, i, j-num_of_step, visited, result, t+1);
        visited[i][j-num_of_step] = 0;
    }
    
    //check if we can go down
    if(i + num_of_step < n && !visited[i+num_of_step][j]){
        result[t] ='D';
        visited[i+num_of_step][j] = 1;
        all_solutions(board, m,n, i+num_of_step, j, visited, result, t+1);
        visited[i+num_of_step][j] = 0;
    }
    
    //check if we can go up
    if(i - num_of_step >= 0 && !visited[i-num_of_step][j]){
        result[t] ='U';
        visited[i-num_of_step][j] = 1;
        all_solutions(board, m,n, i-num_of_step, j, visited, result, t+1);
        visited[i-num_of_step][j] = 0;
    }
}

int main(){
    int finish = 0;
    int n, m;
    
    //read file
    char filename[128];
    printf("Enter file name: ");
    scanf("%123s",filename);
    FILE *fp;
    fp=fopen(filename, "r");
    if(fp==NULL) {
        printf("Error! File did not open.\n");
        return 0;
    }
    
    fscanf(fp,"%d",&n);
    fscanf(fp,"%d",&m);
    
    char **board = (char**)malloc(sizeof(char*)*n);
    int ch;
    
    fscanf(fp,"%c",&ch);
    int visited[MAX][MAX];
    char result[MAX];
    
    //print the input file
    printf("\ninput file: \n");
    printf("%d %d\n", m, n);
    for(int i = 0; i < n; ++i) {
        board[i] = (char*)malloc(sizeof(char)*m);
        for(int j = 0; j < m; ++j){
            fscanf(fp,"%c",&board[i][j]);
            visited[i][j] = 0;
            if (board[i][j] == 'G') {
                finish = i*m+j;
            }
        }
        fscanf(fp, "%c", &ch);
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
    
    //get the shortest path
    printf("\nHere is the shortest path: \n");
    graph g = input_to_graph(board, n, m);
    graph_BFS(g, n*m, m, 0, finish);
    printf("\n");
    
    //get all possible paths
    printf("\nHere are all possible paths: \n");
    visited[0][0] = 1;
    all_solutions(board, m, n, 0, 0, visited, result, 0);
    printf("\n");

    return 0;
}
