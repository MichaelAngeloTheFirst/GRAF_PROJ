#include "View.h"



void View::MyPaint()
{
	wxClientDC dc(this);
	PrepareDC(dc);
	const wxSize dcSize = dc.GetSize();
	
	if (m_model.get_bitmap().Ok() == false)
	{
		return;
	}

	wxImage buf = m_model.get_bitmap().ConvertToImage();
	wxBitmap result = wxBitmap(buf.Rescale(dcSize.x, dcSize.y));
	dc.DrawBitmap(result, wxDefaultPosition, false);

}



View::View(wxWindow* parent, Model & model) : wxPanel(parent), m_model(model)
{
	SetAutoLayout(true); // musi byc w kazdym
	//SetBackgroundColour("red");
	//Bind(wxEVT_PAINT, &View::MyPaint, this);
}


View::~View() = default;
