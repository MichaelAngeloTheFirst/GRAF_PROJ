#pragma once
#include <wx/wx.h>
#include <wx/image.h>


class Model 
{
public:
	Model();
	void model_resize();
	void model_save();
	void model_load(wxString addres);
	const wxImage & get_image();
	const wxBitmap & get_bitmap();

private:
	wxImage m_image;
	wxBitmap m_bitmap;
};