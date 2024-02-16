#include "DrawingPanel.h"
#include "../logic/Moderator.h"
DrawingPanel::DrawingPanel(wxWindow *parent,wxSize size) : wxPanel(parent,wxID_ANY,wxDefaultPosition, size) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    GenerateBoard();
    this->Bind(wxEVT_PAINT,&DrawingPanel::OnPaint,this);
    this->Bind(wxEVT_LEFT_DOWN,&DrawingPanel::MouseLeftSingleClick,this);
    this->Bind(wxEVT_LEFT_UP,&DrawingPanel::MouseLeftUp,this);
    this->Bind(wxEVT_MOTION,&DrawingPanel::MouseDraggin,this);
}

void DrawingPanel::GenerateBoard() {
    for(int i = 0 ; i < boardSize ; i ++) {
        for(int j = 0 ; j < boardSize ; j ++) {
            struct field newField;
            newField.x = i;
            newField.y = j;
            newField.Rect =wxRect(i*fieldSize,j*fieldSize,fieldSize,fieldSize);
            if((i+j)%2==0) {
                newField.colour = new wxColour(*wxWHITE);
            }
            else {
                newField.colour = new wxColour(*wxBLUE);
            }
            fieldList[i][j] = newField;
        }
    }
}

void DrawingPanel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    dc.Clear();
    PaintFields(&dc);
    PaintPieces(&dc);
}

void DrawingPanel::PaintFields(wxPaintDC * dc) {
    wxBrush *brush = new wxBrush(*wxGREEN,wxBRUSHSTYLE_SOLID);
    dc->SetBrush(*brush);
    if(pMode == PaintingMode::Normal || pMode == PaintingMode::Screenshoot) {
        for(int i = 0 ; i < boardSize ; i++) {
            for(int j = 0 ; j < boardSize ; j++) {
                brush->SetColour(*fieldList[i][j].colour);
                dc->SetBrush(*brush);
                dc->DrawRectangle(fieldList[i][j].Rect);
            }
        }
    }
    else {
        wxGraphicsContext *gc  = wxGraphicsContext::Create(*dc);
        gc->DrawBitmap(screenshot,0,0,screenWidth,screenHeight);
        delete gc;
    }
}

void DrawingPanel::PaintPieces(wxPaintDC *dc) {
    wxGraphicsContext *gc  = wxGraphicsContext::Create(*dc);
    wxBrush *brush = new wxBrush(*wxWHITE,wxBRUSHSTYLE_SOLID);
    int x,y;
        if(pMode==PaintingMode::Screenshoot || pMode==PaintingMode::Normal) {
            dc->SetBrush(*brush);
            for(auto i: whitePiecesList) {
                if(!(i->isLock())&&!(i->isKilled())) {
                    x = i->GetX();
                    y = i->GetY();
                    struct field f = fieldList[x][y];
                    wxRect rectangle = f.Rect;
                    gc->DrawBitmap(i->GetBitmap(),rectangle.GetX(),rectangle.GetY(),fieldSize,fieldSize); 
                }
            }
            gc->SetBrush(wxBrush(*wxBLACK));
            for(auto i: blackPiecesList) {
                if(!(i->isLock()) &&!(i->isKilled())) {
                    x = i->GetX();
                    y = i->GetY();
                    struct field f = fieldList[x][y];
                    wxRect rectangle = f.Rect;
                    gc->DrawBitmap(i->GetBitmap(),rectangle.GetX(),rectangle.GetY(),fieldSize,fieldSize); 
                }  
            }
        }
        else {
            gc->DrawBitmap(currentPiece->GetBitmap(),movableX,movableY,fieldSize,fieldSize);
        }
    delete gc;
    }

void DrawingPanel::Flip() {
  wxAffineMatrix2D transform{};
  transform.Mirror(wxHORIZONTAL);
  transform.Translate(-400.0,0.0);
  transform.Mirror(wxVERTICAL);
  transform.Translate(0.0,-400.0);
  for(int i = 0 ; i< 8 ; i++) {
    for(int j = 0 ; j< 8 ; j++) {
      double x = fieldList[i][j].Rect.GetX() + 0.0;
      double y = fieldList[i][j].Rect.GetY() + 0.0;
      double *dx= &x;
      double *dy = &y;
      transform.TransformPoint(&x,&y);
      wxPoint *p = new wxPoint(x-fieldSize,y - fieldSize);
      fieldList[i][j].Rect.SetPosition(*p);
    }
  }
}

void DrawingPanel::SetPieces(std::list<Piece*> *whiteList, std::list<Piece*> *blackList) {
    this->whitePiecesList = *whiteList;
    this->blackPiecesList = *blackList;
    AssignPiecesToFields();
}

