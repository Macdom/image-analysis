#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <sstream>

// Klasa okna s³u¿¹cego do przemna¿ania/przeplatania
class MultFrame : public wxFrame
{
public:
	MultFrame();
	// Uzyskuje wskaŸnik do informacji o tym, czy okno jest wyœwietlone
	void setPointer(short* ptr, wxImage* _mainImg);
	// Uzyskuje obraz na podstawie wprowadzonych przez u¿ytkownika parametrów
	wxImage getResult();
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na którym wyœwietlany jest podgl¹d
	wxPanel* mainPanel;
	// Czy wyœwietlone jest okno s³u¿¹ce do przemna¿ania/przeplatania?
	short* isMult;
	
	// Przycisk "Wczytaj JPG"
	wxButton* btLoad;
	// Okno dialogowe do wczytania obrazu
	wxFileDialog* dialLoad;
	// Suwak do ustawiania udzia³u drugiego obrazu przy przeplataniu
	wxScrollBar* sbContrib;

	// Teksty wyœwietlaj¹ce poziom udzia³u drugiego obrazu przy przeplataniu
	wxStaticText* stContrib;
	wxStaticText* stContrib2;

	// Przycisk "Zastosuj"
	wxButton* btApply;

	// Bitmapa s³u¿¹ca do wyœwietlania obrazu
	wxBitmap mainBMP;
	// Obraz uzyskany z g³ównego okna w momencie otwarcia okienka do przemna¿ania/przeplatania
	wxImage mainImg;
	// Kopia powy¿szego obrazu, do modyfikacji
	wxImage copyImg;
	// Wczytany (drugi) obraz
	wxImage bonusImg;

	// Œcie¿ka do drugiego obrazu
	wxString filename;
	// Czy drugi obraz zosta³ wczytany?
	short isLoad;
	// Udzia³ drugiego obrazu (przy przeplataniu)
	double contribution;

	// Handlery do zdarzeñ
	void btLoad_Click(wxCommandEvent& e);
	void sbContrib_Scroll(wxScrollEvent& e);
	void btApply_Click(wxCommandEvent& e);
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);
};