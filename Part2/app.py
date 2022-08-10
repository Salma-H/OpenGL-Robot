import sys
from PyQt5 import  QtWidgets
from PyQt5.QtCore import QDir
from PyQt5.QtWidgets import  QApplication
from ui_main import Ui_MainWindow
import vtk



class AppWindow(Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.data_dir=None
        self.sliders=[self.ui.horizontalSlider,self.ui.horizontalSlider_5,self.ui.horizontalSlider_4]
        self.labels=[self.ui.iso_val , self.ui.bone_val , self.ui.skin_val]
        self.rendering_type = "Surface rendering"
        self.iso = self.ui.horizontalSlider.value()
        self.s_opacity = self.ui.horizontalSlider_4.value()/100
        self.b_opacity = self.ui.horizontalSlider_5.value()/100
        self.s_color = (255.0 , 127.5 , 76.5 , 255)

        # vtk
        self.surfaceExtractor = vtk.vtkContourFilter()
        self.skinMapper = vtk.vtkGPUVolumeRayCastMapper()
        self.skinProperty = vtk.vtkVolumeProperty()

        self.ren = vtk.vtkRenderer()
        self.ui.centralwidget.vtkWidget.GetRenderWindow().AddRenderer(self.ren)
        self.iren = self.ui.centralwidget.vtkWidget.GetRenderWindow().GetInteractor()
        self.iren.SetInteractorStyle(vtk.vtkInteractorStyleTrackballCamera())
        
        ###################connections#################################
        self.ui.pushButton.clicked.connect(self.open)
        self.ui.comboBox.currentIndexChanged.connect(self.combo_update)
        self.ui.horizontalSlider.valueChanged.connect(self.iso_SLOT)
        self.ui.horizontalSlider_5.valueChanged.connect(self.update_tf)
        self.ui.horizontalSlider_4.valueChanged.connect(self.update_tf)
        self.ui.pushButton_2.clicked.connect(self.skin_color)

    
    def update_tf(self):
        self.s_opacity = self.ui.horizontalSlider_4.value()/100
        self.b_opacity = self.ui.horizontalSlider_5.value()/100
        self.transfer_fun()
        self.sliders_update()
        self.ui.centralwidget.vtkWidget.update()

    def skin_color(self):
        self.s_color = QtWidgets.QColorDialog.getColor()
        self.s_color = self.s_color.getRgb()
        self.transfer_fun()
        self.ui.centralwidget.vtkWidget.update()
  

    def iso_SLOT(self, val):
        self.surfaceExtractor.SetValue(0, val)        
        self.sliders_update()
        self.ui.centralwidget.vtkWidget.update()


    def sliders_update(self):
        self.labels[0].setText(str(self.sliders[0].value()))
        for idx,label in enumerate(self.labels[1:]):
            self.labels[idx+1].setText(str(self.sliders[idx+1].value())+"%")


    def combo_update(self):
        if self.ui.comboBox.currentIndex() == 0:
            #enable iso slider
            self.sliders[0].setEnabled(True)
            #disable ray casting transfer function sliders
            for slider in self.sliders[1:]:
                slider.setDisabled(True)
        else:
            self.sliders[0].setEnabled(False)
            for slider in self.sliders[1:]:
                slider.setEnabled(True)

        self.rendering_type = self.ui.comboBox.currentText()
        self.read()
        
    
    
    def open(self):
        self.data_dir = QtWidgets.QFileDialog.getExistingDirectory(directory = QDir.currentPath())
        #print(self.data_dir)
        if self.data_dir:
            self.ui.label.setText(self.data_dir.split("/")[-1])
            self.read()

        
    def read (self):
        if self.data_dir:
            self.reader = vtk.vtkDICOMImageReader()
            self.reader.SetDirectoryName(self.data_dir)
            #Rendering
            if self.rendering_type == "Surface rendering":
                self.surface_render()
            else:
                self.ray_casting()       
         

    def surface_render (self):
        self.ren.RemoveAllViewProps() 
        self.surfaceExtractor.SetInputConnection(self.reader.GetOutputPort())
        self.surfaceExtractor.SetValue(0, self.ui.horizontalSlider.value())
        surfaceNormals = vtk.vtkPolyDataNormals()
        surfaceNormals.SetInputConnection(self.surfaceExtractor.GetOutputPort())
        surfaceNormals.SetFeatureAngle(60.0)
        surfaceMapper = vtk.vtkPolyDataMapper()
        surfaceMapper.SetInputConnection(surfaceNormals.GetOutputPort())
        surfaceMapper.ScalarVisibilityOff()
        surface = vtk.vtkActor()
        surface.SetMapper(surfaceMapper)
    
        vol= vtk.vtkVolume()
        vol.SetMapper(self.skinMapper)
        self.ren.AddActor(surface)

        self.c = vol.GetCenter()
        # Camera setup
        self.set_cam()
        self.ren.ResetCamera()
        self.ren.ResetCameraClippingRange()        

        # Interact with the data.
        self.init_iren()
        


    def ray_casting(self):
        self.ren.RemoveAllViewProps()
        self.skinMapper.SetInputConnection(self.reader.GetOutputPort())
        self.skinMapper.SetBlendModeToComposite()

        self.transfer_fun()

        self.skinProperty.ShadeOn()
        self.skinProperty.SetAmbient(0.4)
        self.skinProperty.SetDiffuse(0.6)
        self.skinProperty.SetSpecular(0.2)
        self.skinProperty.SetInterpolationTypeToLinear()
        
        skinvolume = vtk.vtkVolume()
        skinvolume.SetMapper(self.skinMapper)
        skinvolume.SetProperty(self.skinProperty)
        self.ren.AddViewProp(skinvolume)
        self.c = skinvolume.GetCenter()

        self.set_cam()
        self.ren.ResetCameraClippingRange() 

        # Interact with the data.
        self.init_iren()



    def set_cam(self):
        camera =  self.ren.GetActiveCamera()
        camera.SetFocalPoint(self.c[0], self.c[1], self.c[2])
        camera.SetPosition(self.c[0] , self.c[1]+1000, self.c[2])
        camera.SetViewUp(0, 0, -1)
    
    def init_iren(self):
        self.iren.Initialize()
        self.ren.Render()
        self.iren.Start()


        
    def transfer_fun(self):
        skinColor = vtk.vtkColorTransferFunction()
        skinColor.AddRGBPoint(0,    0.0, 0.0, 0.0)
        skinColor.AddRGBPoint(5,  self.s_color[0]/255 , self.s_color[1]/255 , self.s_color[2]/255)
        skinColor.AddRGBPoint(1000, 1.0, 0.5, 0.3)
        skinColor.AddRGBPoint(1150, 1.0, 1.0, 0.9)

        skinScalarOpacity = vtk.vtkPiecewiseFunction()
        skinScalarOpacity.AddPoint(0,    0.00)
        skinScalarOpacity.AddPoint(5,  self.s_opacity)
        skinScalarOpacity.AddPoint(1000, 0.15)
        skinScalarOpacity.AddPoint(1150, self.b_opacity)

        skinGradientOpacity = vtk.vtkPiecewiseFunction()
        skinGradientOpacity.AddPoint(0,   0.0)
        skinGradientOpacity.AddPoint(90,  0.5)
        skinGradientOpacity.AddPoint(100, 1.0)

        self.skinProperty.SetColor(skinColor)
        self.skinProperty.SetScalarOpacity(skinScalarOpacity)
        self.skinProperty.SetGradientOpacity(skinGradientOpacity)
        






  
     

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = AppWindow()
    w.show()
    sys.exit(app.exec_())
