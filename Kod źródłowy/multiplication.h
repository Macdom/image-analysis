#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <sstream>

// Klasa okna s�u��cego do przemna�ania/przeplatania
class MultFrame : public wxFrame
{
public:
	MultFrame();
	// Uzyskuje wska�nik do informacji o tym, czy okno jest wy�wietlone
	void setPointer(short* ptr, wxImage* _mainImg);
	// Uzyskuje obraz na podstawie wprowadzonych przez u�ytkownika parametr�w
	wxImage getResult();
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na kt�rym wy�wietlany jest podgl�d
	wxPanel* mainPanel;
	// Czy wy�wietlone jest okno s�u��ce do przemna�ania/przeplatania?
	short* isMult;
	
	// Przycisk "Wczytaj JPG"
	wxButton* btLoad;
	// Okno dialogowe do wczytania obrazu
	wxFileDialog* dialLoad;
	// Suwak do ustawiania udzia�u drugiego obrazu przy przeplataniu
	wxScrollBar* sbContrib;

	// Teksty wy�wietlaj�ce poziom udzia�u drugiego obrazu przy przeplataniu
	wxStaticText* stContrib;
	wxStaticText* stContrib2;

	// Przycisk "Zastosuj"
	wxButton* btApply;

	// Bitmapa s�u��ca do wy�wietlania obrazu
	wxBitmap mainBMP;
	// Obraz uzyskany z g��wnego okna w momencie otwarcia okienka do przemna�ania/przeplatania
	wxImage mainImg;
	// Kopia powy�szego obrazu, do modyfikacji
	wxImage copyImg;
	// Wczytany (drugi) obraz
	wxImage bonusImg;

	// �cie�ka do drugiego obrazu
	wxString filename;
	// Czy drugi obraz zosta� wczytany?
	short isLoad;
	// Udzia� drugiego obrazu (przy przeplataniu)
	double contribution;

	// Handlery do zdarze�
	void btLoad_Click(wxCommandEvent& e);
	void sbContrib_Scroll(wxScrollEvent& e);
	void btApply_Click(wxCommandEvent& e);
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);
};