simple Host
{
parameters:
@display("i=device/pc_s");

gates:
inout port[];
}
simple Switch
{
parameters:
@display("i=device/switch");

gates:
inout port[];
}
network Network
{
parameters:
@display("bgb=1356.1,682.825");
types:
channel Channel extends ned.DelayChannel
{delay = 15ms;}
submodules:
switch0: Switch { @display("p=200,200;i=abstract/switch"); }
switch1: Switch { @display("p=200,400;i=abstract/switch"); }
switch2: Switch { @display("p=200,600;i=abstract/switch"); }
switch3: Switch { @display("p=400,200;i=abstract/switch"); }
switch4: Switch { @display("p=400,400;i=abstract/switch"); }
switch5: Switch { @display("p=400,600;i=abstract/switch"); }
switch6: Switch { @display("p=600,200;i=abstract/switch"); }
switch7: Switch { @display("p=600,400;i=abstract/switch"); }
switch8: Switch { @display("p=600,600;i=abstract/switch"); }
host0: Host  { @display("p=150,150;i=abstract/server;is=s"); }
host1: Host  { @display("p=150,350;i=abstract/server;is=s"); }
host2: Host  { @display("p=150,550;i=abstract/server;is=s"); }
host3: Host  { @display("p=350,150;i=abstract/server;is=s"); }
host4: Host  { @display("p=350,350;i=abstract/server;is=s"); }
host5: Host  { @display("p=350,550;i=abstract/server;is=s"); }
host6: Host  { @display("p=550,150;i=abstract/server;is=s"); }
host7: Host  { @display("p=550,350;i=abstract/server;is=s"); }
host8: Host  { @display("p=550,550;i=abstract/server;is=s"); }

connections:
switch0.port++ <--> Channel <--> switch1.port++;

switch0.port++ <--> Channel <--> switch3.port++;

switch1.port++ <--> Channel <--> switch2.port++;

switch1.port++ <--> Channel <--> switch4.port++;

switch2.port++ <--> Channel <--> switch5.port++;

switch3.port++ <--> Channel <--> switch4.port++;

switch3.port++ <--> Channel <--> switch6.port++;

switch4.port++ <--> Channel <--> switch5.port++;

switch4.port++ <--> Channel <--> switch7.port++;

switch5.port++ <--> Channel <--> switch8.port++;

switch6.port++ <--> Channel <--> switch7.port++;
switch7.port++ <--> Channel <--> switch8.port++;
host0.port++ <--> Channel <--> switch0.port++;
host1.port++ <--> Channel <--> switch1.port++;
host2.port++ <--> Channel <--> switch2.port++;
host3.port++ <--> Channel <--> switch3.port++;
host4.port++ <--> Channel <--> switch4.port++;
host5.port++ <--> Channel <--> switch5.port++;
host6.port++ <--> Channel <--> switch6.port++;
host7.port++ <--> Channel <--> switch7.port++;
host8.port++ <--> Channel <--> switch8.port++;
}