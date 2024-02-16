#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Piece.h"
#include <list>

class Moderator;
struct field {
    int x;
    int y;
    wxRect Rect;
    wxColour *colour;
    Piece *pieceOnMe = nullptr;
};

struct TemporaryData {
    Piece* currentPiece = nullptr;
    int movableX = 0;
    int movableY = 0;
    int previousI = 0;
    int previousJ = 0;
};

enum PaintingMode {
    Normal = 1,
    Screenshoot,
    Moving = 3
};

class DrawingPanel : public wxPanel {
    private:
        bool lock = false;
        Moderator *moderator;
        const int fieldSize = 50;
        const static int boardSize = 8;
        struct field fieldList[boardSize][boardSize];
        std::list<Piece*> blackPiecesList;
        std::list<Piece*> whitePiecesList;
        wxBitmap screenshot;
        PaintingMode pMode = PaintingMode::Normal;
        wxCoord screenWidth,screenHeight;
        int previousI = 0;
        int previousJ = 0;
        Piece* currentPiece = nullptr;
        int movableX = 0;
        int movableY = 0;
    public:
        DrawingPanel(wxWindow *parent,wxSize size);
        virtual ~DrawingPanel(){};
        virtual void OnPaint(wxPaintEvent &event);
        void PaintFields(wxPaintDC *dc);
        void PaintPieces(wxPaintDC *dc);
        void Flip();
        void SetPieces(std::list<Piece*> *whiteList, std::list<Piece*> *blackList);
        void MouseLeftSingleClick(wxMouseEvent &event);
        void MouseLeftUp(wxMouseEvent &event);
        void MouseDraggin(wxMouseEvent &event);
        void AssignPiecesToFields();
        void TakeScreenshot();
        void GenerateBoard();
        void SetModerator(Moderator *m);
        void UpdateField(int i, int j);
        void FetchPiece(wxPoint mousePosition);
        bool FetchField(int i, int j, wxPoint mousePosition);
        bool DoColorsMatch(int i, int j);
        void inline SetPaintingModeTo(PaintingMode p);
        void ResetTemporaryData();
        void Lock();
        void Unlock();
        bool isLock();
        bool isFieldEmpty(int i, int j);
        Piece* FetchPiece(int i, int j);
        void MovePiece(Piece* p, int i, int j);
        void inline PieceReplacement(int i, int j);

};