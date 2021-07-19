# ITU_SKY_UAV

In this repository you can find our codes that we wrote for our fixed wing full RC unmanned aerial vehicle (UAV).

Avionic system that we used in our UAV can be explained as;

-Arduino Nano
-2500 mAh 11.1V LiPo Battery
-60A Skywalker ESC
-A stripboard circuit designed by us that contains headers for wing/tail servo connnections and supply&GND lines
-9000 Watt DC Motor
-4 Servo Motors for ailerons,elevator,rudder (control surfaces on the wings will be used as both ailerons and flaperons due to selected mode from RC Controller)
-RC Controller (Radiolink AT10 II) & R12DS Receiver

---Inner structure explained;

***RC Controller-Arduino Nano Integration***

x-axis of right stick triggers 2 Channels simultaneously and we have inverted one channel to be able to send commands to ailerons as opposite degrees
y-axis of right stick triggers 1 Channel and we have used it as elevator servo motor control channel

x-axis of left stick triggers 1 Channel and we have used it as rudder controller channgel for surface movements
y-axis of left stick triggers 1 Channel and we have used that channel for thrust motor control channel

