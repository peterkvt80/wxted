/** ***************************************************************************
 * Description       : Class for a single teletext line
 * Compiler          : C++
 *
 * Copyright (C) 2014,2016 Peter Kwan
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
    int j=0;
    std::string str="                                       ";
    str.resize(80);
    // std::cout << "Validating length= " << val.length() << std::endl;
    for (unsigned int i=0;i<val.length() && i<80;i++)
    {
        char ch=val[i] & 0x7f;   // Convert to 7 bits
        if (ch==0x1b) // escape?
        {
            i++;
            ch=val[i] & 0x3f;
        }
        // std::cout << val[i] << std::endl;

        // This code maps nulls to ? which was needed because we used null terminated strings.
        // If we use null terminated strings anywhere it will go wrong.
        /*
        if (ch==0x00) // null?
        {
            ch='?'; // Black text.
        }
        */
        str[j++]=ch;
    }
    // short line? Remove the text terminator.
    if (str[j-1]=='\n') j--;
    if (str[j-1]=='\r') j--;
    str.resize(j);
    // std::cout << "Validating done " << std::endl;
    return str;
}

/** GetMappedLine - returns a string with text file-safe mappings applied.
 * It is more or less the reverse of validate.
 * It escapes characters as detailed in the MRG tti format spec.
 */
std::string TTXLine::GetMappedline()
{
    int j=0;
    std::string str;
    str.resize(40);

    for (unsigned int i=0;i<40;i++)
    {
        char ch=m_textline[i] & 0x7f;   // Strip bit 7 just in case
        if (ch<' ') ch |= 0x80;
        str[j++]=ch;
    }
    return str;
}

/** GetMappedLine7bit - returns a string with text file-safe mappings applied.
 * Escape to 7 bit (required by Javascript Droidfax)
 */
std::string TTXLine::GetMappedline7bit()
{
    int j=0;
    std::string str;
    str.resize(80);

    for (unsigned int i=0;i<40;i++)
    {
        char ch=m_textline[i] & 0x7f;   // Strip bit 7
        if (ch<' ')
        {
            str[j++]=0x1b;  // <ESC>
            ch |= 0x40;     // Move control code up
        }
        str[j++]=ch;
    }
    str.resize(j);
    return str;
}

bool TTXLine::HasDoubleHeight()
{
  bool doubleHeight=false;
  uint8_t x=40;
  if (m_textline.empty())
  {
    return false;
  }
  // If the line we are testing isn't long enough, just check the last character.
  if (m_textline.length()<x)
  {
    x=m_textline.length()-1;
  }
  for (unsigned int i=0;i<=x;i++)
  {
    if (m_textline[i]=='\r')
    {
      doubleHeight=true;
    }
  }
  return doubleHeight;
} // HasDoubleHeight


bool TTXLine::IsDoubleHeight(int xLoc=39)
{
  bool doubleHeight=false;
  unsigned int x=xLoc;
  // If the line we are testing isn't long enough, just check the last character.
  // std::cout << m_textline << std::endl;
  if (m_textline.empty())
  {
    return false;
  }
  if (m_textline.length()<x)
  {
    x=m_textline.length()-1;
  }
  for (unsigned int i=0;i<=x;i++)
  {
    if (m_textline[i]=='\r') //  || m_textline[i]==0x10) // Probably mean to write 10 (LF) 0x10=GfxBlack
    {
      doubleHeight=true;
    }
    if (m_textline[i]=='\x12')
    {
      doubleHeight=false;
    }
  }
  return doubleHeight;
}

bool TTXLine::IsBlank()
{
    for (unsigned int i=0;i<40;i++)
        if (m_textline[i]!=' ')
            return false;
    return true; // Yes, the line is blank
}

char TTXLine::SetCharAt(int x,int code)
{
    char c=m_textline[x];
    m_textline[x]=code & 0x7f;
    return c;
}

char TTXLine::GetCharAt(int xLoc)
{
    if (m_textline.length()<(uint16_t)xLoc)
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
        case ttxCodeGraphicsBlack:;
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



