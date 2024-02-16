#include "MovementAnalyzer.h"
#include "Moderator.h"

MovementAnalyzer::MovementAnalyzer(Moderator *m) {
    moderator = m;

}

bool MovementAnalyzer::isLegalMoveForPawn(Piece* pieceToMove, int i, int j) {
    bool result = false;
    int x,y;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(pieceToMove->GetColour() == PieceColour::white) {
        if(!pieceToMove->WasMoved() && (x==i) && (y-2)==j) {
            result = true;
        }
        else if((x==i) && (y-1)==j) {
            result = true;
        }
        else {
            result = false;
        }
    }
    else {
        if(!pieceToMove->WasMoved() && (x==i) && (y+2)==j) {
            result = true;
        }
        else if((x==i) && (y+1==j)) { 
                result = true;
            }
        else {
            result =  false;
        }
    }
    return result;
}

bool MovementAnalyzer::isPawnAttack(Piece* piece, int i, int j) {
    bool result = false;
    bool isFieldRelationsCorrect  = false;
    int x,y;
    PieceColour pColour = piece->GetColour();
    x = piece->GetX();
    y = piece->GetY();
    if(pColour == PieceColour::white) {
        if(y==j+1) {
            if(x==i-1 || x== i+1) {
                isFieldRelationsCorrect = true;
            }
            else {
                isFieldRelationsCorrect = false;
            }

        }
        else {
            isFieldRelationsCorrect = false;
        }
    }
    else {
        if(y == j-1) {
            if(x==i-1||x==i+1) {
                isFieldRelationsCorrect = true;
            }
            else {
                isFieldRelationsCorrect = false;
            }
        }
        else {
            isFieldRelationsCorrect = false;
        }

    }
    if(isFieldRelationsCorrect && !moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        Piece* pieceOnAttackedField = moderator->whitePlayer.panel->FetchPiece(i,j);
        if(pieceOnAttackedField->GetColour() == piece->GetColour()) {
            result = false;
        }
        else {
            result = true;
        }
    }
    return result;
}

bool MovementAnalyzer::isMoveCorrect(Piece* pieceToMove, int i, int j) {
    bool result = false;    
    PieceType pieceToMoveType = pieceToMove->GetPieceType();
    switch(pieceToMoveType) {
        case PieceType::Pawn:
            if(isLegalMoveForPawn(pieceToMove,i,j)) {
                result = isLegalMoveForPawn(pieceToMove,i,j);
            }
           // else if (isPawnAttack(pieceToMove,i,j)) {
          //      result = isPawnAttack(pieceToMove,i,j);
           // }
            else {
                result = false;
            }
            break;
        case PieceType::Knight:
            result = isLegalMoveForKnight(pieceToMove,i,j);
            break;
        case PieceType::Bishop:
            result = isLegalMoveForBishop(pieceToMove,i,j,0);
            break;
        case PieceType::Rook:
            result = isLegalMoveForRook(pieceToMove,i,j);
            break;
        case PieceType::Queen:
            result = isLegalMoveForQueen(pieceToMove,i,j);
            break;
        case PieceType::King:
            result = isKingMove(pieceToMove,i,j);
            break;
        default:
            result = false;
        break;
    }
    return result;
}

bool MovementAnalyzer::isAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    PieceType pType = pieceToMove->GetPieceType();
    switch (pType) {
        case PieceType::Pawn:
            result = isPawnAttack(pieceToMove,i,j);
            break;
        case PieceType::Knight:
            result = isKnightAttack(pieceToMove, i,j);
            break;
        case PieceType::Bishop:
            result = isBishopAttack(pieceToMove, i, j);
            break;
        case PieceType::Rook:
            result = isRookAttack(pieceToMove,i,j);
            break;
        case PieceType::Queen:
            result = isQueenAttack(pieceToMove, i, j);
            break;
        case PieceType::King:
            result = isKingAttack(pieceToMove, i, j);
            break;
        default:
            break;
    }
    return result;
}

bool MovementAnalyzer::isMoveGenerallyPossible(Piece *pieceToMove, int i, int j) {
    bool result;
    if (moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        result = true;
    }
    else {
        Piece* pieceOnField = moderator->whitePlayer.panel->FetchPiece(i,j);
        if(pieceToMove->GetColour()==pieceOnField->GetColour()) {
            result = false;
        }
        else {
            result = true;
        }
    }
    return result;
}

