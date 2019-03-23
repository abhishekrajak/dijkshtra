#include <iostream>
#include <vector>
#define n 10

using namespace std;

int distance_map[n][n];
int parent[n];
int distanceX[n];
bool active[n];
vector<pair<int, int>> vectorX[n];

void initialise(){
    for(int i=0; i<n; i++){
        parent[i] = -1;
        distanceX[i] = 0;
        active[i] = true;
        for(int j=0; j<n; j++){
            distance_map[i][j] = INT_MAX;
        }
    }
}

int get_min_vertex(){
    int minX = INT_MAX;
    int minVertex = -1;
    for(int i=0; i<n; i++){
        if(active[i]){
            if(distanceX[i]<minX){
                minX = distanceX[i];
                minVertex = i;
            }
        }
    }
    return minVertex;
}

void dijkshtra(int source){
    for(int i=0; i<n; i++){
        distanceX[i] = INT_MAX;
    }
    distanceX[source] = 0;
    int current;
    int countX = n;
    while(countX--){
        current = get_min_vertex();
        if(current==-1){
            continue;
        }
        active[current] = false;
        for(pair<int, int>XO : vectorX[current]){
            if(!active[XO.first]){
                continue;
            }
            if(distanceX[current] + distance_map[XO.first][current] <  distance_map[XO.first][source]){
                parent[XO.first] = current;
                distanceX[XO.first] = distanceX[current] + distance_map[XO.first][current];
            }
            else{
                parent[XO.first] = source;
                distanceX[XO.first] = distance_map[XO.first][source];
            }
        }
    }

}

void insert_pair(int a, int b, int dist){
    vectorX[a].push_back(make_pair(b, dist));
    vectorX[b].push_back(make_pair(a, dist));
    distance_map[a][b] = distance_map[b][a] = dist;
}

int main(){

    initialise();

    insert_pair(1, 2, 1);
    insert_pair(1, 3, 7);
    insert_pair(1, 5, 3);
    insert_pair(1, 4, 4);
    insert_pair(2, 4, 2);
    insert_pair(3, 4, 6);
    insert_pair(4, 5, 5);

    dijkshtra(5);

    for(int i=0; i<n; i++){
        cout << distanceX[i] << " ";
    }

    return 0;
}
