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
#define BALLSPEEDINCREASE			0.1
#define BALLSIZE					2
#define BALLCOLISIONCHECKCOOLDOWN	5


//----------------------------------//
//      TEXT DISPLAY SETTINGS		//
//----------------------------------//

// SCORE //
#define SCORETEXTOFFSETX			0
#define SCORETEXTOFFSETY			SCREENSIZE * 0.0833
#define SCORETEXTSIZE				SCREENSIZE - (SCREENSIZE * 0.0833)

// GAME OVER //
#define GOTEXTOFFSETX				0
#define GOTEXTSIZE					SCREENSIZE * 0.2
#define GOTEXTOFFSETY				SCREENSIZE / 2 - GOTEXTSIZE / 2


//----------------------------------//
//          RNG SETTINGS			//
//----------------------------------//

#define MAXRANDOMSTARTPOSTION		360
#define RANDOMANGLEADDITION			21

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}