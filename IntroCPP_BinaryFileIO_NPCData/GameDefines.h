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
#define INITIALBALLSPEED			1.0
#define BALLSCORELIMIT				20.0
#define BALLMAXSPEED				3.0
#define BALLSPEEDSCALAR				((BALLMAXSPEED - INITIALBALLSPEED)/BALLSCORELIMIT)
#define BALLSIZE					2.0
#define BALLCOLISIONCHECKCOOLDOWN	5.0


//----------------------------------//
//      TEXT DISPLAY SETTINGS		//
//----------------------------------//

// SCORE //
#define SCORETEXTOFFSETX			0
#define SCORETEXTOFFSETY			(SCREENSIZE * 0.0833)
#define SCORETEXTSIZE				(SCREENSIZE - (SCREENSIZE * 0.0833))

// GAME OVER //
#define OUTLINESIZE					(SCREENSIZE * 0.0033)
#define GOTEXTOFFSETX				(SCREENSIZE * 0.0166)
#define GOTEXTSIZE					(SCREENSIZE * 0.2 - GOTEXTOFFSETX / 2.0)
#define GOTEXTOFFSETY				(SCREENSIZE / 2.0 - GOTEXTSIZE / 2.0 + GOTEXTOFFSETX / 2.0)


//----------------------------------//
//          RNG SETTINGS			//
//----------------------------------//

#define MAXRANDOMSTARTPOSTION		360
#define RANDOMANGLEADDITION			21

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}