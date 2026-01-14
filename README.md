# wxTED

If you just want to use wxTED, click on Releases to get the latest Windows binary.

wxTED is a teletext editor. wxted supports 26 languages including Arabic, Hebrew, Greek, Turkish and several Cyrillic.
It supports all transmission flags for subtitles, newsflash etc. It also supports carousels (a page with rotating subpages).

It is currently compiled for Windows using Code::Blocks but it has also been tested with Ubuntu and Raspberry Pi OS. It should should also be possible to compile it for Mac. The Windows version can run under Wine on Linux but the clipboard is a bit broken.

Developers: See manual.odt for an outline of how to set up a development environment.

--//--
Personal reminder. Put keys into

~/.ssh/id_rsa

Then do

git remote set-url origin git@github.com:peterkvt80/wxted.git

and you should be able to just do 

git push

## Compiling wxTED for Linux

### Prerequisites

Install the required dependencies:

```bash
# For Ubuntu/Debian-based systems
sudo apt-get update
sudo apt-get install build-essential git libwxgtk3.2-dev
```

### Compilation Steps

1. Clone the repository:
```bash
git clone https://github.com/peterkvt80/wxted.git
cd wxted
```

2. Install teletext fonts:
```bash
cd font
mkdir ~/.fonts
cp *.ttf ~/.fonts
fc-cache fv
```

3. Compile the project:
```bash
g++ -o wxTED \
    -I./include \
    charchange.cpp \
    hamm.c \
    HelpFrame.cpp \
    mapchar.cpp \
    PageSettingsDialog.cpp \
    PaletteFrame.cpp \
    PublishSetupDialog.cpp \
    tedevent.cpp \
    teletext40.cpp \
    ttxline.cpp \
    ttxpage.cpp \
    ttxrow28.cpp \
    wxTEDApp.cpp \
    wxTEDMain.cpp \
    src/T42.cpp \
    src/HeaderPacket.cpp \
    ttxpageset.cpp \    
    `wx-config --cxxflags --libs core,base,adv,html` \
    -std=c++17
```

4. Run wxTED:
```bash
./wxTED
```

### Optional: Installation

To install wxTED system-wide:
```bash
sudo cp wxTED /usr/local/bin/
```

To create a desktop launcher:
```bash
echo "[Desktop Entry]
Name=wxTED
Comment=Teletext Editor
Exec=$PWD/wxTED
Icon=text-editor
Terminal=false
Type=Application
Categories=Graphics;Publishing;" > ~/.local/share/applications/wxted.desktop
```

