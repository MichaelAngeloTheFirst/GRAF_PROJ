#pragma once 
#include <wx/wx.h>
#include "Model.h"


class View : public wxPanel
{
public:
	View(wxWindow * panel, Model & model);
	~View() override;
	void MyPaint();

private:
	Model& m_model;

};
