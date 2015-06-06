# BATPackage Batch File Packager #
BATPackage converts Windows Batch files to actual executables. This is useful for distributing Batch scripts in a more professional manner.

Obviously, this program is Windows only!

For most users, there is a GUI which makes turning BATs into EXEs as easy as pressing a button. Experienced command-prompt scripters will appreciate the inclusion of command line utilities for automated conversion.

## Building ##
There are two parts to BATPackage: the command line utilities, compiled with Open Watcom, and the GUI program, compiled with Visual Studio 2010.

**The command line part must be built for the GUI to work.**

### Building the Command Line Utilities ###
1. Install Open Watcom from http://sourceforge.net/projects/openwatcom/
2. Download the BATPackage code
3. Run `build.bat`

### Building the GUI ###
The GUI should be built with Visual Studio 2010. Other versions of VS may work but are not supported.

1. Follow the instructions above to build the command-line utilities
2. Open `GUI\BATPackage.sln` in the BATPackage code
3. Press **F5** or *Build > Build BATPackage*

## How it Works ##
Adding additional data to an EXE file is very easy. You simply pad it to a certain size and then append whatever data you want to the file. Then, that EXE can open itself with `fopen(argv[0], "r")` and read the data from the position determined earlier.

The BATPackage `loader.exe` copies all data past byte 40,000 in itself into a temporary file `SCRIPT.BAT`, then runs that file in the Command Prompt. Once the script exits, the loader deletes the temporary file.

## License ##
BATPackage is distributed under the GNU GPL as specified in `LICENSE.md`.