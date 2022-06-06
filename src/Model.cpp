#include "Model.h"

const wxImage & Model::get_image()
{
	return m_image;
}

void Model::reset_copy()
{
	m_image_copy = m_image.Copy();
	m_bitmap = wxBitmap(m_image_copy);
}

const wxBitmap & Model::get_bitmap()
{
	return m_bitmap;
}


void Model::set_axis(int n)
{
	num_of_axis = n;
}

void Model::set_angle(double n)
{
	ang_of_axis =  n;
}


int Model::get_axis()
{
	return num_of_axis;
}
double Model::get_angle()
{
	return ang_of_axis;
}

Model::Model()
{
	m_image.AddHandler(new wxJPEGHandler);
	m_image.AddHandler(new wxPNGHandler);

	m_image_copy.AddHandler(new wxJPEGHandler);
	m_image_copy.AddHandler(new wxPNGHandler);
}


void Model::model_load(wxString addres)
{
	m_image.LoadFile(addres, wxBITMAP_TYPE_ANY);
	int smallerDimension = m_image.GetSize().x < m_image.GetSize().y ? m_image.GetSize().x : m_image.GetSize().y;
	m_image.Resize(wxSize(smallerDimension, smallerDimension), wxPoint(0, 0));
	m_image_copy = m_image.Copy();
	m_bitmap = wxBitmap(m_image_copy);
}


void Model::model_save(std::string file_name)
{
	wxImage im_toSave = m_bitmap.ConvertToImage();
	im_toSave.SaveFile(file_name);

}	

void Model::kaleidoscope(int n_axis, double ang_axis)
{
	if (this->m_image.Ok())
	{
		num_of_axis = n_axis;
		this->m_image_copy = this->m_image.Copy();
		const int h = this->m_image_copy.GetHeight();
		const int w = this->m_image_copy.GetWidth();
		const int x0 = h / 2.0;
		const int y0 = w / 2.0;

		const double ang = M_PI / num_of_axis;
		const double ang2 = 180.0 / num_of_axis;
		ang_of_axis = ang_axis;

		cimg_library::CImg<unsigned char> tmp(w, h, 1, 4);
		cimg_library::CImg<unsigned char> toCopy(w, h, 1, 4);
		

		while (ang_of_axis >= 360.0)
		{
			ang_of_axis = ang_of_axis - 360.0;
		}

		double bang2 = ang_of_axis * M_PI / 180.0;

		if (num_of_axis == 1)
		{
			if (bang2 > M_PI / 2.0 && bang2 <= 3 * M_PI / 2.0)
			{

				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x <= (y0 - y) * tan(bang2) + x0)
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
			else
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x >= (y0 - y) * tan(bang2) + x0)
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
		}
		else if (num_of_axis == 2)
		{
			if (bang2 > M_PI / 2.0 && bang2 <= 3 * M_PI / 2.0)
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x <= (y0 - y) * tan(bang2) + x0 && y >= (x - x0) * tan(bang2) + y0)
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
			else
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x >= (y0 - y) * tan(bang2) + x0 && y <= (x - x0) * tan(bang2) + y0)
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
		}
		else
		{
			if (ang + bang2 > M_PI / 2.0 && bang2 <= M_PI/2.0)
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x >= (y0 - y) * tan(ang + bang2) + x0 && x >= (y0 - y) * tan(bang2) + x0)													
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
			else if (bang2 > M_PI/2.0 && ang + bang2 <= 3 * M_PI / 2.0)
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x >= (y0 - y) * tan(ang + bang2) + x0 && x <= (y0 - y) * tan(bang2) + x0)													//x >= (y0 - y) * tan(ang + bang2) + x0 && x >= (y0 - y) * tan(bang2) + x0
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
			else if (ang + bang2 > 3 * M_PI / 2.0 && bang2 <= 3 * M_PI / 2.0)
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x <= (y0 - y) * tan(ang + bang2) + x0 && x <= (y0 - y) * tan(bang2) + x0)													
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
			else
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (x <= (y0 - y) * tan(ang + bang2) + x0 && x >= (y0 - y) * tan(bang2) + x0)													//x >= (y0 - y) * tan(ang + bang2) + x0 && x >= (y0 - y) * tan(bang2) + x0
						{
							tmp(x, y, 0) = this->m_image_copy.GetRed(x, y);
							tmp(x, y, 1) = this->m_image_copy.GetGreen(x, y);
							tmp(x, y, 2) = this->m_image_copy.GetBlue(x, y);
						}
						else
						{
							tmp(x, y, 3) = 0;
						}
					}
				}
			}
		}
		for (int i = 0; i < num_of_axis; i++)
		{
			cimg_library::CImg<unsigned char> toAlter = tmp.get_mirror('x').rotate(2 * (ang2 * i + ang_of_axis), x0, y0, 2, 3);
			cimg_library::CImg<unsigned char> toAlterToo = tmp.get_rotate(2 * (ang2 * i), x0, y0, 2, 3);

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					if (toAlter(x,y,3) != 0)
					{
						toCopy(x, y, 0) = toAlter(x, y, 0);
						toCopy(x, y, 1) = toAlter(x, y, 1);
						toCopy(x, y, 2) = toAlter(x, y, 2);
						toCopy(x, y, 3) = toAlter(x, y, 3);
					}
					else if(toAlterToo(x,y,3) != 0)
					{
						toCopy(x, y, 0) = toAlterToo(x, y, 0);
						toCopy(x, y, 1) = toAlterToo(x, y, 1);
						toCopy(x, y, 2) = toAlterToo(x, y, 2);
						toCopy(x, y, 3) = toAlterToo(x, y, 3);
					}
				}
			}
		}
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				this->m_image_copy.SetRGB(x, y, toCopy(x, y, 0), toCopy(x, y, 1), toCopy(x, y, 2));
			}
		}

		m_bitmap = wxBitmap(m_image_copy);
	}
}

void Model::model_resize()
{

	//m_bitmap.SetSize(w, h);
}