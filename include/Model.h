#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include "CImg.h"
#include <wx/anidecod.h>
#include <wx/quantize.h>
#include <wx/wfstream.h>
//WX_DECLARE_OBJARRAY(wxImage, wxImageArray);


class Model 
{
public:
	Model();
	void model_resize();
	void model_save(std::string file_name);
	void model_load(wxString addres);
	const wxImage kaleidoscope(int n_axis, double ang_axis = 0.0);
	void axis_show(bool show);
	const wxImage & get_image();
	wxImageArray& get_gif_buffer();
	void reset_copy();
	wxBitmap & get_bitmap();
	int get_axis();
	double get_angle();
	void set_axis(int n);
	void set_angle(double n);

private:
	wxImageArray gif_buffer;
	wxImage m_image;
	wxImage m_image_copy;
	wxBitmap m_bitmap;
	int num_of_axis = 1;
	double ang_of_axis = 0.0;
	int frame_count = 60;
};