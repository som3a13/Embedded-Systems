#define WITH_ENGINE_TEMP_CONTROLLER 1

typedef enum{
OFF,
RUNNING
} State;


typedef enum 
{
    RED,
    ORANGE,
    GREEN

}Traffic;

typedef struct {
    State vehicleState;
    Traffic color;
    State AC_State;
    int roomTemp;

    #if WITH_ENGINE_TEMP_CONTROLLER
    State EC_State;
    int engineTemp;
    #endif

    char userInput;
    char sensorsInput;
} SystemState;



void mainMenu();
void sensorsMenu();
void sensorsVal();
void stateAction();
Traffic setTraffic();
char speedControl(Traffic *color);
State setTemp_AC();
State setTemp_EC();

