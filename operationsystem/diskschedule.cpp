#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int FCFS(vector<int> requests) {
    int times = 0;
    for (int i = 1; i < requests.size(); i++) {
        times += abs(requests[i] - requests[i - 1]);
    }
    return times;
}

int SSTF(vector<int> requests) {
    int times = 0;
    int size = requests.size();
    int curr = requests[0];
    requests.erase(requests.begin());
    while (!requests.empty()) {
        auto closest = min_element(requests.begin(), requests.end(),
                                   [curr](int a, int b) {
                                       return abs(a - curr) < abs(b - curr);
                                   });
        times += abs(*closest - curr);
        curr = *closest;
        requests.erase(closest);
    }
    return times;
}

int SCAN(vector<int> requests) {
    int times = 0;
    int size = requests.size();
    int curr = requests[0];
    requests.erase(requests.begin());
    sort(requests.begin(), requests.end());
    auto upper = upper_bound(requests.begin(), requests.end(), curr);
    if (upper != requests.end()) {
        for(auto it = upper; it != requests.end(); it++) {
            times += abs(*it - curr);
            curr = *it;
        }
    }
    if (upper != requests.begin()) {
        for(auto it = prev(upper); it != requests.begin(); it--) {
            times += abs(*it - curr);
            curr = *it;
        }
        times += abs(*requests.begin() - curr);
    }
    return times;
}

int CSCAN(vector<int> requests) {
    int times = 0;
    int size = requests.size();
    int curr = requests[0];
    requests.erase(requests.begin());
    sort(requests.begin(), requests.end());
    auto upper = upper_bound(requests.begin(), requests.end(), curr);
    if (upper != requests.end()) {
        for(auto it = upper; it != requests.end(); it++) {
            times += abs(*it - curr);
            curr = *it;
        }
    }
    if (upper != requests.begin()) {
        times += abs(*requests.begin() - curr);
        curr = *requests.begin();
        for(auto it = requests.begin(); it != upper; it++) {
            times += abs(*it - curr);
            curr = *it;
        }
    }
    return times;
}

int FSCAN(vector<int> requests) {
    int times = 0;
    int que = 0;
    sort(requests.begin(), requests.end());
    vector<vector<int>> queues(2);
    int mid = requests.size() / 2;
    queues[0] = vector<int>(requests.begin(), requests.begin() + mid);
    queues[1] = vector<int>(requests.begin() + mid, requests.end());
    int curr = queues[que][0];
    queues[que].erase(queues[que].begin());
    while (!queues[0].empty() || !queues[1].empty()) {
        sort(queues[que].begin(), queues[que].end());
        while (!queues[que].empty()) {
            times += abs(queues[que].back() - curr);
            curr = queues[que].back();
            queues[que].pop_back();
        }
        que = 1 - que;
    }
    return times;
}

int main() {
    srand(time(0));
    int totalFCFS = 0, totalSSTF = 0, totalSCAN = 0, totalCSCAN = 0, totalFSCAN = 0;
    for (int i = 0; i < 100; i++) {
        vector<int> requests(100);
        for (int j = 0; j < requests.size(); j++) requests[j] = rand() % 200;
        totalFCFS += FCFS(requests);
        totalSSTF += SSTF(requests);
        totalSCAN += SCAN(requests);
        totalCSCAN += CSCAN(requests);
        totalFSCAN += FSCAN(requests);
    }
    cout << "FCFS average seek time:  " << totalFCFS / 100.0 << endl;
    cout << "SSTF average seek time:  " << totalSSTF / 100.0 << endl;
    cout << "SCAN average seek time:  " << totalSCAN / 100.0 << endl;
    cout << "CSCAN average seek time: " << totalCSCAN / 100.0 << endl;
    cout << "FSCAN average seek time: " << totalFSCAN / 100.0 << endl;
    return 0;
}