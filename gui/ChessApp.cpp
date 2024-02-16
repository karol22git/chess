#include "ChessApp.h"
#include "ChessFrame.h"



bool ChessApp::OnInit() {
  ChessFrame *frame = new ChessFrame("Chess",wxDefaultPosition,wxSize(1200,700));
  frame->Show(true);
  frame->Center();
  gameModerator = new Moderator(frame->GetWhitePlayerPanel(),frame->GetBlackPlayerPanel(),frame->GetGraveyardPanel());
  frame->SetModerator(gameModerator);
  gameModerator->StartGame();
  gameModerator->SetFrame(frame);
  frame->GetWhitePlayerPanel()->SetModerator(gameModerator);
  frame->GetBlackPlayerPanel()->SetModerator(gameModerator);
  
  return true;
}

