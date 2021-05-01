27/04/2021 -
 'MkDir()' native function added.
  Include 'MkDir.inc' into the scope of your SA-MP Gamemode script. 
  Call 'CreateFolder(const string[])' with a valid name; this may not include:
      CON, PRN, AUX, NUL, COM0-9, LPT0-9 in Windows or those which contain: ':', '*', '?', ' " ', '<', '>' or '|'; as 
      well as file names which contain solely; a period, a space or are empty. (Users submitting '/' and '\' must be handled by the gamemode script.
29/04/2021 - 
 Some Linux compatabilitiy fixes.
 MkDir.so added to binaries.
30/04/2021 - 
 Some bug fixes.
 'RmDir()' and 'ChDir()' native functions added. (Remove Directory and Check Directory(existence) respectively)
