#include "DrawDialog.h"


DrawDialog::DrawDialog(wxString text,wxWindow *parent) : wxDialog(parent,wxID_ANY,"Game Over",wxDefaultPosition,wxDefaultSize) {
    sText = new wxStaticText(this,wxID_ANY,text);
    acceptButton = new wxButton(this,wxID_OK,"Accept");
    declineButton = new wxButton(this,wxID_CANCEL,"Decline");

    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    bottomSizer->Add(acceptButton,1,wxALL | wxALIGN_CENTER,10);
    bottomSizer->AddStretchSpacer();
    bottomSizer->Add(declineButton,1,wxALL | wxALIGN_CENTER,10);

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(sText,1,wxALL | wxALIGN_CENTER,10);

    wxBoxSizer *generalSizer = new wxBoxSizer(wxVERTICAL);
    generalSizer->Add(topSizer);
    generalSizer->Add(bottomSizer);
    SetSizerAndFit(generalSizer);
}