#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include "CImg.h"


class Model 
{
public:
	Model();
	void model_resize();
	void model_save();
	void model_load(wxString addres);
	void kaleidoscope(int n_axis, double ang_axis = 0.0);
	const wxImage & get_image();
	void reset_copy();
	const wxBitmap & get_bitmap();
	int get_axis();
	double get_angle();

private:
	wxImage m_image;
	wxImage m_image_copy;
	wxBitmap m_bitmap;
	int num_of_axis = 0;
	double ang_of_axis = 0.0;
};