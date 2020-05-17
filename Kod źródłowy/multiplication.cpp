#include "multiplication.h"
#include "operations.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 400

MultFrame::MultFrame() : wxFrame(NULL, wxID_ANY, "Wczytaj drugi obraz", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer2 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainSizer);
	this->SetAutoLayout(true);
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(4, 4), wxSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	mainSizer->Add(mainPanel, 1, wxALIGN_LEFT | wxEXPAND | wxALL, 5);
	mainSizer->Add(mainSizer2, 0, wxALIGN_TOP | wxALL, 5);

	btLoad = new wxButton(this, wxID_ANY, _("Wczytaj JPG"), wxPoint(10, 0), wxSize(140, 25), 0, wxDefaultValidator, _("btLoad"));
	sbContrib = new wxScrollBar(this, wxID_ANY, wxPoint(10, 0), wxSize(140, 25), wxSB_HORIZONTAL, wxDefaultValidator, _("sbContrib"));
	stContrib = new wxStaticText(this, wxID_ANY, "Udzia³ nowego obrazu: 0.5", wxPoint(10, 0), wxSize(220, 25));
	stContrib2 = new wxStaticText(this, wxID_ANY, "Udzia³ pierwotnego obrazu: 0.5", wxPoint(10, 0), wxSize(220, 25));
	btApply = new wxButton(this, wxID_ANY, _("Zastosuj"), wxPoint(10, 0), wxSize(140, 25), 0, wxDefaultValidator, _("btApply"));

	Layout();
	GetSizer()->SetSizeHints(this);
	Center();

	sbContrib->SetScrollbar(50, 0, 100, 10);

	mainSizer2->Add(btLoad, 0, wxALIGN_CENTER, 5);
	mainSizer2->Add(btApply, 0, wxALIGN_CENTER | wxALL, 5);

	mainPanel->Bind(wxEVT_UPDATE_UI, &MultFrame::mainPanel_Update, this);
	Bind(wxEVT_CLOSE_WINDOW, &MultFrame::onClose, this);
	btLoad->Bind(wxEVT_BUTTON, &MultFrame::btLoad_Click, this);
	sbContrib->Bind(wxEVT_SCROLL_CHANGED, &MultFrame::sbContrib_Scroll, this);
	btApply->Bind(wxEVT_BUTTON, &MultFrame::btApply_Click, this);

	dialLoad = new wxFileDialog(this, _("Podaj sciezke"), _(""), _(""), _("*"), wxFD_OPEN);
	isLoad = 0;
	contribution = 0.5;
}

void MultFrame::onClose(wxCloseEvent& e) { *isMult = 0; Destroy(); }

void MultFrame::setPointer(short* ptr, wxImage* _mainImg) {
	isMult = ptr;
	mainImg = _mainImg->Copy();
	copyImg = mainImg.Copy();
	if (*isMult == 2) {
		stContrib->SetLabel("Udzia³ nowego obrazu: 0.5");
		stContrib2->SetLabel("Udzia³ pierwotnego obrazu : 0.5");
		mainSizer2->Add(sbContrib, 0, wxALIGN_CENTER | wxALL, 5);
		mainSizer2->Add(stContrib, 0, wxALIGN_CENTER, 5);
		mainSizer2->Add(stContrib2, 0, wxALIGN_CENTER, 5);
	}
	if (*isMult == 1)
		stContrib->SetLabel("Udzia³ nowego obrazu: 0.5");
		stContrib2->SetLabel("Udzia³ pierwotnego obrazu: 0.5");
	fitInWindow(copyImg, WINDOW_WIDTH, WINDOW_HEIGHT);
}

wxImage MultFrame::getResult() {
	return copyImg;
}

void MultFrame::btLoad_Click(wxCommandEvent& e) {
	dialLoad->SetWildcard("Obraz JPG (*.jpg)|*.jpg");
	if (dialLoad->ShowModal() == wxID_OK) {
		filename = dialLoad->GetPath();
		isLoad = 2;
	}
}

void MultFrame::sbContrib_Scroll(wxScrollEvent& e) {
	contribution = sbContrib->GetThumbPosition() / 100.0;
	std::stringstream str;
	str << "Udzia³ nowego obrazu: " << contribution;
	stContrib->SetLabel(str.str());
	std::stringstream str2;
	str2 << "Udzia³ pierwotnego obrazu: " << (1.0 - contribution);
	stContrib2->SetLabel(str2.str());
}

void MultFrame::btApply_Click(wxCommandEvent& e) {
	if (isLoad != 1) return;
	*isMult = 3;
}

void MultFrame::mainPanel_Update(wxUpdateUIEvent& e) {
	wxClientDC myOtherDC(mainPanel);
	wxBufferedDC myDC(&myOtherDC);
	myDC.Clear();
	int width, height;
	float x, y;
	mainPanel->GetClientSize(&width, &height);
	x = width / 2.;
	y = height / 2.;

	if (isLoad == 2) {
		bonusImg.LoadFile(filename);
		bonusImg.Rescale(mainImg.GetWidth(), mainImg.GetHeight());
		unsigned char* pixels = bonusImg.GetData();
		grayScale(pixels, bonusImg.GetWidth(), bonusImg.GetHeight());
		isLoad = 1;
	}

	if (isLoad == 1) {
		copyImg = mainImg.Copy();
		unsigned char* pixels = copyImg.GetData();
		unsigned char* bonusPixels = bonusImg.GetData();
		if (*isMult == 1) multiplicate(pixels, bonusPixels, copyImg.GetWidth(), copyImg.GetHeight());
		if (*isMult == 2) interlace(pixels, bonusPixels, copyImg.GetWidth(), copyImg.GetHeight(), contribution);
		wxImage curImg = copyImg.Copy();
		fitInWindow(curImg, width, height);
		mainBMP = wxBitmap(curImg);
		myDC.DrawBitmap(mainBMP, x - curImg.GetWidth() / 2.0, y - curImg.GetHeight() / 2.0);
	}
}