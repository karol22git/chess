#include "ChessFrame.h"
#include "../logic/Moderator.h"

ChessFrame::ChessFrame(const wxString &title, const wxPoint &position, const wxSize &size) : 
  wxFrame(nullptr,wxID_ANY,title,position,size,wxDEFAULT_FRAME_STYLE &  ~wxRESIZE_BORDER) {
    CreateButtons();
    CreateSizers();
    GenerateStatusBar();
    GenerateMenu();
    ArrangeTopSizer();
    ArrangeMiddleSizer();
    ArrangeBottomSizer();
    ConnectSizers();
    SetSizerAndFit(sizerForSizers);

    drawButton->Bind(wxEVT_BUTTON,&ChessFrame::DrawButtonEvent,this);
    surrenderButton->Bind(wxEVT_BUTTON,&ChessFrame::SurrenderButtonEvent,this);

}

void ChessFrame::GenerateStatusBar() {
  CreateStatusBar(1,wxSTB_DEFAULT_STYLE | wxSTB_ELLIPSIZE_END);
  SetStatusText(wxT("Whites turn!"),0);
  return;
}

void ChessFrame::GenerateMenu() {
  mainMenuBar = new wxMenuBar();
  gameMenu = new wxMenu();
  helpMenu = new wxMenu();
  mainMenuBar->Append(gameMenu,_T("&File"));
  mainMenuBar->Append(helpMenu,_T("&Help"));
  SetMenuBar(mainMenuBar);
  return;
}

void ChessFrame::CreateButtons() {
  drawButton = new wxButton(this,wxID_ANY,"Draw");
  surrenderButton = new wxButton(this,wxID_ANY,"Surrender");
  return;
}

void ChessFrame::CreateSizers() {
  sizerForSizers = new wxBoxSizer(wxVERTICAL);
  topSizer = new wxBoxSizer(wxHORIZONTAL);
  middleSizer = new wxBoxSizer(wxHORIZONTAL);
  bottomSizer_2 = new wxBoxSizer(wxHORIZONTAL);
  bottomSizer = new wxStaticBoxSizer(wxHORIZONTAL,this,"Actions");
  return;
}

void ChessFrame::ArrangeTopSizer() {
  graveyard = new wxStaticBoxSizer(wxHORIZONTAL,this,"Graveyard");
 // wxPanel *blank1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(480,60));
  gyPanel = new GraveyardPanel(this,wxSize(480,60));
  graveyard->Add(gyPanel,0,wxALL,10);
  //blank1->SetBackgroundColour(*wxCYAN);
  topSizer->AddStretchSpacer();

  topSizer->Add(graveyard,0,wxALL,5);
  topSizer->AddStretchSpacer();
  return;
}

void ChessFrame::ArrangeMiddleSizer() {
  whitePlayerPanel = new DrawingPanel(this,wxSize(400,400));
  whitePlayerPanel->SetBackgroundColour(*wxWHITE);
  blackPlayerPanel = new DrawingPanel(this,wxSize(400,400));
  blackPlayerPanel->Flip();
  blackPlayerPanel->Refresh();
  middleSizer->AddStretchSpacer();
  middleSizer->Add(whitePlayerPanel,0,wxALL,20);
  middleSizer->Add(blackPlayerPanel,0,wxALL,20);
  middleSizer->AddStretchSpacer();
  return;
}

void ChessFrame::ArrangeBottomSizer() {
  wxPanel *separatorPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(200,50));

  bottomSizer->AddStretchSpacer();
  bottomSizer->Add(drawButton,1,wxALL | wxALIGN_CENTER,10);
  bottomSizer->Add(separatorPanel,0,wxEXPAND,10);
  bottomSizer->Add(surrenderButton,1,wxALL | wxALIGN_CENTER,10);
  bottomSizer->AddStretchSpacer();

  bottomSizer_2->AddStretchSpacer();
  bottomSizer_2->Add(bottomSizer,0,wxALL | wxALIGN_CENTER,10);
  bottomSizer_2->AddStretchSpacer();
}

void ChessFrame::ConnectSizers() {
  sizerForSizers->Add(topSizer,0,wxALL,5);
  sizerForSizers->Add(middleSizer,0,wxALL,5);
  sizerForSizers->Add(bottomSizer_2,0,wxALL | wxALIGN_CENTER,5);
}

DrawingPanel* ChessFrame::GetWhitePlayerPanel() {
  return whitePlayerPanel;
}

DrawingPanel* ChessFrame::GetBlackPlayerPanel() {
  return blackPlayerPanel;
}

GraveyardPanel* ChessFrame::GetGraveyardPanel() {
  return gyPanel;
}

void ChessFrame::DrawButtonEvent(wxCommandEvent &event) {
  moderator->Draw();
}

void ChessFrame::SurrenderButtonEvent(wxCommandEvent &event) {
  moderator->Surrender();

}

void ChessFrame::SetModerator(Moderator *m) {
  moderator = m;
}