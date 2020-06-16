#include <string.h>
#include <omnetpp.h>
#include <string>
#include "Host.h"

using namespace omnetpp;
using namespace std;

Define_Module(Host);

void Host::initialize() {
    if (strcmp(getName(), "host8") == 0) {
        cMessage *testMsg = new cMessage("testMsg");
        cMsgPar *msgPar = new cMsgPar("dst");
        msgPar->setStringValue("host1");
        testMsg->addPar(msgPar);
        send(testMsg, "port$o", 0);
    }
}

void Host::handleMessage(cMessage *msg) {
    string dstName = msg->par("dst").stringValue();
    if (dstName.compare(getName()) == 0) {
        bubble("received testMsg");
    }
}
