//********************************************************
// IRCodes.h
//
//
//********************************************************
// ***** SELECT REMOTE TYPE *****
//#define MP3remote
//#define whiteremote
//#define thickremote
#define xtremeremote
//#define BIGremote

#define red     0xFF0000
#define redorg  0xFF4400
#define green   0x00FF00
#define blue    0x0000FF 
#define pink    0xFF99FF
#define yellow  0xFFFF00 
#define cyan    0x00FFFF
#define magenta 0xFF00FF  
#define orange  0xFF8000
#define lime    0x33FF33
#define black   0x000000
#define white   0xFFFFFF
#define purple  0x9933FF
#define turq    0x00EE88

//********************************************************
#ifdef MP3remote
#define num_of_buttons 21 + 1

// MP3 IR Remote Codes
#define IRButton1 0xFFA25D // PWR
#define IRButton2 0xFF629D // MODE
#define IRButton3 0xFFE21D // SPK
#define IRButton4 0xFF22DD // PLAY
#define IRButton5 0xFF02FD // REV
#define IRButton6 0xFFC23D // FOR
#define IRButton7 0xFFE01F // EQ
#define IRButton8 0xFFA857 // -
#define IRButton9 0xFF906F // +
#define IRButton10  0xFF6897 // 0
#define IRButton11  0xFF9867 // LOOP
#define IRButton12  0xFFB04F // U/SD
#define IRButton13  0xFF30CF // 1
#define IRButton14  0xFF18E7 // 2
#define IRButton15  0xFF7A85 // 3
#define IRButton16  0xFF10EF // 4
#define IRButton17  0xFF38C7 // 5
#define IRButton18  0xFF5AA5 // 6
#define IRButton19  0xFF42BD // 7
#define IRButton20  0xFF4AB5 // 8
#define IRButton21  0xFF52AD // 9

#define IRButton22  0xEFFFF1 // dummy
#define IRButton23  0xEFFFF2 // dummy
#define IRButton24  0xEFFFF3 // dummy
#define IRButton25  0xEFFFF4 // dummy
#define IRButton26  0xEFFFF5 // dummy
#define IRButton27  0xEFFFF6 // dummy
#define IRButton28  0xEFFFF7 // dummy

String remoteButtonName[num_of_buttons] = {"Empty", "ON/OFF", "MODE", "SPK", "Play/Pause", "REW", "FWD", "EQ", "MINUS", 
                                     "PLUS", "0", "LOOP", "U/SD", "1", "2", "3", "4", 
                                     "5", "6", "7", "8", "9"
                                     };
                                     
#endif
//********************************************************
#ifdef whiteremote
#define num_of_buttons 24 + 1
#define num_of_colors 16 + 1

// WHITE IR Remote Codes
#define IRButton1 0xF700FF // INC
#define IRButton2 0xF7807F // DEC
#define IRButton3 0xF740BF // OFF
#define IRButton4 0xF7C03F // ON
#define IRButton5 0xF720DF // RED
#define IRButton6 0xF7A05F // GRN
#define IRButton7 0xF7609F // BLU
#define IRButton8 0xF7E01F // WHT
#define IRButton9 0xF710EF // RedOrg
#define IRButton10  0xF7906F // Green2
#define IRButton11  0xF750AF // Cobalt
#define IRButton12  0xF7D02F // FLASH
#define IRButton13  0xF730CF // Orange
#define IRButton14  0xF7B04F // Cyan
#define IRButton15  0xF7708F // DkPurple
#define IRButton16  0xF7F00F // STROBE
#define IRButton17  0xF708F7 // Gold
#define IRButton18  0xF78877 // Turq
#define IRButton19  0xF748B7 // Magenta
#define IRButton20  0xF7C837 // FADE
#define IRButton21  0xF728D7 // Yellow
#define IRButton22  0xF7A857 // Lime
#define IRButton23  0xF76897 // Pink
#define IRButton24  0xF7E817 // SMOOTH

