//uncomment to enable debug
//#define DEBUG

#define S0 A2
#define S1 A3
#define S2 A0
#define S3 A1
#define sensorOut 2

//clickers
#define LCLICK 8
#define RCLICK 7

//motor pins
#define LMF 9
#define LMR 6
#define RMF 5
#define RMR 3

//error factor
#define ERRFACTOR 6

#define MPU_addr 0x68

//ultrasonic pins
#define LEFT 12
#define MIDDLE 11
#define RIGHT 10

//Wall distance
#define WALLDISTANCE 20

//define counter
#define MAXCOUNT 70

#define TILERUN 880

#define RAMPAMGLE 18

#define TILESIZE 30

//uncomment to enable back align
//#define BACKALIGN


//uncomment one of the following algorithms
//#define DFS   //Depth first search
#define LWF     //Left wall follow
//#define RWF   //Right wall follow
















#if (defined(LWF) and defined(RWF) and defined(DFS))
or (notdefined(LWF) and defined(RWF) and defined(DFS))
or (defined(LWF) and notdefined(RWF) and defined(DFS))
or (defined(LWF) and defined(RWF) and notdefined(DFS))
#error "More than one algorithm selected. please select only one."
#endif

#ifndef LWF
#ifndef RWF
#ifndef DFS
#error "Please select atleast one maze solving algorithm"
#endif
#endif
#endif
