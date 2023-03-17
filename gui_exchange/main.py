# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import sys

from PyQt5.QtWidgets import QApplication, QMainWindow

from GUI import Ui_MainWindow


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.
from ctypes import *

# Press the green button in the gutter to run the script.
if __name__ == "__main__":

    dll = cdll.LoadLibrary("./checkCommand")
    #print("add:", dll.add(1, 2))

    app = QApplication(sys.argv)
    f = Ui_MainWindow()
    MainWindow = QMainWindow()
    f.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())



# See PyCharm help at https://www.jetbrains.com/help/pycharm/
