#include "EndGameDialog.h" 



EndGameDialog::EndGameDialog(wxString text,wxWindow *parent) : wxDialog(parent,wxID_ANY,"Game Over",wxDefaultPosition,wxDefaultSize) {
    sText = new wxStaticText(this,wxID_ANY,text);
    quitButton = new wxButton(this,wxID_CANCEL,"Quit game");
    newGameButton = new wxButton(this,wxID_OK,"New game");

    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    bottomSizer->Add(newGameButton,1,wxALL | wxALIGN_CENTER,10);
    bottomSizer->AddStretchSpacer();
    bottomSizer->Add(quitButton,1,wxALL | wxALIGN_CENTER,10);

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(sText,1,wxALL | wxALIGN_CENTER,10);

    wxBoxSizer *generalSizer = new wxBoxSizer(wxVERTICAL);
    generalSizer->Add(topSizer);
    generalSizer->Add(bottomSizer);
    SetSizerAndFit(generalSizer);
}
