#include <wx/wx.h>
#include <wx/slider.h>

class mySlider : public wxFrame
{
public:
  mySlider();

  wxSlider *slider;
  int pos;

  void OnScroll(wxScrollEvent& event);

};

const int ID_SLIDER = 100;