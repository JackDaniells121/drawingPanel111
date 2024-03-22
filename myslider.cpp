#include "myslider.h"

mySlider::mySlider()
       : wxFrame(NULL, wxID_ANY, "title", wxDefaultPosition, wxSize(250, 130))
{
  wxImage::AddHandler( new wxPNGHandler );
  wxPanel *panel = new wxPanel(this);
  slider = new wxSlider(panel, ID_SLIDER, 0, 0, 100, 
      wxPoint(10, 30), wxSize(140, -1));

//   button = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("mute.png"), 
//       wxBITMAP_TYPE_PNG), wxPoint(180, 20));

  Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
      wxScrollEventHandler(mySlider::OnScroll));  
  Center();
}


void mySlider::OnScroll(wxScrollEvent& event)
{
  pos = slider->GetValue(); 

  if (pos == 0) {
      
  } 
}