#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/anidecod.h>
#include <wx/quantize.h>
#include <wx/wfstream.h>
#include "CImg.h"

//WX_DECLARE_OBJARRAY(wxImage, wxImageArray);

/// <summary>
/// Klasa odpowiadająca za obsługę i modyfikację obrazów.
/// </summary>
class Model 
{
public:
	Model();
	void model_resize(); ///<Zmiana wymiarów obrazka.
	void model_save(std::string file_name);///<Zapisanie obrazka do pliku .jpg.
	void model_load(wxString addres);///<Załadowanie obrazka z systemu.
	const wxImage kaleidoscope(const wxImage& img, int n_axis, double ang_axis = 0.0);///<Metoda generująca obraz kalejdoskopu.
	void axis_show(bool show);///<Wyświetlenie osi symetrii kalejdoskopu.
	const wxImage & get_image();///<Zwracanie const referencji do oryginalnego obrazka.
	wxImageArray& get_gif_buffer();///<Zwraca przechowywany wxImageArray używany do stworzenia GIFa.
	void reset_copy();///<Resetuje wynik.
	wxBitmap & get_bitmap();///<Zwraca bitmapę utworzoną z kopii oryginalnego obrazka.
	int get_axis();///<Zwraca ilość osi kalejdoskopu.
	double get_angle();///<Zwraca kąt obrotu obrazka.
	void set_axis(int n);///<Ustala ilość osi symetrii kalejdoskopu.
	void set_scale(int n);///<Nieużywane. Ustala rozmiar klatek w generowanym GIFie.
	void set_frames(int n);///<Nieużywane. Ustala ilość klatek w GIFie.
	void set_angle(double n);///<Ustala który fragment obrazka służy do generowania efektu kalejdoskopu.


private:
	wxImageArray gif_buffer;///<Przechowuje klatki generowanego GIFa.
	wxImage m_image;///<Przechowuje oryginalny obrazek.
	wxImage m_image_copy;///<Przechowuje kopię obrazka, na której wykonywane są operacje.
	wxBitmap m_bitmap;///<Bitmapa wyniku.
	int num_of_axis = 1;///<Ilość osi kalejdoskopu.
	double ang_of_axis = 0.0;///<Kąt ustalający który zakres obrazka służy do generowania kalejdoskopu.
	int frame_count = 60;///<Nieużywane.
	int gif_frames = 90;///<Ilość klatek w GIFie.
	int gif_scale = 500;///<Rozmiar boku klatki GIFa.
};