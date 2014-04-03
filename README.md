# CLCBrowser
## Introduction

CLCBrowser means "Command line controlled (web) browser". This browser has been developped
to show a live preview while you are editing a file in your favourite text editor.


It is fully commandline and remote controllable. Iternally, it starts a server to listen the
commands.


It is based on the amasing webkit integrating a javascript engine, so the render is the same
than in Google Chrome.

   
## Commandline

Usage:
$&gt; clcbrowser [options] [url]

### Options:

-h, --help
Show help


-t, --tab &lt;tab path&gt;
Path to the tab with format window%tab


-g, --geometry &lt;geometry&gt;
set the geometry of the window (syntax :WidthxHeight+OffX+OffY
    

-d, --delete
Flag to delete the tab


-l, --ls, --list
List the tabs


-x, --exit
Exit CLCBrowser

    
### Arguments:

url
url to open

## Install

### Archlinux

On archlinux, there is a package available on AUR.

### Mac OSX / Unix-like

You'll need Qt 5 installed in your system, and qmake available in your path.
You can build from the source availables on https://gitorious.org/clcbrowser/clcbrowser then, type the following command:


$&gt; mkdir build
$&gt; cd build
$&gt; qmake ..
$&gt; make


Then, you can copy the executable produced in you bin path, or make a package for your distribution package manager.

### Windows

An installer will be available soon.

## License

Copyright © 2014 Léo Flaventin Hauchecorne

This file is part of CLCBrowser.

CLCBrowser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CLCBrowser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License

along with CLCBrowser.  If not, see http://www.gnu.org/licenses/

