#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

#define INF INT_MAX

std::vector<std::vector<int>> adj = {
//   u, v, w, x, y, z 
    {0, 0, 0, 0, 0, 0},// u
    {0, 0, 0, 0, 0, 0},// v
    {0, 0, 0, 0, 0, 0},// w
    {0, 0, 0, 0, 0, 0},// x
    {0, 0, 0, 0, 0, 0},// y
    {0, 0, 0, 0, 0, 0} // z
};

std::unordered_map<char, int> toint = {
    {'u', 0}, 
    {'v', 1}, 
    {'w', 2}, 
    {'x', 3}, 
    {'y', 4}, 
    {'z', 5}
};
std::unordered_map<int, char> tochar = {
    {0, 'u'}, 
    {1, 'v'}, 
    {2, 'w'}, 
    {3, 'x'}, 
    {4, 'y'}, 
    {5, 'z'}
};

void dijkstra(int src, std::vector<int>& dist, std::vector<int>& prev) {
    int n = adj.size();
    dist.assign(n, INF);
    prev.assign(n, -1);

    dist[src] = 0;
    std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
    > pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();

        for (int u = 0; u < n; u++) {
            if (adj[v][u] != 0) {
                int new_dist = dist[v] + adj[v][u];
                if (new_dist < dist[u]) {
                    dist[u] = new_dist;
                    prev[u] = v;
                    pq.push({new_dist, u});
                }
            }
        }
    }
}

void printpath(int v, const std::vector<int>& prev, int end) {
    if (v < 0) return;
    printpath(prev[v], prev, end);
    if (end != v) {
        std::cout << tochar[v] << "-";
    }
    else {
        std::cout << tochar[v];
    }
}

void printdijikstra() {
    std::vector<int> dist, prev;
    dijkstra(toint['u'], dist, prev);

    for (int i = 1; i < adj.size(); i++) {
        printpath(i, prev, i);
        std::cout << ": " << dist[i] << std::endl;
    }
}

void addlink(char num, char a, char b) {
    int add;
    if (num == '0') {
        add = 10;
    }
    else {
        add = (int)(num - '0');
    }
    adj[toint[a]][toint[b]] = add;
    adj[toint[b]][toint[a]] = add;
}

bool isNumber(const std::string& str) {
  for (char const& c : str) {
    if (std::isdigit(c) == 0) return false;
  }
  return true;
}

void printadj() {
    std::cout << std::endl;
    std::cout << "Adjacency matrices:" << std::endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << adj[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::string s;
    while (1) {
        std::cout << "Input your id: ";
        std::cin >> s;
        if (s.size() == 8 && isNumber(s)) {
            break;
        }
        else {
            std::cout << "ID invaild!!!" << std::endl;
        } 
    }
    addlink(s[0], 'u', 'v');
    addlink(s[1], 'v', 'x');
    addlink(s[2], 'v', 'w');
    addlink(s[3], 'w', 'x');
    addlink(s[4], 'x', 'y');
    addlink(s[5], 'w', 'y');
    addlink(s[6], 'w', 'z');
    addlink(s[7], 'y', 'z');
    addlink('3', 'u', 'w');
    addlink('2', 'u', 'x');

    printadj();
    printdijikstra();
    
    return 0;
}