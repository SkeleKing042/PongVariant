#pragma once //never twice

//----------------------------------//
//        SCREEN SETTINGS			//
//----------------------------------//

#define SCREENSIZE					300
#define FPS							60


//----------------------------------//
//         PADDLE SETTINGS			//
//----------------------------------//

#define PADDLEPOSOFFSET				10
#define PADDLESPEED					0.04
#define PADDLEWIDTH					10
#define PADDLEHEIGHT				50
#define MOVEPADDLELEFT				KEY_LEFT
#define MOVEPADDLERIGHT				KEY_RIGHT


//----------------------------------//
//          BALL SETTINGS			//
//----------------------------------//

#define STARTINGOFFSETSCALAR		0.1
#define INITIALBALLSPEED			1
#define BALLSCORELIMIT				20
#define BALLMAXSPEED				3
#define BALLSPEEDSCALAR				(double)((BALLMAXSPEED - INITIALBALLSPEED)/BALLSCORELIMIT)
#define BALLSIZE					2
#define BALLCOLISIONCHECKCOOLDOWN	5


//----------------------------------//
//      TEXT DISPLAY SETTINGS		//
//----------------------------------//

// SCORE //
#define SCORETEXTOFFSETX			0
#define SCORETEXTOFFSETY			(double)(SCREENSIZE * 0.0833)
#define SCORETEXTSIZE				(double)(SCREENSIZE - (SCREENSIZE * 0.0833))

// GAME OVER //
#define OUTLINESIZE					(double)(SCREENSIZE * 0.0033)
#define GOTEXTOFFSETX				(double)(SCREENSIZE * 0.0166)
#define GOTEXTSIZE					(double)(SCREENSIZE * 0.2 - GOTEXTOFFSETX / 2)
#define GOTEXTOFFSETY				(double)(SCREENSIZE / 2 - GOTEXTSIZE / 2 + GOTEXTOFFSETX / 2)


//----------------------------------//
//          RNG SETTINGS			//
//----------------------------------//

#define MAXRANDOMSTARTPOSTION		360
#define RANDOMANGLEADDITION			21

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}