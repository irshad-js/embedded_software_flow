"""
A rapid prototype of the microwave model
intended for simulation and state model verification
"""
from enum import Enum
import time
import sys
import json


class Door_position(Enum):
    Open = 0
    Closed = 1


class Microwave_wattage(Enum):
    _600_watts = 1
    _750_watts = 2
    _900_watts = 3


class Grill_temperature(Enum):
    _180_degree_celsius = 1
    _200_degree_celsius = 2
    _205_degree_celsius = 3
    _210_degree_celsius = 4


class State(Enum):
    CHECK_MW_DOOR_CLOSED = 0
    DISPLAY_MW_TIMER = 1
    SET_MW_TIMER = 2
    ACTIVATE_MAGNETRON = 3
    DISPLAY_WATTAGE_STATE = 4
    SET_WATTAGE_STATE = 5
    PAUSED_MW_STATE = 6
    COOKING_COMPLETE = 7
    CHECK_GL_DOOR_CLOSED = 8
    DISPLAY_GL_TIMER = 9
    SET_GL_TIMER = 10
    ACTIVATE_HEATING_ELEMENT = 11
    DISPLAY_TEMPERATURE = 12
    SET_TEMPERATURE = 13
    PAUSED_GL_STATE = 14


class Signals(Enum):
    START_BUTTON = 0
    MENU_BUTTON = 1
    UP_BUTTON = 2
    DOWN_BUTTON = 3
    ROTARY_UP = 4
    ROTARY_DOWN = 5
    DOOR_OPENED = 6
    DOOR_CLOSED = 7
    READY_TO_START = 8
    TICK = 9


class MainStateObject:
    """Main state object to hold elements, states in memory"""

    def __init__(self):
        self.current_state = State.DISPLAY_WATTAGE_STATE
        self.door_state = Door_position.Closed
        self.timer_value = 0
        self.timer_initial_transition_placeholder = 0
        self.microwave_wattage = Microwave_wattage._600_watts
        self.grill_temperature = Grill_temperature._200_degree_celsius


def update_timer(state_object, signal_object):
    if state_object.current_state == State.SET_MW_TIMER or State.SET_GL_TIMER:
        if signal_object == "UP_BUTTON" or signal_object == "ROTARY_UP":
            if state_object.timer_initial_transition_placeholder != 0:
                state_object.timer_value += 2 * 60
                state_object.timer_initial_transition_placeholder = 0
            else:
                state_object.timer_value += 1 * 60
        if (
            signal_object == "DOWN_BUTTON" or signal_object == "ROTARTY_DOWN"
        ) and state_object.timer_value > 1:
            state_object.timer_value -= 1 * 60


def update_wattage_or_temperature(state_object, signal_object):
    if state_object.current_state == State.SET_WATTAGE_STATE:
        if signal_object == "UP_BUTTON" or signal_object == "ROTARY_UP":
            state_object.microwave_wattage = Microwave_wattage(
                (state_object.microwave_wattage.value + 1) % 3
            ).name
        if (
            signal_object == "DOWN_BUTTON" or signal_object == "ROTARTY_DOWN"
        ) and state_object.microwave_wattage.value > 2:
            state_object.microwave_wattage = Microwave_wattage(
                state_object.microwave_wattage.value - 1
            ).name

    if state_object.current_state == State.SET_TEMPERATURE:
        if signal_object == "UP_BUTTON" or signal_object == "ROTARY_UP":
            state_object.grill_temperature = Grill_temperature(
                (state_object.grill_temperature.value + 1) % 4
            ).name
        if (
            signal_object == "DOWN_BUTTON" or signal_object == "ROTARTY_DOWN"
        ) and state_object.grill_temperature.value > 2:
            state_object.grill_temperature.value = Grill_temperature(
                (state_object.grill_temperature - 1)
            ).name


