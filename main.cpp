#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/slider.h"
// #include "myslider.cpp"

class BasicDrawPane : public wxPanel
{
    
public:
    BasicDrawPane(wxFrame* parent);
    
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    
    void render(wxDC& dc);

    wxDC *dc2;
    
    DECLARE_EVENT_TABLE()
};


class MyApp: public wxApp
{
    bool OnInit();

    void onScroll(wxScrollEvent& event);
    
    wxFrame *frame;
    BasicDrawPane * drawPane;
    wxSlider *slider;
public:
        
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
	
    drawPane = new BasicDrawPane( (wxFrame*) frame );
    sizer->Add(drawPane, 1, wxEXPAND);
	
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    
    frame->Show();
    
    int ID_SLIDER = 100;

    this->slider = new wxSlider(drawPane, ID_SLIDER, 0, 0, 100, 
      wxPoint(10, 30), wxSize(140, -1));

    Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
    wxScrollEventHandler(MyApp::onScroll));  

    return true;
} 

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)

EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent)
{
}

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
    this->dc2 = &dc;
}

void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void rysujMalpke(wxDC&  dc, int angle)
{
    // rysowanie malpki
    dc.SetBrush(*wxWHITE_BRUSH); // green filling
    dc.SetPen( wxPen( wxColor(0,0,0), 2 ) ); // 2-pixels-thick red outline
    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ ); //glowa
    dc.DrawCircle( wxPoint(190,95), 2 /* radius */ ); //oko
    dc.DrawCircle( wxPoint(210,95), 2 /* radius */ ); //oko
    dc.DrawLine( 190, 110, 210, 110 );  //usta

    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 200, 125, 200, 260 ); // tlow
    dc.DrawLine( 200, 125, 170, 220 ); // reka

    dc.DrawLine( 200, 125, 230, 220 ); // reka
}

void rysujGwiazde(wxDC&  dc, wxColor color )
{
    wxPoint points[6];
    points[0].x = 100; points[0].y = 150;
    points[1].x = 70; points[1].y = 210;
    points[2].x = 160; points[2].y = 180;
    points[3].x = 40; points[3].y = 180;
    points[4].x = 130; points[4].y = 210;
    points[5].x = 100; points[5].y = 150;

    dc.DrawPolygon(5, points);
}

void BasicDrawPane::render(wxDC&  dc)
{
    // draw some text
    dc.DrawText(wxT("Testing"), 40, 260); 
    
    rysujMalpke(dc, 45);
    
    wxColor color = wxColor(0,0,0);
    rysujGwiazde(dc, color);
    
    //tekst pod katem
    wxPoint center;
    center.x = 250;
    center.y = 100;
    dc.DrawRotatedText(wxString::Format("Rotated by %d°", 90), center, 90);
}

void MyApp::onScroll(wxScrollEvent& event)
{
    int slider_val = slider->GetValue();
    wxColor color = wxColor(0,0,0);
    // wxString str = wxString::Format(wxT("%f"), slider_val);
    // drawPane->dc2->DrawText(str, 50, 270); 
}