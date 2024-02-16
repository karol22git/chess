#pragma once
#include <wx/wx.h>
#include <list>

class Piece;
class Moderator;
struct field;
struct pair {
    int x;
    int y;
};
class MovementAnalyzer {
    private:
        Moderator* moderator;
        std::list<struct pair> blockedCoordinates;
        std::list<Piece*> piecesThatAttackKing;
        std::list<struct pair> possibleKingMoves; 
        std::list<struct pair> emptyFields;

    public:
        MovementAnalyzer(Moderator *m);
        bool isMoveLegal(Piece* pieceToMove, int i, int j);
        bool isMoveCorrect(Piece* pieceToMove, int i, int j);
        bool isMoveGenerallyPossible(Piece *pieceToMove, int i, int j);
        bool isPawnAttack(Piece* piece, int i, int j);
        bool isLegalMoveForPawn(Piece* pieceToMove, int i, int j);
        bool isAttack(Piece* pieceToMove, int i, int j);
        bool isLegalMoveForKnight(Piece* pieceToMove, int i, int j);
        bool isKnightAttack(Piece* pieceToMove, int i, int j);
        bool isLegalMoveForBishop(Piece* pieceToMove, int i, int j,int ifAttack);
        bool isBishopAttack(Piece *pieceToMove, int i, int j);
        bool isLegalMoveForRook(Piece* pieceToMove, int i, int j);
        bool isRookAttack(Piece* pieceToMove, int i, int j);
        bool isLegalMoveForQueen(Piece* pieceToMove, int i, int j);
        bool isQueenAttack(Piece* pieceToMove, int i, int j);
        bool isKingMove(Piece* pieceToMove, int i, int j);
        bool isKingAttack(Piece* pieceToMove, int i, int j);
        bool isAttackingKingAfterMove(Piece* PieceToMove,int i, int j);
        bool isEnemyKingInDangerAfterMove(Piece* pieceToMove);
        void GetKingCoordinates(Piece* pieceToMove,int *x,int *y);
        bool isDiagonalEmpty(int kingx,int kingy,int piecex,int piecey);
        bool isVerticalLineEmpty(int y1, int y2, int x);
        bool isHorizontalLineEmpty(int x1, int x2, int y);
        bool LookForCheckFromKnight(Piece* pieceToMove);
        bool LookForCheckFromPawn(Piece* pieceToMove);
        void inline MarkFieldAsBlocked(struct field fieldToadd);
        bool isCheckMate(Piece* piece);
        bool CanKingEvenMove(Piece* pieceToMove);
        void BlockVerticalLine(int y1,int y2, int x);
        void BlockHorizontalLine(int x1, int x2,int y);
        void BlockDiagonalLine(int x1, int y1, int x2, int y2);
        //void LookForPossibleMovesForKing(Piece* piece);
        void GeneratePossibleMovesForKing(Piece* piece);
        bool isLegalCoordiantes(int i, int j);
        void ReadPossibleMovesForKing();
        Piece* GetBlackKing();
        Piece* GetWhiteKing();
        void ReadBlockedFields();
        bool CanKingAttackThisField(Piece* king, int i, int j);
        bool isPieceCovered(Piece* piece);
        void EmptyFieldsAroundKing(Piece* piece);
        void BlockField(int i, int j);
        bool isPawnCoverField(Piece *pawn, int i, int j);
        bool isClassicPawnAttack(Piece *pawn, int i, int j);
        void Reset();


};

