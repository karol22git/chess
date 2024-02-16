#include "Piece.h"

Piece::Piece(wxBitmap icon, int position[2],PieceType type,PieceColour p) {
    this->icon = icon;
    this->position[0] = position[0];
    this->position[1] = position[1];
    this->type = type;
    this->pColour = p;
}


wxBitmap Piece::GetBitmap() {
    return this->icon;
}

int Piece::GetX() {
    return position[0];
}

int Piece::GetY() {
    return position[1];
}


void Piece::Lock() {
    this->lock=true;
}

void Piece::Unlock() {
    this->lock = false;
}

bool Piece::isLock() {
    return this->lock;
}

void Piece::SetPosition(int x, int y) {
    this->position[0] = x;
    this->position[1] = y;
}

PieceColour Piece::GetColour() {
    return this->pColour;
}

PieceType Piece::GetPieceType() {
    return this->type;
}

bool Piece::WasMoved() {
    return moved;
}

void Piece::FirstMove() {
    this->moved=true;
}

void Piece::Kill() {
    this->kill  = true;
}

bool Piece::isKilled() {
    return this->kill;
}