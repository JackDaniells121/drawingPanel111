#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/slider.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
// #include "myslider.cpp"

class BasicDrawPane : public wxPanel
{
public:
    BasicDrawPane(wxFrame* parent);
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
    wxDC *dc2;
    int liczba;
    int liczbaColor;
    wxString tekst;
    DECLARE_EVENT_TABLE()
};

class MyApp: public wxApp
{
    bool OnInit();
    void onScroll(wxScrollEvent& event); //przesuwanie slidera
    void onScrollColor(wxScrollEvent& event); //przesuwanie slidera
    void onSave(wxCommandEvent& event); //do przycisku zapisywania
    void onCheckbox(wxCommandEvent& event); //zaznaczenie kwadracika
    void onTextEdit(wxCommandEvent& event);

    wxFrame *frame;
    BasicDrawPane * drawPane;
    wxSlider *slider;
    wxSlider *sliderColor;
    wxButton *button;
    wxCheckBox *checkbox;
    wxTextCtrl *textctrl;
public:
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
    drawPane = new BasicDrawPane( (wxFrame*) frame);
    drawPane->liczba = 0;
    drawPane->liczbaColor = 0;
    drawPane->tekst = "tekst";
    sizer->Add(drawPane, 1, wxEXPAND);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();
    int ID_BUTTON = 1;
    int ID_CHECKBOX = 2;
    int ID_SLIDER = 100;
    int ID_SLIDER_COLOR = 102;
    int ID_TEXTCTRL = 101;

    this->button = new wxButton(drawPane, ID_BUTTON, wxT("Save"), 
                        wxPoint(400, 20));
    this->checkbox = new wxCheckBox(drawPane, ID_CHECKBOX, wxT("Show banana"), 
                            wxPoint(400, 60));
    this->slider = new wxSlider(drawPane, ID_SLIDER, 0, 0, 100, 
                        wxPoint(400, 100), wxSize(140, -1));
    this->sliderColor = new wxSlider(drawPane, ID_SLIDER_COLOR, 0, 0, 250, 
                        wxPoint(400, 220), wxSize(140, -1));
    this->textctrl = new wxTextCtrl(drawPane, ID_TEXTCTRL, wxT(""), 
                        wxPoint(400, 120), wxSize(-1, -1), wxTE_MULTILINE);

    Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, 
        wxCommandEventHandler(MyApp::onSave));
    Connect(ID_CHECKBOX, wxEVT_COMMAND_CHECKBOX_CLICKED, 
            wxCommandEventHandler(MyApp::onCheckbox));
    Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
        wxScrollEventHandler(MyApp::onScroll)); 
    Connect(ID_SLIDER_COLOR, wxEVT_COMMAND_SLIDER_UPDATED, 
            wxScrollEventHandler(MyApp::onScrollColor)); 
    Connect(ID_TEXTCTRL, wxEVT_COMMAND_TEXT_UPDATED, 
        wxCommandEventHandler(MyApp::onTextEdit));   

    return true;
} 

void MyApp::onSave(wxCommandEvent& event)
{
    wxInitAllImageHandlers();
    std::cout << "save event " << std::endl; //wypisanie w terminalu
    event.Skip();
    wxBitmap myBitmap(200, 200); 
    wxMemoryDC dc;
    dc.SelectObject(myBitmap);
    wxFont font=dc.GetFont();
    font.SetPointSize(15);
    dc.SetTextForeground(*wxBLACK);
    dc.DrawRectangle(0,0,50,100);
    wxString s(_T("A"));
    dc.DrawText(s, 5,5);
    //setting propper file path
    wxFileName f(wxStandardPaths::Get().GetExecutablePath()); //pobieranie sciezki do katalogu
    wxString appPath(f.GetPath());
    wxString path(appPath + _T("/test.png"));
    myBitmap.SaveFile(path, wxBITMAP_TYPE_PNG);
}

//show banana checkbox
void MyApp::onCheckbox(wxCommandEvent& event)
{
    // kod ktory laduje bana
    std::cout << "checkbox event" << std::endl;
    event.Skip();
}

void MyApp::onTextEdit(wxCommandEvent& event)
{
    this->drawPane->tekst = this->textctrl->GetValue();
    this->drawPane->paintNow();
    std::cout << this->textctrl->GetValue() << std::endl;
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
void BasicDrawPane::render(wxDC&  dc)
{
    dc.DrawRectangle(0,0,380,400);
    // draw some text
    dc.SetPen( wxPen( wxColor(liczbaColor,0,100), 2 ) );
    dc.DrawText(wxT("Testing"), 40, 260);

    //giwazdka 
    dc.SetPen( wxPen( wxColor(liczbaColor,250-liczbaColor,0), 2 ) );
    wxPoint points[6];
    points[0].x = 100; points[0].y = 20;
    points[1].x = 70; points[1].y = 80;
    points[2].x = 160; points[2].y = 50;
    points[3].x = 40; points[3].y = 50;
    points[4].x = 130; points[4].y = 80;
    points[5].x = 100; points[5].y = 20;
    dc.DrawPolygon(5, points);
    //malpka
    dc.SetBrush(*wxWHITE_BRUSH); // green filling
    dc.SetPen( wxPen( wxColor(0,0,0), 2 ) ); // 2-pixels-thick red outline
    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ ); //glowa
    dc.DrawCircle( wxPoint(190,95), 2 /* radius */ ); //oko
    dc.DrawCircle( wxPoint(210,95), 2 /* radius */ ); //oko
    dc.DrawLine( 190, 110, 210, 110 );  //usta
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 200, 125, 200, 260 ); // tlow
    dc.DrawLine( 200, 125, 170-liczba, 220-liczba ); // reka
    dc.DrawLine( 200, 125, 230, 220 ); // reka
    //tekst pod katem
    wxPoint center;
    center.x = 300;
    center.y = 270;

    dc.DrawRotatedText(wxString::Format(tekst), center, 90);
}
void MyApp::onScroll(wxScrollEvent& event)
{
    int slider_val = slider->GetValue();
    this->drawPane->liczba = slider_val;
    this->drawPane->paintNow();
}

void MyApp::onScrollColor(wxScrollEvent& event)
{
    int slider_color_val = sliderColor->GetValue();
    this->drawPane->liczbaColor = slider_color_val;
    this->drawPane->paintNow();
}