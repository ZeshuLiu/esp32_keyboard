import sys
from tkinter.ttk import Combobox
from PyQt5.QtWidgets import QApplication , QMainWindow 
from MainPage import *

class Editor_Main(QMainWindow, Ui_LayoutEditor):
    def __init__(self, parent=None):
        super(Editor_Main,self).__init__(parent)
        self.setupUi(self)
        self.setupButton()
    
    def setupButton(self):
        #按钮触发
        self.pushButton.clicked.connect(self.onClicked)
    
    def onClicked(self):
        print("button Pressed")
        print("comb says:"+self.getModel())

    def getModel(self):
        return self.comboBox.currentText()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWin = Editor_Main()
#    myWin.setupButton()

    myWin.show()
    sys.exit(app.exec_())