#include "tedevent.h"

TEDEvent::TEDEvent(EventType evt) : eventType(EventNone), nextEvent(nullptr), lastEvent(nullptr), charList(NULL)
{
    SeteventType(evt);
}

TEDEvent::TEDEvent() : eventType(EventNone), nextEvent(nullptr), lastEvent(nullptr), charList(nullptr)
{
    //ctor
}

TEDEvent::~TEDEvent()
{
    //dtor
    if (this->nextEvent!=nullptr)
        delete (nextEvent);
}

void TEDEvent::print()
{
    std::string s;
    CharChange* p;
    switch (eventType)
    {
    case EventNone     : s="NO EVENT";
        std::cout << "[TEDEvent::print] " << s << std::endl;
        break;
    case EventKey      : s="KEY";
        std::cout << "[TEDEvent::print] " << s <<std::endl;
        p=charList;
        for (p=charList;p!=nullptr;p=p->Getnext())
        {
            std::cout << "[TEDEvent::print] old" << p->GetOldChar() <<std::endl;
            std::cout << "[TEDEvent::print] new" << p->GetNewChar() <<std::endl;
            std::cout << "[TEDEvent::print] x" << p->GetLoc().x <<std::endl;
            std::cout << "[TEDEvent::print] y" << p->GetLoc().y <<std::endl;
        }
        break;
    case EventSave     : s="SAVE";
        std::cout << "[TEDEvent::print] " << s << std::endl;
        break;
    case EventLanguage : s="LANGUAGE";
        std::cout << "[TEDEvent::print] " << s << std::endl;
        break;
    }
}

void TEDEvent::dump()
{
    TEDEvent* p;
    EventType evt;
    for (p=this;p!=nullptr;p=p->GetlastEvent())
    {
        std::cout << "[TEDEvent::dump]" << std::endl;
        evt=p->GeteventType();
        char oc=p->charList->GetOldChar();
        char nc=p->charList->GetNewChar();
        std::cout << "Event type=" << evt << "char=" << oc << "=>" << nc << std::endl;
    }
}

void TEDEvent::SetnextEvent(TEDEvent* val)
{
    // Before setting the next event, clear the previous head.
    if (nextEvent!=NULL)
        delete nextEvent;
    nextEvent = val;
}
