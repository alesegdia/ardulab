#!/usr/bin/python

import os
import Tkinter as tk
from Tkinter import *
import thread
import serial
import argparse

class UI(tk.Frame):
    def __init__(self, ser, Master=None, **kwargs):
        self.ser = ser
        apply(tk.Frame.__init__, (self, Master), kwargs)
        self.mainFrame = tk.Frame(self)
        self.mainFrame.pack(side='top', expand='yes', fill='both')
        self.topFrame = tk.Frame(self.mainFrame)
        self.topFrame.pack(side='top', fill='x')
        self.botFrame = tk.Frame(self.mainFrame)
        self.botFrame.pack(side='bottom', expand='yes', fill='both')
        self.cmdEntry = tk.Entry(self.topFrame)
        self.cmdEntry.pack(side=LEFT, expand='yes', fill='both')
        self.sendButton = tk.Button(self.topFrame, text='send', command=self.sendCmd)
        self.sendButton.pack(side=RIGHT)
        self.logTextBox = tk.Text(self.botFrame)
        self.logTextBox.pack(side=TOP, expand=1, fill=BOTH)

    def sendCmd(self):
        ser.write(self.cmdEntry.get())

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--tty', type=str, help='tty device')
    args = parser.parse_args()
    ser = serial.Serial(args.tty, 9600)
    Root = tk.Tk()
    app = UI(ser, Root)
    app.pack(expand='yes', fill='both')
    def dat_thread():
        i=0
        while True:
            i=i+1
            msg = str(i) + ") " + ser.readline()
            print(msg)
            app.logTextBox.insert(END, msg)

    thread.start_new(dat_thread,())
    Root.geometry('260x150+10+10')
    Root.title("theapp")
    Root.mainloop()
