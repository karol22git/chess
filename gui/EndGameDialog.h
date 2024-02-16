#pragma once
#include <wx/wx.h>


class EndGameDialog : public wxDialog {
    private:
        const int height = 50;
        const int width = 100;
        wxString victorious;
        wxButton * quitButton;
        wxButton *newGameButton;
        wxStaticText *sText;
    public:
        EndGameDialog(wxString text,wxWindow *parent);
};