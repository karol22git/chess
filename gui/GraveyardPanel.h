#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Piece.h"
#include <list>
class GraveyardPanel : public wxPanel {
    private:
        const static int fieldSize = 30;
        const static int rows  = 2;
        const static int columns = 16;
        std::list<Piece*> graveyardPieceList;
    public:
        GraveyardPanel(wxWindow *parent, wxSize size);
        virtual ~GraveyardPanel(){};
        virtual void OnPaint(wxPaintEvent &event);
        void PaintFields(wxPaintDC *dc);
        void PaintPieces(wxPaintDC *dc);
        void AddPieceToList(Piece* pieceToAdd);
        void FreeList();

};