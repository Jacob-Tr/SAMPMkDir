 Include 'MkDir.inc' into the scope of your SA-MP Gamemode. 
 Call 'CreateFolder(const string[])' with a valid name; this may not include:
     CON, PRN, AUX, NUL, COM0-9, LPT0-9 in Windows or those which contain: '/', '\', ':', '*', '?', ' " ', '<', '>' or '|'; as 
     well as file names which contain solely a period or space.
29/04/2021 - 
 Various linux compatbilitiy fixes.
 MkDir.so added to binaries.