#define IRButton25  0xEFFFF4 // dummy
#define IRButton26  0xEFFFF5 // dummy
#define IRButton27  0xEFFFF6 // dummy
#define IRButton28  0xEFFFF7 // dummy

String remoteButtonName[num_of_buttons] = {"Empty", "Brt", "Dim", "OFF", "ON ", "RED", "GRN", "BLU", "WHT", 
                                     "RedOrg", "GRN2", "BLU2", "FLASH", "Orange", "Cyan", "Purple", "STROBE", 
                                     "Gold", "Turq", "LtPurp", "FADE", "Yellow", "DkBlu", "Pink", "SMOOTH"
                                     };
                                     
int32_t colorArray[num_of_colors] = {0,     0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF,    0xBB2F00,  0x00BB00,   0x0059ff,   0xff8c00,  
                                     0x00FFFF, 0x6a00ff, 0xffdd00, 0x00ffe5,  0xFF00FF, 0xFFFF00, 0x00ff55, 0xff00b7}; 
                                     
String colorString[num_of_colors] = {"Empty",  "Red",  "Green",   "Blue",   "White",  "RedOrange", "Green2",  "Cobalt",  "Orange", 
                                     "Cyan",  "DkPurple", "Gold",  "Turq",   "Magenta", "Yellow",  "Lime",    "Pink"}; 
                                                                         



#endif
//********************************************************
#ifdef thickremote
#define num_of_buttons 28 + 1

// THICK IR Remote Codes
#define IRButton1 0xF738C7 // White
#define IRButton2 0xF7B847 // Dim
#define IRButton3 0xF77887 // Bright
#define IRButton4 0xF7F807 // ON/OFF
#define IRButton5 0xF700FF // COLOR
#define IRButton6 0xF7807F // RGB 
#define IRButton7 0xF740BF // RGBCYM
#define IRButton8 0xF7C03F // Rainbow
#define IRButton9 0xF720DF // Hearts
#define IRButton10  0xF7A05F // Flag
#define IRButton11  0xF7609F // Pumpkin
#define IRButton12  0xF7E01F // Gift
#define IRButton13  0xF710EF // Circle
#define IRButton14  0xF7906F // UP
#define IRButton15  0xF750AF // DOWN
#define IRButton16  0xF7D02F // MUSIC
#define IRButton17  0xF730CF // AUTO
#define IRButton18  0xF7B04F // REW
#define IRButton19  0xF7708F // FWD
#define IRButton20  0xF7F00F // JUMP
#define IRButton21  0xF708F7 // 4HR
#define IRButton22  0xF78877 // LEFT
#define IRButton23  0xF748B7 // RIGHT
#define IRButton24  0xF7C837 // SMOOTH
#define IRButton25  0xF728D7 // 8HR
#define IRButton26  0xF7A857 // CometLeft
#define IRButton27  0xF76897 // CometRight
#define IRButton28  0xF7E817 // METEOR

String remoteButtonName[num_of_buttons] = {"Empty", "WHITE", "Dim", "Bright", "ON/OFF ", "COLOR", "RGB", "RGBCYM", "Rainbow", 
                                     "Hearts", "Flag", "Pumpkin", "Gift", "Circle", "UP", "DOWN", "MUSIC", 
                                     "AUTO", "REW", "FWD", "JUMP", "4HR", "LEFT", "RIGHT", "SMOOTH", 
                                     "8HR", "CometLEFT", "CometRIGHT", "METEOR"};

#endif
//********************************************************
#ifdef xtremeremote
#define num_of_buttons 20 + 1

// XTREME IR Remote Codes
#define IRButton0   0
#define IRButton1   0xFFA25D
#define IRButton2   0xFFE21D
#define IRButton3   0xFF22DD
#define IRButton4   0xFF02FD
#define IRButton5   0xFFC23D
#define IRButton6   0xFFE01F
#define IRButton7   0xFFA857
#define IRButton8   0xFF906F
#define IRButton9   0xFF6897
#define IRButton10  0xFF9867
#define IRButton11  0xFFB04F
#define IRButton12  0xFF30CF
#define IRButton13  0xFF18E7
#define IRButton14  0xFF7A85
#define IRButton15  0xFF10EF
#define IRButton16  0xFF38C7
#define IRButton17  0xFF5AA5
#define IRButton18  0xFF42BD
#define IRButton19  0xFF52AD
#define IRButton20  0xFF4AB5


