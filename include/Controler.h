#pragma once
#include <wx/wx.h>
#include "id.h"
#include "View.h"
#include "Model.h"

class Controler : public wxPanel
{
public:
	Controler(wxWindow* parent, View& view, Model & model);
	~Controler() override;
	void onLoadClick(wxCommandEvent& event);
	void onSaveClick(wxCommandEvent& event);

private:
	wxButton* m_loadButton = nullptr;
	wxButton* m_saveButton = nullptr;
	wxCheckBox* m_checkbox = nullptr;
	wxSlider* m_axisSlider = nullptr;
	wxBoxSizer* m_bsizer = nullptr;
	View& m_view;
	Model& m_model;


};
