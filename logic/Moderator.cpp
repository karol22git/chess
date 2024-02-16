#include "Moderator.h"
#include "../gui/ChessFrame.h"
#include "MovementAnalyzer.h"
Moderator::Moderator(DrawingPanel *whitePanel,DrawingPanel *blackPanel, GraveyardPanel *gyPanel) {
    whitePlayer.panel = whitePanel;
    blackPlayer.panel = blackPanel;
    
    gPanel  = gyPanel;

    whitePlayer.playerColour = Tour::white;
    blackPlayer.playerColour = Tour::black;

    pGenerator = new PieceGenerator();
    pGenerator->GeneratePieces();
    mAnalyzer = new MovementAnalyzer(this);

    whitePlayer.piececsList = pGenerator->GetWhitePieces();
    blackPlayer.piececsList = pGenerator->GetBlackPieces();

    ProvidePieces();

}

Moderator::Moderator() {
}


void Moderator::ProvidePieces() {
    whitePlayer.panel->SetPieces(&whitePlayer.piececsList,&blackPlayer.piececsList);
    blackPlayer.panel->SetPieces(&whitePlayer.piececsList,&blackPlayer.piececsList);
    return;
}

void Moderator::Update() {
    whitePlayer.panel->Refresh();
    blackPlayer.panel->Refresh();
    return;
}

void Moderator::UpdateBoard(PieceColour t, int i, int j) {
        whitePlayer.panel->UpdateField(i,j);
        blackPlayer.panel->UpdateField(i,j);
}

void Moderator::UpdateBoardWithPiece(Piece* p,int i, int j) {
    whitePlayer.panel->MovePiece(p,i,j);
    blackPlayer.panel->MovePiece(p,i,j);
}

void Moderator::NextTour() {
    CheckOff();
    if(tour == PieceColour::white) {
        tour = PieceColour::black;
        whitePlayer.panel->Lock();
        blackPlayer.panel->Unlock();
        frame->SetStatusText("Blacks tour!");
    }
    else {
        tour = PieceColour::white;
        whitePlayer.panel->Unlock();
        blackPlayer.panel->Lock();
        frame->SetStatusText("Whites turn!");
    }
}

PieceColour Moderator::WhoseTour() {
    return tour;
}

void Moderator::StartGame() {
    whitePlayer.panel->Unlock();
    blackPlayer.panel->Lock();
}
MoveType Moderator::CheckMove(Piece* pieceToMove, int i, int j) {
    MoveType result = MoveType::IllegalMove;
    if(mAnalyzer->isMoveLegal(pieceToMove,i,j)) {
        result = MoveType::NormalMove;
    }
    else {
        result = MoveType::IllegalMove;
    }
    if(mAnalyzer->isAttack(pieceToMove,i,j)) {
        result = MoveType::Attack;
    }
    return result;
}

void Moderator::KillPiece(Piece* pieceToKill) {
    pieceToKill->Kill();
    whitePlayer.piececsList.remove(pieceToKill);
    blackPlayer.piececsList.remove(pieceToKill);
    gPanel->AddPieceToList(pieceToKill);
    gPanel->Refresh();
}

void Moderator::Check(Piece* pieceToMove) {
    if(mAnalyzer->isEnemyKingInDangerAfterMove(pieceToMove)) {
        CheckOn();
        mAnalyzer->ReadPossibleMovesForKing();
        if(mAnalyzer->isCheckMate(pieceToMove)) {
            //std::cout<<"Game over"<<std::endl;
            EndGame();
        }
    }
}

void Moderator::SetFrame(ChessFrame *f) {
    this->frame= f;
}
void Moderator::EndGame() {
    wxString victorious;
    if(tour == PieceColour::white) {
        victorious = "Black is victorious";
    }
    else {
        victorious = "White is victorious";
    }
    if(whitePlayer.panel->HasCapture()) {
        whitePlayer.panel->ReleaseMouse();
    }
    if(blackPlayer.panel->HasCapture()){
        blackPlayer.panel->ReleaseMouse();
    }
    EndGameDialog *egDialog = new EndGameDialog(victorious,frame);
    if(egDialog->ShowModal()==wxID_OK) {
        NewGame();
    }
    else {
        frame->Destroy();
    }
}

void Moderator::NewGame() {
    gPanel->FreeList();
    graveyardPieceList.clear();
    delete pGenerator;
    pGenerator = new PieceGenerator();

    whitePlayer.panel->GenerateBoard();
    blackPlayer.panel->GenerateBoard();
    blackPlayer.panel->Flip();
    pGenerator->GeneratePieces();
    mAnalyzer = new MovementAnalyzer(this);

    whitePlayer.piececsList = pGenerator->GetWhitePieces();
    blackPlayer.piececsList = pGenerator->GetBlackPieces();

    ProvidePieces();

    whitePlayer.panel->Refresh();
    whitePlayer.panel->Unlock();

    blackPlayer.panel->Refresh();
    blackPlayer.panel->Lock();

    tour = PieceColour::white;
}

void Moderator::Draw() {
    wxString message;
       if(tour == PieceColour::white) {
        message = "White player offers draw. Do You accept?";
    }
    else {
        message = "Black player offers draw. Do You accept?";
    }
    DrawDialog *dDialog = new DrawDialog(message,frame);
    if(dDialog->ShowModal()==wxID_OK) {
    EndGameDialog *egDialog = new EndGameDialog("Draw!",frame);
    if(egDialog->ShowModal()==wxID_OK) {
        NewGame();
    }
    else {
        frame->Destroy();
    }
    }
    else {
        
    }
}

void Moderator::Surrender() {  
    wxString victorious ;
    if(tour == PieceColour::white) {
        victorious = "White player has gave up, Black is victorious!";
    }
    else {
        victorious = "Black player has gave up, White is victorious!";
    }
    EndGameDialog *egDialog = new EndGameDialog(victorious,frame);
    if(egDialog->ShowModal()==wxID_OK) {
        NewGame();
    }
    else {
        frame->Destroy();
    }
}

bool Moderator::isCheck() {
    return check;
}

void Moderator::CheckOn() {
    check = true;
}

void Moderator::CheckOff() {
    mAnalyzer->Reset();
    check = false;
}