#include "GraveyardPanel.h"

GraveyardPanel::GraveyardPanel(wxWindow *parent, wxSize size) : wxPanel(parent,wxID_ANY,wxDefaultPosition, size) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT,&GraveyardPanel::OnPaint,this);
}

void GraveyardPanel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    dc.Clear();
    PaintFields(&dc);
    PaintPieces(&dc);
}

void GraveyardPanel::PaintFields(wxPaintDC *dc) {
    wxBrush *brush = new wxBrush(*wxGREEN,wxBRUSHSTYLE_SOLID);
    dc->SetBrush(*brush);
    for(int i = 0; i < rows; i++) {
        for(int j = 0 ; j < columns ; j++) {
            if((i+j)%2 == 0 ) {
                brush->SetColour(*wxGREEN);
                dc->SetBrush(*brush);
            }
            else {
                brush->SetColour(*wxWHITE);
                dc->SetBrush(*brush);
            }
            dc->DrawRectangle(j*fieldSize,i*fieldSize,fieldSize,fieldSize);
        }

    }
}

void GraveyardPanel::PaintPieces(wxPaintDC *dc) {
    wxGraphicsContext *gc  = wxGraphicsContext::Create(*dc);
    wxBrush *brush = new wxBrush(*wxWHITE,wxBRUSHSTYLE_SOLID);
    int x, y;
    for(auto p: graveyardPieceList) {
        x = p->GetX();
        y = p->GetY();
        gc->DrawBitmap(p->GetBitmap(),x*fieldSize,y*fieldSize,fieldSize,fieldSize);
    }
    delete gc;
}

void GraveyardPanel::AddPieceToList(Piece* pieceToAdd) {
    int lastWhiteX,lastWhiteY;
    int lastBlackX, lastBlackY;
    lastWhiteX = 0;
    lastBlackX = 0;
    for(auto p: graveyardPieceList) {
        if(p->GetColour() == PieceColour::white) {
            lastWhiteX = p->GetX()+1;
        }
        else {
            lastBlackX = p->GetX()+1;

        }
    }
    if(pieceToAdd->GetColour() == PieceColour::white) {
        pieceToAdd->SetPosition(lastWhiteX,0);
    }
    else {
        pieceToAdd->SetPosition(lastBlackX,1);
    }
    graveyardPieceList.push_back(pieceToAdd);
}

void GraveyardPanel::FreeList() {
    graveyardPieceList.clear();
}