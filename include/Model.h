#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include "CImg.h"


class Model 
{
public:
	Model();
	void model_resize();
	void model_save(std::string file_name);
	void model_load(wxString addres);
	void kaleidoscope(int n_axis, double ang_axis = 0.0, bool silent = false);
	void axis_show(bool show);
	const wxImage & get_image();
	void reset_copy();
	const wxBitmap & get_bitmap();
	int get_axis();
	double get_angle();
	void set_axis(int n);
	void set_angle(double n);

private:
	wxImage m_image;
	wxImage m_image_copy;
	wxBitmap m_bitmap;
	int num_of_axis = 1;
	double ang_of_axis = 0.0;
};