#pragma once 
#include <wx/wx.h>
#include "Model.h"

/// <summary>
/// Klasa odpowiadająca za wyświetlanie obrazka.
/// </summary>
class View : public wxPanel
{
public:
	View(wxWindow * panel, Model & model);
	~View() override;
	void MyPaint();///<Rysuje obrazek na ekran za pomocą bitmapy.

private:
	Model& m_model;

};
