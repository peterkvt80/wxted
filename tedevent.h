#ifndef TEDEVENT_H
#define TEDEVENT_H

#include <iostream>
#include "charchange.h"

/***************************************************************
 * Name:      tedevent.cpp
 * Purpose:   Teletext editor edit event
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan (http://www.teastop.co.uk)
 * License:
  *
 * Copyright (C) 2014-2016, Peter Kwan
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 *************************************************************************** **/

 /**
  * A Ted Event is a keystroke or a menu selection
  * Some Events can be rolled back.
  * This class stores events in a linked list so that undo and redo can be supported
  */

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
        bool CharIsNull(){return charList==nullptr;}

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
