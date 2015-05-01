/* Why is this so complicated?
 * Because keystrokes could potentially generate a collection of character changes.
 * At the moment it only does one, which is usually good enough to get out of trouble.
 */
#ifndef CHARCHANGE_H
#define CHARCHANGE_H
#include <iostream>
#include "wx/gdicmn.h"

class CharChange
{
    public:
        /** Default constructor */
        CharChange();
        /** Default destructor */
        virtual ~CharChange();
        /** Access next
         * \return The current value of next
         */
        CharChange* Getnext() { return next; }
        /** Set next
         * \param val New value to set
         */
        void Setnext(CharChange* val) { next = val; }

        /** When a character on the screen changes, log it
         * \param wxc : Cursor coordinate
         * \param oldchar : The character that was originally there
         * \param newchar : The character that replaced it
         */
        void AddChange(wxPoint wxc,char oldchar, char newchar);

        /** Access Cursor Loc
         * \return The current Loc
         */
        wxPoint GetLoc(){return m_CursorLoc;}

        /** Set Loc
         * \param val New value to set
         */
        void SetLoc(wxPoint val) { m_CursorLoc = val; }

        /** Display the event details
         *
         */
        void print();

        /**
         * \return the previous char
         */
        char GetOldChar(){return m_OldChar;}

        /**
         * \return The current char
         */
        char GetNewChar(){return m_NewChar;}

    protected:
    private:
        CharChange* next; //!< Member variable "next"
        char m_OldChar;
        char m_NewChar;
        wxPoint m_CursorLoc;
};

#endif // CHARCHANGE_H
