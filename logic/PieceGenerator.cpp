#include "PieceGenerator.h"


void PieceGenerator::GeneratePieces() {
    GenerateWhitePieces();
    GenerateBlackPieces();
    return;
}

void PieceGenerator::GenerateWhitePieces() {
    GenerateWhitePawns();
    GenerateWhiteKnights();
    GenerateWhiteBishops();
    GenerateWhiteRooks();
    GenerateWhiteQueen();
    GenerateWhiteKing();
    return;
}

void PieceGenerator::GenerateBlackPieces() {
    GenerateBlackPawns();
    GenerateBlackKnights();
    GenerateBlackBishops();
    GenerateBlackRooks();
    GenerateBlackQueen();
    GenerateBlackKing();
    return;
}

void PieceGenerator::GenerateWhitePawns() {
    wxBitmap image;
    image.LoadFile("../images/white_pawn.svg.png",wxBITMAP_TYPE_ANY);
    for (int i = 0 ; i < 8 ; i++) {
        int pos[2]  = {i,6};
        Piece *white_pawn = new Piece(image,pos,PieceType(1),PieceColour(1));
        whitePiecesList.push_back(white_pawn);
    }
    return;
}

void PieceGenerator::GenerateWhiteKnights() {
    wxBitmap image;
    image.LoadFile("../images/white_knight.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2]  = {1,7};
    int posB[2] = {6,7};
    Piece *white_knightA = new Piece(image,posA,PieceType(2),PieceColour(1));
    Piece *white_knightB = new Piece(image,posB,PieceType(2),PieceColour(1));
    whitePiecesList.push_back(white_knightA);
    whitePiecesList.push_back(white_knightB);
    return;
}

void PieceGenerator::GenerateWhiteBishops() {
    wxBitmap image;
    image.LoadFile("../images/white_bishop.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2]  = {2,7};
    int posB[2] = {5,7};
    Piece *white_bishopA = new Piece(image,posA,PieceType(3),PieceColour(1));
    Piece *white_bishopB = new Piece(image,posB,PieceType(3),PieceColour(1));
    whitePiecesList.push_back(white_bishopA);
    whitePiecesList.push_back(white_bishopB);
    return;
}

void PieceGenerator::GenerateWhiteRooks() {
    wxBitmap image;
    image.LoadFile("../images/white_rook.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2] = {0,7};
    int posB[2] = {7,7};
    Piece *white_rookA = new Piece(image,posA,PieceType(4),PieceColour(1));
    Piece *white_rookB = new Piece(image,posB,PieceType(4),PieceColour(1));
    whitePiecesList.push_back(white_rookA);
    whitePiecesList.push_back(white_rookB);
    return;
}

void PieceGenerator::GenerateWhiteQueen() {
    wxBitmap image;
    image.LoadFile("../images/white_queen.svg.png",wxBITMAP_TYPE_ANY);
    int pos[2]  = {3,7};
    Piece *white_queen = new Piece(image,pos,PieceType(5),PieceColour(1));
    whitePiecesList.push_back(white_queen);
    return;
}

void PieceGenerator::GenerateWhiteKing() {
    wxBitmap image;
    image.LoadFile("../images/white_king.svg.png",wxBITMAP_TYPE_ANY);
    int pos[2] = {4,7};
    Piece *white_king = new Piece(image,pos,PieceType(6),PieceColour(1));
    whitePiecesList.push_back(white_king);
    return;
}

void PieceGenerator::GenerateBlackPawns() {
    wxBitmap image;
    image.LoadFile("../images/black_pawn.svg.png",wxBITMAP_TYPE_ANY);
    for (int i = 0 ; i < 8 ; i++) {
        int pos[2]  = {i,1};
        Piece *black_pawn = new Piece(image,pos,PieceType(1),PieceColour(2));
        blackPiecesList.push_back(black_pawn);
    }
    return;
}

void PieceGenerator::GenerateBlackKnights() {
    wxBitmap image;
    image.LoadFile("../images/black_knight.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2]  = {1,0};
    int posB[2] = {6,0};
    Piece *black_knightA = new Piece(image,posA,PieceType(2),PieceColour(2));
    Piece *black_knightB = new Piece(image,posB,PieceType(2),PieceColour(2));
    blackPiecesList.push_back(black_knightA);
    blackPiecesList.push_back(black_knightB);
    return;
}

void PieceGenerator::GenerateBlackBishops() {
    wxBitmap image;
    image.LoadFile("../images/black_bishop.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2]  = {2,0};
    int posB[2] = {5,0};
    Piece *black_bishopA = new Piece(image,posA,PieceType(3),PieceColour(2));
    Piece *black_bishopB = new Piece(image,posB,PieceType(3),PieceColour(2));
    blackPiecesList.push_back(black_bishopA);
    blackPiecesList.push_back(black_bishopB);
    return;
}

void PieceGenerator::GenerateBlackRooks() {
    wxBitmap image;
    image.LoadFile("../images/black_rook.svg.png",wxBITMAP_TYPE_ANY);
    int posA[2] = {0,0};
    int posB[2] = {7,0};
    Piece *black_rookA = new Piece(image,posA,PieceType(4),PieceColour(2));
    Piece *black_rookB = new Piece(image,posB,PieceType(4),PieceColour(2));
    blackPiecesList.push_back(black_rookA);
    blackPiecesList.push_back(black_rookB);
    return;
}

void PieceGenerator::GenerateBlackQueen() {
    wxBitmap image;
    image.LoadFile("../images/black_queen.svg.png",wxBITMAP_TYPE_ANY);
    int pos[2]  = {3,0};
    Piece *black_queen = new Piece(image,pos,PieceType(5),PieceColour(2));
    blackPiecesList.push_back(black_queen);
    return;
}

void PieceGenerator::GenerateBlackKing() {
    wxBitmap image;
    image.LoadFile("../images/black_king.svg.png",wxBITMAP_TYPE_ANY);
    int pos[2] = {4,0};
    Piece *black_king = new Piece(image,pos,PieceType(6),PieceColour(2));
    blackPiecesList.push_back(black_king);
    return;
}


PieceGenerator::PieceGenerator() {
    
}

std::list<Piece*> PieceGenerator::GetBlackPieces() {
    return blackPiecesList;
}

std::list<Piece*> PieceGenerator::GetWhitePieces() {
    return whitePiecesList;
}