#ifndef __HOST_H__
#define __HOST_H__

#include <string.h>
#include <omnetpp.h>
#include <string>
#include <queue>

using namespace omnetpp;
using namespace std;

class Host: public cSimpleModule {
private:
    // constant
    int EXB_SIZE;
    double TIMEOUT;
    double MSG_GEN_TIME_PERIOD;
    double CHANNEL_DELAY;
    double INTERVAL;

    bool isSender;
    std::string pairHostName;

    int lastestMsgId = -1;

    int *receivedMsgCount;
    int numInterval;
    int interval = 0;

    static int *recvMsgCountSum;

    // source queue
    queue<int> SQ;

    // exit buffer
    queue<int> EXB;

    // s? ch? tr?ng c?a ENB c?a switch
    int numSpacesOfNextENB;

    void generateMessage();
    void SQtoEXB(); // Chuy?n g�i tin t? SQ sang EXB
    void sendMsg(); // G?i t? EXB di sang n�t kh�c

protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    void incNumSpacesOfNextENB();
};

#endif

