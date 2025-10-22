#ifndef TTXROW28_H
#define TTXROW28_H

#include "ttxline.h"
#include "hamm.h"


class TTXRow28 : public TTXLine
{
  public:
    /** Default constructor */
    TTXRow28();
    TTXRow28(std::string line);
    /** Default destructor */
    virtual ~TTXRow28();

  protected:

  private:
    // See ETSI EN 300 706 Table 4
    // Expanded fields from the packet 28 row
    unsigned int dc = 0; /// Designation code
    unsigned int pageFunction = 0; /// Page function (dc 3..0) default 0 = level 1 page
    unsigned int pageCoding = 0; /// Page coding (dc 6..4) default 2 = Hamming DC + 13 triples
    unsigned int defaultG0G2CharacterSet = 0; /// Primary character set. 4 bits region and 3 bits language. 0 = Region 0 English
    unsigned int secondG0G2CharacterSet = 0; /// Second character set. 4 bits region and 3 bits language. 0 = region 0 English
    unsigned int clut[4][8]; /// Four CLUTs of eight colours each 12 bits @todo load this up with the standard defaults
    unsigned int defaultScreenColour = 0; /// default black. [!] Bits 4,3 are CLUT, 2,1,0 are Colour
    unsigned int defaultRowColour= 0; /// default black [!] Bits 4,3 are CLUT, 2,1,0 are Colour
    unsigned int remap = 0; /// 0..7 Colour Table remapping.
    bool blackBackgroundSub = false; /// Allow CLUT to change the background colour
    bool enableLeftPanel = false; /// Show the left hand panel. false = do not show left panel
    bool enableRightPanel = false; /// Show the right panel. false = do not show right panel
    bool sidePanelStatusFlag = false; /// false = side panels only required at level 3.5.
    bool leftColumns = -1; /// 0..15

    // Implied field
    bool rightColumns = 0; /// implied. 16 - leftColumns. [!] @todo Turn this into a function

    // Functions

    /** @brief Decode the OL,28 packet into its individual components
     *  @param line The tti formatted packet string parameter
     *  @return true if it decoded OK
     */
    bool decode(std::string line);

    /** @brief Set the cluts to all the default values
     *
     */
    void defaultClut();

};

#endif // TTXROW28_H
