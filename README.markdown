
Ookjor mobile bluetooth camera software
=======================================


Purpose
-------
Ookjor shows S60 3rd and 5th edition phones' cameras and screens live on the computer - for teaching, demonstrating products via the live-camera, demonstrating S60 phone usage and S60 software - wirelessly via Bluetooth.

You can connect your computer or notebook to a projector (or big LCD TVs that have s-video or HDMI ports) in a meeting room, class room, event hall.

Usage
-----
1. Use mobile phone's camera to demonstrate various things live:
(Ookjor would start the phone-camera streaming after connected)
- Show and demonstrate new products and services (in stores, shopping-malls, event halls, etc)
- Show what you write or the diagrams you draw on paper
- Show how to use equipment
- Teach how to do scientific experiments
- Show how to cook
- Show the person speaking

2. Show phone's screen live on the computer:
(After Ookjor is connected, press "Done" to switch to mobile-screen streaming)
- Showcase and demonstrate how to use mobile phones (at events, phone stores, etc.)
- Showcase and demonstrate how to use mobile software applications and games.


Requirements
------------
- A (Nokia) S60 3rd/5th edition phone (Symbian OS 9.0 or newer).
- A computer/notebook running GNU/Linux OS with Bluetooth hardware and BlueZ dirver. Tested on Ubuntu 9.10 - see <http://www.ubuntu.com> - a great and free alternative to MS Windows.
- Qt4 ( Go to Applications > Accessories > Terminal and type or copy-paste: sudo apt-get install libqtcore4 libqtgui4 )


How to use
-----------
1. Download the latest release from <http://www.clearevo.com/ookjor>

2. Extract the zip/archive file (right-click, "Extract here"), select the "Ookjor.sh" file right-click > properties > permissions > make sure the "allow to execute" checkbox is checked. (or in terminal: chmod +x Ookjor.sh)

3. Double click the "Ookjor.sh" file, select "Run", or in terminal: ./Ookjor.sh in this directory.

4. You must first install (press "Send installer to phone" button in step 1 to send and install on phone) and start the mobile Ookjor program on your phone. (It would be in Menu > Applications > "Install. apps." or "My own", etc)
   - If send fails because your system doesn't have "bluetooth-sendto" available, send the installer (OokjorS603rdAnd5th.sisx, in the folder bin_src/OokjorS60/sis) to phone manually using other methods.

5. When mobile phone Ookjor shows - Press "Connect" on Computer - then on this computer Ookjor program: Press "Connect to Mobile", select your phone and the mobile screen or camera should start showing in a few seconds.

- Ookjor would start the live camera view display on the computer, ready to use! Press the Zoom + or - buttons in the computer Ookjor to adjust.

- If you want to show mobile screen instead of the camera view, select "Done" on mobile while connected.


Bluetooth Engine Library
----------
Ookjor's bluetooth engine has been adjusted to become its own project/library to be easier to adapt for use in other apps. The engine is PatienceBTEngine: <http://github.com/ykasidit/PatienceBTEngine>

Compiling
---------
Please see HOWTO_COMPILE file.


License
-------
Copyright (C) 2009 Kasidit Yusuf.

This file is part of Ookjor.

Ookjor is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ookjor is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ookjor.  If not, see <http://www.gnu.org/licenses/>.


About
-------
Ookjor was developed by Kasidit Yusuf.
Please visit the official page on <http://www.clearevo.com/ookjor> for more info.
