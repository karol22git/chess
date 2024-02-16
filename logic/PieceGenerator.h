#pragma once
#include <wx/wx.h>
#include <list>
#include "../gui/Piece.h"

class PieceGenerator {
    private:
        std::list<Piece*> whitePiecesList;
        std::list<Piece*> blackPiecesList;
    public:
        PieceGenerator();
        void GeneratePieces();
        void GenerateWhitePieces();
        void GenerateBlackPieces();
        void GenerateWhitePawns();
        void GenerateWhiteKnights();
        void GenerateWhiteBishops();
        void GenerateWhiteRooks();
        void GenerateWhiteQueen();
        void GenerateWhiteKing();
        void GenerateBlackPawns();
        void GenerateBlackKnights();
        void GenerateBlackBishops();
        void GenerateBlackRooks();
        void GenerateBlackQueen();
        void GenerateBlackKing();
        std::list<Piece*> GetWhitePieces();
        std::list<Piece*> GetBlackPieces();
};