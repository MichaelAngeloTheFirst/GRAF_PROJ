#include "Model.h"

const wxImage & Model::get_image()
{
	return m_image;
}

const wxBitmap & Model::get_bitmap()
{
	return m_bitmap;
}

Model::Model()
{
	m_image.AddHandler(new wxJPEGHandler);
	m_image.AddHandler(new wxPNGHandler);
}


void Model::model_load(wxString addres)
{
	m_image.LoadFile(addres, wxBITMAP_TYPE_ANY);
	m_bitmap = wxBitmap(m_image);
}


void Model::model_save()
{
	wxImage im_toSave = m_bitmap.ConvertToImage();
	im_toSave.SaveFile("wynik.jpg");

}	

void Model::model_resize()
{

	//m_bitmap.SetSize(w, h);
}