def statemachine_handler(state_object, signal_object):
    """This is the main handler function that
    takes care of the state transition and the
    logic that has to be handled in the different states


    Args:
        state_object (MainObject type): An object created using
        the MainObject type to store state information and other
        information to be retained during operation
        signal_object (Signal Enum): The different combinations
        of the signal available to be processed
    """
    if state_object.current_state == State.DISPLAY_MW_TIMER:
        print("Current state - Displaying Microwave timer")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Transitioning to setting microwave timer now")
            state_object.current_state = State.SET_MW_TIMER
            state_object.timer_initial_transition_placeholder = signal_object
    elif state_object.current_state == State.SET_MW_TIMER:
        print("Current state - Modifying Microwave timer")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Handling user inputs now")
            update_timer(state_object, signal_object)
        if signal_object == "START_BUTTON":
            print("Transitioning to check door state now")
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED
    elif state_object.current_state == State.DISPLAY_WATTAGE_STATE:
        print("Current state - Displaying Microwave wattage")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Transitioning to setting microwave wattage now")
            state_object.current_state = State.SET_WATTAGE_STATE
        if signal_object == "START_BUTTON":
            print("Selecting default microwave wattage")
            state_object.current_state = State.DISPLAY_MW_TIMER
        if signal_object == "MENU_BUTTON":
            print("Selecting Grill operation")
            state_object.current_state = State.DISPLAY_TEMPERATURE

    elif state_object.current_state == State.SET_WATTAGE_STATE:
        print("Current state - Modifying Microwave wattage")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Handling user inputs now")
            update_wattage_or_temperature(state_object, signal_object)
            print("Microwave wattage at - {1}", state_object.microwave_wattage)
        if signal_object == "START_BUTTON":
            print("Current state is going to transition to timer setting")
            state_object.current_state = State.DISPLAY_MW_TIMER
    elif state_object.current_state == State.CHECK_MW_DOOR_CLOSED:
        print("Current state - Checking Microwave door")
        # A guard condition here checks the status of door
        if signal_object == Signals.TICK:
            if state_object.door_state == Door_position.Closed:
                print("Microwave door is closed, activating magnetron in next state")
                state_object.current_state = State.ACTIVATE_MAGNETRON
        if signal_object == "DOOR_OPENED":
            if state_object.door_state == Door_position.Closed:
                print("Microwave door is closed, activating magnetron in next state")
                state_object.current_state = State.ACTIVATE_MAGNETRON
            else:
                print("Microwave door is still open")

    elif state_object.current_state == State.ACTIVATE_MAGNETRON:
        print("Current state - Microwave magnetron in operation")
        if signal_object == Signals.TICK:
            state_object.timer_value -= 1
        if signal_object == "START_BUTTON":
            print("Cooking with microwave interrupted - transition to pause state")
            state_object.current_state = State.PAUSED_STATE
        if signal_object == "DOOR_OPENED":
            print("Door opened mid way to cooking - transition to door check state")
            # stop cooking and change state
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED
        if state_object.timer_value == 0:
            print("Cooking complete")
            state_object.current_state = State.COOKING_COMPLETE

    elif state_object.current_state == State.PAUSED_MW_STATE:
        print("System is put into pause state")
        if signal_object == "START_BUTTON":
            print("Resume command acknowledged")
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED

    elif state_object.current_state == State.COOKING_COMPLETE:
        print("System is put to Cooking complete state")
        if signal_object == Signals.TICK:
            print("User is reminded by constant beeps")
        if (
            signal_object == "START_BUTTON"
            or signal_object == "MENU_BUTTON"
            or signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("End state")
            # there is a bug here. even if the end state is printed to console
            # there is a chance that tick signal is serviced from next
            # tick firing
    elif state_object.current_state == State.DISPLAY_TEMPERATURE:
        print("Current state - Displaying Grill temperature")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Transitioning to setting grill temperature now")
            state_object.current_state = State.SET_TEMPERATURE
        if signal_object == "START_BUTTON":
            print("Selecting default grill temperature")
            state_object.current_state = State.DISPLAY_GL_TIMER
    elif state_object.current_state == State.SET_TEMPERATURE:
        print("Current state - Modifying Grill temperature")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Handling user inputs now")
            update_wattage_or_temperature(state_object, signal_object)
            print(
                "Grill temperature setting at position - {1}",
                state_object.grill_temperature,
            )
        if signal_object == "START_BUTTON":
            print("Current state is going to transition to timer setting")
            state_object.current_state = State.DISPLAY_GL_TIMER
    elif state_object.current_state == State.DISPLAY_GL_TIMER:
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Transitioning to setting grill timer now")
            state_object.current_state = State.SET_GL_TIMER
            state_object.timer_initial_transition_placeholder = signal_object
    elif state_object.current_state == State.SET_GL_TIMER:
        print("Current state - Modifying grill timer")
        if (
            signal_object == "UP_BUTTON"
            or signal_object == "DOWN_BUTTON"
            or signal_object == "ROTARTY_DOWN"
            or signal_object == "ROTARY_UP"
        ):
            print("Handling user inputs now")
            update_timer(state_object, signal_object)
        if signal_object == "START_BUTTON":
            print("Transitioning to check door state now")
            state_object.current_state = State.CHECK_GL_DOOR_CLOSED
    elif state_object.current_state == State.CHECK_GL_DOOR_CLOSED:
        print("Current state - Checking Grill door")
        # A guard condition here checks the status of door
        if signal_object == Signals.TICK:
            if state_object.door_state == Door_position.Closed:
                print("Grill door is closed, activating heating element in next state")
                state_object.current_state = State.ACTIVATE_HEATING_ELEMENT
        if signal_object == "DOOR_OPENED":
            if state_object.door_state == Door_position.Closed:
                print("Grill door is closed, activating heating element in next state")
                state_object.current_state = State.ACTIVATE_HEATING_ELEMENT
            else:
                print("Grill door is still open")
    elif state_object.current_state == State.ACTIVATE_HEATING_ELEMENT:
        print("Current state - Grill in operation")
        if signal_object == Signals.TICK:
            state_object.timer_value -= 1
        if signal_object == "START_BUTTON":
            print("Cooking with grill interrupted - transition to pause state")
            state_object.current_state = State.PAUSED_STATE
        if signal_object == "DOOR_OPENED":
            print("Door opened mid way to cooking - transition to door check state")
            # stop cooking and change state
            state_object.current_state = State.CHECK_GL_DOOR_CLOSED
        if state_object.timer_value == 0:
            print("Cooking complete")
            state_object.current_state = State.COOKING_COMPLETE

    elif state_object.current_state == State.PAUSED_GL_STATE:
        print("System is put into pause state")
        if signal_object == "START_BUTTON":
            print("Resume command acknowledged")
            state_object.current_state = State.CHECK_GL_DOOR_CLOSED


def execute_state_functionalities(state_obj, signals, time_slp=0.1):
    time.sleep(time_slp)
    statemachine_handler(state_obj, signals)


def main():
    """Start of the model"""
    main_object = MainStateObject()
    list_of_arguments_passed_in = sys.argv
    json_to_parse = 0
    if len(list_of_arguments_passed_in) > 1:
        if list_of_arguments_passed_in[1] == "NON_GUI":
            with open(
                list_of_arguments_passed_in[2], "r", encoding="utf-8"
            ) as json_file:
                json_to_parse = json.load(json_file)
            array_placeholder = json_to_parse["commands"]
            for signals in array_placeholder:
                execute_state_functionalities(main_object, Signals(signals).name)
    # while True:
    for _ in range(0, 300):
        try:
            execute_state_functionalities(main_object, Signals.TICK)
        except KeyboardInterrupt:
            return 0


if __name__ == "__main__":
    main()
