#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"

typedef char (*funPTR)(Traffic *);

SystemState systemState={OFF,RED,OFF,35,
#if WITH_ENGINE_TEMP_CONTROLLER 
OFF ,
140
#endif
}; 

int main(void) {
    
    mainMenu();
    return 0;
}

void mainMenu() {
    printf("a. Turn on the vehicle engine\n");
    printf("b. Turn off the vehicle engine\n");
    printf("c. Quit the system\n\n");
    
    while (1) {
        printf("Enter your choice: ");
        scanf(" %c", &systemState.userInput);

        if (systemState.userInput == 'a' || systemState.userInput == 'A' ||
            systemState.userInput == 'b' || systemState.userInput == 'B' ||
            systemState.userInput == 'c' || systemState.userInput == 'C') {
            break;
        } else {
            printf("Invalid option. Please enter a valid option.\n");
        }
    }

    switch (systemState.userInput) {
        case 'a':
        case 'A':
            systemState.vehicleState = RUNNING;
            stateAction();
            break;
        case 'b':
        case 'B':
            systemState.vehicleState = OFF;
            stateAction();
            break;
        case 'c':
        case 'C':
            printf("System is Shutting down..\n");
            break;
        default:
            break;
    }
}

void sensorsMenu() {
    do {
        printf("a. Turn off the engine\n");
        printf("b. Set traffic light color\n");
        printf("c. Set the room Temp\n");
        #if WITH_ENGINE_TEMP_CONTROLLER
        printf("d. Set the engine Temp\n\n");
        #endif

        while (1) {
            printf("Enter your choice: ");
            scanf(" %c", &systemState.sensorsInput);

            if (systemState.sensorsInput == 'a' || systemState.sensorsInput == 'A' ||
                systemState.sensorsInput == 'b' || systemState.sensorsInput == 'B' ||
                systemState.sensorsInput == 'c' || systemState.sensorsInput == 'C' 
                #if WITH_ENGINE_TEMP_CONTROLLER
                || systemState.sensorsInput == 'd' || systemState.sensorsInput == 'D'
                #endif
                ) {
                break;
            } else {
                printf("Invalid option. Please enter a valid option.\n");
            }
        }

        switch (systemState.sensorsInput) {
            case 'a':
            case 'A':
                systemState.vehicleState = OFF;
                stateAction();
                break;
            case 'b':
            case 'B':
                systemState.color = setTraffic();
                sensorsVal();
                break;
            case 'c':
            case 'C':
                systemState.AC_State = setTemp_AC();
                sensorsVal();
                break;
            #if WITH_ENGINE_TEMP_CONTROLLER
            case 'd':
            case 'D':
                systemState.EC_State = setTemp_EC();
                sensorsVal();
                break;
            #endif
            default:
                break;
        }

    } while (systemState.userInput != 'c' && systemState.userInput != 'C');
}

void sensorsVal() {
    funPTR speedPTR;
    speedPTR = speedControl;
    
    if (speedPTR(&systemState.color) == 30) {
        if (systemState.AC_State == OFF) {
            systemState.AC_State = RUNNING;
            systemState.roomTemp = (float)systemState.roomTemp * (5.0 / 4) + 1;
        }
        #if WITH_ENGINE_TEMP_CONTROLLER
        if (systemState.EC_State == OFF) {
            systemState.EC_State = RUNNING;
            systemState.engineTemp = (float)systemState.engineTemp * (5.0 / 4) + 1;
        }
        #endif
    }
    
    if (systemState.vehicleState) {
        printf("Vehicle Engine Status : ON \n");
    } else {
        printf("Vehicle Engine Status : OFF \n");
    }

    printf("Vehicle Speed : %d Km/Hr\n", speedControl(&systemState.color));

    if (systemState.AC_State) {
        printf("AC status : ON\n");
    } else {
        printf("AC status : OFF\n");
    }

    printf("Vehicle Room Temp : %0.2f C \n", (float)systemState.roomTemp);
#if WITH_ENGINE_TEMP_CONTROLLER
    if (systemState.EC_State) {
        printf("EC status : ON\n");
    } else {
        printf("EC status : OFF\n");
    }

    printf("Vehicle Engine Temp : %0.2f C \n\n", (float)systemState.engineTemp);
#endif
}

void stateAction() {
    if (systemState.vehicleState == OFF) {
        printf("Vehicle engine is OFF\n\n");
        mainMenu();
    } else if (systemState.vehicleState == RUNNING) {
        printf("Vehicle engine is RUNNING\n\n");
        sensorsMenu();
    }
}

char speedControl(Traffic *color) {
    unsigned char vehicleSpeed = 0;

    if (*color == GREEN) {
        vehicleSpeed = 100;
    } else if (*color == ORANGE) {
        vehicleSpeed = 30;
    } else if (*color == RED) {
        vehicleSpeed = 0;
    }

    return vehicleSpeed;
}

Traffic setTraffic() {
    Traffic color;

    printf("Set Traffic Light\n");

    while (1) {
        printf("Enter color: ");
        scanf(" %c", &systemState.userInput);

        if (systemState.userInput == 'g' || systemState.userInput == 'G' ||
            systemState.userInput == 'o' || systemState.userInput == 'O' ||
            systemState.userInput == 'R' || systemState.userInput == 'r') {
            break;
        } else {
            printf("Invalid option. Please enter a valid option.\n");
        }
    }

    switch (systemState.userInput) {
        case 'g':
        case 'G':
            color = GREEN;
            break;
        case 'o':
        case 'O':
            color = ORANGE;
            break;
        case 'r':
        case 'R':
            color = RED;
            break;
        default:
            break;
    }

    return color;
}

State setTemp_AC() {
    printf("Enter Vehicle Room Temperature: ");
    scanf(" %d", &systemState.roomTemp);
    State AC_State = OFF;

    if (systemState.roomTemp < 10 || systemState.roomTemp > 30) {
        AC_State = RUNNING;
        systemState.roomTemp = 20;
    } else {
        AC_State = OFF;
    }

    return AC_State;
}

#if WITH_ENGINE_TEMP_CONTROLLER

State setTemp_EC() {
    printf("Enter Vehicle Engine Temperature: ");
    scanf(" %d", &systemState.engineTemp);
    State EC_State = OFF;

    if (systemState.engineTemp < 100 || systemState.engineTemp > 150) {
        EC_State = RUNNING;
        systemState.engineTemp = 125;
    } else {
        EC_State = OFF;
    }

    return EC_State;
}

#endif