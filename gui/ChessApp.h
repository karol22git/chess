#pragma once
#include <wx/wx.h>
#include <wx/display.h>
#include "../logic/Moderator.h"

class ChessApp : public wxApp {
  private:
    Moderator *gameModerator;
  public:
    bool OnInit() override;
};