void DrawingPanel::AssignPiecesToFields() {
    for(auto i : whitePiecesList) {
        int x = i->GetX();
        int y = i->GetY();
        fieldList[x][y].pieceOnMe = i;
    }
    for(auto i : blackPiecesList) {
        int x = i->GetX();
        int y = i ->GetY();
        fieldList[x][y].pieceOnMe = i;
    }
}
void DrawingPanel::MouseLeftSingleClick(wxMouseEvent &event) {
    /*for(int i = 0 ; i< boardSize ; i++) {
        for(int j = 0 ; j<boardSize ; j++) {
            if(fieldList[i][j].Rect.Contains(event.GetPosition())) {
                std::cout<<i<<" "<<j<<std::endl;
            }
        }
    }*/
    if(isLock()) {
        return;
    }
    if(!event.LeftDown()) {
        return;
    }
    if(!HasCapture()) {
        CaptureMouse();
    }
    wxPoint mousePosition = event.GetPosition();
    for(int i = 0 ; i <boardSize ; i++) {
        for(int j = 0 ; j < boardSize ; j++) {
            if(FetchField(i,j,mousePosition)&& DoColorsMatch(i,j)) {                 
                    currentPiece = fieldList[i][j].pieceOnMe;
                    if(moderator->isCheck() && currentPiece->GetPieceType()!=PieceType::King) {
                        currentPiece = nullptr;
                        return;
                    }
                    previousI = i;
                    previousJ = j;
                    currentPiece->Lock();
                    SetPaintingModeTo(PaintingMode::Screenshoot);
                    Refresh();
                    Update();
                    TakeScreenshot();
                    movableX = mousePosition.x  - (fieldSize/2);
                    movableY = mousePosition.y - (fieldSize/2);
                    SetPaintingModeTo(PaintingMode::Moving);
                    Refresh();
                    Update();
                    break;
                }
            }
        }
    }


void DrawingPanel::FetchPiece(wxPoint mousePosition) {

}

Piece* DrawingPanel::FetchPiece(int i, int j) {
    if(fieldList[i][j].pieceOnMe==nullptr)  {
        return nullptr;
    }
    else {
        return fieldList[i][j].pieceOnMe;
    }
}

void inline DrawingPanel::SetPaintingModeTo(PaintingMode p) {
    pMode = p;
}
bool DrawingPanel::FetchField(int i, int j, wxPoint mousePosition) {
    if(fieldList[i][j].Rect.Contains(mousePosition)&&fieldList[i][j].pieceOnMe!=nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool DrawingPanel::DoColorsMatch(int i, int j) { 
    if(fieldList[i][j].pieceOnMe->GetColour() == moderator->WhoseTour()) {
        return true;
    }
    else {
        return false;
    }

}

void DrawingPanel::MouseLeftUp(wxMouseEvent &event) {
    if(event.LeftUp()&&currentPiece!=nullptr) {
        wxPoint point = event.GetPosition();
        for(int i = 0 ; i < boardSize ; i++) {
            for(int j = 0 ; j< boardSize ; j++) {
                if(fieldList[i][j].Rect.Contains(point)) {
                    MoveType moveType = moderator->CheckMove(currentPiece, i,j);
                    switch(moveType) {
                        case MoveType::NormalMove:
                            PieceReplacement(i,j);
                            break;
                        case MoveType::Attack:
                            moderator->KillPiece(fieldList[i][j].pieceOnMe);
                            PieceReplacement(i,j);
                            break;
                        case MoveType::IllegalMove:
                            break;
                        default:
                            break;
                    }
                if(moveType!=MoveType::IllegalMove) {
        moderator->Check(currentPiece);}
                }
            }
        }
        currentPiece->Unlock();
        SetPaintingModeTo(PaintingMode::Normal);
        moderator->Update();
        
        ResetTemporaryData();
    }
    if(HasCapture()) {
            ReleaseMouse();
        }
}

void DrawingPanel::ResetTemporaryData() {
    previousI = 0 ;
    previousJ = 0;
    movableX= 0;
    movableY=0;
    currentPiece = nullptr;
}

void DrawingPanel::MouseDraggin(wxMouseEvent &event) {
    if(event.Dragging()) {
        if(currentPiece!=nullptr) {
            SetPaintingModeTo(PaintingMode::Moving);
            wxPoint mousePosition = event.GetPosition();
            movableX = mousePosition.x  - (fieldSize/2);
            movableY = mousePosition.y - (fieldSize/2);
            Refresh();
            Update();
        }
    }
}

void DrawingPanel::TakeScreenshot() {
    wxWindowDC dcScreen(this);
    dcScreen.GetSize(&screenWidth,&screenHeight);
    screenshot = wxBitmap(screenWidth,screenHeight,-1);
    wxMemoryDC memDC;
    memDC.SelectObject(screenshot);
    memDC.Blit(0,0,screenWidth,screenHeight,&dcScreen,0,0);
    memDC.SelectObject(wxNullBitmap);
}

void DrawingPanel::SetModerator(Moderator *m) {
    moderator = m;
    return;
}

void DrawingPanel::UpdateField(int i, int j) {
    fieldList[i][j].pieceOnMe=nullptr;
}


void DrawingPanel::Lock() {
    lock = true;
}

void DrawingPanel::Unlock() {
    lock = false;
}

bool DrawingPanel::isLock() {
    return lock;
}

bool DrawingPanel::isFieldEmpty(int i, int j) {
    if(fieldList[i][j].pieceOnMe==nullptr) {
        return true;
    }
    else {
        return false;
    }
}

void DrawingPanel::MovePiece(Piece* p, int i, int j) {
    fieldList[i][j].pieceOnMe=p;
}

void inline DrawingPanel::PieceReplacement(int i, int j) {
    fieldList[i][j].pieceOnMe = currentPiece;
    fieldList[i][j].pieceOnMe->SetPosition(i,j);
    fieldList[previousI][previousJ].pieceOnMe = nullptr;
    moderator->UpdateBoardWithPiece(currentPiece,i,j);
    moderator->UpdateBoard(moderator->WhoseTour(),previousI,previousJ);
    moderator->NextTour();
    if(!currentPiece->WasMoved()) {
        currentPiece->FirstMove();
    }

}