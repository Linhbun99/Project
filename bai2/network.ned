simple SendingHost
{
    parameters:
        int EXB_SIZE = 2; // Exit buffer size
    gates:
        output out;
}

simple ReceivingHost
{
    parameters:
    gates:
        input in;
        output out;
}

simple Switch
{
    parameters:
        int EXB_SIZE = 2;
        int ENB_SIZE = 2; // Entrance buffer size
        double OPERATION_TIME_PERIOD = 0.005;
    gates:
        input in[];
        output out;
}

network Network
{
    parameters:
        double TIMEOUT = 1; // Simulation time = 1s
        double MSG_GEN_TIME_PERIOD = 0.005; // Message generation time period = 5ms
        double INTERVAL = 0.005; // Interval = 5ms
        // Credit delay = 1ms
        double CREDIT_DELAY @display("bgb=231.84,132.72") = 0.001;
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 15ms;
        }
    submodules:
        A: SendingHost {
            @display("i=abstract/server;p=38.22,29.82");
        }
        B: SendingHost {
            @display("i=abstract/server;p=38,120");
        }
        C: SendingHost {
            @display("i=abstract/server;p=38,209");
        }
        D: Switch {
            @display("p=193,120;i=abstract/switch");
        }
        E: ReceivingHost {
            @display("i=abstract/server;p=330,120");
        }
    connections:
        A.out --> Channel --> D.in++;
        B.out --> Channel --> D.in++;
        C.out --> Channel --> D.in++;
        D.out --> Channel --> E.in;
        E.out --> D.in++;
}
