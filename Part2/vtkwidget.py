import vtk
from PyQt5 import QtGui
from PyQt5 import QtWidgets
from vtk.qt.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
from PyQt5.QtWidgets import QLabel

class vtkWidget(QtWidgets.QWidget):

    def __init__(self, parent = None):
        QtWidgets.QWidget.__init__(self, parent)
        self.vbl = QtWidgets.QVBoxLayout()

        self.vtkWidget = QVTKRenderWindowInteractor(self)
        self.vbl.addWidget(self.vtkWidget)
        
        self.ren = vtk.vtkRenderer()
        self.vtkWidget.GetRenderWindow().AddRenderer(self.ren)
        self.iren = self.vtkWidget.GetRenderWindow().GetInteractor()
        self.renWin = self.vtkWidget.GetRenderWindow()
        
        self.vtkWidget.show()
        self.iren.Initialize()
        self.setLayout(self.vbl)