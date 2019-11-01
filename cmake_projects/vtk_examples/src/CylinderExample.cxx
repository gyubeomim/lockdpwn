#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <array>

int main() {
  vtkSmartPointer<vtkNamedColors> colors =
                  vtkSmartPointer<vtkNamedColors>::New();

  std::array<unsigned char, 4> bkg({26,51,102,255});
  colors->SetColor("BkgColor", bkg.data());

  vtkSmartPointer<vtkCylinderSource> cylinder =
      vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetResolution(8);

  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());



  return 0;
}
