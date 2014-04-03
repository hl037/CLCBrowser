#include <QByteArray>

QByteArray htmlhelp = QByteArray(
R"the_html_string(
<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8">
   <title></title>

   <style>

body
{
   font-family : sans-serif;
}

h1,h2,h3
{
   font-family : serif;
}

h1
{
   font-size : 200%;
   color : #008;
   border-bottom : medium solid #f00;
   width : 630px;
}

h2
{
   font-size : 150%;
   color : #080;
   display : inline-block;
   border-bottom : thin solid #008;
   margin-bottom : 5px;
   margin-top : 15px;
}

h3
{
   font-size : 125%;
   color : #00A;
   display : inline-block;
   border-bottom :thin solid #080;
   margin-top : 15px;
   margin-bottom : 5px;
}

p
{
   margin-left : 30px;
   margin-top : 0.7em;
   margin-bottom : 0.7em;
   max-width : 600px
}

p.opt
{
   border : thin dotted #000;
   position : relative;
   min-height : 3em;
}

.cmd,.opt
{
   background-color : #000;
   color : #CCC;
   font-family : monospace;
}

.license
{
   font-family : monospace;
}

span.optitem
{
   position : absolute;
   left : 0px;
   width : 30%;
}

span.optdesc
{
   position : absolute;
   right : 0px;
   width : 60%;
}
   </style>

</head>
<body>
   <h1>CLCBrowser</h1>
   <h2>Introduction</h2>
   <p>
      CLCBrowser means "Command line controlled (web) browser". This browser has been developped
      to show a live preview while you are editing a file in your favourite text editor.
   </p>
   <p>
      It is fully commandline and remote controllable. Iternally, it starts a server to listen the
      commands.
   </p>
   <p>
      It is based on the amasing webkit integrating a javascript engine, so the render is the same
      than in Google Chrome.
   </p>

   <h2>Commandline</h2>
   <p class="cmd">
      Usage:<br/>
      $&gt; clcbrowser [options] [url]
   </p>
   <h3>Options:</h3>
   <p class="opt">
      <span class="optitem">-h, --help</span>
      <span class="optdesc">Show help</span>
   </p>
   <p class="opt">
      <span class="optitem">-t, --tab &lt;tab path&gt;</span>
      <span class="optdesc">Path to the tab with format window%tab</span>
   </p>
   <p class="opt">
      <span class="optitem">-g, --geometry &lt;geometry&gt;</span>
      <span class="optdesc">set the geometry of the window (syntax :WidthxHeight+OffX+OffY</span>
   </p>

   <p class="opt">
      <span class="optitem">-d, --delete</span>
      <span class="optdesc">Flag to delete the tab</span>
   </p>
   <p class="opt">
      <span class="optitem">-l, --ls, --list</span>
      <span class="optdesc">List the tabs</span>
   </p>
   <p class="opt">
      <span class="optitem">-x, --exit</span>
      <span class="optdesc">Exit CLCBrowser</span>
   </p>

   <h3>Arguments:</h3>
   <p class="opt">
      <span class="optitem">url</span>
      <span class="optdesc">url to open</span>
   </p>



   <h2>Install</h2>
   <br/>
   <h3>Archlinux</h3>
   <p>
      On archlinux, there is a package available on AUR.
   </p>
   <h3>Mac OSX / Unix-like</h3>
   <p>
      You'll need Qt 5 installed in your system, and qmake available in your path.
      You can build from the source availables on <a href="https://gitorious.org/clcbrowser/clcbrowser">
      gitorious</a>. then, type the following command:
   </p>
   <p class="cmd">
      $&gt; mkdir build <br/>
      $&gt; cd build<br/>
      $&gt; qmake ..<br/>
      $&gt; make<br/>
   </p>
   <p>
      Then, you can copy the executable produced in you bin path, or make a package for your distribution package manager.
   </p>
   <h3>Windows</h3>
   <p>
      An installer will be available soon.
   </p>
   <h2>License</h2>
   <p class="license">
      Copyright © 2014 Léo Flaventin Hauchecorne
      <br/><br/>
      This file is part of CLCBrowser.
      <br/><br/>
      CLCBrowser is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.
      <br/><br/>
      CLCBrowser is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.
      You should have received a copy of the GNU General Public License
      <br/><br/>
      along with CLCBrowser.  If not, see <a href ="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a>.
   </p>
</body>
</html>
)the_html_string");
