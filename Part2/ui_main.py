from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QDockWidget, QGroupBox, QHBoxLayout, QLabel, QPushButton, QSlider, QVBoxLayout, QWidget, QSizePolicy, QSpacerItem , QComboBox)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import QSize , QCoreApplication , QMetaObject , QRect 
from vtkwidget import vtkWidget

class Ui_MainWindow(QtWidgets.QMainWindow):
    def setupUi(self, MainWindow):
        MainWindow.resize(960, 789)
        self.centralwidget = vtkWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)
        self.centralwidget.setMaximumSize(QSize(684, 789))

        self.dockWidget_4 = QDockWidget(MainWindow)
        self.dockWidget_4.setObjectName(u"dockWidget_4")
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        self.dockWidget_4.setSizePolicy(sizePolicy)
        self.dockWidget_4.setMinimumSize(QSize(320, 789))
        self.dockWidget_4.setAutoFillBackground(False)
        self.dockWidget_4.setAllowedAreas(Qt.LeftDockWidgetArea|Qt.RightDockWidgetArea)
        self.dockWidgetContents_4 = QWidget()
        self.dockWidgetContents_4.setObjectName(u"dockWidgetContents_4")

        self.verticalLayoutWidget = QWidget(self.dockWidgetContents_4)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(0, 0, 320, 789))
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(1, 0, 0, 0)
        self.groupBox_3 = QtWidgets.QGroupBox(self.verticalLayoutWidget)
        self.groupBox_3.setObjectName(u"groupBox_3")
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHeightForWidth(self.groupBox_3.sizePolicy().hasHeightForWidth())
        self.groupBox_3.setSizePolicy(sizePolicy)
        self.groupBox_3.setMinimumSize(QSize(316, 60))
        self.groupBox_3.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)
        self.groupBox_3.setFlat(False)
        self.groupBox_3.setCheckable(False)
        self.horizontalLayoutWidget = QWidget(self.groupBox_3)
        self.horizontalLayoutWidget.setObjectName(u"horizontalLayoutWidget")
        self.horizontalLayoutWidget.setGeometry(QRect(1, 19, 316, 41))
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.label = QtWidgets.QLabel(self.horizontalLayoutWidget)
        self.label.setObjectName(u"label")
        self.label.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout.addWidget(self.label)

        self.pushButton = QPushButton(self.horizontalLayoutWidget)
        self.pushButton.setObjectName(u"pushButton")
        sizePolicy1 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.pushButton)


        self.verticalLayout.addWidget(self.groupBox_3)

        self.verticalSpacer_7 = QSpacerItem(20, 10, QSizePolicy.Minimum, QSizePolicy.Fixed)

        self.verticalLayout.addItem(self.verticalSpacer_7)

        self.groupBox_4 = QGroupBox(self.verticalLayoutWidget)
        self.groupBox_4.setObjectName(u"groupBox_4")
        sizePolicy.setHeightForWidth(self.groupBox_4.sizePolicy().hasHeightForWidth())
        self.groupBox_4.setSizePolicy(sizePolicy)
        self.groupBox_4.setMinimumSize(QSize(316, 60))
        self.groupBox_4.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)
        self.groupBox_4.setFlat(False)
        self.groupBox_4.setCheckable(False)
        self.horizontalLayoutWidget_2 = QWidget(self.groupBox_4)
        self.horizontalLayoutWidget_2.setObjectName(u"horizontalLayoutWidget_2")
        self.horizontalLayoutWidget_2.setGeometry(QRect(1, 19, 316, 41))
        self.horizontalLayout_2 = QHBoxLayout(self.horizontalLayoutWidget_2)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0,0,0,0)
        self.comboBox = QComboBox(self.horizontalLayoutWidget_2)
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.setObjectName(u"comboBox")

        self.horizontalLayout_2.addWidget(self.comboBox)
        self.comboBox.setEnabled(True)


        self.verticalLayout.addWidget(self.groupBox_4)

        self.verticalSpacer_6 = QSpacerItem(20, 20, QSizePolicy.Minimum, QSizePolicy.Fixed)

        self.verticalLayout.addItem(self.verticalSpacer_6)

        self.groupBox_2 = QGroupBox(self.verticalLayoutWidget)
        self.groupBox_2.setObjectName(u"groupBox_2")
        sizePolicy2 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.MinimumExpanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy2)
        self.groupBox_2.setMinimumSize(QSize(315, 200))
        self.verticalLayoutWidget_2 = QWidget(self.groupBox_2)
        self.verticalLayoutWidget_2.setObjectName(u"verticalLayoutWidget_2")
        self.verticalLayoutWidget_2.setGeometry(QRect(1, 50, 316, 51))
        self.verticalLayout_2 = QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.label_2 = QLabel(self.verticalLayoutWidget_2)
        self.label_2.setObjectName(u"label_2")
        sizePolicy3 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy3)
        self.label_2.setMinimumSize(QSize(0, 16))

        self.verticalLayout_2.addWidget(self.label_2)
        
        self.iso_val = QLabel(self.verticalLayoutWidget_2)
        self.iso_val.setMinimumSize(QSize(0, 16))
        self.iso_val.setObjectName(u"iso_val")
        self.iso_val.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.verticalLayout_2.addWidget(self.iso_val)


        self.horizontalSlider = QSlider(self.verticalLayoutWidget_2)
        self.horizontalSlider.setObjectName(u"horizontalSlider")
        self.horizontalSlider.setMaximum(1200)
        self.horizontalSlider.setProperty("value", 500)
        self.iso_val.setText(str(self.horizontalSlider.value()))
        self.horizontalSlider.setSingleStep(10)
        self.horizontalSlider.setPageStep(20)
        self.horizontalSlider.setOrientation(Qt.Horizontal)
        self.verticalLayout_2.addWidget(self.horizontalSlider)
        self.horizontalSlider.setEnabled(True)


        self.verticalLayoutWidget_4 = QWidget(self.groupBox_2)
        self.verticalLayoutWidget_4.setObjectName(u"verticalLayoutWidget_4")
        self.verticalLayoutWidget_4.setGeometry(QRect(1, 130, 316, 51))
        self.verticalLayout_6 = QVBoxLayout(self.verticalLayoutWidget_4)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.label_6 = QLabel(self.verticalLayoutWidget_4)
        self.label_6.setObjectName(u"label_6")
        sizePolicy3.setHeightForWidth(self.label_6.sizePolicy().hasHeightForWidth())
        self.label_6.setSizePolicy(sizePolicy3)
        self.label_6.setMinimumSize(QSize(0, 16))

        self.verticalLayout_6.addWidget(self.label_6)

        self.bone_val = QLabel(self.verticalLayoutWidget_2)
        self.bone_val.setMinimumSize(QSize(0, 16))
        self.bone_val.setObjectName(u"bone_val")
        self.bone_val.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.verticalLayout_6.addWidget(self.bone_val)


        self.horizontalSlider_5 = QSlider(self.verticalLayoutWidget_4)
        self.horizontalSlider_5.setObjectName(u"horizontalSlider_5")
        self.horizontalSlider_5.setMaximum(100)
        self.horizontalSlider_5.setProperty("value", 85)
        self.bone_val.setText(str(self.horizontalSlider_5.value())+"%")
        self.horizontalSlider_5.setEnabled(False)
        self.horizontalSlider_5.setOrientation(Qt.Horizontal)

        self.verticalLayout_6.addWidget(self.horizontalSlider_5)

        self.verticalLayoutWidget_3 = QWidget(self.groupBox_2)
        self.verticalLayoutWidget_3.setObjectName(u"verticalLayoutWidget_3")
        self.verticalLayoutWidget_3.setGeometry(QRect(1, 230, 316, 150))
        

        self.verticalLayout_5 = QVBoxLayout(self.verticalLayoutWidget_3)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        
        self.label_5 = QLabel(self.verticalLayoutWidget_3)
        self.label_5.setObjectName(u"label_5")
        sizePolicy3.setHeightForWidth(self.label_5.sizePolicy().hasHeightForWidth())
        self.label_5.setSizePolicy(sizePolicy3)
        self.label_5.setMinimumSize(QSize(0, 16))

        self.verticalLayout_5.addWidget(self.label_5)
        self.skin_val = QLabel(self.verticalLayoutWidget_2)
        self.skin_val.setMinimumSize(QSize(0, 16))

        self.skin_val.setObjectName(u"skin_val")
        self.skin_val.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.verticalLayout_5.addWidget(self.skin_val)

        self.horizontalSlider_4 = QSlider(self.verticalLayoutWidget_3)
        self.horizontalSlider_4.setObjectName(u"horizontalSlider_4")
        self.horizontalSlider_4.setMaximum(100)
        self.horizontalSlider_4.setProperty("value", 0)
        self.skin_val.setText(str(self.horizontalSlider_4.value())+"%")
        self.horizontalSlider_4.setEnabled(False)
        self.horizontalSlider_4.setOrientation(Qt.Horizontal)

        self.verticalLayout_5.addWidget(self.horizontalSlider_4)

     

        self.pushButton_2 = QPushButton(self.verticalLayoutWidget_3)
        self.pushButton_2.setObjectName(u"pushButton_2")

        self.verticalLayout_5.addWidget(self.pushButton_2)

        self.verticalSpacer_3 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_5.addItem(self.verticalSpacer_3)

        self.horizontalLayoutWidget_3 = QWidget(self.groupBox_2)
        self.horizontalLayoutWidget_3.setObjectName(u"horizontalLayoutWidget_3")
        self.horizontalLayoutWidget_3.setGeometry(QRect(1, 100, 316, 31))
        self.horizontalLayout_3 = QHBoxLayout(self.horizontalLayoutWidget_3)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.horizontalLayout_3.addItem(self.verticalSpacer)

        self.horizontalLayoutWidget_4 = QWidget(self.groupBox_2)
        self.horizontalLayoutWidget_4.setObjectName(u"horizontalLayoutWidget_4")
        self.horizontalLayoutWidget_4.setGeometry(QRect(1, 200, 316, 31))
        self.horizontalLayout_4 = QHBoxLayout(self.horizontalLayoutWidget_4)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.horizontalLayout_4.addItem(self.verticalSpacer_2)


        self.verticalLayout.addWidget(self.groupBox_2)

        self.dockWidget_4.setWidget(self.dockWidgetContents_4)
        MainWindow.addDockWidget(Qt.LeftDockWidgetArea, self.dockWidget_4)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("MainWindow", u"Folder", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"None", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"Open DICOM", None))
        self.pushButton_2.setText(QCoreApplication.translate("MainWindow", u"Skin Color", None))
        self.groupBox_4.setTitle(QCoreApplication.translate("MainWindow", u"Rendering", None))
        self.comboBox.setItemText(0, QCoreApplication.translate("MainWindow", u"Surface rendering", None))
        self.comboBox.setItemText(1, QCoreApplication.translate("MainWindow", u"Ray casting rendering", None))

        self.groupBox_2.setTitle(QCoreApplication.translate("MainWindow", u"Control", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"Iso ", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"Bone Opacity", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"Skin Opacity", None))
    # retranslateUi

