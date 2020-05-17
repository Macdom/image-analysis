#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>

// Klasa okna wyœwietlaj¹cego histogram
class HistFrame : public wxFrame
{
public:
	HistFrame();
	// Uzyskuje wskaŸnik do informacji o tym, czy okno jest wyœwietlone
	void setPointer(bool* ptr);
	// Oblicza histogram do wyœwietlenia go
	void drawHistogram(unsigned char* pixels, unsigned int width, unsigned int height);
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na którym wyœwietlany jest histogram
	wxPanel* mainPanel;
	// Czy okno histogramu jest wyœwietlone?
	bool* isHist;

	// Histogram w postaci tablicy
	unsigned int colorCount[256];
	// Kolor o najwiêkszej czêstotliwoœci. Liczony by móc znormalizowaæ wielkoœæ wykresu histogramu
	unsigned int biggestCount;

	// Handlery do zdarzeñ
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);
};