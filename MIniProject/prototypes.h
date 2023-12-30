#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#define WITH_ENGINE_TEMP_CONTROLLER 1

// Enumerations
typedef enum {
    OFF,      ///< Component is turned off.
    RUNNING   ///< Component is running.
} State;

typedef enum {
    RED,      ///< Red traffic light.
    ORANGE,   ///< Orange traffic light.
    GREEN     ///< Green traffic light.
} Traffic;

// Structure
typedef struct {
    State vehicleState;   ///< State of the vehicle (ON/OFF).
    Traffic color;        ///< Traffic light color.
    State AC_State;        ///< State of the AC system.
    int roomTemp;         ///< Room temperature.

#if WITH_ENGINE_TEMP_CONTROLLER
    State EC_State;        ///< State of the engine temperature controller.
    int engineTemp;        ///< Engine temperature.
#endif

    char userInput;        ///< User input for menus.
    char sensorsInput;     ///< User input for sensors menu.
} SystemState;

// Function pointer type
typedef char (*funPTR)(Traffic);

// Function Declarations with Doxygen-style Comments

/**
 * @brief Display the main menu and handle user input.
 */
void mainMenu();

/**
 * @brief Display the sensors menu and handle user input for sensors.
 */
void sensorsMenu();

/**
 * @brief Display sensor values based on the system state.
 */
void sensorsVal();

/**
 * @brief Perform actions based on the system state (e.g., turn on/off the engine).
 */
void stateAction();

/**
 * @brief Determine vehicle speed based on the traffic light color.
 * @return Traffic light color.
 */
Traffic setTraffic();

/**
 * @brief Determine the speed of the vehicle based on the traffic light color.
 * @param color
 * @return vehicleSpeed
 */
char speedControl(Traffic color);

/**
 * @brief Set the room temperature and return the state of the AC system.
 * @return AC system state.
 */
State setTemp_AC();

#if WITH_ENGINE_TEMP_CONTROLLER
/**
 * @brief Set the engine temperature and return the state of the engine temperature controller.
 * @return Engine temperature controller state.
 */
State setTemp_EC();
#endif

#endif  // PROTOTYPES_H
