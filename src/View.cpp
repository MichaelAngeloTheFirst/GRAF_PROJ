#include "View.h"



void View::MyPaint()
{
	wxClientDC dc(this);
	PrepareDC(dc);
	if (m_model.get_bitmap().Ok() ==true) 
		dc.DrawBitmap(m_model.get_bitmap(), wxDefaultPosition, false);
	else 
		wxLogError("NIE MOGE RYSOWAC");
}



View::View(wxWindow* parent, Model & model) : wxPanel(parent), m_model(model)
{
	SetAutoLayout(true); // musi byc w kazdym
	//SetBackgroundColour("red");
	//Bind(wxEVT_PAINT, &View::MyPaint, this);
}


View::~View() = default;