String remoteButtonName[num_of_buttons] = {"Empty", "ON", "OFF", "RED", "GREEN", "BLUE", "GOLD", "FOR", "Lime", 
                                     "LEFT", "STOP", "RIGHT", "DomeLEFT", "REV", "DomeRIGHT", "White", "FADE", 
                                     "JUMP", "RESET", "DEC", "INC"};

#endif
//********************************************************
#ifdef BIGremote
#define num_of_buttons 44 + 1

//********************************************************
// BIG Remote
#define IRButton1 0xFF3AC5 // INC
#define IRButton2 0xFFBA45 // DEC
#define IRButton3 0xFF827D // PLAY
#define IRButton4 0xFF02FD // PWR
#define IRButton5 0xFF1AE5 // RED
#define IRButton6 0xFF9A65 // GREEN
#define IRButton7 0xFFA25D // BLUE
#define IRButton8 0xFF22DD // WHITE
#define IRButton9 0xFF2AD5 // ORANGE a
#define IRButton10  0xFFAA55 // LIME b
#define IRButton11  0xFF926D // COBALT c
#define IRButton12  0xFF12ED // LTPURPLE d
#define IRButton13  0xFF0AF5 // e
#define IRButton14  0xFF8A75 // f
#define IRButton15  0xFFB24D // g
#define IRButton16  0xFF32CD // h
#define IRButton17  0xFF38C7 // i
#define IRButton18  0xFFB847 // j
#define IRButton19  0xFF7887 // k
#define IRButton20  0xFFF807 // l
#define IRButton21  0xFF18E7 // YELLOW m
#define IRButton22  0xFF9867 // n
#define IRButton23  0xFF58A7 // DKPURPLE o
#define IRButton24  0xFFD827 // CYAN p
#define IRButton25  0xFF28D7 // REDUP
#define IRButton26  0xFFA857 // GREENUP
#define IRButton27  0xFF6897 // BLUEUP
#define IRButton28  0xFFE817 // QUICK
#define IRButton29  0xFF08F7 // REDDN
#define IRButton30  0xFF8877 // GREENDN
#define IRButton31  0xFF48B7 // BLUEDN
#define IRButton32  0xFFC837 // SLOW
#define IRButton33  0xFF30CF // DIY1
#define IRButton34  0xFFB04F // DIY2
#define IRButton35  0xFF708F // DIY3
#define IRButton36  0xFFF00F // AUTO
#define IRButton37  0xFF10EF // DIY4
#define IRButton38  0xFF906F // DIY5
#define IRButton39  0xFF50AF // DIY6
#define IRButton40  0xFFD02F // FLASH
#define IRButton41  0xFF20DF // JUMP3
#define IRButton42  0xFFA05F // JUMP7
#define IRButton43  0xFF609F // FADE3
#define IRButton44  0xFFE01F // FADE7

String remoteButtonName[num_of_buttons] = {"Empty", "INC", "DEC", "PLAY", "PWR", "RED", "GREEN", "BLUE", "WHITE", 
                                     "ORANGE a", "LIME b", "COBALT c", "LTPURPLE d", "e", "fPink", "g", "h", 
                                     "i", "j", "k", "l", "YELLOW m", "n", "DKPURPLE o", "CYAN p", "REDUP", "GREENUP", "BLUEUP", "QUICK", 
                                     "REDDN", "GREENDN", "BLUEDN", "SLOW", "DIY1", "DIY2", "DIY3", "AUTO", "DIY4",
                                     "DIY5", "DIY6", "FLASH", "JUMP3", "JUMP7", "FADE3", "FADE7"};

#endif
//********************************************************

#define IR_JUNK     0xFFFFFFFF
//********************************************************
