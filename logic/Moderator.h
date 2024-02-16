#pragma once
#include "../gui/Piece.h"
#include "../gui/DrawingPanel.h"
#include "../gui/GraveyardPanel.h"
#include "../gui/EndGameDialog.h"
#include "../gui/DrawDialog.h"
#include "PieceGenerator.h"
#include <list>

enum class Tour {
    white =1,
    black = 2
};

struct Player {
    std::list<Piece*> piececsList;
    DrawingPanel* panel;
    Tour playerColour;
};

enum  MoveType{
    NormalMove = 1,
    Attack = 2,
    IllegalMove = 3
};
class MovementAnalyzer;
class ChessFrame;
class Moderator {
    private:
        std::list<Piece*> graveyardPieceList;
        GraveyardPanel* gPanel;
        PieceColour tour = PieceColour::white;
        PieceGenerator *pGenerator;
        MovementAnalyzer *mAnalyzer;
        struct Player whitePlayer,blackPlayer;
        ChessFrame *frame;
        bool check = false;
    public:
        Moderator(DrawingPanel *whitePanel,DrawingPanel *blackPanel,GraveyardPanel* gyPanel);
        Moderator();
        virtual ~Moderator(){};
        void ProvidePieces();
        void Update();
        void UpdateBoard(PieceColour t, int i, int j);
        void NextTour();
        void StartGame();
        PieceColour WhoseTour();
        MoveType CheckMove(Piece* pieceToMove, int i, int j);
        void UpdateBoardWithPiece(Piece* p,int i, int j);
        void KillPiece(Piece* pieceToKill);
        void Check(Piece* pieceToMove);
        void EndGame();
        void SetFrame(ChessFrame *f);
        void NewGame();
        void Surrender();
        void Draw();
        bool isCheck();
        void CheckOn();
        void CheckOff();
        friend class MovementAnalyzer;
}; 