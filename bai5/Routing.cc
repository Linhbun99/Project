#include "Routing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <list>

using namespace std;

Routing *Routing::singleton_ = nullptr;

Routing::Routing(){
    init();
}

Routing* Routing::getInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new Routing();
    }
    return singleton_;
}

vector<vector<string>> Routing::getAdjList() {
    return adjList;
}

void Routing::init() {

    /////////////////////////////////////
    // Reading connections list from file

    string line;
    ifstream myfile("./ConnectionsList.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            char buffer[10];
            int i = 0;
            adjList.push_back(*new vector<string>);
            for (auto it = line.begin(); it != line.end(); it++) {
                if (*it != ' ') {
                    buffer[i++] = *it;
                }
                else {
                    string s = string(buffer, i);
                    adjList.back().push_back(s);
                    i = 0;
                }
            }
            string s = string(buffer, i);
            adjList.back().push_back(s);
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    for (auto v : adjList) {
        for (auto s : v) {
            cout << s << " ";
        }
        cout << "\n";
    }

    //    adjList:

    //    switch0 switch1 switch3 host0
    //    switch1 switch2 switch0 switch4 host1
    //    switch2 switch1 switch5 host2
    //    switch3 switch4 switch6 switch0 host3
    //    switch4 switch5 switch3 switch7 switch1 host4
    //    switch5 switch4 switch8 switch2 host5
    //    switch6 switch7 switch3 host6
    //    switch7 switch8 switch6 switch4 host7
    //    switch8 switch7 switch5 host8

    int k = 0;
    for (auto line : adjList) {
        switchesMap.insert(pair<string, int>(line.front(), k));
//        cout<< k<<endl;
        hostsMap.insert(pair<string, int>(line.back(), 1000 + k));
        k++;
    }

// switchdMap
/*  1 3
    2 0 4
    1 5
    4 6 0
    5 3 7 1
    4 8 2
    7 3
    8 6 4
    7 5
*/

    // Init connections matrix

    numSwitch = adjList.size();
    conn = new int* [numSwitch];


    for (int i = 0; i < numSwitch; i++) {
        lineLength = adjList[i].size(); //line length = 4
        conn[i] = new int[lineLength - 1]; // conn [3]
        for (int j = 0; j < lineLength - 2; j++) { // for j = 0;1
            conn[i][j] = switchesMap.at(adjList[i][j+1]);
        }
        conn[i][lineLength - 2] = hostsMap.at(adjList[i][lineLength - 1]);
    }

    for (int i = 0; i < numSwitch; i++) {
        lineLength = adjList[i].size();
        for (int j = 0; j < lineLength - 1; j++) {
            cout << conn[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * src: id của switch gửi
 * dst: id của switch nhận
 * return: cổng ra
 */
int Routing::next(int src, int dst) {
    if (src == dst) {
        return -1;
    }
    bool* visited = new bool[numSwitch] {false};
    queue<list<pair<int, int>>> myqueue;
    lineLength = adjList[src].size();
    for (int i = 0; i < lineLength - 2; i++) {
        list<pair<int, int>> l1;
        l1.push_back(pair<int, int>(conn[src][i], i));
//        cout<<"line 135"<< conn[src][i] <<" "<< i<< endl;
        myqueue.push(l1);
    }
    visited[src] = true;
    while (!myqueue.empty()) {
        list<pair<int, int>> l1 = myqueue.front();
        myqueue.pop();
        int hop = l1.back().first;
        if (hop == dst) {
            return l1.front().second;
        }
        lineLength = adjList[hop].size();
        for (int i = 0; i < lineLength - 2; i++) {
            if (!visited[conn[hop][i]]) {
                list<pair<int, int>> l2(l1);
                l2.push_back(pair<int, int>(conn[hop][i], i));
                myqueue.push(l2);
            }
        }
        visited[hop] = true;
    }
    return -2;
}

void Routing::printPath(int src, int dst) {
    cout << "path from " << src << " to " << dst << endl;
    int nextPort = next(src, dst);
    while (nextPort != -1) {
        printf_s("(%d,%d)->", src, nextPort);
        src = conn[src][nextPort];
        nextPort = next(src, dst);
    }
    cout << dst;
}

/**
 * srcName: tên nút gửi (có thể là switch hoặc host)
 * dstName: tên nút nhận (có thể là switch hoặc host)
 * return: Cổng ra
 */
int Routing::next(const char *srcName, const char *dstName) {
    int srcId = -1;
    int dstId = -1;
    // giả sử nút gửi là host1 và nhận là host5
    if (hostsMap.find(string(srcName)) != hostsMap.end()) { // đã tìm đến
        return 0;
    }
    srcId = switchesMap.at(string(srcName)); // srcId = 1

    if (hostsMap.find(string(dstName)) != hostsMap.end()) { // nếu tiếp theo vẫn chưa phải là nút đích if 5 != 1
        dstId = hostsMap.at(string(dstName)); // chỉ số của nút đích -- 5
        lineLength = adjList[srcId].size();
        if (conn[srcId][lineLength - 2] == dstId) { // if 3 = 5
//            cout<<"line 187"<<conn[srcId][lineLength - 2]<<" "<<lineLength - 2<< endl ;
            return lineLength - 2;
        }
//        cout<< "call to line 193:   ";
        for (int i = 0; i < numSwitch; i++) {
            lineLength = adjList[i].size();
            if (conn[i][lineLength - 2] == dstId) {
//                cout<<"line 193 " <<srcId<<endl;

                return next(srcId, i);
            }
        }

        return -1;
    }

    dstId = switchesMap.at(string(dstName));
    cout<<srcId <<dstId <<endl;
    return next(srcId, dstId);
}

/**
 * srcName: tên switch gửi
 * return: bảng định tuyến
 */
map<string, int> Routing::getRoutingTable(const char *srcName) {
    map<string, int> routingTable;
    for (int i = 0; i < numSwitch; i++) {
        lineLength = adjList[i].size();
        routingTable.insert(pair<string, int>(adjList[i][lineLength - 1], next(srcName, adjList[i][lineLength - 1].c_str())));
    }
    return routingTable;
}
