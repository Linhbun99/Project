#ifndef __LAB06_2_SENDING_HOST_H_
#define __LAB06_2_SENDING_HOST_H_

#include <string.h>
#include <omnetpp.h>
#include <iostream>
#include <string>
#include <queue>

using namespace omnetpp;
using namespace std;

class SendingHost: public cSimpleModule {
private:
    // constant
    int EXB_SIZE;
    double TIMEOUT;
    double MSG_GEN_TIME_PERIOD;
    double CHANNEL_DELAY;

    int lastestMsgId = -1;

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
    virtual void handleMessage(cMessage *msg) override;

public:
    void incNumSpacesOfNextENB();
};

#endif

