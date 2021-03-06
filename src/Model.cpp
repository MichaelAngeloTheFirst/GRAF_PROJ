#include "Model.h"
#include <omp.h>



void Model::set_axis(int n)
{
	num_of_axis = n;
}
void Model::set_scale(int n)
{
	gif_scale = n;
}
void Model::set_frames(int n)
{
	gif_frames = n;
}
void Model::set_angle(double n)
{
	ang_of_axis =  n;
}


wxImageArray& Model::get_gif_buffer() 
{
	return gif_buffer;
}
int Model::get_axis()
{
	return num_of_axis;
}
double Model::get_angle()
{
	return ang_of_axis;
}
const wxImage& Model::get_image()
{
	return m_image;
}
wxBitmap& Model::get_bitmap()
{
	return m_bitmap;
}


Model::Model()
{
	m_image.AddHandler(new wxJPEGHandler);
	m_image.AddHandler(new wxPNGHandler);

	m_image_copy.AddHandler(new wxJPEGHandler);
	m_image_copy.AddHandler(new wxPNGHandler);
	gif_buffer =  wxImageArray();
}



void Model::reset_copy()
{
	m_image_copy = m_image.Copy();
	m_bitmap = wxBitmap(m_image_copy);
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
	m_image_copy.SaveFile(file_name);
}	


/// <param name="img">Obrazek, na którym będzie nakładany efekt.</param>
/// <param name="n_axis">Ilość osi kalejdoskopu.</param>
/// <param name="ang_axis">Zakres obrazka wykorzystany do generowania kalejdoskopu.</param>
/// <returns>Obrazek odzwierciedlający działanie kalejdoskopu.</returns>
/// <summary>
/// 		Kalejdoskop jest generowany za pomocą operacji odbić lustrzanych wzdłuż osi symetrii. Wszystko po prawej stronie osi odbicia jest powielone na lewą stronę. 
///			Aby to zrealizować, obrazek jest początkowo obracany, aby oś symetrii pokrywała się z pionową osią.Następnie tworzona jest tymczasowa bitmapa, zawierająca lustrzane odbicie całości,
///			a na końcu oba obrazki są ze sobą sklejane. Dodatkowo dla przyspieszenia algorytmu wykorzystano multithreading.
/// </summary>

