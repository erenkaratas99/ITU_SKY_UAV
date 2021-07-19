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


***Avionics Explanined***

Between 11.1V LiPo Battery and main DC Motor 60A ESC had connected.  5V O/P of ESC had connected to our stripboard circuit that contains headers.

In stripboard, every header have one O/P for PWM signal and the other 2 line had used for GND & Supply lines.

The header for ESC O/P had used as main header to GND and Supply lines for other headers. O/P's of GND and Supply line have connected to Arduino Nano afterwards.

Supply O/P of stripboard is connected to Nano's VIN pin to feed it. GND O/P is connected to Nano because ***GND lines of ESC and Nano should be common***.



***Arduino code explained***


Data comes from R12DS receiver had manipulated by function 'map' to be able to write in servo motors as desired degrees.

All analog pins had filtered to get rid of electrical noise.

State control process had been applied also.
