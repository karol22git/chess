#pragma once
#include <wx/wx.h>
#include "DrawingPanel.h"
#include "GraveyardPanel.h"
#include "../logic/Moderator.h"

class Moderator;
class ChessFrame : public wxFrame {
  private:
    wxBoxSizer *topSizer;
    wxBoxSizer *middleSizer;
    wxStaticBoxSizer *bottomSizer;
    wxStaticBoxSizer *graveyard;
    wxBoxSizer *sizerForSizers;
    wxBoxSizer *bottomSizer_2;
    wxButton *drawButton;
    wxButton *surrenderButton;
    wxMenuBar *mainMenuBar;
    wxMenu *gameMenu;
    wxMenu *helpMenu;
    DrawingPanel *whitePlayerPanel;
    DrawingPanel *blackPlayerPanel;
    GraveyardPanel *gyPanel;
    void GenerateStatusBar();
    void GenerateMenu();
    void CreateButtons();
    void CreateSizers();
    void ArrangeTopSizer();
    void ArrangeMiddleSizer();
    void ArrangeBottomSizer();
    void ConnectSizers();
    Moderator* moderator;
  public:
    ChessFrame(const wxString &title,const wxPoint &position, const wxSize &size);
    DrawingPanel* GetWhitePlayerPanel();
    DrawingPanel* GetBlackPlayerPanel();
    GraveyardPanel* GetGraveyardPanel();
    void DrawButtonEvent(wxCommandEvent &event);
    void SurrenderButtonEvent(wxCommandEvent &event);
    void SetModerator(Moderator *m);
};
