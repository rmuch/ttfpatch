# TTFPatch Patches and Builds

## Introduction

Ever wanted to embed a freely licensed font into your web page, for example as a local mirror of a Google Web Font, but you were presented with an error message like `@font-face failed OpenType embedding permission check. Permission must be Installable.` from Internet Explorer?

Do you have the right to use a font, but due to technical error, the font has been built with the wrong permission flag?

Are you a font author who wants to change the permission flag on their font?

This tool is here to help.

## About

TTFPatch was created by Wolfram Eßer, for modifying the font embedding licensing flag flag of TTF fonts.

This project is based on TTFPatch, updated to build with Visual Studio 2013 and to allow modification of permission flags of fonts conforming to OpenType rev 1.4 and 1.6 specifications.

## Disclaimer

Please be mindful of whether you are within your rights to make modifications to the font file. This tool is intended to be used by font authors and other permitted individuals who wish to set and change permission flags on their fonts.

Be aware that this application directly modifies the font file and may destructively alter the font. Always keep a backup of the original font file.

Further disclaimer terms apply to this product. For more information, see the license file.

## License

Licensing information is contained in `LICENSE.md`. To read the original licensing terms for this project, please see `docs/ttfpatch-1.0-readme.txt`.

## Links

 * [TTFPATCH by Wolfram Eßer](http://www.derwok.de/downloads/ttfpatch/)
