27/04/2021 -
Include 'MkDir.inc' into the scope of your SA-MP Gamemode script. 
 Call 'CreateFolder(const string[])' with a valid name; this may not include:
     CON, PRN, AUX, NUL, COM0-9, LPT0-9 in Windows or those which contain: '/', '\', ':', '*', '?', ' " ', '<', '>' or '|'; as 
     well as file names which contain solely; a period, a space or are empty.
29/04/2021 - 
 Various Linux compatbilitiy fixes.
 MkDir.so added to binaries.
