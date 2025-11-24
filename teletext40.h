#ifndef _TELETEXT40_H_
#define _TELETEXT40_H_

#include <iostream>
#include <stdint.h>
#include "stdio.h"
#include "string.h"

#include "ttxpage.h"

void save_to_hash(int cset, char* encoding, uint8_t cc[24][40], const char* website, std::shared_ptr<TTXPage> page);
void load_from_hash(std::shared_ptr<TTXPage> page, char* str);
#endif // _TELETEXT40_H_
