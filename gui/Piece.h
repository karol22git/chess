#pragma once
#include <wx/wx.h>

enum PieceType {
    Pawn = 1,
    Knight,
    Bishop,
    Rook,
    Queen,
    King = 6
};

enum PieceColour {
    white = 1,
    black  = 2
};

class Piece {
    private:
        wxBitmap icon;
        int position[2];
        PieceType type;
        PieceColour pColour;
        bool lock = false;
        bool moved = false;
        bool kill = false;
    public:
        Piece(wxBitmap icon,int position[2],PieceType type,PieceColour p);
        virtual ~Piece(){};
        wxBitmap GetBitmap();
        int GetX();
        int GetY();
        bool isLock();
        void Lock();
        void Unlock();
        void SetPosition(int x, int y);
        PieceColour GetColour();
        PieceType GetPieceType();
        bool WasMoved();
        void FirstMove();
        void Kill();
        bool isKilled();
        //virtual bool IsLegalMove(int destination[2])=0;
};