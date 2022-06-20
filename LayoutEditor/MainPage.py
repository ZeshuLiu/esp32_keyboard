# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainPage.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_LayoutEditor(object):
    def setupUi(self, LayoutEditor):
        LayoutEditor.setObjectName("LayoutEditor")
        LayoutEditor.setWindowModality(QtCore.Qt.NonModal)
        LayoutEditor.resize(400, 300)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(LayoutEditor.sizePolicy().hasHeightForWidth())
        LayoutEditor.setSizePolicy(sizePolicy)
        self.centralwidget = QtWidgets.QWidget(LayoutEditor)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.horizontalLayoutWidget.setGeometry(QtCore.QRect(0, 170, 401, 80))
        self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.horizontalLayoutWidget)
        self.label.setMaximumSize(QtCore.QSize(90, 16777215))
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.comboBox = QtWidgets.QComboBox(self.horizontalLayoutWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.comboBox.sizePolicy().hasHeightForWidth())
        self.comboBox.setSizePolicy(sizePolicy)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.horizontalLayout.addWidget(self.comboBox)
        self.pushButton = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.pushButton.setMaximumSize(QtCore.QSize(100, 16777215))
        self.pushButton.setObjectName("pushButton")
        self.horizontalLayout.addWidget(self.pushButton)
        LayoutEditor.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(LayoutEditor)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 400, 23))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        LayoutEditor.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(LayoutEditor)
        self.statusbar.setObjectName("statusbar")
        LayoutEditor.setStatusBar(self.statusbar)
        self.actionOpen = QtWidgets.QAction(LayoutEditor)
        self.actionOpen.setObjectName("actionOpen")
        self.actionClose = QtWidgets.QAction(LayoutEditor)
        self.actionClose.setObjectName("actionClose")
        self.actionSave = QtWidgets.QAction(LayoutEditor)
        self.actionSave.setObjectName("actionSave")
        self.menu.addAction(self.actionSave)
        self.menu.addAction(self.actionOpen)
        self.menu.addAction(self.actionClose)
        self.menu.addSeparator()
        self.menubar.addAction(self.menu.menuAction())

        self.retranslateUi(LayoutEditor)
        QtCore.QMetaObject.connectSlotsByName(LayoutEditor)

    def retranslateUi(self, LayoutEditor):
        _translate = QtCore.QCoreApplication.translate
        LayoutEditor.setWindowTitle(_translate("LayoutEditor", "LayoutEditor"))
        self.label.setText(_translate("LayoutEditor", "Select Model:"))
        self.comboBox.setItemText(0, _translate("LayoutEditor", "MasterYoda_rev1.0"))
        self.comboBox.setItemText(1, _translate("LayoutEditor", "Joker_60_rev1.0"))
        self.pushButton.setText(_translate("LayoutEditor", "Start"))
        self.menu.setTitle(_translate("LayoutEditor", "菜单"))
        self.actionOpen.setText(_translate("LayoutEditor", "Open"))
        self.actionClose.setText(_translate("LayoutEditor", "Close"))
        self.actionSave.setText(_translate("LayoutEditor", "Save"))