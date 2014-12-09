#ifndef TEDEVENT_H
#define TEDEVENT_H

#include <iostream>
#include "charchange.h"

enum EventType {EventNone, EventSave, EventKey, EventLanguage};


class TEDEvent
{
    public:
        /** Default constructor */
        TEDEvent();
        /** Event type constructor */
        TEDEvent(EventType evt);
        /** Default destructor */
        virtual ~TEDEvent();
        /** Access eventType
         * \return The current value of eventType
         */
        EventType GeteventType() { return eventType; }
        /** Set eventType
         * \param val New value to set
         */
        void SeteventType(EventType val) { eventType = val; }
        /** Access nextEvent
         * \return The current value of nextEvent
         */
        TEDEvent* GetnextEvent() { return nextEvent; }
        /** Set nextEvent
         * \param val New value to set
         */
        void SetlastEvent(TEDEvent* val) { lastEvent = val; }        /** Access nextEvent
         * \return The current value of nextEvent
         */
        TEDEvent* GetlastEvent() { return lastEvent; }
        /** Set nextEvent
         * \param val New value to set
         */
        void SetnextEvent(TEDEvent* val);

        /** If the char list is empty
         * \return true if the char list is empty
         */
        bool CharIsNull(){return charList==0;}

        /** Set the char iist
         * TODO: Test that the charList is not already set. Danger of memory leaks.
         */
        void SetCharList(CharChange* cc) {charList=cc;}

        /** Get the charList
         *
         */
         CharChange* GetCharList() {return charList;}

        /** Display the event details
         *
         */
        void print();

        /** Display the Undo list (backwards)
         *
         */
        void dump();


    protected:
    private:
        EventType eventType; //!< Member variable "eventType"
        TEDEvent* nextEvent; //!< Member variable "nextEvent"
        TEDEvent* lastEvent; //!< Member variable "nextEvent"
        CharChange* charList;
};

#endif // TEDEVENT_H
