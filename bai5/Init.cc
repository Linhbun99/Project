#include "Init.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Initializer *Initializer::singleton_ = nullptr;

Initializer* Initializer::getInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new Initializer();
    }
    return singleton_;
}

/**
 * Xáo trộn danh sách các host
 */
Initializer::Initializer() {
    seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int x = 0; x < N; x++) {
                char name[10];
                sprintf(name, "host%d", x);
                hostNames.push_back(string(name));
    }

    shuffle(hostNames.begin(), hostNames.end(),
            std::default_random_engine(seed));
}

/**
 * Lấy ra nhiệm vụ của một host (gửi / nhận)
 * hostName: tên host
 * return: true nếu là host gửi, false nếu là host nhận
 */
bool Initializer::getDuty(std::string hostName) {
    for (int i = 0; i < hostNames.size() / 2; i++) {
        if (hostNames[i].compare(hostName) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Lấy ra nút cặp với host hiện tại
 * hostName: tên host
 * return: tên host còn lại
 */
string Initializer::getPairHostName(std::string hostName) {
    int thisIndex = -1;
    int size = hostNames.size();
    for (int i = 0; i < size; i++) {
        if (hostNames[i].compare(hostName) == 0) {
            thisIndex = i;
            break;
        }
    }

    if (thisIndex == -1) {
        throw "ERROR";
    }

    if (thisIndex < size / 2) {
        return hostNames[thisIndex + size / 2];
    }
    else {
        return hostNames[thisIndex - size / 2];
    }
}
