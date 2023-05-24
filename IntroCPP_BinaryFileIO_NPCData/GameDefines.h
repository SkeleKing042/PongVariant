#pragma once //never twice

//----------------------------------//
//        SCREEN SETTINGS			//
//----------------------------------//

#define SCREENSIZE					600
#define FPS							60


//----------------------------------//
//		 DIFFICULTY SCALES			//
//----------------------------------//

#define TIER1						1.0
#define TIER2						2.0
#define TIER3						3.0
#define TIER4						4.0
#define TIER5						5.0



//----------------------------------//
//         PADDLE SETTINGS			//
//----------------------------------//

#define PADDLEPOSOFFSET				SCREENSIZE * 0.034
#define PADDLESPEED					0.02
#define PADDLEWIDTH					SCREENSIZE * 0.034
#define PADDLEHEIGHT				SCREENSIZE * 0.167
#define MOVEPADDLELEFT				KEY_LEFT
#define MOVEPADDLERIGHT				KEY_RIGHT


//----------------------------------//
//          BALL SETTINGS			//
//----------------------------------//

#define STARTINGOFFSETSCALAR		SCREENSIZE * 0.00034
#define INITIALBALLSPEED			SCREENSIZE * 0.0033
#define BALLSCORELIMIT				20
#define BALLMAXSPEED				SCREENSIZE * 0.01
#define BALLSPEEDSCALAR				((BALLMAXSPEED - INITIALBALLSPEED)/BALLSCORELIMIT)
#define BALLSIZE					SCREENSIZE * 0.0067
#define BALLCOLISIONCHECKCOOLDOWN	5


//----------------------------------//
//    GAME TEXT DISPLAY SETTINGS	//
//----------------------------------//

// SCORE //
#define SCORETEXTOFFSETX			0
#define SCORETEXTOFFSETY			(SCREENSIZE * 0.0833)
#define SCORETEXTSIZE				(SCREENSIZE - (SCREENSIZE * 0.084))

// GAME OVER //
#define OUTLINESIZE					(SCREENSIZE * 0.0033)
#define GOTEXTOFFSETX				SCREENSIZE * 0.0067
#define GOTEXTSIZE					SCREENSIZE * 0.197
#define GOTEXTOFFSETY				SCREENSIZE * 0.415
#define GOSCORESPACING				SCREENSIZE * 0.034
#define GOSCOREMOVEMENTMULTIPLIER	SCREENSIZE * 0.0134

#define NEXTKEY						KEY_ENTER


//----------------------------------//
//          RNG SETTINGS			//
//----------------------------------//

#define MAXRANDOMSTARTPOSTION		360
#define RANDOMANGLEADDITION			21


//----------------------------------//
//		 MAIN MENU SETTINGS			//
//----------------------------------//

// SHARED BUTTON SETTINGS //
#define BUTTONWIDTH					SCREENSIZE * 0.234
#define BUTTONHEIGHT				SCREENSIZE * 0.117
#define BUTTONSPACING				SCREENSIZE * 0.034

// START BUTTON //
#define STARTBUTTONX				SCREENSIZE / 2.0 - BUTTONWIDTH - BUTTONSPACING
#define STARTBUTTONY				SCREENSIZE - SCREENSIZE * 0.167
#define STARTBUTTONTEXT				"START"
#define STARTINPUT					KEY_ENTER

// DIFFICULTY TABS //
#define DIFFTABXMULTIPLIER			BUTTONWIDTH / 5.0
#define DIFFTABXOFFSET              SCREENSIZE * 0.0034
#define DIFFTABWIDTH				SCREENSIZE * 0.034
#define DIFFTABYOFFSET				SCREENSIZE - DIFFTABWIDTH
#define DIFFTABHEIGHT				DIFFTABWIDTH / 2.0

// QUIT BUTTON //
#define QUITBUTTONX					SCREENSIZE / 2.0 + BUTTONSPACING
#define QUITBUTTONY					STARTBUTTONY
#define QUITBUTTONTEXT				"QUIT"

// BUTTON TEXT //
#define MENUTEXTSIZE				SCREENSIZE * 0.054

// TITLE TEXT //
#define TITLETEXT					"PO"
#define TITLEXPOS					0
#define TITLEYPOS					SCREENSIZE * 0.084
#define TITLESIZE					SCREENSIZE * 0.7667
#define TITLEMOVEMENTSCALE			SCREENSIZE * 0.0067

//----------------------------------//
//      GAME MODE MENU SETTINGS		//
//----------------------------------//

#define MODEMENUBUTTONSPACING		SCREENSIZE * 0.034
#define MODEMENUSIDESPACING			SCREENSIZE - BUTTONSPACING * 2
#define MODEMENUBUTTONHEIGHT		SCREENSIZE * 0.1
#define MODEMENUBUTTONXOFFSET		MODEMENUBUTTONSPACING
#define MODEMENUBUTTONYOFFSET		MODEMENUBUTTONSPACING + 0.0667 * SCREENSIZE
#define MODEMENUEXTRAMODES			6
#define MODEMENUBUTTONSPERROW		2
#define MODEMENUNAMES				6

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

//---------//
// COLOURS //
//---------//

// PLAYER & BALL
#define PLAYERCOLOURA				CLITERAL(Color){245,245,245,255}
#define PLAYERCOLOURB				CLITERAL(Color){200,200,200,255}
#define BALLCOLOUR					CLITERAL(Color){255,255,255,255}

// MISC
#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}
#define DEEPRED						CLITERAL(Color){80, 0, 0, 128}
#define DEEPERRED					CLITERAL(Color){40, 0, 0, 255}
#define HIDDENWHITE					CLITERAL(Color){255, 255, 255, 191}
#define COVERBLACK					CLITERAL(Color){0,0,0,64}

// PURE
#define PURERED						CLITERAL(Color){255,0,0,255}
#define PUREGREEN					CLITERAL(Color){0,255,0,255}
#define PUREBLUE					CLITERAL(Color){0,0,255,255}

// DIFFICULTY SCALES
#define DIFF2						CLITERAL(Color){100, 0, 0, 64}
#define DIFF3						CLITERAL(Color){100, 0, 0, 128}
#define DIFF4						CLITERAL(Color){100, 0, 0, 192}
#define DIFF5						CLITERAL(Color){100, 0, 0, 255}