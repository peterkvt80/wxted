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

    /**
     * @brief remap - Convert a colour 0..7 to a 12 bit RGB value
     * Uses the current CLUT remapping to select the color
     * @param colour - Value from 0 to 7
     * @param useForeground - If true, use the colour from the foreground CLUT
     * @return 12 bit RGB value
     */
    unsigned int Remap(unsigned int colour, bool useForeground);

    /** SetRemap. Controls the CLUT remapping.
     *  @param mapval - CLUT remapping value 0..7
     */
    void SetRemap(unsigned int mapVal){remap = mapVal;}; // @todo Check range of value

    /** GetRemap. Controls the CLUT remapping.
     *  @return - The current CLUT remapping value 0..7
     */
    unsigned int GetRemap(){return remap;};

    /** Language - Get the language number 0..7
     *  @param primary - If true returns the primary language
     *  @return Language code 0..7
     */
    unsigned int Language(bool primary);

    /** Region - Get the language number 0..7
     *  @param primary - If true returns the primary region
     *  @return Region code 0..10
     */
    unsigned int Region(bool primary);

    /** encode - Put X28 member data into TTI OL,28 string
     *  @return TTI OL,28 packet string.
     */
    std::string encode();

    /** @brief Set the cluts to all the default values
     *
     */
    void defaultClut();

    unsigned int GetColour(unsigned int clutIx, unsigned int colour){return clut[clutIx][colour];};
    void SetColour(unsigned int colourVal, unsigned int clutIx, unsigned int colour){clut[clutIx][colour] = colourVal;};

  protected:

  private:
    // See ETSI EN 300 706 Table 4
    // Expanded fields from the packet 28 row
    unsigned int dc = -1; /// Designation code
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
    unsigned int leftColumns = -1; /// 0..15

    /// Number of columns in right panel
    unsigned int rightColumns();

    // Functions

    /** @brief Decode the OL,28 packet into its individual components
     *  @param line The tti formatted packet string parameter
     *  @return true if it decoded OK
     */
    bool decode(std::string line);

    bool isValid(){return dc >= 0;}; /// If this object has valid data

};

#endif // TTXROW28_H
