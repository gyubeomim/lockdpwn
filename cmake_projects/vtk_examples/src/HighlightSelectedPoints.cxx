#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkRendererCollection.h>
#include <vtkProperty.h>
#include <vtkPlanes.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkAreaPicker.h>
#include <vtkExtractGeometry.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIdFilter.h>

class InteractorStyle : public vtkInteractorStyleRubberBandPick {
 public:
  static InteractorStyle* New();
  vtkTypeMacro(InteractorStyle, vtkInteractorStyleRubberBandPick);

  InteractorStyle() {
    this->SelectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    this->SelectedActor = vtkSmartPointer<vtkActor>::New();
    this->SelectedActor->SetMapper(SelectedMapper);
  }

  virtual void OnLeftButtonUp() {
    // Forward events
    vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

    vtkPlanes* frustum = static_cast<vtkAreaPicker*>(this->GetInteractor()->GetPicker())->GetFrustum();

    vtkSmartPointer<vtkExtractGeometry> extractGeometry = vtkSmartPointer<vtkExtractGeometry>::New();

    extractGeometry->SetImplicitFunction(frustum);

  }

  void SetPoints(vtkSmartPointer<vtkPolyData> points) { this->Points = points; }

 private:
  vtkSmartPointer<vtkPolyData> Points;
  vtkSmartPointer<vtkActor> SelectedActor;
  vtkSmartPointer<vtkDataSetMapper> SelectedMapper;
};
vtkStandardNewMacro(InteractorStyle);

int main(int argc, char **argv) {


  return 0;
}
