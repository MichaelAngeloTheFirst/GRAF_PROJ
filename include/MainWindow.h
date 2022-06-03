#pragma once 
#include <wx/wx.h>
#include "Controler.h"
#include "View.h"
#include "id.h"

class MainWindow : public wxFrame
{
public: 
	MainWindow();
	~MainWindow() override;
	void MW_resize(wxCommandEvent & event);

private:
	int m_w_height = 800;
	int m_w_width = 1200;
	wxBoxSizer* m_bsizer = nullptr;
	Controler* m_control = nullptr;

	//view
	View* m_view = nullptr;
	Model m_model{};

};
