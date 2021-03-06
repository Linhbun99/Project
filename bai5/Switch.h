#ifndef __SWITCH_H__
#define __SWITCH_H__

#include <string.h>
#include <omnetpp.h>
#include <string>
#include <queue>
#include "Routing.h"

//Torus 2D: LINE_LENGTH = 6
//Torus 2D: LINE_LENGTH = 8
#define LINE_LENGTH 6

using namespace omnetpp;
using namespace std;

class Switch: public cSimpleModule {
private:
    double TIMEOUT;
    double CREDIT_DELAY;
    double OPERATION_TIME_PERIOD;
    double CHANNEL_DELAY;

    int ENB_SIZE;
    int EXB_SIZE;
    int lineLength;
    cModule *neighbors[LINE_LENGTH - 1];

    queue<cMessage*> ENB[LINE_LENGTH - 1];
    queue<cMessage*> EXB[LINE_LENGTH - 1];

    int numSpacesOfNextENB[LINE_LENGTH - 2];

    map<string, int> routingTable;

    void printRoutingTable();
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    int chooseENB(int EXBid);
    void ENBtoEXB(int ENBid, int EXBid);
    void incNumSpacesOfNextENB(const char *switchName);
};

#endif

