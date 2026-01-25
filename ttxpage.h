#ifndef TTXPAGE_H
#define TTXPAGE_H
#include <stdlib.h>
#include "string.h"
#include <iostream>
#include <sstream>
#include <vector> // Required for std::vector
#include <memory> // Required for std::unique_ptr

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
#include "ttxrow28.h"

#include "T42.h"
#include "HeaderPacket.h"

#include "hamm.h"
// #include "hamm-tables.h"
#include "tedevent.h"

#include "masktemplate.h" // MS command in tti files

//#include "wxTEDMain.h"
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

// Rows 25 to 28 are page related enhancements for higher levels.
// 29 is magazine related.
// Hopefully we will preserve these rows even if we don't process them
#define MAXROW 29

class TTXPage
{
  public:
    /** Default constructor */
    TTXPage();

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
     * \param cursorSubLoc : The graphics cursor sub position as a wxWidgets point. This returns with the updated sub character location.
     * \return nothing \\ bool true if the cursor location is in Alpha mode
     */
     void SetCharAt(int code, int modifiers, wxPoint& cursorLoc, wxPoint& cursorSubLoc, bool ShowHeader);

    /** Set the subcode
     * \param subcode : A subcode value from 0000 to FFFF
     * \return nothing yet
     */
     void SetSubCode(int subCode) {m_subCode=subCode;}
     int GetSubCode() {return m_subCode;}

    /** Setter/Getter for m_pageStatus
     */
    int GetPageStatus() {return m_pageStatus;}
    void SetPageStatus(int ps) { if (m_pageStatus!=ps)SetPageChanged(true);m_pageStatus=ps; }
    void SetPageChanged(bool change){pageChanged=change;};
    bool GetPageChanged(); // True if the page has changed

    /** Setter/Getter for m_fastTextLink
     *  @param linkNumber - 0 to 5
     *  @return The link value as an integer. (need to convert to hex when saving)
     */
     int GetLink(int linkNumber){return m_fastextLinks[linkNumber];};

    /** Is this location in Alpha mode
     * \param loc : Character coordinate (0..39,1..24)
     * \return
     */
     bool IsAlphaMode(wxPoint loc);

    /** Set the language.
     * 0=English, 1=German, 2=Swedish, 3=Italian, 4=French, 5=Spanish, 6=Czech
     * \param language A language number 0..6 for Western Europe.
     * \return Nothing.
     */
    void SetLanguage(int language, bool UsePrimary);

    /** Get the language.
     * @param primary - If true returns the primary language
     * \return language 0..6.
     */
    int GetLanguage(bool primary);

    /** Set the region.
     * A region is just one of the 16 sets of character sets.
     * \param region : A hex value 0..f
     * \return Nothing.
     */
    void SetRegion(int region, bool primary); // Probably want to check primary or second font

    /** Get the region.
     *  @param primary - If true returns the primary region
     * \return region 0..f.
     */
    int GetRegion(bool primary);

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
    std::shared_ptr<TEDEvent> GetUndo();

    /** undo/redo
     * Step back one keystroke
     */
    void Undo(wxPoint& cursorloc);


    /** Insert a line below the line number indicated in cursorLoc
     *  and leave the current row blank
     */
    void InsertLine(wxPoint& cursorLoc);
    /** Delete a line below the current line and shift lower lines up one
     *  and leave the last row blank
     */
    void DeleteLine(wxPoint& cursorLoc);

    /**
    * @brief remap - Convert a colour 0..7 to a 12 bit RGB value
    * Uses the current CLUT remapping to select the color
    * @param colour - Value from 0 to 7
    * @param useForeground - If true, use the colour from the foreground CLUT
    * @return 12 bit RGB value
    */
    unsigned int Remap(unsigned int colour, bool useForeground);

    /** @brief GetX28Row - Get access to the X28 language and palette enhancement packet
     *  @return - TTXRow28* pointer
     */
     std::shared_ptr<TTXRow28> GetX28Row(){return m_row28;};

    void SetRow28(std::shared_ptr<TTXRow28> pkt28){m_row28=pkt28;};

    /** Output lines as tti
     *  @param ttxfile : Output stream to send lines
     *  @param mpp : Pageset teletext mag/page number 0x100 to 0x8fe
     */
    void OutputLines(std::ofstream& ttxfile, int mpp); /// Send ttx lines to an output stream

    /** Setter/Getter for cycle counter/timer seconds
    */
    int GetCycleTime() {return m_cycleTimeSeconds;}
    void SetCycleTime(int time){if(m_cycleTimeSeconds!=time)SetPageChanged(true);m_cycleTimeSeconds=time;}

    /** Setter/Getter for cycle counter/timer seconds
    */
    char GetCycleTimeMode() {return m_cycleTimeType;}
    void SetCycleTimeMode(char mode){if(m_cycleTimeType!=mode)SetPageChanged(true);m_cycleTimeType=mode;}

    /** mask template access
    */
    bool AddMask(std::string line){return m_mask.AddMask(line);};
    std::string WriteMask(){return m_mask.WriteMask();};
    size_t GetMaskCount(){return m_mask.GetMaskCount();};

  protected:
  private:
    // Private variables
    // Private objects
    std::vector<std::unique_ptr<TTXLine>> m_pLine; // OL. 26,27,28,29 might be set by other apps. Keep whatever people put in there
    std::shared_ptr<TTXRow28> m_row28;           // OL,28 Packet X28 only
    int m_fastextLinks[6];      // FL - Per page feature

    int m_subCode;              // SC - Definitely a per-page feature
    int m_pageStatus;           // PS - Might be per page feature, so leave it here
    // Private functions
    void m_Init();
    int instance;

    /* Undo/Redo */
    std::shared_ptr<TEDEvent> undoList; // Root
    std::shared_ptr<TEDEvent> m_current;  // Current pointer
    void AddEvent(EventType evt, wxPoint wxc, char oldChar, char newChar); // Add an event to the undo list


    bool pageChanged; // True if anything in this page changed
    int m_cycleTimeSeconds; // Carousel display time
    char m_cycleTimeType; // C or T. Cycled or Timed

    MaskTemplate m_mask; // Templating mask for data fields
};

#endif // TTXPAGE_H