bool MovementAnalyzer::isMoveLegal(Piece* pieceToMove,int i, int j) {
    bool result = false;
    if(isMoveGenerallyPossible(pieceToMove,i,j)) {
        result = isMoveCorrect(pieceToMove,i,j);
    }
    else {
        result =  false;
    }
    return result;
}

bool MovementAnalyzer::isLegalMoveForKnight(Piece* pieceToMove, int i, int j) {
    bool result = false;
    int x,y;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(i==x+1&& j == y+2) {
        result = true;
    }
    else if(i==x-1&& j == y+2) {
        result = true;
    }
    else if(i == x-1 && j== y-2) {
        result = true;
    }
    else if(i==x+1 && j==y-2) {
        result = true;
    }
    else if(i ==x+2 && j == y+1) {
        result = true;
    }
    else if(i==x-2 && j==y+1) {
        result = true;
    }
    else if(i == x+2 && j == y-1) {
        result = true;
    }
    else if (i == x-2 && j==y-1) {
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool MovementAnalyzer::isKnightAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    if(moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        result = false;
    }
    else  {
    result =  isLegalMoveForKnight(pieceToMove,i,j);
    }
    return result;
}

bool MovementAnalyzer::isLegalMoveForBishop(Piece* pieceToMove, int i, int j,int ifAttack) {
    bool result = false;
    bool isAnyObstacle = false;
    int x,y,distance;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(std::abs(x - i)  == std::abs(y - j)) {
        distance = std::abs(i - x);
        if(x<i && y<j) {
            for(int step = 1 ; step <= distance - ifAttack ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x+step,y+step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        else if(x <i && y>j) {
            for(int step = 1 ; step <= distance - ifAttack ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x+step,y-step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        else if(x>i && y>j) {
            for(int step = 1 ; step <= distance - ifAttack; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x-step,y-step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        else {
            for(int step = 1 ; step <= distance -ifAttack; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x-step,y+step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        if(isAnyObstacle) {
            result = false;
    }
    else {
        result = true;
    }
    }
    else {
        result = false;
    }
    /*if(isAnyObstacle) {
            result = false;
    }
    else {
        result = true;
    }*/
    return result;
}

bool MovementAnalyzer::isBishopAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    if(moderator->whitePlayer.panel->isFieldEmpty(i,j) || (pieceToMove->GetX() == i && pieceToMove->GetY()==j)) {
        result = false;
    }
    else {
        result = isLegalMoveForBishop(pieceToMove, i,j,1);
    }
    return result;
}

bool MovementAnalyzer::isLegalMoveForRook(Piece* pieceToMove, int i, int j) {
    bool result = false;
    bool isAnyObstacle = false;
    int x,y,distance;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(x==i) {
        distance = std::abs(y - j);
        if(y>j) {
            for(int step = 1 ; step <= distance - 1 ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x,y-step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        else {
            for(int step = 1 ; step <= distance - 1 ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x,y+step)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
    }
    else {
        distance = std::abs(x-i);
        if(x>i) {
            for(int step = 1 ; step <= distance - 1 ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x-step,y)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
        else {
            for(int step = 1 ; step <= distance - 1 ; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x+step,y)) {
                    isAnyObstacle = true;
                    break;
                }
            }
        }
    }
    if(isAnyObstacle) {
        result = false;
    }
    else {
        result = true;
    }
    return result;
}

bool MovementAnalyzer::isRookAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    if(moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        result = false;
    }
    else {
        result = isLegalMoveForRook(pieceToMove,i,j);
    }
    return result;
}

bool MovementAnalyzer::isLegalMoveForQueen(Piece* pieceToMove, int i, int j) {
    bool result = false;
    int x, y;

    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(std::abs(x-i) == std::abs(y-j)) {
        result = isLegalMoveForBishop(pieceToMove,i,j,0);
    }
    else if (x==i || y==j) {
        result = isLegalMoveForRook(pieceToMove,i,j);

    }
    else {
        result = false;
    }
    return result;
}

bool MovementAnalyzer::isQueenAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    int x, y;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        result = false;
    }
    else {
        if(std::abs(x-i) == std::abs(y-j)) {
        result = isBishopAttack(pieceToMove,i,j);
        }
        else if (x==i || y==j) {
            result = isRookAttack(pieceToMove,i,j);
        }
        else {
            result = false;
        }   
    }
    return result;
}

bool MovementAnalyzer::isKingMove(Piece* pieceToMove, int i, int j) {
    bool result = false;
    if(moderator->isCheck()) {
        std::cout<<"t"<<std::endl;
        for(auto f: possibleKingMoves) {
            if(f.x == i && f.y ==j) {
               
                result = true;
            }
        }
        return result;
    }
    int x, y;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if((i==x+1&& y==j) || (x==i-1&&y==j) || (x==i&&j==y+1) || (x==i && j==y-1) || std::abs(x-i)==1 &&std::abs(y-j)==1) {
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool MovementAnalyzer::isKingAttack(Piece* pieceToMove, int i, int j) {
    bool result = false;
    int x, y;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    if(moderator->whitePlayer.panel->isFieldEmpty(i,j)) {
        result = false;
    }
    else {
        result = isKingMove(pieceToMove,i,j);
    }
    return result;
}
bool MovementAnalyzer::isAttackingKingAfterMove(Piece* pieceToMove, int i, int j) {
    return false;

}

bool MovementAnalyzer::isEnemyKingInDangerAfterMove(Piece* pieceToMove) {
    bool result = false;
    bool isDangerFromRook = false;
    bool isDangerFromBishop = false;
    bool isDangerFromQueen = false;
    bool isDangerFromPawn = false;
    bool isDangerFromKnight = false;
    PieceType pType = pieceToMove->GetPieceType();

    int kingX,kingY,pieceX,pieceY;
    pieceX = pieceToMove->GetX();
    pieceY = pieceToMove->GetY();
    GetKingCoordinates(pieceToMove,&kingX,&kingY);
    EmptyFieldsAroundKing(pieceToMove);
    std::list<Piece*> enemyPieces;
    if(pieceToMove->GetColour()==PieceColour::white) {
        enemyPieces = moderator->whitePlayer.piececsList;
    }
    else {
        enemyPieces = moderator->blackPlayer.piececsList;
    }

    for(auto p: enemyPieces) {
        if(!(p->isKilled())) {
        if(p->GetPieceType()==PieceType::Rook) {
            if(p->GetX() == kingX) {
                if(isVerticalLineEmpty(kingY,p->GetY(),kingX)) {
                int step;
                if(kingY<p->GetY()) {
                    step = -1;
                }
                else {
                    step = 1;
                }
                BlockVerticalLine(p->GetY(),kingY+step,kingX);
                isDangerFromRook=true;
                piecesThatAttackKing.push_back(p);}
            }
            else if(p->GetY() == kingY) {
                if(isHorizontalLineEmpty(kingX,p->GetX(),kingY)) {
                int step;
                if(kingX<p->GetX()) {
                    step = -1;
                }
                else {
                    step = 1;
                }
                BlockHorizontalLine(kingX+step,p->GetX(),kingY);
                isDangerFromRook=true;
                piecesThatAttackKing.push_back(p);}
            }
            for(auto field: emptyFields) {
            if(p->GetX() == field.x) {
                if(isVerticalLineEmpty(field.y,p->GetY(),field.x)) {
                    
                    BlockVerticalLine(p->GetY(),field.y,field.x);
                    //isDangerFromRook=true;
                    //piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            else if(p->GetY() == field.y) {
                if(isHorizontalLineEmpty(field.x,p->GetX(),field.y)) {
                    BlockHorizontalLine(field.x,p->GetX(),field.y);
                    //isDangerFromRook=true;
                    //piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
        }
        }
        else if(p->GetPieceType()==PieceType::Bishop) {
            if(std::abs(kingX - p->GetX())==std::abs(kingY -p->GetY())) {
                if(isDiagonalEmpty(kingX,kingY,p->GetX(),p->GetY())) {
                    int stepx,stepy;
                    if(kingX<p->GetX() && kingY <p->GetY()) {
                        stepx = -1;
                        stepy = -1;
                        
                    }
                    else if(kingX> p->GetX() && kingY > p->GetY()) {
                        stepx = 1;
                        stepy = 1;
                    }
                    else if(kingX>p->GetX() && kingY < p->GetY()) {
                        stepx = 1;
                        stepy = -1;
                    }
                    else {
                        stepx = -1;
                        stepy = 1;
                    }
                    BlockDiagonalLine(kingX+stepx,kingY+stepy,p->GetX(),p->GetY());
                    isDangerFromBishop = true;
                    piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            for(auto field: emptyFields) {
                if(std::abs(field.x - p->GetX()) == std::abs(field.y - p->GetY())) {
                    if(isDiagonalEmpty(field.x,field.y,p->GetX(),p->GetY())) {
                        BlockDiagonalLine(field.x,field.y,p->GetX(),p->GetY());
                    }
                }
            }
        }
        else if(p->GetPieceType()==PieceType::Queen) {
            if(p->GetX() == kingX) {
                if(isVerticalLineEmpty(kingY,p->GetY(),kingX)) {
                int step;
                if(kingY<p->GetY()) {
                    step = -1;
                }
                else {
                    step = 1;
                }
                    BlockVerticalLine(kingY + step,p->GetY(),kingX);
                    isDangerFromQueen=true;
                    piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            else if(p->GetY() == kingY) {
                if(isHorizontalLineEmpty(kingX,p->GetX(),kingY)) {
                    int step;
                if(kingX<p->GetX()) {
                    step = -1;
                }
                else {
                    step = 1;
                }
                    BlockHorizontalLine(kingX+step,p->GetX(),kingY);
                    isDangerFromQueen=true;
                    piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            else if(std::abs(kingX - p->GetX())==std::abs(kingY -p->GetY())) {
                if(isDiagonalEmpty(kingX,kingY,p->GetX(),p->GetY())) {
                    int stepx,stepy;
                    if(kingX<p->GetX() && kingY <p->GetY()) {
                        stepx = -1;
                        stepy = -1;
                        
                    }
                    else if(kingX> p->GetX() && kingY > p->GetY()) {
                        stepx = 1;
                        stepy = 1;
                    }
                    else if(kingX>p->GetX() && kingY < p->GetY()) {
                        stepx = 1;
                        stepy = -1;
                    }
                    else {
                        stepx = -1;
                        stepy = 1;
                    }
                    BlockDiagonalLine(kingX+stepx,kingY+stepy,p->GetX(),p->GetY());
                    isDangerFromQueen = true;
                    piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            for(auto field: emptyFields) {
                if(p->GetX() == field.x) {
                if(isVerticalLineEmpty(field.y,p->GetY(),field.x)) {
                    BlockVerticalLine(field.y,p->GetY(),field.x);
                    //isDangerFromQueen=true;
                   // piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            else if(p->GetY() == field.y) {
                if(isHorizontalLineEmpty(field.x,p->GetX(),field.y)) {
                    BlockHorizontalLine(field.x,p->GetX(),field.y);
                    //isDangerFromQueen=true;
                    //piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            else if(std::abs(field.x - p->GetX())==std::abs(field.y -p->GetY())) {
                if(isDiagonalEmpty(field.x,field.y,p->GetX(),p->GetY())) {
                    BlockDiagonalLine(field.x,field.y,p->GetX(),p->GetY());
                    //isDangerFromQueen = true;
                    //piecesThatAttackKing.push_back(p);
                    //break;
                }
            }
            }
        }
        else if(p->GetPieceType() == PieceType::Knight) {
            for(auto field: emptyFields) {
                if(isLegalMoveForKnight(p,field.x,field.y)) {
                    BlockField(field.x,field.y);
                }
            }
        }
        else if(p->GetPieceType() == PieceType::Pawn) {
            for(auto field: emptyFields) {
                if(isPawnCoverField(p, field.x, field.y)) {
                    BlockField(field.x,field.y);
                }
            }
        }
    }
    }
    if(pType == PieceType::Knight) {
        isDangerFromKnight = LookForCheckFromKnight(pieceToMove);
        if(isDangerFromKnight) {
        piecesThatAttackKing.push_back(pieceToMove); }
    }
    else if(pType == PieceType::Pawn) {
        isDangerFromPawn = LookForCheckFromPawn(pieceToMove);
        if(isDangerFromPawn) {
            piecesThatAttackKing.push_back(pieceToMove);
        }
    }
    if(isDangerFromBishop || isDangerFromRook || isDangerFromQueen || isDangerFromKnight || isDangerFromPawn) {
        result = true;
        ReadBlockedFields();
    }
    else {
        emptyFields.clear();
        possibleKingMoves.clear();
        blockedCoordinates.clear();
        piecesThatAttackKing.clear();
    }
    return result;
}

bool MovementAnalyzer::isDiagonalEmpty(int kingx,int kingy,int piecex,int piecey) {
    bool result = true;
    int beginningX,begginigY,endingX,endingY;
    int distance = std::abs(kingx - piecex) - 1;
        if(kingx<piecex && kingy<piecey) {
            for(int step = 1 ; step <= distance; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(kingx+step,kingy+step)) {
                    result = false;
                    break;
                }
            }
        }
        else if(kingx <piecex&& kingy>piecey) {
            for(int step = 1 ; step <= distance; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(kingx+step,kingy-step)) {
                    result = false;
                    break;
                }
            }
        }
        else if(kingx>piecex && kingy>piecey) {
            for(int step = 1 ; step <= distance; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(kingx-step,kingy-step)) {
                    result = false;
                    break;
                }
            }
        }
        else {
            for(int step = 1 ; step <= distance; ++step) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(kingx-step,kingy+step)) {
                    result = false;
                    break;
                }
            }
        }
        return result;
}

bool MovementAnalyzer::isVerticalLineEmpty(int y1, int y2, int x) {
    bool result = true;
    int beginning,ending;
    if(y1>y2) {
        beginning = y2;
        ending = y1;

    }
    else {
        beginning = y1;
        ending = y2;
    }
    int distance = ending - beginning - 1;
    for(int step = 1; step<=distance; ++step) {
        if(!moderator->whitePlayer.panel->isFieldEmpty(x,beginning+step)) {
            result = false;
            break;
        }
    }
    return result;

}

bool MovementAnalyzer::isHorizontalLineEmpty(int x1, int x2, int y) {
    bool result  = true;
    int beginning,ending;
    if(x1>x2) {
        beginning = x2;
        ending = x1;
    }
    else {
        beginning = x1;
        ending = x2;
    }
    int distance = ending - beginning-1;
    for(int step = 1; step<=distance ; ++step) {
        if(!moderator->whitePlayer.panel->isFieldEmpty(beginning+step,y)) {
            result  = false;
            break;

        }
    }
    return result;
}
void MovementAnalyzer::GetKingCoordinates(Piece* pieceToMove,int *x, int *y) {
    PieceColour pCol = pieceToMove->GetColour();
    if(pCol == PieceColour::white) {
        for(auto p : moderator->blackPlayer.piececsList) {
            if(p->GetPieceType() == PieceType::King) {
                *x = p->GetX();
                *y = p->GetY();
                break;
            }
        }
    }
    else {
        for(auto p : moderator->whitePlayer.piececsList) {
            if(p->GetPieceType() == PieceType::King) {
                *x = p->GetX();
                *y = p->GetY();
                break;
            }
        }
    }
    return;
}

bool MovementAnalyzer::LookForCheckFromKnight(Piece* pieceToMove) {
    bool result = false;
    int x,y,kingX,kingY;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    GetKingCoordinates(pieceToMove,&kingX,&kingY);
    result = isKnightAttack(pieceToMove,kingX,kingY);
    return result;
}

bool MovementAnalyzer::LookForCheckFromPawn(Piece* pieceToMove) {
    bool result = false;
    int x,y,kingX,kingY;
    x = pieceToMove->GetX();
    y = pieceToMove->GetY();
    GetKingCoordinates(pieceToMove,&kingX,&kingY);
    result = isPawnAttack(pieceToMove,kingX,kingY);
    return result;
}

void inline MovementAnalyzer::MarkFieldAsBlocked(struct field fieldToBlock) {

}

bool MovementAnalyzer::isCheckMate(Piece* piece) {
    GeneratePossibleMovesForKing(piece);
    ReadPossibleMovesForKing();
    bool result = false;
     if(possibleKingMoves.size() == 0) {
        result = true;
    }
    
    return result;
}

bool MovementAnalyzer::CanKingEvenMove(Piece* pieceToMove) {
    PieceColour pColour = pieceToMove->GetColour();
    int kingX,kingY;
    GetKingCoordinates(pieceToMove,&kingX,&kingY);
    return false;

}

void MovementAnalyzer::BlockVerticalLine(int y1, int y2,int x) {
    int beginning,ending;
    if(y1 > y2) {
        beginning = y2;
        ending = y1;
    }
    else {
        beginning = y1;
        ending = y2;
    }
    for(int step = 0; step <= ending - beginning ; ++step) {
        struct pair blockedField;
        blockedField.x = x;
        blockedField.y = beginning +step;
        blockedCoordinates.push_back(blockedField);
    }
}

void MovementAnalyzer::BlockHorizontalLine(int x1, int x2, int y) {
    int beginning,ending;
    if(x1>x2) {
        beginning = x2;
        ending = x1;
    }
    else {
        beginning = x1;
        ending = x2;
    }
    std::cout<<"beginning "<<beginning<<" "<<ending<<std::endl;
    int distance = ending - beginning;
    for(int step = 0 ; step <= distance ; ++step) {
        struct pair blockedField;
        blockedField.x = beginning + step;
        blockedField.y = y;
        blockedCoordinates.push_back(blockedField);
    }
}

void MovementAnalyzer::BlockDiagonalLine(int x1, int y1, int x2, int y2) {
    int distance = std::abs(x1-x2) - 1;
    struct pair bf;
    bf.x = x1;
    bf.y = y1;
    blockedCoordinates.push_back(bf);
    if(x1<x2 && y1<y2) {
        for(int step = 1 ; step<= distance ; ++step) {
            struct pair blockedField;
            blockedField.x = x1 +step;
            blockedField.y = y1 +step;
            blockedCoordinates.push_back(blockedField);
        }
    }
    else if(x1 > x2 && y1 > y2) {
        for(int step = 1 ; step <= distance ; ++step) {
             struct pair blockedField;
            blockedField.x = x1 +step;
            blockedField.y = y1 +step;
            blockedCoordinates.push_back(blockedField);
        }
    }
    else if(x1 < x2 && y1 > y2) {
        for(int step = 1 ; step <= distance ; ++step) {
             struct pair blockedField;
            blockedField.x = x1 +step;
            blockedField.y = y1 -step;
            blockedCoordinates.push_back(blockedField);
        }
    }
    else {
        for(int step = 1 ; step <= distance ; ++step) {
             struct pair blockedField;
            blockedField.x = x1 -step;
            blockedField.y = y1 +step;
            blockedCoordinates.push_back(blockedField);
        }
    }
}

void MovementAnalyzer::BlockField(int i, int j) {
    struct pair blockedField;
    blockedField.x = i;
    blockedField.y = j;
    blockedCoordinates.push_back(blockedField);
}
bool MovementAnalyzer::isLegalCoordiantes(int i, int j) {
    if (i>-1 && i< 8) {
        if(j>-1 && j < 8) {
            return true;
        }
    }
    return false;
}

void MovementAnalyzer::GeneratePossibleMovesForKing(Piece* piece) {
    Piece* king;
    if(piece->GetColour()==PieceColour::white) {
        king = GetBlackKing();
    }
    else {
        king = GetWhiteKing();
    }
    bool isAnyObstacle = false;
    int x,y;
    x = king->GetX();
    y = king->GetY();
    for(auto eField: emptyFields) {
        for(auto bField: blockedCoordinates) {
            if(eField.x == bField.x && eField.y == bField.y) {
                isAnyObstacle = true;
            }
        }
        if(isAnyObstacle) {
            isAnyObstacle = false;
        }
        else {
            possibleKingMoves.push_back(eField);
        }
    }
    for(int i = -1 ; i< 2 ; ++i) {
        for(int j = -1 ; j < 2 ; ++j) {
            if(isLegalCoordiantes(x + i , y + j)) {
                if(!moderator->whitePlayer.panel->isFieldEmpty(x+i,y+j)) {
                    Piece* fetchedPiece = moderator->whitePlayer.panel->FetchPiece(x+i,y+j);
                    if(!(fetchedPiece->GetColour() == king->GetColour())) {
                    if(CanKingAttackThisField(king,x+i,y+j)) {
                        struct pair p;
                        p.x = x+i;
                        p.y= y +j;
                        possibleKingMoves.push_back(p);}
                    
                }
                else {
                }
            }}}}
}

void MovementAnalyzer::ReadPossibleMovesForKing() {
    if(possibleKingMoves.empty()) {
        std::cout<<"Brak ruchow"<<std::endl;
    }
    else {
    for(auto m: possibleKingMoves) {
        std::cout<<"Possible move "<<m.x<<" "<<m.y<<std::endl;
    }}  
}

void MovementAnalyzer::ReadBlockedFields() {
    for(auto m: blockedCoordinates) {
        std::cout<<"blocked field "<<m.x<<" "<<m.y<<std::endl;
    }
  
}
Piece* MovementAnalyzer::GetWhiteKing() {
    for(auto p: moderator->whitePlayer.piececsList) {
        if(p->GetPieceType() == PieceType::King) {
            return p;
        }
    }
    return nullptr;
}

Piece* MovementAnalyzer::GetBlackKing() {
    for(auto p: moderator->blackPlayer.piececsList) {
        if(p->GetPieceType() == PieceType::King) {
            return p;
        }
    }
    return nullptr;
}

bool MovementAnalyzer::CanKingAttackThisField(Piece* king, int i, int j) {
    bool result = false;
    Piece* fetchedPiece = moderator->whitePlayer.panel->FetchPiece(i,j);
    result = !(isPieceCovered(fetchedPiece));
    return result;

}

bool MovementAnalyzer::isPieceCovered(Piece* piece) {
    bool result = false;

    bool coverByPawn = false;
    bool coverByKnight = false;
    bool coverByBishop = false;
    bool coverByRook = false;
    bool coverByQueen = false;
    int i = piece->GetX();
    int j = piece->GetY();
    std::list<Piece*> alliedPieces;
    if(piece->GetColour() == PieceColour::white) {
        alliedPieces = moderator->whitePlayer.piececsList;
    }
    else {
        alliedPieces = moderator->blackPlayer.piececsList;
    }
    for(auto p: alliedPieces) {
        if(p->GetPieceType() == PieceType::Knight) {
            coverByKnight = isLegalMoveForKnight(p,i,j);
            
            if(coverByKnight) {
                break;
            }
        }
        else if(p->GetPieceType() == PieceType::Bishop) {
            coverByKnight = isLegalMoveForBishop(p,i,j,0);
            if(coverByKnight) {
                break;
            }
        }
        else if(p->GetPieceType() == PieceType::Rook) {
            coverByRook = isLegalMoveForRook(p,i,j);
            if(coverByRook) {
                break;
            }
        }
        else if(p->GetPieceType() == PieceType::Queen) {
            if(p->GetX()!= piece->GetX() && p->GetY()!= piece->GetY()) {
            coverByQueen = isLegalMoveForQueen(p,i,j);
            if(coverByQueen) {
                break;
            }}
        }
        else if(p->GetPieceType() == PieceType::Pawn) {
            coverByPawn = isClassicPawnAttack(p,i,j);
            if(coverByPawn) {
                break;
            }
        }
    }
    if(coverByPawn || coverByKnight || coverByBishop || coverByRook || coverByQueen) {
        result = true;
    }
    return result;
}

bool MovementAnalyzer::isClassicPawnAttack(Piece *pawn, int i, int j) {
    bool result = false;
    int step;
    int x = pawn->GetX();
    int y = pawn->GetY();
    PieceColour pColour = pawn->GetColour();
    if(pColour==PieceColour::white) {
        step = -1;
    }
    else {
        step = 1;
     }
     if( (i ==x +1 || i == x-1) && j == y+step) {
        result = true;
     }
     return result;
}
void MovementAnalyzer::EmptyFieldsAroundKing(Piece* piece) {
    Piece *king;
    PieceColour  pk = piece->GetColour();
    if(pk == PieceColour::white) {
        king = GetBlackKing();
    }
    else {
        king = GetWhiteKing();
    }
    int x = king->GetX();
    int y = king->GetY();
    for(int i = -1 ; i< 2 ; ++i) {
        for(int j = -1 ; j < 2 ; ++j) {
            if(isLegalCoordiantes(x + i, y + j)) {
                if(moderator->whitePlayer.panel->isFieldEmpty(x+i,y+j)) {
                    struct pair p;
                    p.x = x+i;
                    p.y = y+j;
                    emptyFields.push_back(p);
                }
            }
        }
    }

}


bool MovementAnalyzer::isPawnCoverField(Piece *pawn, int i, int j) {
    bool result = false;
    int step;
    if(pawn->GetColour() == PieceColour::white) {
        step = -1;
    }
    else {
        step = 1;
    }
    int x = pawn->GetX();
    int y = pawn->GetY();
    if( i == x+1 || i == x - 1) {
        if(j == y+step) {
            result = true;
        }
    }
    return result;
}

void MovementAnalyzer::Reset() {
    emptyFields.clear();
    possibleKingMoves.clear();
    blockedCoordinates.clear();
    piecesThatAttackKing.clear();
}