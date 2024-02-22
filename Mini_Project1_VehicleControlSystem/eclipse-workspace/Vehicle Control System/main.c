/**
 * @file main.c
 * @author Mohamed Ismail \n Instructor :  Mohamed Tarek
 * @brief Main file for the project
 * @version 1
 * @date 30/12/2023
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"


/**
 * @brief System state representing the overall state of the vehicle system.
 *
 * Initial values are set for systemState based on configuration options.
 */
SystemState systemState = {
    OFF, RED, OFF, 35,
#if WITH_ENGINE_TEMP_CONTROLLER
    OFF, 140
#endif
};

SystemState *ptr = &systemState; /**< Pointer to the system state structure. */

/**
 * @brief Entry point of the program.
 *
 * Calls the main menu function and returns 0 upon completion.
 *
 * @return 0 upon successful execution.
 */
int main(void)
{
    mainMenu();

    return 0;
}

/**
 * @brief Displays the main menu and handles user input.
 *
 * The main menu provides options to turn on/off the vehicle engine or quit the system.
 * Upon user input, appropriate actions are taken.
 */

void mainMenu()
{
    printf("a. Turn on the vehicle engine\n");
    printf("b. Turn off the vehicle engine\n");
    printf("c. Quit the system\n\n");
    fflush(stdout);
    while (1)
    {
        printf("Enter your choice: ");
        fflush(stdout);
        scanf(" %c", &ptr->userInput);

        if (ptr->userInput == 'a' || ptr->userInput == 'A' ||
            ptr->userInput == 'b' || ptr->userInput == 'B' ||
            ptr->userInput == 'c' || ptr->userInput == 'C')
        {
            break;
        }
        else
        {
            printf("Invalid option. Please enter a valid option.\n");
            fflush(stdout);
        }
    }

    switch (ptr->userInput)
    {
    case 'a':
    case 'A':
        ptr->vehicleState = RUNNING;
        stateAction();
        break;
    case 'b':
    case 'B':
        ptr->vehicleState = OFF;
        stateAction();
        break;
    case 'c':
    case 'C':
        printf("System is Shutting down..\n");
        fflush(stdout);
        break;
    default:
        break;
    }
}

/**
 * @brief Displays the sensors menu and handles user input for sensor-related actions.
 *
 * The sensor menu allows the user to perform various actions related to the vehicle's sensors.
 */
void sensorsMenu()
{
    do
    {
        printf("\n");
        printf("a. Turn off the engine\n");
        printf("b. Set traffic light color\n");
        printf("c. Set the room Temp\n");
        fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROLLER
        printf("d. Set the engine Temp\n\n");
        fflush(stdout);
#endif

        while (1)
        {
            printf("Enter your choice: ");
            fflush(stdout);
            scanf(" %c", &ptr->sensorsInput);

            if (ptr->sensorsInput == 'a' || ptr->sensorsInput == 'A' ||
                ptr->sensorsInput == 'b' || ptr->sensorsInput == 'B' ||
                ptr->sensorsInput == 'c' || ptr->sensorsInput == 'C'
#if WITH_ENGINE_TEMP_CONTROLLER
                || ptr->sensorsInput == 'd' || ptr->sensorsInput == 'D'
#endif
            )
            {
                break;
            }
            else
            {
                printf("Invalid option. Please enter a valid option.\n");
                fflush(stdout);
            }
        }

        switch (ptr->sensorsInput)
        {
        case 'a':
        case 'A':
            ptr->vehicleState = OFF;
            stateAction();
            break;
        case 'b':
        case 'B':
            ptr->color = setTraffic();
            sensorsVal();
            break;
        case 'c':
        case 'C':
            ptr->AC_State = setTemp_AC();
            sensorsVal();
            break;
#if WITH_ENGINE_TEMP_CONTROLLER
        case 'd':
        case 'D':
            ptr->EC_State = setTemp_EC();
            sensorsVal();
            break;
#endif
        default:
            break;
        }

    } while (ptr->userInput != 'c' && ptr->userInput != 'C');
}

/**
 * @brief Displays sensor values based on the system state.
 *
 * The sensor values include the vehicle's engine status, speed, AC status, and room/engine temperatures.
 */