const wxImage Model::kaleidoscope(const wxImage& img, int n_axis, double ang_axis)
{
	if (!m_image.Ok())
		return m_image;
	

		
		num_of_axis = n_axis;
		m_image_copy = img.Copy();
		const int h = m_image_copy.GetHeight();
		const int w = h;
		const int x0 = h / 2.0;
		const int y0 = w / 2.0;
		const double ang = M_PI / num_of_axis;
		const double ang2 = 180.0 / num_of_axis;


		cimg_library::CImg<unsigned char> tmp(1, 1, 1, 4,0,0,0,0);
		tmp.resize(w, h);
		cimg_library::CImg<unsigned char> toCopy(w, h, 1, 4, 0);
		unsigned char* imageTemp = m_image_copy.GetData();


		#pragma omp for
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++) 
			{
				tmp[w * h * 0 + w * y + x] = imageTemp[3 * (w * y + x) + 0];
				tmp[w * h * 1 + w * y + x] = imageTemp[3 * (w * y + x) + 1];
				tmp[w * h * 2 + w * y + x] = imageTemp[3 * (w * y + x) + 2];
			}

		if (ang_axis) {
			tmp.rotate(ang_axis, x0, y0, 1, 3);
		}

		/* Stara wersja generatora. Porzucona z powodu niskiej wydajności.
		double upperRange = -M_PI / 2. + ang + 1e-3f;
		double lowerRange = -M_PI / 2.;
		#pragma omp for
		for (int x = x0-1; x < w; x++)
			for (int y = 0; y < h; y++)
			{
				double a = atan2(y - y0, x - x0);
				if (lowerRange <= a && a <= upperRange)
				{
					tmp(x, y, 3) =255;
				}
				else
				{
					break;
				}
			}

		#pragma omp for
		for (int i = 0; i < num_of_axis; i++)
		{
			cimg_library::CImg<unsigned char> toAlter = tmp.get_rotate(2*ang2 * i , x0, y0, 3, 3);
			cimg_library::CImg<unsigned char> toAlterToo = toAlter.get_mirror('x');
			//cimg_library::CImg<unsigned char> toAlterToo = tmp.get_mirror('x');
			//cimg_library::CImg<unsigned char> toAlter = tmp;
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
					
					else if (toAlterToo(x, y, 3) != 0)
					{
						toCopy(x, y, 0) = toAlterToo(x, y, 0);
						toCopy(x, y, 1) = toAlterToo(x, y, 1);
						toCopy(x, y, 2) = toAlterToo(x, y, 2);
						toCopy(x, y, 3) = toAlterToo(x, y, 3);
					}
					
				}
			}
		}
		#pragma omp for
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				m_image_copy.SetRGB(x, y, toCopy(x, y, 0), toCopy(x, y, 1), toCopy(x, y, 2));
			}
		}
		*/

		for (int i = 0; i < num_of_axis; i++)
		{	
			tmp.rotate(ang2 * i, x0, y0, 1, 3);
			cimg_library::CImg<unsigned char> mirror = tmp.get_mirror('x');


			#pragma omp for
			for (int x = 0; x < w/2; x++)
				for (int y = 0; y < h; y++)
				{
					tmp[w * h * 0 + w * y + x] = mirror[w * h * 0 + w * y + x];
					tmp[w * h * 1 + w * y + x] = mirror[w * h * 1 + w * y + x];
					tmp[w * h * 2 + w * y + x] = mirror[w * h * 2 + w * y + x];
				}
				
		}


		#pragma omp for
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
			{
				imageTemp[3 * (w * y + x) + 0] = tmp[w * h * 0 + w * y + x];
				imageTemp[3 * (w * y + x) + 1] = tmp[w * h * 1 + w * y + x];
				imageTemp[3 * (w * y + x) + 2] = tmp[w * h * 2 + w * y + x];
			}

		return m_image_copy;
}

/// <summary>
/// Metoda rysująca linie osi symetrii na obrazku kalejdoskopu.
///	
///	Metoda ta rysuje osi kaleidoskopu poprzez kolorowanie pikseli obrazka na kolor czerwony, wykorzystując do tego bibliotekę CImg.
/// </summary>
/// <param name="show"></param>

void Model::axis_show(bool show)
{
	if (show)
	{
		wxImage axis_copy = m_image_copy.Copy();
		const int w = axis_copy.GetWidth();
		const int h = axis_copy.GetHeight();
		cimg_library::CImg<unsigned int> axis(w, h, 1, 4);
		const int x0 = w / 2.0;
		const int y0 = h / 2.0;
		double ang = M_PI / num_of_axis;

		for (int i = 0; i < num_of_axis; i++)
		{
			double a = i * ang;
			double check = (a == i * M_PI || a == M_PI / 2.0) ? 0 : 0.5;

			for(int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					if (x >= (y - y0) * tan(a) + x0 - 1 - check && x <= (y - y0) * tan(a) + x0 + 1 + check && a != M_PI / 2.0)
					{

						axis(x, y, 0) = 255;
						axis(x, y, 1) = 0;
						axis(x, y, 2) = 0;

					}
					else if (a == M_PI/2.0 && y <= (x-x0) / tan(a) + y0 + 1 + check && y >= (x - x0) / tan(a) + y0 - 1 - check)
					{
						axis(x, y, 0) = 255;
						axis(x, y, 1) = 0;
						axis(x, y, 2) = 0;
					}
					else if (axis(x, y, 0) != 255)
					{
						axis(x, y, 3) = 0;
					}			
				}
			}
		}
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				if(axis(x,y,0) == 255)
					axis_copy.SetRGB(x, y, axis(x, y, 0), axis(x, y, 1), axis(x, y, 2));
			}
		}

		m_bitmap = wxBitmap(axis_copy);
	}
	else 
	{
		m_bitmap = wxBitmap(m_image_copy);
	}
}

void Model::model_resize()
{

	//m_bitmap.SetSize(w, h);
}