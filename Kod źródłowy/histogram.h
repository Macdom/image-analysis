#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>

// Klasa okna wy�wietlaj�cego histogram
class HistFrame : public wxFrame
{
public:
	HistFrame();
	// Uzyskuje wska�nik do informacji o tym, czy okno jest wy�wietlone
	void setPointer(bool* ptr);
	// Oblicza histogram do wy�wietlenia go
	void drawHistogram(unsigned char* pixels, unsigned int width, unsigned int height);
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na kt�rym wy�wietlany jest histogram
	wxPanel* mainPanel;
	// Czy okno histogramu jest wy�wietlone?
	bool* isHist;

	// Histogram w postaci tablicy
	unsigned int colorCount[256];
	// Kolor o najwi�kszej cz�stotliwo�ci. Liczony by m�c znormalizowa� wielko�� wykresu histogramu
	unsigned int biggestCount;

	// Handlery do zdarze�
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);
};