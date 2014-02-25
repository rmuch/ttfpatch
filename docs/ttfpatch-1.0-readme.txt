
TTFPATCH v1.0 - (C) by Wolfram Esser [wok@derwok.de] 2001-02-23

TTFPATCH is a Win32 commandline tool, which provides an easy way for font 
designers to set the 'embeddable' flags of their own true type fonts. 
TTFPATCH comes as Windows 32-bit executable and with complete C++ sourcecode.
So if you like, you can build your own binary for your OS platform. 
TTFPATCH has no graphical user interface, it is a commandline tool.

Download current version here:
     http://www.derwok.de  [select 'Downloads']


Usage examples:
---------------
If you (as the font designer) want to PROHIBIT embedding of your font
e.g. in Adobe Acrobat PDF files, simply run: 

     ttfpatch myfont.ttf 2

On the other hand, if you (as the font designer) decide to ALLOW the
users of your font to embed your font into documents (like Adobe Acrobat
PDF files), then you should run e.g.:

     ttfpatch myfont.ttf 4

If you are not(!) the designer / copyright holder of a font, you are not 
allowed to use this tool to change the fsType value of a given TrueType 
font! Respect the copyright of the font designer!

Usage: 
     ttfpatch TrueTypeFontFile [NewFsTypeValue]

fsType values:
       0: embedding for permanent installation
       1: reserved - do not use!
       2: embedding restricted (not allowed!)
       4: embedding for preview & printing allowed
       8: embedding for editing allowed

Hint: fsType values can be added. So a fsType value of '12' 
(which is 4 + 8) means set 'embedding for preview&printing
allowed' and set 'embedding for editing allowed'.


WARNING!!!
----------
THE PROGRAM DIRECTLY CHANGES THE FILE (NO TEMPFILE OR DIFFERENT OUTFILE!)
IT MAY BE POSSIBLE (THOUGH UNLIKELY) THAT YOUR FONTFILE IS DESTROYED
AFER USING THIS PROGRAM. SO KEEP A BACKUP OF THE FILE TO BE MODIFIED!!!

This programm and ist sourcecode are freeware. 
You may do everything you want with the source / binary, as long
as you keep my (C)opyright notice unchanged.

DISCLAIMER
----------
THIS FREEWARE PROGRAM IS PROVIDED BY WOLFRAM ESSER "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL
PROJECT MAYO OR ITS CONTRIBUTORS BE HELD LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES, LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
IF YOUR LOCALITY DOES NOT ALLOW THESE WARRANTY CONDITIONS, YOU ARE 
NOT GRANTED PERMISSION TO USE.


TrueType Font, TTF and Microsoft are registered trademarks of Microsoft Corp.
Adobe, Acrobat, PDF are registered trademarks of Acrobat Corp.
OS/2 is a registered trademark of IBM Corp.


Wuerzburg, Germany 2001-02-23

