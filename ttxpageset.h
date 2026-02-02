#ifndef TTXPAGESET_H
#define TTXPAGESET_H
/** ***************************************************************************
 * Description       : Class for a teletext page set. ie. a page and none or more subpages
 * Compiler          : C++
 *
 * Copyright (C) 2025 - 2026, Peter Kwan
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
#include "ttxpage.h"
#include <mutex>

class TTXPageSet
{
  public:
    /** Default constructor */
    TTXPageSet();
    /** Default destructor */
    virtual ~TTXPageSet();
    /** Constructor with initial page **/
    TTXPageSet(std::string filename, std::string shortFilename);

    TTXPage* GetPage(int page){
      // Check that page is in range
      if (page >= pages.size())
      {
        return nullptr;
      }
      return pages[page].get();
    };


    /** Load an EP1 page
     * \param filename : The source file
     * \return true if the page was loaded
     */
    bool m_LoadEP1(std::string filename);

    /** Load a T42 page
     * \param filename : The source file
     * \return true if the page was loaded
     */
    bool m_LoadT42(std::string filename);

    /** Load a VTX page
     * \param filename : The source file
     * \return true if the page was loaded
     */
    bool m_LoadVTX(std::string filename);

    /** Load a VTP page
     * \param filename : The source file
     * \return true if the page was loaded
     */
    bool m_LoadVTP(std::string filename);

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

    /** @brief Has anything changed that would require a Save?
     * Should check this before closing a page
     */
    bool GetPageChanged(); //
    void SetPageChanged(bool changed);

    /** Setter/Getter for m_description
    */
    std::string GetDescription() {return m_description;}
    void SetDescription(std::string desc){if(m_description!=desc)SetPageChanged(true);m_description=desc;}


    /** Setter/Getter for m_sourcepage
    *  This is the filename that was used to load the page
    */
    std::string GetSourcePage() {return m_sourcepage;}
    void SetSourcePage(std::string fname){if(m_sourcepage!=fname)SetPageChanged(true);m_sourcepage=fname;}


    /** Setter/Getter for m_shortFilename
    *  The short filename doesn't have a path
    */
    std::string GetShortFilename() {return m_shortFilename;}
    void SetShortFilename(std::string fname){if(m_shortFilename!=fname)SetPageChanged(true);m_shortFilename=fname;}

    /** Get the page count
     * \return Total number of pages.
     */
    int GetPageCount() {return pages.size();};

    /* Undo/Redo */
    std::shared_ptr<TEDEvent> undoList;
    std::shared_ptr<TEDEvent> m_current;  // Current pointer
    void AddEvent(EventType evt, wxPoint wxc, char oldChar, char newChar); // Add an event to the undo list

    /**
     * \return true if the page has been loaded
     */
    bool IsLoaded(){return m_loaded;};

    int findPageNumber(char* buf); /// ?

    // Page management. Current page, add page, delete page
    TTXPage* CurrentPage(); /// Get a raw TTXPage pointer to the current page
    TTXPage* PreviousPage(); /// Set the current page to the previous page and return its raw TTXPage pointer
    TTXPage* NextPage(); /// Set the current page to the next page and return its raw TTXPage pointer
    TTXPage* SelectPage(int pageIndex); /// Sets the current page index. Also returns the TTXPage raw pointer
    int CurrentPageIndex(){return m_currentPageIndex;}; /// Return the index of the current page

    int GetPageNumber(); /// Return the current mppss page number
    void SetPageNumber(int mppss); /// Set the mppss number of the page

    //////////////////// CAROUSEL MANAGEMENT
    void InsertPageAfter(); /// Insert a new page after the current page
    void DeletePage(); /// Delete the current page

    void debug(std::string message);

  protected:

  private:
    bool pageChanged;         /// True if we have done some edits (on any subpage)


    // TTXPage* m_currentPage; /// An observer pointer to the page currently viewed and edited
    int m_currentPageIndex; //
    bool m_loaded;  /// Not sure what this is for. Probably true if we have a page loaded
    std::vector<std::unique_ptr<TTXPage>> pages; //!< Member variable "pages"

    int m_PageNumber;  // PN
    std::string m_destination;  // DS
    std::string m_sourcepage;   // SP
    std::string m_shortFilename;
    std::string m_description;  // DE

    void m_Init();  /// Constructor initialisations
    std::mutex m_pageMutex;
    std::mutex m_loadMutex;

};

#endif // TTXPAGESET_H
