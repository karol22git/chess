#pragma once
#include <wx/wx.h>

class DrawDialog : public wxDialog {
    private:
        const int height = 50;
        const int width = 100;
        wxString message;
        wxButton *acceptButton;
        wxButton *declineButton;
        wxStaticText *sText;
    public:
        DrawDialog(wxString text,wxWindow *parent);
};