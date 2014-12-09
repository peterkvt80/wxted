#ifndef TTXPAGE_H
#define TTXPAGE_H
#include <stdlib.h>
#include <iostream>

#include <fstream>
#include <string>

#include <cstdlib>
#include <iomanip>

// wxWidgets stuff
// For wxPoint
#include <wx/gdicmn.h>
// For wx keyboard codes
#include <wx/defs.h>


#include "ttxcodes.h"
#include "ttxline.h"

#include "tedevent.h"

#define FIRSTPAGE 0x1ff00

// MiniTED Page Status word
#define PAGESTATUS_C4_ERASEPAGE     0x4000
#define PAGESTATUS_C5_NEWSFLASH     0x0001
#define PAGESTATUS_C6_SUBTITLE      0x0002
#define PAGESTATUS_C7_SUPPRESSHDR   0x0004
#define PAGESTATUS_C8_UPDATE        0x0008
#define PAGESTATUS_C9_INTERRUPTED   0x0010
#define PAGESTATUS_C10_INHIBIT      0x0020
#define PAGESTATUS_TRANSMITPAGE     0x8000
#define PAGESTATUS_SUBSTITUTEPAGE   0x0800
#define PAGESTATUS_C11_SERIALMAG    0x0040

class TTXPage
{
    public:

        /** Default constructor */
        TTXPage();

        /** Construct from a file */
        TTXPage(std::string filename,  std::string shortFilename);

        /** Default destructor */
        ~TTXPage();

        /** Copy constructor
         *  \param other Object to copy from
         */
        TTXPage(const TTXPage& other);

        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        TTXPage& operator=(const TTXPage& other);

        /** Access m_SubPage
         * \return The current value of m_SubPage
         */
        TTXPage* Getm_SubPage() { return m_SubPage; }

        /** Set m_SubPage
         * \param val New value to set
         */
        void Setm_SubPage(TTXPage* val) { m_SubPage = val; }

        /** Get the page
         *  Warning! This is not the teletext page number. It is just an index to the pages in this list.
         * \return Pointer to the page object that we want
         */
         TTXPage* GetPage(unsigned int pageNumber);

         /** Setter/Getter for m_pageNumber
          */
         int GetPageNumber() {return m_PageNumber;}
         void SetPageNumber(int page);

         /** Setter/Getter for m_pageStatus
          */
         int GetPageStatus() {return m_pagestatus;}
         void SetPageStatus(int ps){m_pagestatus=ps;}

         /** Setter/Getter for m_description
          */
         std::string GetDescription() {return m_description;}
         void SetDescription(std::string desc){m_description=desc;}

         /** Setter/Getter for cycle counter/timer seconds
          */
         int GetCycleTime() {return m_cycletimeseconds;}
         void SetCycleTime(int time){m_cycletimeseconds=time;}

         /** Setter/Getter for cycle counter/timer seconds
          */
         char GetCycleTimeMode() {return m_cycletimetype;}
         void SetCycleTimeMode(char mode){m_cycletimetype=mode;}

         /** Setter/Getter for m_sourcepage
          *  This is the filename that was used to load the page
          */
         std::string GetSourcePage() {return m_sourcepage;}
         void SetSourcePage(std::string fname){m_sourcepage=fname;}

         /** Setter/Getter for m_shortFilename
          *  The short filename doesn't have a path
          */
         std::string GetShortFilename() {return m_shortFilename;}
         void SetShortFilename(std::string fname){m_shortFilename=fname;}

         /** Get the page count
         *  It also replaces the subcode sequence. (Is this a good idea?)
         * Must only call this in the root page.
         * \return Number of subpages.
         */
        int GetPageCount();

        /** Get a row of text
         * \return The TTXLine object of the required row. Check result for NULL if there isn't an actual row.
         */
         TTXLine* GetRow(unsigned int rowNumber);

        /** Set row rownumber with text line.
         * \return nowt
         */
         void SetRow(unsigned int rownumber, std::string line);

        /** Set a character at a particular location
         * \param code : The keyboard code
         * \param cursorLoc : The cursor location as a wxWidgets point. This returns with the updated location.
         * \param cursorSubLoc : The grapihics cursor sub position as a wxWidgets point. This returns with the updated sub character location.
         * \return nothing \\ bool true if the cursor location is in Alpha mode
         */
         void SetCharAt(int code, int modifiers, wxPoint& cursorLoc, wxPoint& cursorSubLoc, bool ShowHeader);

        /** Load an EP1 page
         * \param filename : The source file
         * \return true if the page was loaded
         */
        bool m_LoadEP1(std::string filename);

        /** Load a TTX page (Cebra)
         * \param filename : The source file
         * \return true if the page was loaded
         */
        bool m_LoadTTX(std::string filename);

        /** Load a TTI page (MRG Systems)
         * \param filename : The source file
         * \return true if the page was loaded
         */
        bool m_LoadTTI(std::string filename);

        /** Save the whole page set
         * \param filename : The destination file
         * \return false if the save failed
         */
        bool SavePage(std::string filename);

        /** Save the page set back to the original file
         * \return false if the save failed
         */
        bool SavePageDefault();


        /** Set the subcode
         * \param subcode : A subcode value from 0000 to FFFF
         * \return nothing yet
         */
         void SetSubCode(int subcode) {m_subcode=subcode;}

        /** Is this location in Alpha mode
         * \param loc : Character coordinate (0..39,1..24)
         * \return
         */
         bool IsAlphaMode(wxPoint loc);

        /** Copy the metadata from page to here.
         *  Metadata is everything except the actual text lines and the SubPage link.
         * \param page : A TTXPage object to copy from
         * \return
         */
        void CopyMetaData(TTXPage* page);

        /** Set the language.
         * 0=Engliah, 1=German, 2=Swedish, 3=Italian, 4=French, 5=Spanish, 6=Czech
         * \param language A language number 0..6 for western europe.
         * \return Nothing.
         */
        void SetLanguage(int language);

        /** Get the language.
         * \return language 0..6.
         */
        int GetLanguage();

        /** Get a Fastext link
         * \param link 0..5 where 0..3 are the main links, 5 is index and 4, nobody knows why
         * \return A link number (in hex base)
         */
        int GetFastextLink(int link);

        /** Set a Fastext link
         * \param link 0..5 where 0..3 are the main links, 5 is index and 4, nobody knows why
         * \param value - The link page number. Note that out of range numbers less than 0x100 are permitted. Droidfax can use these to switch services.
         */
        void SetFastextLink(int link, int value);

        /** undo/redo
         * \return the last event
         */
        TEDEvent* GetUndo();

        /** undo/redo
         * Step back one keystroke
         */
        void Undo(wxPoint& cursorloc);

    protected:
    private:
        // Private variables
        int m_PageNumber;  // PN
        // Private objects
        TTXPage* m_SubPage; //!< Member variable "m_SubPage"
        TTXLine* m_pLine[25];   // OL
        int m_fastextlinks[6];      // FL

        std::string m_destination;  // DS
        std::string m_sourcepage;   // SP
        std::string m_shortFilename;
        std::string m_description;  // DE
        int m_cycletimeseconds;     // CT
        char m_cycletimetype;       // CT
        int m_subcode;              // SC
        int m_pagestatus;           // PS

        // Private functions
        void m_Init();
        void m_OutputLines(std::ofstream& ttxfile, TTXPage* p);
        int instance;

        /* Undo/Redo */
        TEDEvent* undoList; // Root
        TEDEvent* m_current;  // Current pointer
        void AddEvent(EventType evt, wxPoint wxc, char oldchar, char newchar); // Add an event to the undo list


};

#endif // TTXPAGE_H
