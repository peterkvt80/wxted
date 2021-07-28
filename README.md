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
