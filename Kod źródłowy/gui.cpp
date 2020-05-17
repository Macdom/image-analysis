#include "histogram.h"
#include "multiplication.h"
#include "gui.h"
#include "operations.h"

wxIMPLEMENT_APP(AOProject);

bool AOProject::OnInit() {
	// Utwórz i wyœwietl g³ówne okno programu
	AOFrame* frame = new AOFrame();
	frame->Show(true);
	return true;
}

AOFrame::AOFrame() : wxFrame(NULL, wxID_ANY, "Projekt - Analiza obrazów") {
	// W konstruktorze ustawiane s¹ domyœlne wartoœci kontrolek (po³o¿enie, czy s¹ aktywne itp.)
	// oraz przypisywane s¹ handlery zdarzeñ do zdarzeñ

	SetSize(1000, 600);

	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer2 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainSizer);
	this->SetAutoLayout(true);
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(4, 4), wxSize(500, 200));
	mainSizer->Add(mainPanel, 1, wxALIGN_LEFT | wxEXPAND | wxALL, 5);
	mainSizer->Add(mainSizer2, 0, wxALIGN_TOP | wxALL, 5);

	btLoad = new wxButton(this, wxID_ANY, _("Wczytaj JPG"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btLoad"));
	btSave = new wxButton(this, wxID_ANY, _("Zapisz do JPG"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btSave"));
	stInfo = new wxStaticText(this, wxID_ANY, "Aby wprowadziæ zmiany", wxPoint(10, 0), wxSize(180, 25));
	stInfo2 = new wxStaticText(this, wxID_ANY, "przez suwaki, kliknij", wxPoint(10, 0), wxSize(180, 25));
	stInfo3 = new wxStaticText(this, wxID_ANY, "\"Zastosuj\"", wxPoint(10, 0), wxSize(180, 25));
	sbBrightness = new wxScrollBar(this, wxID_ANY, wxPoint(10, 0), wxSize(150, 25), wxSB_HORIZONTAL, wxDefaultValidator, _("sbBrightness"));
	stBrightness = new wxStaticText(this, wxID_ANY, "Zmiana jasnosci: 0", wxPoint(10, 0), wxSize(150, 25));
	sbContrast = new wxScrollBar(this, wxID_ANY, wxPoint(10, 0), wxSize(150, 25), wxSB_HORIZONTAL, wxDefaultValidator, _("sbContrast"));
	stContrast = new wxStaticText(this, wxID_ANY, "Kontrast: 1", wxPoint(10, 0), wxSize(150, 25));
	sbGamma = new wxScrollBar(this, wxID_ANY, wxPoint(10, 0), wxSize(150, 25), wxSB_HORIZONTAL, wxDefaultValidator, _("sbGamma"));
	stGamma = new wxStaticText(this, wxID_ANY, "Korekcja gamma: 1", wxPoint(10, 0), wxSize(150, 25));
	btApply = new wxButton(this, wxID_ANY, _("Zastosuj"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btApply"));
	btHistogram = new wxButton(this, wxID_ANY, _("Wyœwietl histogram"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btHistogram"));
	btRestore = new wxButton(this, wxID_ANY, _("Zresetuj obraz"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btRestore"));
	btNormHist = new wxButton(this, wxID_ANY, _("Rozci¹gnij histogram"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btNormHist"));
	btEqualHist = new wxButton(this, wxID_ANY, _("Wyrównaj histogram"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btEqualHist"));
	btMultImage = new wxButton(this, wxID_ANY, _("Przemnó¿ obrazy"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btMultImage"));
	btInterImage = new wxButton(this, wxID_ANY, _("Przepleæ obrazy"), wxPoint(10, 0), wxSize(180, 25), 0, wxDefaultValidator, _("btInterImage"));

	mainImg.AddHandler(new wxJPEGHandler);

	sbBrightness->SetScrollbar(50, 0, 100, 10);
	sbContrast->SetScrollbar(50, 0, 100, 10);
	sbGamma->SetScrollbar(50, 0, 100, 10);

	mainSizer2->Add(btLoad, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btSave, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer2->Add(stInfo, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(stInfo2, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(stInfo3, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(sbBrightness, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer2->Add(stBrightness, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(sbContrast, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(stContrast, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(sbGamma, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(stGamma, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btApply, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btHistogram, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer2->Add(btNormHist, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btEqualHist, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer2->Add(btMultImage, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btInterImage, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer2->Add(btRestore, 0, wxALIGN_CENTER, 5);

	Layout();
	GetSizer()->SetSizeHints(this);
	Center();

	btLoad->Bind(wxEVT_BUTTON, &AOFrame::btLoad_Click, this);
	btSave->Bind(wxEVT_BUTTON, &AOFrame::btSave_Click, this);
	sbBrightness->Bind(wxEVT_SCROLL_CHANGED, &AOFrame::sbBrightness_Scroll, this);
	sbContrast->Bind(wxEVT_SCROLL_CHANGED, &AOFrame::sbContrast_Scroll, this);
	sbGamma->Bind(wxEVT_SCROLL_CHANGED, &AOFrame::sbGamma_Scroll, this);
	btApply->Bind(wxEVT_BUTTON, &AOFrame::btApply_Click, this);
	btRestore->Bind(wxEVT_BUTTON, &AOFrame::btRestore_Click, this);
	btNormHist->Bind(wxEVT_BUTTON, &AOFrame::btNormHist_Click, this);
	btHistogram->Bind(wxEVT_BUTTON, &AOFrame::btHistogram_Click, this);
	btEqualHist->Bind(wxEVT_BUTTON, &AOFrame::btEqualHist_Click, this);
	btMultImage->Bind(wxEVT_BUTTON, &AOFrame::btMultImage_Click, this);
	btInterImage->Bind(wxEVT_BUTTON, &AOFrame::btInterImage_Click, this);
	mainPanel->Bind(wxEVT_UPDATE_UI, &AOFrame::mainPanel_Update, this);
	Bind(wxEVT_CLOSE_WINDOW, &AOFrame::onClose, this);

	dialLoad = new wxFileDialog(this, _("Podaj sciezke"), _(""), _(""), _("*"), wxFD_OPEN);
	dialSave = new wxFileDialog(this, _("Podaj sciezke"), _(""), _(""), _("*"), wxFD_SAVE);
	isLoad = 0;
	isSave = false;
	isHist = new bool(false);
	isMult = new short(0);

	imgWidth = 1;
	imgHeight = 1;
}

void AOFrame::onExit(wxCommandEvent& e) {
	// Zwolnij pamiêæ przy wy³¹czaniu programu
	if (isHist != NULL) delete isHist;
	if (isMult != NULL) delete isMult;
	Close(true);
}

void AOFrame::onClose(wxCloseEvent& e) {
	// Zamknij wszystkie okna
	if (*isHist) histFrame->Close(true);
	if (*isMult) multFrame->Close(true);
	Destroy();
}

void AOFrame::btLoad_Click(wxCommandEvent& e) {
	// Wydaj rozkaz wczytania obrazu (wczytanie odbêdzie siê w mainPanel_Update())
	dialLoad->SetWildcard("Obraz JPG (*.jpg)|*.jpg");
	if (dialLoad->ShowModal() == wxID_OK) {
		filename = dialLoad->GetPath();
		isLoad = 2;
	}
}

void AOFrame::btSave_Click(wxCommandEvent& e) {
	// Wydaj rozkaz zapisu obrazu (zapis odbêdzie siê w mainPanel_Update())
	if (isLoad != 1) return;
	dialSave->SetWildcard("Obraz JPG (*.jpg)|*.jpg");
	if (dialSave->ShowModal() == wxID_OK) {
		outFilename = dialSave->GetPath();
		isSave = true;
	}
}

void AOFrame::sbBrightness_Scroll(wxScrollEvent& e) {
	// Uaktualnij i wyœwietl wartoœæ poziomu jasnoœci
	brightness = sbBrightness->GetThumbPosition() * 2 - 100;
	std::stringstream str;
	str << "Zmiana jasnosci: " << brightness;
	stBrightness->SetLabel(str.str());
}

void AOFrame::sbContrast_Scroll(wxScrollEvent& e) {
	// Uaktualnij i wyœwietl wartoœæ poziomu kontrastu
	contrast = sbContrast->GetThumbPosition() / 50.0;
	std::stringstream str;
	str << "Kontrast: " << contrast;
	stContrast->SetLabel(str.str());
}

void AOFrame::sbGamma_Scroll(wxScrollEvent& e) {
	// Uaktualnij i wyœwietl wartoœæ poziomu korekcji gamma
	gamma = sbGamma->GetThumbPosition() / 100.0 + 0.5;
	std::stringstream str;
	str << "Korekcja gamma: " << gamma;
	stGamma->SetLabel(str.str());
}

void AOFrame::btApply_Click(wxCommandEvent& e) {
	// Zastosuj zmiany jasnoœci, kontrastu i korekcji gamma
	if (isLoad != 1) return;
	copyImg = mainImg.Copy();
	unsigned char* pixels = copyImg.GetData();
	setBrightness(pixels, copyImg.GetWidth(), copyImg.GetHeight(), brightness);
	setContrast(pixels, copyImg.GetWidth(), copyImg.GetHeight(), contrast);
	setGamma(pixels, copyImg.GetWidth(), copyImg.GetHeight(), gamma);
	if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
}

void AOFrame::btHistogram_Click(wxCommandEvent& e) {
	// Jeœli okno histogramu jest zamkniête, utwórz i wyœwietl je
	if (isLoad != 1) return;
	if (*isHist) return;
	histFrame = new HistFrame();
	*isHist = true;
	histFrame->setPointer(isHist);
	histFrame->Show(true);

	// Wydaj rozkaz wygenerowania histogramu
	unsigned char* pixels = copyImg.GetData();
	histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
}

void AOFrame::btRestore_Click(wxCommandEvent& e) {
	// Przywróæ oryginalny obraz oraz domyœlne ustawienia
	if (isLoad != 1) return;
	sbBrightness->SetThumbPosition(50);
	sbContrast->SetThumbPosition(50);
	sbGamma->SetThumbPosition(50);
	wxScrollEvent scrollEv;
	sbBrightness_Scroll(scrollEv);
	sbContrast_Scroll(scrollEv);
	sbGamma_Scroll(scrollEv);
	copyImg = mainImg.Copy();
	unsigned char* pixels = copyImg.GetData();
	if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
}

void AOFrame::btNormHist_Click(wxCommandEvent& e) {
	// Rozci¹gnij histogram i uaktualnij go
	if (isLoad != 1) return;
	unsigned char* pixels = copyImg.GetData();
	normalizeHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
	if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
}

void AOFrame::btEqualHist_Click(wxCommandEvent& e) {
	// Wyrównaj histogram i uaktualnij go
	if (isLoad != 1) return;
	unsigned char* pixels = copyImg.GetData();
	equalHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
	if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
}

void AOFrame::btMultImage_Click(wxCommandEvent& e) {
	// Jesli okno do przemna¿ania/przeplatania obrazów jest zamkniête, utwórz i wyœwietl je
	if (isLoad != 1) return;
	if (*isMult) return;
	multFrame = new MultFrame();
	*isMult = 1;
	multFrame->setPointer(isMult, &copyImg);
	multFrame->Show(true);
}

void AOFrame::btInterImage_Click(wxCommandEvent& e) {
	// Jesli okno do przemna¿ania/przeplatania obrazów jest zamkniête, utwórz i wyœwietl je
	if (isLoad != 1) return;
	if (*isMult) return;
	multFrame = new MultFrame();
	*isMult = 2;
	multFrame->setPointer(isMult, &copyImg);
	multFrame->Show(true);
}

void AOFrame::mainPanel_Update(wxUpdateUIEvent& e) {
	// Jeœli dokonana i zaakceptowana zosta³a zmiana w oknie przemna¿ania/przeplatania, zastosuj j¹ do g³ównego okna
	if (*isMult == 3) {
		copyImg = multFrame->getResult();
		multFrame->Close();
		unsigned char* pixels = copyImg.GetData();
		if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
	}

	// Wczytaj obraz jeœli trzeba
	if (isLoad == 2) {
		mainImg.LoadFile(filename);
		imgWidth = mainImg.GetWidth();
		imgHeight = mainImg.GetHeight();
		unsigned char* pixels = mainImg.GetData();
		// Zmieñ obraz na czarno - bia³y
		grayScale(pixels, imgWidth, imgHeight);
		copyImg = mainImg.Copy();
		pixels = copyImg.GetData();
		if (*isHist) histFrame->drawHistogram(pixels, copyImg.GetWidth(), copyImg.GetHeight());
		isLoad = 1;
	}

	// Zapisz obraz jeœli trzeba
	if (isSave) {
		copyImg.SaveFile(outFilename, wxBITMAP_TYPE_JPEG);
		isSave = false;
	}

	// WxClientDC i wxBufferedDC s³u¿¹ do rysowania i wyœwietlania elementów na panelu
	wxClientDC myOtherDC(mainPanel);
	wxBufferedDC myDC(&myOtherDC);
	myDC.Clear();

	// Uzyskaj wymiary panelu (szerokoœæ, wysokoœæ, x œrodka, y œrodka)
	int width, height;
	float x, y;
	mainPanel->GetClientSize(&width, &height);
	x = width / 2.;
	y = height / 2.;

	// Jeœli jest ju¿ jakiœ obraz wczytany
	if (isLoad == 1) {
		wxImage curImg = copyImg.Copy();
		// Dostosuj rozmiar obrazu do wielkoœci okna (tak by zajmowa³ mo¿liwie najwiêksz¹ przestrzeñ z zachowaniem proporcji)
		fitInWindow(curImg, width, height);
		mainBMP = wxBitmap(curImg);
		// Wyœwietl obraz
		myDC.DrawBitmap(mainBMP, x - curImg.GetWidth()/2.0, y - curImg.GetHeight()/2.0);
	}
}