#include "charchange.h"

CharChange::CharChange() : m_CursorLoc(wxPoint(0,0)), m_OldChar(' '), m_NewChar(' '), next(0)
{
    //ctor
}

CharChange::~CharChange()
{
    //dtor
    if (next!=0)
    {
        std::cout << "TODO: need to destruct any remaining changes in this list" << std::endl;
        delete next;
    }
}

void CharChange::AddChange(wxPoint wxc,char oldchar, char newchar)
{
    m_CursorLoc=wxc;
    m_OldChar=oldchar;
    m_NewChar=newchar;
    std::cout << "AddChange x,y=" <<wxc.x<<","<<wxc.y << "old=>new=" << oldchar <<"=>"<<newchar << std::endl;
}
