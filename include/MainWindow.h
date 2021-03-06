#pragma once 
#include <wx/wx.h>
#include "Controler.h"
#include "View.h"
#include "id.h"

/// <summary>
/// Klasa odpowiadająca za stworzenie okna.
/// </summary>
class MainWindow : public wxFrame
{
public: 
	MainWindow();
	~MainWindow() override;
	void MW_resize(wxEvent & event);
	void MW_hideControl(wxCommandEvent& event);
private:
	///Wymiary okienka
	int m_w_height = 800;
	int m_w_width = 1200;

	wxBoxSizer* m_bsizer = nullptr;///<Sizer układający pasek UI i panel z obrazkiem.
	Controler* m_control = nullptr;///<Klasa z elementami UI. Posiada funkcje zmieniające parametry klasy przechowującej dane m_model.

	wxButton* m_collapseButton = nullptr;///<Nieużywane. Chowa pasek UI.
	bool hideControl = false;
	View* m_view = nullptr;///<Klasa wyświetlająca wygenerowany obrazek z m_model.
	Model m_model{};///<Klasa z danymi i funkcjami generującymi efekt kalejdoskopu.

};
