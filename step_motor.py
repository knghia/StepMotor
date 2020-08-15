
import sys
from serial import Serial
from PyQt5 import QtGui
from PyQt5 import QtCore
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *


class Window(QWidget):

    def __init__(self):
        super().__init__()
        self.InitGui()
        self.InitPort()
        self.InitControlStep()

    def InitPort(self):
        self.uart = Serial(port='COM5',baudrate=9600)
        if(self.uart.isOpen()):
            return
        self.uart.open()

    def InitGui(self):
        self.title = "Control step motor"
        self.top = 200
        self.left = 500
        self.width = 400
        self.height = 300
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)


    def InitControlStep(self):

        self.control_step = QFrame(self)

        self.slider = QSlider(self.control_step)
        self.slider.setOrientation(Qt.Horizontal)
        self.slider.setTickPosition(QSlider.TicksBelow)

        self.slider.setMinimum(0)
        self.slider.setMaximum(360)
        self.slider.valueChanged[int].connect(self.changedValue)
        self.slider.setGeometry(20,10,360,50)

        self.entry_value = QLineEdit(self.control_step,text='0')
        self.entry_value.setAlignment(QtCore.Qt.AlignCenter)
        self.entry_value.move(20, 60)
        self.entry_value.resize(100, 50)
        self.entry_value.setFont(QtGui.QFont("Consola", 20))
        self.entry_value.returnPressed.connect(self.load_value)
        self.entry_value.setValidator(QIntValidator())

        self.send_value_angle = QPushButton(self.control_step,text='LOAD')
        self.send_value_angle.clicked.connect(self.send_angle)
        self.send_value_angle.move(200,60)

        #self.send_value_button = QPushButton(self.control_step,text='SEND')

    def send_angle(self):
        value = int(self.entry_value.text())
        self.uart.write((':'+str(value)).encode())

    def load_value(self):
        value = int(self.entry_value.text())
        self.slider.setValue(value)


    def changedValue(self,value):
        self.entry_value.setText(str(value))


def main():
    App = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(App.exec())

if __name__ == "__main__":
    main()