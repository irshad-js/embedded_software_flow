"""
A rapid prototype of the microwave model
intended for simulation and state model verification
"""
from enum import Enum
import time
import sys


class Door_position(Enum):
    Open = 0
    Closed = 1


class State(Enum):
    CHECK_MW_DOOR_CLOSED = 0
    DISPLAY_MW_TIMER = 1
    SET_MW_TIMER = 2
    ACTIVATE_MAGNETRON = 3
    DISPLAY_WATTAGE_STATE = 4
    SET_WATTAGE_STATE = 5
    PAUSED_STATE = 6
    COOKING_COMPLETE = 7


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


def update_timer(state_object, signal_object):
    if state_object.current_state == State.SET_MW_TIMER:
        if signal_object == Signals.UP_BUTTON or signal_object == Signals.ROTARY_UP:
            if state_object.timer_initial_transition_placeholder != 0:
                state_object.timer_value += 2 * 60
                state_object.timer_initial_transition_placeholder = 0
            else:
                state_object.timer_value += 1 * 60
        if (
            signal_object == Signals.DOWN_BUTTON or signal_object == Signals.ROTARY_DOWN
        ) and state_object.timer_value > 1:
            state_object.timer_value -= 1 * 60


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
            signal_object == Signals.UP_BUTTON
            or signal_object == Signals.DOWN_BUTTON
            or signal_object == Signals.ROTARY_DOWN
            or signal_object == Signals.ROTARY_UP
        ):
            print("Transitioning to setting microwave timer now")
            state_object.current_state = State.SET_MW_TIMER
            state_object.timer_initial_transition_placeholder = signal_object
    elif state_object.current_state == State.SET_MW_TIMER:
        print("Current state - Modifying Microwave timer")
        if (
            signal_object == Signals.UP_BUTTON
            or signal_object == Signals.DOWN_BUTTON
            or signal_object == Signals.ROTARY_DOWN
            or signal_object == Signals.ROTARY_UP
        ):
            print("Handling user inputs now")
            update_timer(state_object, signal_object)
        if signal_object == Signals.START_BUTTON:
            print("Transitioning to check door state now")
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED
    elif state_object.current_state == State.DISPLAY_WATTAGE_STATE:
        print("Current state - Displaying Microwave wattage")
        if (
            signal_object == Signals.UP_BUTTON
            or signal_object == Signals.DOWN_BUTTON
            or signal_object == Signals.ROTARY_DOWN
            or signal_object == Signals.ROTARY_UP
        ):
            print("Transitioning to setting microwave wattage now")
            state_object.current_state = State.SET_WATTAGE_STATE
        if signal_object == Signals.START_BUTTON:
            print("Selecting default microwave wattage")
            state_object.current_state = State.DISPLAY_MW_TIMER

    elif state_object.current_state == State.SET_WATTAGE_STATE:
        print("Current state - Modifying Microwave wattage")
        if (
            signal_object == Signals.UP_BUTTON
            or signal_object == Signals.DOWN_BUTTON
            or signal_object == Signals.ROTARY_DOWN
            or signal_object == Signals.ROTARY_UP
        ):
            print("Handling user inputs now")
        if signal_object == Signals.START_BUTTON:
            print("Current state is going to transition to timer setting")
            state_object.current_state = State.DISPLAY_MW_TIMER
    elif state_object.current_state == State.CHECK_MW_DOOR_CLOSED:
        print("Current state - Checking Microwave door")
        # A guard condition here checks the status of door
        if signal_object == Signals.TICK:
            state_object.timer_value -= 1
            if state_object.door_state == Door_position.Closed:
                print("Microwave door is closed, activating magnetron in next state")
                state_object.current_state = State.ACTIVATE_MAGNETRON
        if signal_object == Signals.DOOR_OPENED:
            if state_object.door_state == Door_position.Closed:
                print("Microwave door is closed, activating magnetron in next state")
                state_object.current_state = State.ACTIVATE_MAGNETRON
            else:
                print("Microwave door is still open")

    elif state_object.current_state == State.ACTIVATE_MAGNETRON:
        print("Current state - Microwave magnetron in operation")
        if signal_object == Signals.TICK:
            state_object.timer_value -= 1
        if signal_object == Signals.START_BUTTON:
            print("Cooking with microwave interrupted - transition to pause state")
            state_object.current_state = State.PAUSED_STATE
        if signal_object == Signals.DOOR_OPENED:
            print("Door opened mid way to cooking - transition to door check state")
            # stop cooking and change state
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED
        if state_object.timer_value == 0:
            print("Cooking complete")
            state_object.current_state = State.COOKING_COMPLETE

    elif state_object.current_state == State.PAUSED_STATE:
        print("System is put into pause state")
        if signal_object == Signals.START_BUTTON:
            print("Resume command acknowledged")
            state_object.current_state = State.CHECK_MW_DOOR_CLOSED

    elif state_object.current_state == State.COOKING_COMPLETE:
        print("System is put to Cooking complete state")
        if signal_object == Signals.TICK:
            print("User is reminded by constant beeps")


def execute_state_functionalities(state_obj, signals):
    time.sleep(0.25)
    statemachine_handler(state_obj, signals)


def main():
    """Start of the model"""
    main_object = MainStateObject()
    list_of_arguments_passed_in = sys.argv
    if list_of_arguments_passed_in[1] == "NON_GUI_SIM":
        recorded_signals = [
            Signals.START_BUTTON,
            Signals.UP_BUTTON,
            Signals.UP_BUTTON,
            Signals.UP_BUTTON,
            Signals.START_BUTTON,
            Signals.TICK,
        ]
        for signals in recorded_signals:
            execute_state_functionalities(main_object, signals)
        for _ in range(0, 200):
            execute_state_functionalities(main_object, Signals.TICK)
    return 0


if __name__ == "__main__":
    main()
