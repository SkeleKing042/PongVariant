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


//----------------------------------//
//          BALL SETTINGS			//
//----------------------------------//

#define STARTINGOFFSETSCALAR		0.1
#define INITIALBALLSPEED			1
#define BALLSPEEDINCREASE			0.1
#define BALLSIZE					2
#define BALLCOLISIONCHECKCOOLDOWN	5


//----------------------------------//
//     SCORE DISPLAY SETTINGS		//
//----------------------------------//


#define TEXTOFFSETX					0
#define TEXTOFFSETY					SCREENSIZE * 0.0833
#define TEXTSIZE					SCREENSIZE - (SCREENSIZE * 0.0833)


//----------------------------------//
//          RNG SETTINGS			//
//----------------------------------//

#define MAXRANDOMSTARTPOSTION		360
#define RANDOMANGLEADDITION			21

//----------------------------------//
//			   EXTRAS				//
//----------------------------------//

#define NOTEXACTLYBLACK				CLITERAL(Color){40, 40, 40, 255}