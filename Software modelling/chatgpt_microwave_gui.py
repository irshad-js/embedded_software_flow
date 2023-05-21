import sys
import time
import threading
import traceback
from tkinter import Tk, Frame, Button, Label, LEFT, Canvas, FALSE
from tkinter import MouseWheelEvent, KeyEvent

BUTTON_STYLE = {
    "borderwidth": 2,
    "font": ("Helvetica", 10, "bold"),
    "fg": "white",
    "bg": "black",
    "activebackground": "green",
}


class State(object):
    """Base class for State pattern."""

    def __init__(self, microwave):
        self.microwave = microwave

    def start(self):
        pass

    def stop(self):
        pass


class StoppedState(State):
    def start(self):
        if self.microwave.timer.total != "0000":
            # print "Cooking . . ."
            self.microwave.door.itemconfig(self.microwave.door.window, fill="yellow")
            self.microwave.set_state(CookingState)
            # No Lock required as 'timer.total' changes happen asynchronously
            self.microwave.timer_thread = threading.Thread(
                target=self.microwave.timer.countdown
            )
            self.microwave.timer_thread.start()

    def stop(self):
        """Clear timer if stopped and stop is pressed."""
        self.microwave.timer.total = "0000"
        self.microwave.timer.refresh()


class CookingState(State):
    def stop(self):
        self.microwave.set_state(StoppedState)
        # print "Stopped"
        self.microwave.door.itemconfig(self.microwave.door.window, fill="grey")


class FrameComponent(Frame):
    def __init__(self, *args, **kwargs):
        Frame.__init__(self, *args, **kwargs)
        self.create()
        self.pack()

    def create(self):
        pass


class Microwave(FrameComponent):
    def __init__(self, master):
        FrameComponent.__init__(self, master)
        self.state = StoppedState(self)
        self.timer_thread = None

    def create(self):
        self.door = Door(self)
        self.timer = Timer(self)
        self.knob = RotaryKnob(self)
        self.controls = KnobControls(self)

    def set_state(self, state_class):
        self.state = state_class(self)

    def shutdown(self):
        """Stop microwave, and wait for last active thread to terminate"""
        self.controls.stop_oven()
        if self.timer_thread and self.timer_thread.is_alive():
            self.timer_thread.join()
        self.master.destroy()


class Timer(FrameComponent):
    def __init__(self, master):
        self.total = "0000"
        FrameComponent.__init__(self, master)

    def create(self):
        self.timer_label = Label(
            self,
            width=8,
            borderwidth=10,
            font=("Helvetica", 15, "bold"),
            bg="black",
            fg="green",
        )
        self.refresh()
        self.timer_label.pack