void sensorsVal()
{
    funPTR speedPTR;
    speedPTR = speedControl;

    if (speedPTR(ptr->color) == 30)
    {
        if (ptr->AC_State == OFF)
        {
            ptr->AC_State = RUNNING;
            ptr->roomTemp = (float)ptr->roomTemp * (5.0 / 4) + 1;
        }
#if WITH_ENGINE_TEMP_CONTROLLER
        if (ptr->EC_State == OFF)
        {
            ptr->EC_State = RUNNING;
            ptr->engineTemp = (float)ptr->engineTemp * (5.0 / 4) + 1;
        }
#endif
    }

    if (ptr->vehicleState)
    {
        printf("Vehicle Engine Status : ON \n");
        fflush(stdout);
    }
    else
    {
        printf("Vehicle Engine Status : OFF \n");
        fflush(stdout);
    }

    printf("Vehicle Speed : %d Km/Hr\n", speedControl(ptr->color));

    if (ptr->AC_State)
    {
        printf("AC status : ON\n");
        fflush(stdout);
    }
    else
    {
        printf("AC status : OFF\n");
        fflush(stdout);
    }

    printf("Vehicle Room Temp : %0.2f C \n", (float)ptr->roomTemp);
#if WITH_ENGINE_TEMP_CONTROLLER
    if (ptr->EC_State)
    {
        printf("EC status : ON\n");
        fflush(stdout);
    }
    else
    {
        printf("EC status : OFF\n");
        fflush(stdout);
    }

    printf("Vehicle Engine Temp : %0.2f C \n\n", (float)ptr->engineTemp);
#endif
}

/**
 * @brief Performs actions based on the system state.
 *
 * Actions include displaying messages about the vehicle engine status and navigating to the appropriate menu.
 */
void stateAction()
{
    if (ptr->vehicleState == OFF)
    {
        printf("Vehicle engine is OFF\n\n");
        fflush(stdout);
        mainMenu();
    }
    else if (ptr->vehicleState == RUNNING)
    {
        printf("Vehicle engine is RUNNING\n\n");
        fflush(stdout);
        sensorsMenu();
    }
}

/**
 * @brief Determine the speed of the vehicle based on the traffic light color.
 * @param color
 * @return vehicleSpeed
 */
char speedControl(Traffic color)
{
    unsigned char vehicleSpeed = 0;

    if (color == GREEN)
    {
        vehicleSpeed = 100;
    }
    else if (color == ORANGE)
    {
        vehicleSpeed = 30;
    }
    else if (color == RED)
    {
        vehicleSpeed = 0;
    }

    return vehicleSpeed;
}

/**
 * @brief Sets the traffic light color.
 *
 * User input is taken to set the traffic light color.
 *
 * @return Traffic light color.
 */
Traffic setTraffic()
{
    Traffic color;

    printf("Set Traffic Light\n\n");
    fflush(stdout);

    while (1)
    {
        printf("Enter color: ");
        fflush(stdout);
        scanf(" %c", &ptr->userInput);

        if (ptr->userInput == 'g' || ptr->userInput == 'G' ||
            ptr->userInput == 'o' || ptr->userInput == 'O' ||
            ptr->userInput == 'R' || ptr->userInput == 'r')
        {
            break;
        }
        else
        {
            printf("Invalid option. Please enter a valid option.\n");
            fflush(stdout);
        }
    }

    switch (ptr->userInput)
    {
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

/**
 * @brief Sets the room temperature and returns the state of the AC system.
 *
 * User input is taken to set the room temperature, and the AC system state is determined accordingly.
 *
 * @return AC system state.
 */
State setTemp_AC()
{
    printf("Enter Vehicle Room Temperature: ");
    fflush(stdout);
    scanf(" %d", &ptr->roomTemp);
    State AC_State = OFF;

    if (ptr->roomTemp < 10 || ptr->roomTemp > 30)
    {
        AC_State = RUNNING;
        ptr->roomTemp = 20;
    }
    else
    {
        AC_State = OFF;
    }

    return AC_State;
}

#if WITH_ENGINE_TEMP_CONTROLLER

/**
 * @brief Sets the engine temperature and returns the state of the engine temperature controller.
 *
 * User input is taken to set the engine temperature, and the engine temperature controller state is determined accordingly.
 *
 * @return Engine temperature controller state.
 */
State setTemp_EC()
{
    printf("Enter Vehicle Engine Temperature: ");
    fflush(stdout);
    scanf(" %d", &ptr->engineTemp);
    State EC_State = OFF;

    if (ptr->engineTemp < 100 || ptr->engineTemp > 150)
    {
        EC_State = RUNNING;
        ptr->engineTemp = 125;
    }
    else
    {
        EC_State = OFF;
    }

    return EC_State;
}

#endif
