/** ***************************************************************************
 * Description       : Class for a single teletext line
 * Compiler          : C++
 *
 * Copyright (C) 2014, Peter Kwan
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

#include "ttxline.h"


TTXLine::TTXLine(std::string const& line):m_textline(line)
{
    // Also check that it is 40 characters, correctly de-escaped and processed for
    m_textline=validate(line);
}

TTXLine::TTXLine():m_textline("                                        ")
{
}

TTXLine::~TTXLine()
{
    //dtor
}

/** Set m_textline
 * \param val New value to set
 */
void TTXLine::Setm_textline(std::string const& val)
{
    m_textline = validate(val);
}

/** Validate - given a string, it validates it to ensure that the
 *  string follows the required format. 7 bit transmission ready.
 * It de-escapes and/or remaps characters as detailed in the MRG tti format spec.
 * It also treats \r very carefully.
 * If the string ends in \r or \r\n then it is treated as a terminator and is discarded.
 */
std::string TTXLine::validate(std::string const& val)
{
    char ch;
    int j=0;
    std::string str;
    str.resize(80);

    for (unsigned int i=0;i<val.length();i++)
    {
        ch=val[i] & 0x7f;   // Convert to 7 bits
        if (ch==0x1b) // escape?
        {
            i++;
            ch=val[i] & 0x3f;
        }
        // std::cout << val[i] << std::endl;
        str[j++]=ch;
    }
    // short line? Remove the text terminator.
    if (str[j-1]=='\n') j--;
    if (str[j-1]=='\r') j--;
    str.resize(j);
    return str;
}

/** GetMappedLine - returns a string with text file-safe mappings applied.
 * It is more or less the reverse of validate.
 * It escapes characters as detailed in the MRG tti format spec.
 */
std::string TTXLine::GetMappedline()
{
    char ch;
    int j=0;
    std::string str;
    str.resize(40);

    for (unsigned int i=0;i<40;i++)
    {
        ch=m_textline[i] & 0x7f;   // Strip bit 7 just in case
        if (ch<' ') ch |= 0x80;
        str[j++]=ch;
    }
    return str;
}


bool TTXLine::IsDoubleHeight()
{
    for (unsigned int i=0;i<m_textline.length();i++)
        if (m_textline[i]=='\r' || m_textline[i]==0x10)
            return true;
    return false;
}

void TTXLine::SetCharAt(int x,int code)
{
    m_textline[x]=code & 0x7f;
}

char TTXLine::GetCharAt(int xLoc)
{
    if (m_textline.length()<xLoc)
    {
        // extend the line to 40 characters
        std::cout << "[TTXLine::SetCharAt] oops, need to extend this line" << std::endl;
    }
    return m_textline[xLoc];
}


bool TTXLine::IsAlphaMode(int loc)
{
    // TODO: Not sure what cursor we should use for graphics mode capital letters
    bool result=true;
    if (loc>39) return true;
    for (int i=0;i<loc;i++)
    {
        switch (m_textline[i])
        {
        case ttxCodeAlphaBlack:;
        case ttxCodeAlphaRed:;
        case ttxCodeAlphaGreen:;
        case ttxCodeAlphaYellow:;
        case ttxCodeAlphaBlue:;
        case ttxCodeAlphaMagenta:;
        case ttxCodeAlphaCyan:;
        case ttxCodeAlphaWhite:;
            result=true;
            break;
        case ttxCodeGraphicsRed:;
        case ttxCodeGraphicsGreen:;
        case ttxCodeGraphicsYellow:;
        case ttxCodeGraphicsBlue:;
        case ttxCodeGraphicsMagenta:;
        case ttxCodeGraphicsCyan:;
        case ttxCodeGraphicsWhite:;
            result=false;
            break;
        default:; // Do nothing
        }
        // This is probably a mistake or it needs a third state: "Alpha in a graphics region".
        //if (m_textLine[i]>='A' && m_textLine[i]<'Z')
        //    result=false;
    }
    return result;
}

std::string TTXLine::GetLine()
{
    // If the string is less than 40 characters we need to pad it or get weird render errors
    int len=m_textline.length();
    if (len<40)
        for (int i=len;i<40;i++)
            m_textline+=" ";
    return m_textline;
}



