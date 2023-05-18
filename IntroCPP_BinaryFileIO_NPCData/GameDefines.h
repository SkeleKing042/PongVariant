#pragma once //never twice

//----------------------------------//
//        SCREEN SETTINGS			//
//----------------------------------//

#define SCREENSIZE					300
#define FPS							60


//----------------------------------//
//         PADDLE SETTINGS			//
//----------------------------------//

#define PADDLEPOSOFFSET				10.0
#define PADDLESPEED					0.04
#define PADDLEWIDTH					10.0
#define PADDLEHEIGHT				50.0
#define MOVEPADDLELEFT				KEY_LEFT
#define MOVEPADDLERIGHT				KEY_RIGHT


//----------------------------------//
//          BALL SETTINGS			//
//----------------------------------//

#define STARTINGOFFSETSCALAR		0.1
#define INITIALBALLSPEED			3.0
#define BALLSCORELIMIT				20.0
#define BALLMAXSPEED				3.0
#define BALLSPEEDSCALAR				((BALLMAXSPEED - INITIALBALLSPEED)/BALLSCORELIMIT)
#define BALLSIZE					2.0
#define BALLCOLISIONCHECKCOOLDOWN	5.0


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
#define GOSCORESPACING				10
#define GOSCOREMOVEMENTMULTIPLIER	4

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
#define STARTBUTTONTEXT				"Start"
#define STARTBUTTONCHARS			5.0
#define STARTINPUT					KEY_ENTER

// QUIT BUTTON //
#define QUITBUTTONX					SCREENSIZE / 2.0 + BUTTONSPACING
#define QUITBUTTONY					STARTBUTTONY
#define QUITBUTTONTEXT				"Quit"
#define QUITBUTTONCHARS				4.0

// BUTTON TEXT //
#define MENUTEXTSIZE				SCREENSIZE * 0.054

// TITLE TEXT //
#define TITLETEXT					"PO"
#define TITLEXPOS					0
#define TITLEYPOS					SCREENSIZE * 0.084
#define TITLESIZE					SCREENSIZE * 0.7667
#define TITLEMOVEMENTSCALE			2.0

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}
#define DEEPRED						CLITERAL(Color){80, 0, 0, 128}
#define DEEPERRED					CLITERAL(Color){40, 0, 0, 255}
#define HIDDENWHITE					CLITERAL(Color){255, 255, 255, 191}
#define PURERED						CLITERAL(Color){255,0,0,255}
#define PUREGREEN					CLITERAL(Color){0,255,0,255}
#define PUREBLUE					CLITERAL(Color){0,0,255,255}