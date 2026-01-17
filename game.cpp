//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================
#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <fstream>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Food.h"
#include "Game.h"
using namespace std;
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
/*
 * Main Canvas drawing function.
 * */
 
//the only global variable
Game game;

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	
	
	
	//for restarting the game
	if(game.restart())
	{
	  
	  game.setScore(0);
	  game.setPaddleLength(50);
	  game.setBallSpeed(5);
	  game.setTimeForPower3(0);
	  game.setTimeForPower4(0);
	  game.setTimeForPower5(0);
	  game.setBallPowerActive1(0);
	  game.setBallPowerActive2(0);
	  game.setBallPowerActive3(0);
	  game.setBallPowerActive4(0);
	  game.setBallPowerActive5(0);
	  game.setTotalLives(2);
	  game.setBallReset(1);
	  game.setBallResetTime(300);
	  game.setLevel(1);
	  game.setPaused(0);
	  game.setEnd(0);
	  game.setStored(0);
	  game.setSeeScore(0);
	  game.setRestart(0);
	  game.getBall().setX((1020/2) + 10);
          game.getBall().setY(840/2);
          game.getBall2().setShow(0); 
	  game.getBall3().setShow(0);	 
	  game.setBallDirectionY("upY");
	  game.setBallDirectionX("upX");
	  //resetting bricks and power ups
	  for(int i = 0; i< 8; i++)
	  {
		for(int j = 0; j<5 ; j++)
		{
		   game.getBricks()[i][j].reset();
		   game.getPower()[i][j].reset();   
	        }
          }
          
          for(int i = 0; i< 20; i++)
	  {
		for(int j = 0; j<5 ; j++)
		{
		   game.getBricks2()[i][j].reset();
		   game.getPower2()[i][j].reset();
	        }
          }
		
	  for(int i = 0; i< 12; i++)
	  {
		for(int j = 0; j<11 ; j++)
		{
		  game.getBricks3()[i][j].reset();
		  game.getPower3()[i][j].reset();
	        }
          }   
	   
	   
	}
	//for viewing highscores stored in file
	else
	if(game.SeeHighScore())
	{
	    glClear(GL_COLOR_BUFFER_BIT);
	    
	    DrawString(480, 460, "Press B to go back" , colors[RED]);
	    ifstream myfile("highscores.txt");
		if(myfile.is_open())
	      {
		int i = 0;
		string line;
               while (getline(myfile, line))                                                         
	       {
	        DrawString(280, 320 + i, line, colors[WHITE]);
	        i = i+20;
	       } 
	       myfile.close();
	      i=0;
	      }
	      
	       glutSwapBuffers();
	
	}
	//for viewing scores stored in file
	else
	if(game.SeeScore())
	{
	    glClear(GL_COLOR_BUFFER_BIT);
	    
	    DrawString(480, 460, "Press B to go back" , colors[RED]);
	    ifstream myfile("scores.txt");
		if(myfile.is_open())
	      {
		int i = 0;
		string line;
               while (getline(myfile, line))                                                         
	       {
	        DrawString(280, 320 + i, line, colors[WHITE]);
	        i = i+20;
	       } 
	       myfile.close();
	      i=0;
	      }
	      
	       glutSwapBuffers();
	}
	//menu system when game ends
	else
	if(game.End())
	{
	   glClear(GL_COLOR_BUFFER_BIT);
	   DrawString(480, 460, "Congratulations!! You win" , colors[GREEN]);
	   DrawString(480, 440, "Score = " + to_string(game.getScore()) , colors[MISTY_ROSE]);
	   DrawString(480, 420, "Press S to view Scores " , colors[MISTY_ROSE]);
	   DrawString(480, 400, "Press R to Restart " , colors[MISTY_ROSE]);
	   DrawString(480, 380, "Press H to view HighScores " , colors[MISTY_ROSE]);
	   
	   glutSwapBuffers();
	}
	//menu system when game is paused
	else
	if(game.Paused())
	{
	   
	   glClear(GL_COLOR_BUFFER_BIT);
	   DrawString(480, 460, "Press B to resume" , colors[RED]);
	   DrawString(480, 440, "Press S to view Scores " , colors[MISTY_ROSE]);
	   DrawString(480, 420, "Press R to Restart " , colors[MISTY_ROSE]);
	   DrawString(480, 400, "Press H to view HighScores " , colors[MISTY_ROSE]);
	   
	   glutSwapBuffers();
	   
	
	}
	//menu system when lives are 0
	else
	if(game.getTotalLives() == 0)
	{
	   glClear(GL_COLOR_BUFFER_BIT);
	   DrawString(480, 460, "GAME OVER!!" , colors[RED]);
	   DrawString(480, 440, "Score = " + to_string(game.getScore()) , colors[MISTY_ROSE]);
	   DrawString(480, 420, "Press S to view Scores " , colors[MISTY_ROSE]);
	   DrawString(480, 400, "Press R to Restart " , colors[MISTY_ROSE]);
	   DrawString(480, 380, "Press H to view HighScores " , colors[MISTY_ROSE]);
	   
	   
	   //storing score only once
	   if(!game.Stored())
	   {
	       //storing highscore
	      if(game.getScore() > game.getHighscore())
	      {
	        game.setHighscore(game.getScore());
	        std::ofstream scorefile;
	        scorefile.open("highscores.txt" , std::ios::app);
	        if(scorefile.is_open())
	        {
		
		  scorefile <<game.getHighscore()<<endl;                                               
		  scorefile.close();
	        }
	        else
	        {
	         // Handle file opening error
		  std::cerr << "Error opening file!" << std::endl;
	        }

	      }
	   
	   
	       //storing highscore
	      std::ofstream scorefile;
	      scorefile.open("scores.txt" , std::ios::app);
	      if(scorefile.is_open())
	      {
		
		scorefile <<game.getScore()<<endl;                                               
		scorefile.close();
	      }
	      else
	      {
	       // Handle file opening error
		std::cerr << "Error opening file!" << std::endl;
	      }
	      
	      game.setStored(1);
           }

	   glutSwapBuffers();
	}
	//menu when player loses a life
	else
	if(game.getBallReset())
	{ 
	          glClear(GL_COLOR_BUFFER_BIT);
	          
	          if(game.getBallSpeed() != 5)
	          {
	            game.setBallSpeed(5);	      
		    game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
	            game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
	          }
	          
	          
	           if(game.getBallResetTime() != 0)
	           {
	             DrawString(480, 460, "Get Ready!!" , colors[RED]);
	           }
	           game.setBallResetTime(game.getBallResetTime() - 1);
	           if(game.getBallResetTime() == 0)
	           {
	            game.setBallReset(0);
	           }
	         
	          glutSwapBuffers();
	}
	//whole game
	else
	{
	        
	        glClear(GL_COLOR_BUFFER_BIT);
	        //top data
		DrawString(70, 800, "Score = " + to_string(game.getScore()) , colors[MISTY_ROSE]);
		DrawString(210, 800, "23i-2552", colors[MISTY_ROSE]);
		DrawString(360, 800, "Moiz Khalid", colors[MISTY_ROSE]);
		DrawString(510, 800, "HighScore = "  + to_string(game.getHighscore()), colors[MISTY_ROSE]);
		DrawString(900, 820, "Lives = " + to_string(game.getTotalLives()) , colors[MISTY_ROSE]);
		
		
		//drawing paddle according to color
		if(game.getPaddle().getColor() == 0)
		{
		  DrawLine(game.getPaddle().getX()-game.getPaddleLength() , game.getPaddle().getY() , game.getPaddle().getX()+game.getPaddleLength() , game.getPaddle().getY() , 50 , colors[GREEN]);
                  if(game.getLevel() == 3)
		  DrawLine(game.getPaddle2().getX()-game.getPaddleLength() , game.getPaddle2().getY() , game.getPaddle2().getX()+game.getPaddleLength() , game.getPaddle2().getY() , 50 , colors[GREEN]);
		}
		else
		if(game.getPaddle().getColor() == 1)
		{
		   DrawLine(game.getPaddle().getX()-game.getPaddleLength() , game.getPaddle().getY() , game.getPaddle().getX()+game.getPaddleLength() , game.getPaddle().getY() , 50 , colors[PINK]);
                  if(game.getLevel() == 3)
		  DrawLine(game.getPaddle2().getX()-game.getPaddleLength() , game.getPaddle2().getY() , game.getPaddle2().getX()+game.getPaddleLength() , game.getPaddle2().getY() , 50 , colors[PINK]);
		} 
		else
		if(game.getPaddle().getColor() == 2)
		{
		   DrawLine(game.getPaddle().getX()-game.getPaddleLength() , game.getPaddle().getY() , game.getPaddle().getX()+game.getPaddleLength() , game.getPaddle().getY() , 50 , colors[BLUE]);
                  if(game.getLevel() == 3)
		  DrawLine(game.getPaddle2().getX()-game.getPaddleLength() , game.getPaddle2().getY() , game.getPaddle2().getX()+game.getPaddleLength() , game.getPaddle2().getY() , 50 , colors[BLUE]);
		} 
		else
		if(game.getPaddle().getColor() == 3)
		{
		   DrawLine(game.getPaddle().getX()-game.getPaddleLength() , game.getPaddle().getY() , game.getPaddle().getX()+game.getPaddleLength() , game.getPaddle().getY() , 50 , colors[RED]);
                  if(game.getLevel() == 3)
		  DrawLine(game.getPaddle2().getX()-game.getPaddleLength() , game.getPaddle2().getY() , game.getPaddle2().getX()+game.getPaddleLength() , game.getPaddle2().getY() , 50 , colors[RED]);
		} 
		else
		if(game.getPaddle().getColor() == 4)
		{
		   DrawLine(game.getPaddle().getX()-game.getPaddleLength() , game.getPaddle().getY() , game.getPaddle().getX()+game.getPaddleLength() , game.getPaddle().getY() , 50 , colors[YELLOW]);
                  if(game.getLevel() == 3)
		  DrawLine(game.getPaddle2().getX()-game.getPaddleLength() , game.getPaddle2().getY() , game.getPaddle2().getX()+game.getPaddleLength() , game.getPaddle2().getY() , 50 , colors[YELLOW]);
		} 
		
		
		//drawing brick pattern for level 1
		
	     if(game.getLevel() == 1)
	     {	
			for(int i = 0; i<8; i++)
			{
				 for(int j = 0; j< 5; j++)
				 {
					  if(!game.getBricks()[i][j].getStatus())
					  {  
						     if(game.getBricks()[i][j].getC() == 0)
						     {
						      DrawLine( game.getBricks()[i][j].getX()-50 , game.getBricks()[i][j].getY() ,  game.getBricks()[i][j].getX()+50 , game.getBricks()[i][j].getY() , 0 , colors[GREEN]);
						     }
						     else
						     if(game.getBricks()[i][j].getC() == 1)
						     {
						      DrawLine( game.getBricks()[i][j].getX()-50 , game.getBricks()[i][j].getY() ,  game.getBricks()[i][j].getX()+50 , game.getBricks()[i][j].getY() , 0 , colors[PINK]);
						     }
						     else
						     if(game.getBricks()[i][j].getC() == 2)
						     {
						      DrawLine( game.getBricks()[i][j].getX()-50 , game.getBricks()[i][j].getY() ,  game.getBricks()[i][j].getX()+50 , game.getBricks()[i][j].getY() , 0 , colors[BLUE]);
						     }
						     else
						     if(game.getBricks()[i][j].getC() == 3)
						     {
						      DrawLine( game.getBricks()[i][j].getX()-50 , game.getBricks()[i][j].getY() ,  game.getBricks()[i][j].getX()+50 , game.getBricks()[i][j].getY() , 0 , colors[RED]);
						     }
						     else
						     if(game.getBricks()[i][j].getC() == 4)
						     {
						      DrawLine( game.getBricks()[i][j].getX()-50 , game.getBricks()[i][j].getY() ,  game.getBricks()[i][j].getX()+50 , game.getBricks()[i][j].getY() , 0 , colors[YELLOW]);
						     }
					  }
				 }
			}
	      }
	      else  // drawing bricks for level 2
	      if(game.getLevel() == 2)
	      {
			
			for(int i = 0; i<20; i++)
			{
				 for(int j = 0; j< 5; j++)
				 {
					  if(!game.getBricks2()[i][j].getStatus())
					  {  
						     if(game.getBricks2()[i][j].getC() == 0)
						     {
						      DrawLine( game.getBricks2()[i][j].getX()-25 , game.getBricks2()[i][j].getY() ,  game.getBricks2()[i][j].getX()+25 , game.getBricks2()[i][j].getY() , 0 , colors[GREEN]);
						     }
						     else
						     if(game.getBricks2()[i][j].getC() == 1)
						     {
						      DrawLine( game.getBricks2()[i][j].getX()-25 , game.getBricks2()[i][j].getY() ,  game.getBricks2()[i][j].getX()+25 , game.getBricks2()[i][j].getY() , 0 , colors[PINK]);
						     }
						     else
						     if(game.getBricks2()[i][j].getC() == 2)
						     {
						      DrawLine( game.getBricks2()[i][j].getX()-25 , game.getBricks2()[i][j].getY() ,  game.getBricks2()[i][j].getX()+25 , game.getBricks2()[i][j].getY() , 0 , colors[BLUE]);
						     }
						     else
						     if(game.getBricks2()[i][j].getC() == 3)
						     {
						      DrawLine( game.getBricks2()[i][j].getX()-25 , game.getBricks2()[i][j].getY() ,  game.getBricks2()[i][j].getX()+25 , game.getBricks2()[i][j].getY() , 0 , colors[RED]);
						     }
						     else
						     if(game.getBricks2()[i][j].getC() == 4)
						     {
						      DrawLine( game.getBricks2()[i][j].getX()-25 , game.getBricks2()[i][j].getY() ,  game.getBricks2()[i][j].getX()+25 , game.getBricks2()[i][j].getY() , 0 , colors[YELLOW]);
						     }
					     
					  }
				 }
			}
      
	      }
	      else // drawing bricks for level 3
	      if(game.getLevel() == 3)
	      {
	      
	          for(int i = 0; i<12; i++)
			{
				 for(int j = 0; j< 11; j++)
				 {
					  if(!game.getBricks3()[i][j].getStatus())
					  {  
						     if(game.getBricks3()[i][j].getC() == 0)
						     {
						      DrawLine( game.getBricks3()[i][j].getX()-25 , game.getBricks3()[i][j].getY() ,  game.getBricks3()[i][j].getX()+25 , game.getBricks3()[i][j].getY() , 0 , colors[GREEN]);
						     }
						     else
						     if(game.getBricks3()[i][j].getC() == 1)
						     {
						      DrawLine( game.getBricks3()[i][j].getX()-25 , game.getBricks3()[i][j].getY() ,  game.getBricks3()[i][j].getX()+25 , game.getBricks3()[i][j].getY() , 0 , colors[PINK]);
						     }
						     else
						     if(game.getBricks3()[i][j].getC() == 2)
						     {
						      DrawLine( game.getBricks3()[i][j].getX()-25 , game.getBricks3()[i][j].getY() ,  game.getBricks3()[i][j].getX()+25 , game.getBricks3()[i][j].getY() , 0 , colors[BLUE]);
						     }
						     else
						     if(game.getBricks3()[i][j].getC() == 3)
						     {
						      DrawLine( game.getBricks3()[i][j].getX()-25 , game.getBricks3()[i][j].getY() ,  game.getBricks3()[i][j].getX()+25 , game.getBricks3()[i][j].getY() , 0 , colors[RED]);
						     }
						     else
						     if(game.getBricks3()[i][j].getC() == 4)
						     {
						      DrawLine( game.getBricks3()[i][j].getX()-25 , game.getBricks3()[i][j].getY() ,  game.getBricks3()[i][j].getX()+25 , game.getBricks3()[i][j].getY() , 0 , colors[YELLOW]);
						     }
					     
					  }
				 }
			}
	      
	      }	
		
		
		//checking for brick collision for level 1
		
	    if(game.getLevel() == 1)
	    {	
		for(int i = 0; i<8; i++)
		{
		 for(int j = 0; j< 5; j++)
		 {
			  if(!game.getBricks()[i][j].getStatus())
			  {
			     if( (game.getBall().getY() - 10 == game.getBricks()[i][j].getY() && ((game.getBall().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall().getX()<= game.getBricks()[i][j].getX() + 50))))
			     {
				 game.setBallDirectionY("upY");       
				 game.getBricks()[i][j].setHits(); 
				 
				 game.getBall().setColor(game.getBricks()[i][j].getC());       
			     }
			     if( (game.getBall().getY() == game.getBricks()[i][j].getY() && ((game.getBall().getX() + 10 == game.getBricks()[i][j].getX() - 50 || game.getBall().getX() - 10 == game.getBricks()[i][j].getX() + 50) ) ))
			     {   
			         if(game.getBallDirectionY() == "downY")
				 game.setBallDirectionY("upY");
				 else
				 game.setBallDirectionY("downY");
				 game.getBricks()[i][j].setHits();  
				 game.getBall().setColor(game.getBricks()[i][j].getC());     
			     }
			
			
			     if( game.getBall().getY() + 10 == game.getBricks()[i][j].getY() && (((game.getBall().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall().getX()<= game.getBricks()[i][j].getX() + 50))) )
			     {
				 game.setBallDirectionY("downY");       
				 game.getBricks()[i][j].setHits();      
				 game.getBall().setColor(game.getBricks()[i][j].getC()); 
			     }
			     
			     
			     if(game.getBallPowerActive5())
			     {
			     
		             if( game.getBall2().getY() - 10 == game.getBricks()[i][j].getY() && ((game.getBall2().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall2().getX()<= game.getBricks()[i][j].getX() + 50))) 
			     {
				 game.setBall2DirectionY("upY");       
				 game.getBricks()[i][j].setHits();       
			     }
			     
			     
			      if( (game.getBall2().getY() == game.getBricks()[i][j].getY() && ((game.getBall2().getX() + 10 == game.getBricks()[i][j].getX() - 50 || game.getBall2().getX() - 10 == game.getBricks()[i][j].getX() + 50) ) ) )
			     {
				 if(game.getBall2DirectionY() == "downY")
				 game.setBall2DirectionY("upY");
				 else
				 game.setBall2DirectionY("downY");
				 game.getBricks()[i][j].setHits();      
			     }
			
			
			     if( game.getBall2().getY() + 10 == game.getBricks()[i][j].getY() && ((game.getBall2().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall2().getX()<= game.getBricks()[i][j].getX() + 50)))
			     {
				 game.setBall2DirectionY("downY");       
				 game.getBricks()[i][j].setHits();       
			     }
			     
			     
			     
			      if( game.getBall3().getY() - 10 == game.getBricks()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall3().getX()<= game.getBricks()[i][j].getX() + 50)) )
			     {
				 game.setBall3DirectionY("upY");       
				 game.getBricks()[i][j].setHits();       
			     }
			     
			     
			     
			     if( (game.getBall3().getY() == game.getBricks()[i][j].getY() && ((game.getBall3().getX() + 10 == game.getBricks()[i][j].getX() - 50 || game.getBall3().getX() - 10 == game.getBricks()[i][j].getX() + 50) ) ))
			     {
				 if(game.getBall3DirectionY() == "downY")
				 game.setBall3DirectionY("upY");
				 else
				 game.setBall3DirectionY("downY");
				 game.getBricks()[i][j].setHits();       
			     }
			
			
			     if( game.getBall3().getY() + 10 == game.getBricks()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks()[i][j].getX() - 50 && game.getBall3().getX()<= game.getBricks()[i][j].getX() + 50)) )
			     {
				 game.setBall3DirectionY("downY");       
				 game.getBricks()[i][j].setHits();       
			     }

			     }		     
			
			  if(game.getBricks()[i][j].getStatus())
			  {
			    
			    game.setScore(game.getScore() + 1);
			    
			    //for moving to next level
			    if(game.getScore() == 40)
			    {
			           game.setLevel(2);
			           game.getBall().setX((1020/2) + 10);
				   game.getBall().setY(840/2);
				   game.getBall2().setShow(0); 
				   game.getBall3().setShow(0);
				   game.setBallReset(1);
				   game.setBallResetTime(300);
				   game.setBallDirectionY("upY");
				   game.setBallDirectionX("upX");
				   game.setPaddleLength(50);
				   game.setBallPowerActive3(0);
				   game.setBallPowerActive4(0);
				   game.setBallPowerActive5(0);
				   game.getPaddle().setX((1020/2));
				   game.getPaddle().setY(50);
				   game.setTotalLives(2);
				   game.getPaddle().setColor(1);
		   		   game.getBall().setColor(3);
			    }
			   
			   
			  }
			  
			  
			  }
			  
			  
			  if(game.getBricks()[i][j].getStatus())
			  {
			    //command to make the powerups fall
			    if(!game.getPower()[i][j].isActive())
			    {
			       game.getPower()[i][j].setActive(1); 
			    }
	 
			  }
		   }
		 }
		 
		}
		else //checking for brick collision for level 2
		if(game.getLevel() == 2)
                {
                
                for(int i = 0; i<20; i++)
		{
		 for(int j = 0; j< 5; j++)
		 {
			  if(!game.getBricks2()[i][j].getStatus())
			  {
			     if( game.getBall().getY() - 10 == game.getBricks2()[i][j].getY() && ((game.getBall().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall().getX()<= game.getBricks2()[i][j].getX() + 25)) )
			     {
				 game.setBallDirectionY("upY");       
				 game.getBricks2()[i][j].setHits(); 
				 game.getBall().setColor(game.getBricks2()[i][j].getC());      
			     }
			     
			     
			     if( (game.getBall().getY() == game.getBricks2()[i][j].getY() && ((game.getBall().getX() + 10 == game.getBricks2()[i][j].getX() - 25 || game.getBall().getX() - 10 == game.getBricks2()[i][j].getX() + 25) ) ))
			     {   
			         if(game.getBallDirectionY() == "downY")
				 game.setBallDirectionY("upY");
				 else
				 game.setBallDirectionY("downY");
				 game.getBricks()[i][j].setHits();     
				 game.getBall().setColor(game.getBricks2()[i][j].getC());  
			     }
			
			     if( game.getBall().getY() + 10 == game.getBricks2()[i][j].getY() && ((game.getBall().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall().getX()<= game.getBricks2()[i][j].getX() + 25) ))
			     {
				 game.setBallDirectionY("downY");       
				 game.getBricks2()[i][j].setHits();  
				 game.getBall().setColor(game.getBricks2()[i][j].getC());     
			     }
			     
			     
			     if(game.getBallPowerActive5())
			     {
			     
				   if( (game.getBall2().getY() - 10 == game.getBricks2()[i][j].getY()  && ((game.getBall2().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall2().getX()<= game.getBricks2()[i][j].getX() + 25))) )
			     {
				 game.setBall2DirectionY("upY");       
				 game.getBricks2()[i][j].setHits();       
			     }
			
			
			     if( game.getBall2().getY() == game.getBricks2()[i][j].getY() && ((game.getBall2().getX() - 10 >= game.getBricks2()[i][j].getX() - 25 && game.getBall2().getX() - 10 <= game.getBricks2()[i][j].getX() + 25) || (game.getBall2().getX() + 10 >= game.getBricks2()[i][j].getX() - 25 && game.getBall2().getX() + 10 <= game.getBricks2()[i][j].getX() + 25)) )
			     {
				 if(game.getBall2DirectionY() == "downY")
				 game.setBall2DirectionY("upY");
				 else
				 game.setBall2DirectionY("downY");
				 game.getBricks()[i][j].setHits();      
			     }
			
			     if( game.getBall2().getY() + 10 == game.getBricks2()[i][j].getY() && ((game.getBall2().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall2().getX()<= game.getBricks2()[i][j].getX() + 25)) )
			     {
				 game.setBall2DirectionY("downY");       
				 game.getBricks2()[i][j].setHits();       
			     }
			     
			     
			     
			      if( game.getBall3().getY() - 10 == game.getBricks2()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall3().getX()<= game.getBricks2()[i][j].getX() + 25)) )
			     {
				 game.setBall3DirectionY("upY");       
				 game.getBricks2()[i][j].setHits();       
			     }
			     
			     if((game.getBall3().getY() == game.getBricks2()[i][j].getY() && ((game.getBall3().getX() + 10 == game.getBricks2()[i][j].getX() - 25 || game.getBall3().getX() - 10 == game.getBricks2()[i][j].getX() + 25) ) ) )
			     {
				 if(game.getBall3DirectionY() == "downY")
				 game.setBall3DirectionY("upY");
				 else
				 game.setBall3DirectionY("downY");
				 game.getBricks()[i][j].setHits();       
			     }
			
			
			     if( game.getBall3().getY() + 10 == game.getBricks2()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks2()[i][j].getX() - 25 && game.getBall3().getX()<= game.getBricks2()[i][j].getX() + 25)) )
			     {
				 game.setBall3DirectionY("downY");       
				 game.getBricks2()[i][j].setHits();       
			     }

			     }		     
			
			  if(game.getBricks2()[i][j].getStatus())
			  { 
			  
			    bool allDestroyed = 1;
			    for(int i = 0; i< 20; i++)
			    {
			     for(int j = 0; j<5 ; j++)
			     {
			       if(!game.getBricks2()[i][j].getStatus())
			       {
			         allDestroyed = 0;
			       }
			     }
			    }
			  
			    game.setScore(game.getScore() + 1);
			    
			    //for moving to next level
			    if(game.getScore() == 140 || allDestroyed)
			    {
			           game.setLevel(3);
			           game.getBall().setX((1020/2) + 10);
				   game.getBall().setY(840/2);
				   game.getBall2().setShow(0); 
				   game.getBall3().setShow(0);
				   game.setBallReset(1);
				   game.setBallResetTime(300);
				   game.setBallDirectionY("upY");
				   game.setBallDirectionX("upX");
				   game.setPaddleLength(50);
				   game.setBallPowerActive3(0);
				   game.setBallPowerActive4(0);
				   game.setBallPowerActive5(0);
				   game.getPaddle().setX((1020/2));
				   game.getPaddle().setY(50);
				   game.setTotalLives(2);
				   game.getPaddle().setColor(1);
		   		   game.getBall().setColor(3);
			    }
			    
			  }
			  
			  
		       }
			  
			  
			  if(game.getBricks2()[i][j].getStatus())
			  {
			    //command to make the powerups fall
			    if(!game.getPower2()[i][j].isActive())
			    {
			       game.getPower2()[i][j].setActive(1); 
			    }
	 
			  }
		    }
		 }

                }
                else //checking for brick collision for level 3
                {
                
                       for(int i = 0; i<12; i++)
		{
		 for(int j = 0; j<11; j++)
		 {
			  if(!game.getBricks3()[i][j].getStatus())
			  {
			     if( game.getBall().getY() - 10 == game.getBricks3()[i][j].getY() && ((game.getBall().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBallDirectionY("upY");       
				 game.getBricks3()[i][j].setHits();  
				 game.getBall().setColor(game.getBricks3()[i][j].getC());     
			     }
			
			     
			     if( (game.getBall().getY() == game.getBricks3()[i][j].getY() && ((game.getBall().getX() + 10 == game.getBricks3()[i][j].getX() - 25 || game.getBall().getX() - 10 == game.getBricks3()[i][j].getX() + 25) ) ))
			     {   
			         if(game.getBallDirectionY() == "downY")
				 game.setBallDirectionY("upY");
				 else
				 game.setBallDirectionY("downY");
				 game.getBricks()[i][j].setHits();   
				 game.getBall().setColor(game.getBricks3()[i][j].getC());    
			     }
			     
			     if( game.getBall().getY() + 10 == game.getBricks3()[i][j].getY() && ((game.getBall().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBallDirectionY("downY");       
				 game.getBricks3()[i][j].setHits();   
				 game.getBall().setColor(game.getBricks3()[i][j].getC());    
			     }
			     
			     
			     if(game.getBallPowerActive5())
			     {
			     
		             if( game.getBall2().getY() - 10 == game.getBricks3()[i][j].getY() && ((game.getBall2().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall2().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBall2DirectionY("upY");       
				 game.getBricks3()[i][j].setHits();       
			     }
			     
			     
			     if( (game.getBall2().getY() == game.getBricks3()[i][j].getY() && ((game.getBall2().getX() + 10 == game.getBricks3()[i][j].getX() - 25 || game.getBall2().getX() - 10 == game.getBricks3()[i][j].getX() + 25) ) ) )
			     {
				 if(game.getBall2DirectionY() == "downY")
				 game.setBall2DirectionY("upY");
				 else
				 game.setBall2DirectionY("downY");
				 game.getBricks()[i][j].setHits();      
			     }
			
			     if( game.getBall2().getY() + 10 == game.getBricks3()[i][j].getY() && ((game.getBall2().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall2().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBall2DirectionY("downY");       
				 game.getBricks3()[i][j].setHits();       
			     }
			     
			     
			     
			      if( game.getBall3().getY() - 10 == game.getBricks3()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall3().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBall3DirectionY("upY");       
				 game.getBricks3()[i][j].setHits();       
			     }
			     
			     
			     if( (game.getBall3().getY() == game.getBricks3()[i][j].getY() && ((game.getBall3().getX() + 10 == game.getBricks3()[i][j].getX() - 25 || game.getBall3().getX() - 10 == game.getBricks3()[i][j].getX() + 25) ) )  )
			     {
				 if(game.getBall3DirectionY() == "downY")
				 game.setBall3DirectionY("upY");
				 else
				 game.setBall3DirectionY("downY");
				 game.getBricks()[i][j].setHits();       
			     }
			
			
			     if( game.getBall3().getY() + 10 == game.getBricks3()[i][j].getY() && ((game.getBall3().getX() >= game.getBricks3()[i][j].getX() - 25 && game.getBall3().getX()<= game.getBricks3()[i][j].getX() + 25)) )
			     {
				 game.setBall3DirectionY("downY");       
				 game.getBricks3()[i][j].setHits();       
			     }

			     }		     
			
			  if(game.getBricks3()[i][j].getStatus())
			  {
			    bool allDestroyed2 = 1;
			    for(int i = 0; i< 12; i++)
			    {
			     for(int j = 0; j<11 ; j++)
			     {
			       if(!game.getBricks3()[i][j].getStatus())
			       {
			         allDestroyed2 = 0;
			       }
			     }
			    }
			    
			    game.setScore(game.getScore() + 1);
			    
			    //for moving to end screen
			    if(allDestroyed2)
			    {
			    
			       game.setEnd(1);
			      
			    }
			    
			  }
			  
			  
			  }
			  
			  
			  if(game.getBricks3()[i][j].getStatus())
			  {
			    //command to make the powerups fall
			    if(!game.getPower3()[i][j].isActive())
			    {
			       game.getPower3()[i][j].setActive(1); 
			    }
	 
			  }
		   }
		 }
                
                
                
                
                
                
                
                
           }		 
		 
		 //checking for power ups level 1
		 if(game.getLevel() == 1)
		 {
		 
			 for(int i = 0; i< 8; i++)
			 {
				  for(int j = 0 ; j < 5; j++)
				  {
				    if(game.getPower()[i][j].isActive())
				    {
				    
					     if(game.getPower()[i][j].getType() == 1)
					       {
						  if(game.getPower()[i][j].Show())
						  DrawTriangle( game.getPower()[i][j].getX() - 10, game.getPower()[i][j].getY() - 20 , game.getPower()[i][j].getX() + 10, game.getPower()[i][j].getY() - 20 , game.getPower()[i][j].getX() , game.getPower()[i][j].getY(), colors[GREEN] );
						  
						  
						  if(game.getPaddle().getY() >= game.getPower()[i][j].getY() - 20 && game.getPaddle().getY() <= game.getPower()[i][j].getY() && (game.getPower()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) && (game.getPower()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower()[i][j].getY() - 20 == game.getPaddle().getY() && ((game.getPower()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()))))
						  {
						     if(game.getPaddleLength() != 75 && game.getPower()[i][j].Show())
						     {
						       game.setPaddleLength(game.getPaddleLength() + 25);
						       game.getPower()[i][j].setShow(0);
						     }
						     
						     
						     game.getPower()[i][j].setActive(0);

						  }

						  game.getPower()[i][j].setY(game.getPower()[i][j].getY() - 5);
						  
					       }
					       else
					       if(game.getPower()[i][j].getType() == 2)
					       {
						 if(game.getPower()[i][j].Show())
						 DrawSquare( game.getPower()[i][j].getX() , game.getPower()[i][j].getY() ,20,colors[PINK]);
						 
						 
						 
						 
						 
						 if(game.getPaddle().getY() >= game.getPower()[i][j].getY() && game.getPaddle().getY() <= game.getPower()[i][j].getY() && (game.getPower()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) )
						  {
						     if(game.getPaddleLength() != 25)
						     {
						       game.setPaddleLength(game.getPaddleLength() - 25);
						       game.getPower()[i][j].setShow(0);
						     }
						     
						     
						     game.getPower()[i][j].setActive(0);

						  }
						 
						 
						 
						 
						 game.getPower()[i][j].setY(game.getPower()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower()[i][j].getType() == 3)
					       {
					       
						 if(game.getPower()[i][j].Show())
						 DrawCircle(game.getPower()[i][j].getX(),game.getPower()[i][j].getY(),5,colors[BLUE]);
						 
						 
						 
						if(!game.getBallPowerActive3()) 
						{
						 if(game.getPaddle().getY() >= game.getPower()[i][j].getY() - 5 && game.getPaddle().getY() <= game.getPower()[i][j].getY() + 5 && (game.getPower()[i][j].getX() - 5 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() + 5 <=  game.getPaddle().getX() + game.getPaddleLength()) )
						  {
						   
						    game.setBallSpeed(1);
						    
						    game.setTimeForPower3(650);
						     
						    game.getPower()[i][j].setShow(0); 
						    
						    game.getPower()[i][j].setTimer(1);
						     game.setBallPowerActive3(1);
						     game.setBallPowerActive4(0);
						  
						  }
						 
						 } 
						  
						  if(game.getTimeForPower3() != 0 && game.getPower()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower3(game.getTimeForPower3() - 1);
						    
						    if(game.getTimeForPower3() == 0)
						    {
						      game.setBallSpeed(5);
						      
						      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
						      game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
						      
						      if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
							game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
							
							game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
							game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
						      
						      }
						      
						      game.getPower()[i][j].setActive(0);
						      game.getPower()[i][j].setShow(1);
						      game.getPower()[i][j].setTimer(0);
						      game.setBallPowerActive3(0);
						    }
						  }
						 
						 
						 
						 
						 game.getPower()[i][j].setY(game.getPower()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower()[i][j].getType() == 4)
					       {
						  if(game.getPower()[i][j].Show())
						  {
						    DrawSquare( game.getPower()[i][j].getX() , game.getPower()[i][j].getY() ,20,colors[RED]);
						    DrawSquare( game.getPower()[i][j].getX() + 20 , game.getPower()[i][j].getY() ,20,colors[RED]);
						  } 
						  
						      
						if(!game.getBallPowerActive4())
						{       
						      
						 if(game.getPaddle().getY() >= game.getPower()[i][j].getY() && game.getPaddle().getY() <= game.getPower()[i][j].getY() && ( (game.getPower()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX()  <=  game.getPaddle().getX() + game.getPaddleLength() )|| ((game.getPower()[i][j].getX() + 40 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() + 40  <=  game.getPaddle().getX() + game.getPaddleLength() ))))
						  {
						   
						    game.setBallSpeed(10);
						    
						    game.setTimeForPower4(650);
						    
						    game.getPower()[i][j].setTimer(1);
						    
						    game.setBallPowerActive3(0);
						    
						    game.getBall().setX(game.getBall().getX() + (10 - (game.getBall().getX()  % 10)));
						    game.getBall().setY(game.getBall().getY() + (10 - (game.getBall().getY()  % 10)));
						    
						    if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (10 - (game.getBall2().getX()  % 10)));
							game.getBall2().setY(game.getBall2().getY() + (10 - (game.getBall2().getY()  % 10)));
							
							game.getBall3().setX(game.getBall3().getX() + (10 - (game.getBall3().getX()  % 10)));
							game.getBall3().setY(game.getBall3().getY() + (10 - (game.getBall3().getY()  % 10)));
						      
						      }
						    
						    
						    game.getPower()[i][j].setShow(0); 
						     game.setBallPowerActive4(1);
						  
						  }
						  
						  
						 } 
						  
						  if(game.getTimeForPower4() != 0 && game.getPower()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower4(game.getTimeForPower4() - 1);
						    
						    if(game.getTimeForPower4() == 0)
						    {
						      game.setBallSpeed(5);
						      
						      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
						      game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
						      
						      if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
							game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
							
							game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
							game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
						      
						      }
						      
						      game.getPower()[i][j].setActive(0);
						      game.getPower()[i][j].setShow(1);
						      game.setBallPowerActive4(0);
						      game.getPower()[i][j].setTimer(0);
						    }
						  }

						  game.getPower()[i][j].setY(game.getPower()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower()[i][j].getType() == 5)
					       {
						  if(game.getPower()[i][j].Show())
						 DrawSquare( game.getPower()[i][j].getX() , game.getPower()[i][j].getY() ,20,colors[YELLOW]);
						 
						 
						if(!game.getBallPowerActive5())
						{ 
						 
						 if(game.getPaddle().getY() >= game.getPower()[i][j].getY() && game.getPaddle().getY() <= game.getPower()[i][j].getY() && (game.getPower()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) && !game.getBall2().Show() )
						 {
						   
						     game.setTimeForPower5(850);
						   
						     game.getBall2().setShow(1);
						     game.getBall3().setShow(1);
						     game.getPower()[i][j].setTimer(1);
						   
						   
						     if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "upY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      
						      if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "downY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("downX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "upY")
						      {
							game.setBall2DirectionX("upX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "downY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      } 
						   
						     game.getPower()[i][j].setShow(0);
						     game.setBallPowerActive5(1);
						 }
						 
						 }
						 
						   if(game.getTimeForPower5() != 0 && game.getPower()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower5(game.getTimeForPower5() - 1);
						    
						    if(game.getTimeForPower5() == 0)
						    {
						      
						      game.getBall2().setShow(0);
						      game.getBall3().setShow(0);
						      game.getPower()[i][j].setTimer(0);
						      game.getPower()[i][j].setActive(0);
						      game.getPower()[i][j].setShow(1);
						      game.setBallPowerActive5(0);
						    }
						  }
			 
						 game.getPower()[i][j].setY(game.getPower()[i][j].getY() - 5);
					       }

				    }
				  }
			 }
		}
		else  //checking for power ups level 2
		if(game.getLevel() == 2)
		{
		    
		  for(int i = 0; i< 20; i++)
		 {
		  for(int j = 0 ; j < 5; j++)
		  {
		    if(game.getPower2()[i][j].isActive())
		    {
		    
			     if(game.getPower2()[i][j].getType() == 1)
			       {
				  if(game.getPower2()[i][j].Show())
				  DrawTriangle( game.getPower2()[i][j].getX() - 10, game.getPower2()[i][j].getY() - 20 , game.getPower2()[i][j].getX() + 10, game.getPower2()[i][j].getY() - 20 , game.getPower2()[i][j].getX() , game.getPower2()[i][j].getY(), colors[GREEN] );
				  
				  
				  if(game.getPaddle().getY() >= game.getPower2()[i][j].getY() - 20 && game.getPaddle().getY() <= game.getPower2()[i][j].getY() && (game.getPower2()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) && (game.getPower2()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower2()[i][j].getY() - 20 == game.getPaddle().getY() && ((game.getPower2()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower2()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()))))
				  {
				     if(game.getPaddleLength() != 75 && game.getPower2()[i][j].Show())
				     {
				       game.setPaddleLength(game.getPaddleLength() + 25);
				       game.getPower2()[i][j].setShow(0);
				     }
				     
				     
				     game.getPower2()[i][j].setActive(0);

				  }

				  game.getPower2()[i][j].setY(game.getPower2()[i][j].getY() - 5);
				  
			       }
			       else
			       if(game.getPower2()[i][j].getType() == 2)
			       {
				 if(game.getPower2()[i][j].Show())
				 DrawSquare( game.getPower2()[i][j].getX() , game.getPower2()[i][j].getY() ,20,colors[PINK]);
				 
				 
				 
				 
				 
				 if(game.getPaddle().getY() >= game.getPower2()[i][j].getY() && game.getPaddle().getY() <= game.getPower2()[i][j].getY() && (game.getPower2()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) )
				  {
				     if(game.getPaddleLength() != 25)
				     {
				       game.setPaddleLength(game.getPaddleLength() - 25);
				       game.getPower2()[i][j].setShow(0);
				     }
				     
				     
				     game.getPower2()[i][j].setActive(0);

				  }
				 
				 
				 
				 
				 game.getPower2()[i][j].setY(game.getPower2()[i][j].getY() - 5);
			       }
			       else
			       if(game.getPower2()[i][j].getType() == 3)
			       {
			       
				 if(game.getPower2()[i][j].Show())
				 DrawCircle(game.getPower2()[i][j].getX(),game.getPower2()[i][j].getY(),5,colors[BLUE]);
				 
				 
				 
				if(!game.getBallPowerActive3()) 
				{
				 if(game.getPaddle().getY() >= game.getPower2()[i][j].getY() - 5 && game.getPaddle().getY() <= game.getPower2()[i][j].getY() + 5 && (game.getPower2()[i][j].getX() - 5 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() + 5 <=  game.getPaddle().getX() + game.getPaddleLength()) )
				  {
				   
				    game.setBallSpeed(1);
				    
				    game.setTimeForPower3(650);
				     
				    game.getPower2()[i][j].setShow(0); 
				    
				    game.getPower2()[i][j].setTimer(1);
				     game.setBallPowerActive3(1);
				     game.setBallPowerActive4(0);
				  
				  }
				 
				 } 
				  
				  if(game.getTimeForPower3() != 0 && game.getPower2()[i][j].getTimer())
				  {
				    
				    game.setTimeForPower3(game.getTimeForPower3() - 1);
				    
				    if(game.getTimeForPower3() == 0)
				    {
				      game.setBallSpeed(5);
				      
				      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
			              game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
				      
				      if(game.getBallPowerActive5())
				      {
				        
				        game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
			                game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
			                
			                game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
			                game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
				      
				      }
				      
				      game.getPower2()[i][j].setActive(0);
				      game.getPower2()[i][j].setShow(1);
				      game.getPower2()[i][j].setTimer(0);
				      game.setBallPowerActive3(0);
				    }
				  }
				 
				 
				 
				 
				 game.getPower2()[i][j].setY(game.getPower2()[i][j].getY() - 5);
			       }
			       else
			       if(game.getPower2()[i][j].getType() == 4)
			       {
				  if(game.getPower2()[i][j].Show())
				  {
				    DrawSquare( game.getPower2()[i][j].getX() , game.getPower2()[i][j].getY() ,20,colors[RED]);
				    DrawSquare( game.getPower2()[i][j].getX() + 20 , game.getPower2()[i][j].getY() ,20,colors[RED]);
				  } 
				  
				      
				if(!game.getBallPowerActive4())
				{       
				      
				 if(game.getPaddle().getY() >= game.getPower2()[i][j].getY() && game.getPaddle().getY() <= game.getPower2()[i][j].getY() && ( (game.getPower2()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX()  <=  game.getPaddle().getX() + game.getPaddleLength() )|| ((game.getPower2()[i][j].getX() + 40 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() + 40  <=  game.getPaddle().getX() + game.getPaddleLength() ))))
				  {
				   
				    game.setBallSpeed(10);
				    
				    game.setTimeForPower4(650);
				    
				    game.getPower2()[i][j].setTimer(1);
				    
				    game.setBallPowerActive3(0);
				    
				    game.getBall().setX(game.getBall().getX() + (10 - (game.getBall().getX()  % 10)));
			            game.getBall().setY(game.getBall().getY() + (10 - (game.getBall().getY()  % 10)));
			            
			            if(game.getBallPowerActive5())
				      {
				        
				        game.getBall2().setX(game.getBall2().getX() + (10 - (game.getBall2().getX()  % 10)));
			                game.getBall2().setY(game.getBall2().getY() + (10 - (game.getBall2().getY()  % 10)));
			                
			                game.getBall3().setX(game.getBall3().getX() + (10 - (game.getBall3().getX()  % 10)));
			                game.getBall3().setY(game.getBall3().getY() + (10 - (game.getBall3().getY()  % 10)));
				      
				      }
				    
				    
				    game.getPower2()[i][j].setShow(0); 
				     game.setBallPowerActive4(1);
				  
				  }
				  
				  
				 } 
				  
				  if(game.getTimeForPower4() != 0 && game.getPower2()[i][j].getTimer())
				  {
				    
				    game.setTimeForPower4(game.getTimeForPower4() - 1);
				    
				    if(game.getTimeForPower4() == 0)
				    {
				      game.setBallSpeed(5);
				      
				      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
			              game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
			              
			              if(game.getBallPowerActive5())
				      {
				        
				        game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
			                game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
			                
			                game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
			                game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
				      
				      }
				      
				      game.getPower2()[i][j].setActive(0);
				      game.getPower2()[i][j].setShow(1);
				      game.setBallPowerActive4(0);
				      game.getPower2()[i][j].setTimer(0);
				    }
				  }

				  game.getPower2()[i][j].setY(game.getPower2()[i][j].getY() - 5);
			       }
			       else
			       if(game.getPower2()[i][j].getType() == 5)
			       {
				  if(game.getPower2()[i][j].Show())
				 DrawSquare( game.getPower2()[i][j].getX() , game.getPower2()[i][j].getY() ,20,colors[YELLOW]);
				 
				 
				if(!game.getBallPowerActive5())
				{ 
				 
				 if(game.getPaddle().getY() >= game.getPower2()[i][j].getY() && game.getPaddle().getY() <= game.getPower2()[i][j].getY() && (game.getPower2()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower2()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) && !game.getBall2().Show() )
				 {
				   
				     game.setTimeForPower5(850);
				   
				     game.getBall2().setShow(1);
				     game.getBall3().setShow(1);
				     game.getPower2()[i][j].setTimer(1);
				   
				   
				     if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "upY")
				      {
				        game.setBall2DirectionX("downX");
	    			        game.setBall2DirectionY("upY");
	    			        game.setBall3DirectionX("upX");
	    			        game.setBall3DirectionY("downY");
				      }
				      
				      
				      if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "downY")
				      {
				        game.setBall2DirectionX("downX");
	    			        game.setBall2DirectionY("upY");
	    			        game.setBall3DirectionX("downX");
	    			        game.setBall3DirectionY("downY");
				      }
				      
				      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "upY")
				      {
				        game.setBall2DirectionX("upX");
	    			        game.setBall2DirectionY("upY");
	    			        game.setBall3DirectionX("upX");
	    			        game.setBall3DirectionY("downY");
				      }
				      
				      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "downY")
				      {
				        game.setBall2DirectionX("downX");
	    			        game.setBall2DirectionY("upY");
	    			        game.setBall3DirectionX("upX");
	    			        game.setBall3DirectionY("downY");
		                      } 
				   
				     game.getPower2()[i][j].setShow(0);
				     game.setBallPowerActive5(1);
				 }
				 
				 }
				 
				   if(game.getTimeForPower5() != 0 && game.getPower2()[i][j].getTimer())
				  {
				    
				    game.setTimeForPower5(game.getTimeForPower5() - 1);
				    
				    if(game.getTimeForPower5() == 0)
				    {
				      
				      game.getBall2().setShow(0);
				      game.getBall3().setShow(0);
		                      game.getPower2()[i][j].setTimer(0);
				      game.getPower2()[i][j].setActive(0);
				      game.getPower2()[i][j].setShow(1);
				      game.setBallPowerActive5(0);
				    }
				  }
	 
				 game.getPower2()[i][j].setY(game.getPower2()[i][j].getY() - 5);
			       }

		      }
		    }
		  }
		}
		else //checking for power ups level 1
		{
		
		        for(int i = 0; i< 12; i++)
			 {
				  for(int j = 0 ; j < 11; j++)
				  {
				    if(game.getPower3()[i][j].isActive())
				    {
				    
					     if(game.getPower3()[i][j].getType() == 1)
					       {
						  if(game.getPower3()[i][j].Show())
						  DrawTriangle( game.getPower3()[i][j].getX() - 10, game.getPower3()[i][j].getY() - 20 , game.getPower3()[i][j].getX() + 10, game.getPower3()[i][j].getY() - 20 , game.getPower3()[i][j].getX() , game.getPower3()[i][j].getY(), colors[GREEN] );
						  
						  
						  if(game.getPaddle().getY() >= game.getPower3()[i][j].getY() - 20 && game.getPaddle().getY() <= game.getPower3()[i][j].getY() && (game.getPower3()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) && (game.getPower3()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower3()[i][j].getY() - 20 == game.getPaddle().getY() && ((game.getPower3()[i][j].getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() - 10 <=  game.getPaddle().getX() + game.getPaddleLength()) || (game.getPower3()[i][j].getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() + 10 <=  game.getPaddle().getX() + game.getPaddleLength()))))
						  {
						     if(game.getPaddleLength() != 75 && game.getPower3()[i][j].Show())
						     {
						       game.setPaddleLength(game.getPaddleLength() + 25);
						       game.getPower3()[i][j].setShow(0);
						     }
						     
						     
						     game.getPower3()[i][j].setActive(0);

						  }

						  game.getPower3()[i][j].setY(game.getPower3()[i][j].getY() - 5);
						  
					       }
					       else
					       if(game.getPower3()[i][j].getType() == 2)
					       {
						 if(game.getPower3()[i][j].Show())
						 DrawSquare( game.getPower3()[i][j].getX() , game.getPower3()[i][j].getY() ,20,colors[PINK]);
						 
						 
						 
						 
						 
						 if(game.getPaddle().getY() >= game.getPower3()[i][j].getY() && game.getPaddle().getY() <= game.getPower3()[i][j].getY() && (game.getPower3()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) )
						  {
						     if(game.getPaddleLength() != 25)
						     {
						       game.setPaddleLength(game.getPaddleLength() - 25);
						       game.getPower3()[i][j].setShow(0);
						     }
						     
						     
						     game.getPower3()[i][j].setActive(0);

						  }
						 
						 
						 
						 
						 game.getPower3()[i][j].setY(game.getPower3()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower3()[i][j].getType() == 3)
					       {
					       
						 if(game.getPower3()[i][j].Show())
						 DrawCircle(game.getPower3()[i][j].getX(),game.getPower3()[i][j].getY(),5,colors[BLUE]);
						 
						 
						 
						if(!game.getBallPowerActive3()) 
						{
						 if(game.getPaddle().getY() >= game.getPower3()[i][j].getY() - 5 && game.getPaddle().getY() <= game.getPower3()[i][j].getY() + 5 && (game.getPower3()[i][j].getX() - 5 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() + 5 <=  game.getPaddle().getX() + game.getPaddleLength()) )
						  {
						   
						    game.setBallSpeed(1);
						    
						    game.setTimeForPower3(650);
						     
						    game.getPower3()[i][j].setShow(0); 
						    
						    game.getPower3()[i][j].setTimer(1);
						     game.setBallPowerActive3(1);
						     game.setBallPowerActive4(0);
						  
						  }
						 
						 } 
						  
						  if(game.getTimeForPower3() != 0 && game.getPower3()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower3(game.getTimeForPower3() - 1);
						    
						    if(game.getTimeForPower3() == 0)
						    {
						      game.setBallSpeed(5);
						      
						      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
						      game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
						      
						      if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
							game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
							
							game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
							game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
						      
						      }
						      
						      game.getPower3()[i][j].setActive(0);
						      game.getPower3()[i][j].setShow(1);
						      game.getPower3()[i][j].setTimer(0);
						      game.setBallPowerActive3(0);
						    }
						  }
						 
						 
						 
						 
						 game.getPower3()[i][j].setY(game.getPower3()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower3()[i][j].getType() == 4)
					       {
						  if(game.getPower3()[i][j].Show())
						  {
						    DrawSquare( game.getPower3()[i][j].getX() , game.getPower3()[i][j].getY() ,20,colors[RED]);
						    DrawSquare( game.getPower3()[i][j].getX() + 20 , game.getPower3()[i][j].getY() ,20,colors[RED]);
						  } 
						  
						      
						if(!game.getBallPowerActive4())
						{       
						      
						 if(game.getPaddle().getY() >= game.getPower3()[i][j].getY() && game.getPaddle().getY() <= game.getPower3()[i][j].getY() && ( (game.getPower3()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX()  <=  game.getPaddle().getX() + game.getPaddleLength() )|| ((game.getPower3()[i][j].getX() + 40 >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() + 40  <=  game.getPaddle().getX() + game.getPaddleLength() ))))
						  {
						   
						    game.setBallSpeed(10);
						    
						    game.setTimeForPower4(650);
						    
						    game.getPower3()[i][j].setTimer(1);
						    
						    game.setBallPowerActive3(0);
						    
						    game.getBall().setX(game.getBall().getX() + (10 - (game.getBall().getX()  % 10)));
						    game.getBall().setY(game.getBall().getY() + (10 - (game.getBall().getY()  % 10)));
						    
						    if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (10 - (game.getBall2().getX()  % 10)));
							game.getBall2().setY(game.getBall2().getY() + (10 - (game.getBall2().getY()  % 10)));
							
							game.getBall3().setX(game.getBall3().getX() + (10 - (game.getBall3().getX()  % 10)));
							game.getBall3().setY(game.getBall3().getY() + (10 - (game.getBall3().getY()  % 10)));
						      
						      }
						    
						    
						    game.getPower3()[i][j].setShow(0); 
						     game.setBallPowerActive4(1);
						  
						  }
						  
						  
						 } 
						  
						  if(game.getTimeForPower4() != 0 && game.getPower3()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower4(game.getTimeForPower4() - 1);
						    
						    if(game.getTimeForPower4() == 0)
						    {
						      game.setBallSpeed(5);
						      
						      game.getBall().setX(game.getBall().getX() + (5 - (game.getBall().getX()  % 5)));
						      game.getBall().setY(game.getBall().getY() + (5 - (game.getBall().getY()  % 5)));
						      
						      if(game.getBallPowerActive5())
						      {
							
							game.getBall2().setX(game.getBall2().getX() + (5 - (game.getBall2().getX()  % 5)));
							game.getBall2().setY(game.getBall2().getY() + (5 - (game.getBall2().getY()  % 5)));
							
							game.getBall3().setX(game.getBall3().getX() + (5 - (game.getBall3().getX()  % 5)));
							game.getBall3().setY(game.getBall3().getY() + (5 - (game.getBall3().getY()  % 5)));
						      
						      }
						      
						      game.getPower3()[i][j].setActive(0);
						      game.getPower3()[i][j].setShow(1);
						      game.setBallPowerActive4(0);
						      game.getPower3()[i][j].setTimer(0);
						    }
						  }

						  game.getPower3()[i][j].setY(game.getPower3()[i][j].getY() - 5);
					       }
					       else
					       if(game.getPower3()[i][j].getType() == 5)
					       {
						  if(game.getPower3()[i][j].Show())
						 DrawSquare( game.getPower3()[i][j].getX() , game.getPower3()[i][j].getY() ,20,colors[YELLOW]);
						 
						 
						if(!game.getBallPowerActive5())
						{ 
						 
						 if(game.getPaddle().getY() >= game.getPower3()[i][j].getY() && game.getPaddle().getY() <= game.getPower3()[i][j].getY() && (game.getPower3()[i][j].getX() >= game.getPaddle().getX() - game.getPaddleLength() && game.getPower3()[i][j].getX() <=  game.getPaddle().getX() + game.getPaddleLength()) && !game.getBall2().Show() )
						 {
						   
						     game.setTimeForPower5(850);
						   
						     game.getBall2().setShow(1);
						     game.getBall3().setShow(1);
						     game.getPower3()[i][j].setTimer(1);
						   
						   
						     if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "upY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      
						      if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "downY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("downX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "upY")
						      {
							game.setBall2DirectionX("upX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      }
						      
						      if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "downY")
						      {
							game.setBall2DirectionX("downX");
			    			        game.setBall2DirectionY("upY");
			    			        game.setBall3DirectionX("upX");
			    			        game.setBall3DirectionY("downY");
						      } 
						   
						     game.getPower3()[i][j].setShow(0);
						     game.setBallPowerActive5(1);
						 }
						 
						 }
						 
						   if(game.getTimeForPower5() != 0 && game.getPower3()[i][j].getTimer())
						  {
						    
						    game.setTimeForPower5(game.getTimeForPower5() - 1);
						    
						    if(game.getTimeForPower5() == 0)
						    {
						      
						      game.getBall2().setShow(0);
						      game.getBall3().setShow(0);
						      game.getPower3()[i][j].setTimer(0);
						      game.getPower3()[i][j].setActive(0);
						      game.getPower3()[i][j].setShow(1);
						      game.setBallPowerActive5(0);
						    }
						  }
			 
						 game.getPower3()[i][j].setY(game.getPower3()[i][j].getY() - 5);
					       }

				    }
				  }
			 }
	
		}
		
                
                //drawing ball according to color
		if(game.getBall().Show())
		{
		        if(game.getBall().getColor() == 0)
			DrawCircle(game.getBall().getX(), game.getBall().getY(), game.getBall().getRadius() ,colors[GREEN]);
			else
			if(game.getBall().getColor() == 1)
			DrawCircle(game.getBall().getX(), game.getBall().getY(), game.getBall().getRadius() ,colors[PINK]);
			else
			if(game.getBall().getColor() == 2)
			DrawCircle(game.getBall().getX(), game.getBall().getY(), game.getBall().getRadius() ,colors[BLUE]);
			else
			if(game.getBall().getColor() == 3)
			DrawCircle(game.getBall().getX(), game.getBall().getY(), game.getBall().getRadius() ,colors[RED]);
			else
			if(game.getBall().getColor() == 4)
			DrawCircle(game.getBall().getX(), game.getBall().getY(), game.getBall().getRadius() ,colors[YELLOW]);
		}
		if(game.getBall2().Show())
		{
			DrawCircle(game.getBall2().getX(), game.getBall2().getY(), game.getBall2().getRadius() ,colors[MAGENTA]);
		}
		if(game.getBall3().Show())
		{
			DrawCircle(game.getBall3().getX(), game.getBall3().getY(), game.getBall3().getRadius() ,colors[MAGENTA]);
		}
		
		
		//calculating movement of ball
		if(game.getBall().Show() && !game.getBall2().Show() && !game.getBall3().Show())
		{
			if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "upY")
			{
				game.getBall().setX(game.getBall().getX() + game.getBallSpeed());
				game.getBall2().setX(game.getBall().getX());
				game.getBall3().setX(game.getBall().getX());
				game.getBall().setY(game.getBall().getY() + game.getBallSpeed());
				game.getBall2().setY(game.getBall().getY());
				game.getBall3().setY(game.getBall().getY());
			}
			if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "upY")
			{
				game.getBall().setX(game.getBall().getX() - game.getBallSpeed());
				game.getBall2().setX(game.getBall().getX());
				game.getBall3().setX(game.getBall().getX());
				game.getBall().setY(game.getBall().getY() + game.getBallSpeed());
				game.getBall2().setY(game.getBall().getY());
				game.getBall3().setY(game.getBall().getY());
			}
			if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "downY")
			{
				game.getBall().setX(game.getBall().getX() + game.getBallSpeed());
				game.getBall2().setX(game.getBall().getX());
				game.getBall3().setX(game.getBall().getX());
				game.getBall().setY(game.getBall().getY() - game.getBallSpeed());
				game.getBall2().setY(game.getBall().getY());
				game.getBall3().setY(game.getBall().getY());
			}
			if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "downY")
			{
				game.getBall().setX(game.getBall().getX() - game.getBallSpeed());
				game.getBall2().setX(game.getBall().getX());
				game.getBall3().setX(game.getBall().getX());
				game.getBall().setY(game.getBall().getY() - game.getBallSpeed());
				game.getBall2().setY(game.getBall().getY());
				game.getBall3().setY(game.getBall().getY());
			}
		}
		else
		{
		        //calculating movement of all 3 balls
			if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "upY")
			{
				game.getBall().setX(game.getBall().getX() + game.getBallSpeed());
				
				game.getBall().setY(game.getBall().getY() + game.getBallSpeed());
		
			}
			if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "upY")
			{
				game.getBall().setX(game.getBall().getX() - game.getBallSpeed());
				
				game.getBall().setY(game.getBall().getY() + game.getBallSpeed());
				
			}
			if(game.getBallDirectionX() == "upX" && game.getBallDirectionY() == "downY")
			{
				game.getBall().setX(game.getBall().getX() + game.getBallSpeed());
				
				game.getBall().setY(game.getBall().getY() - game.getBallSpeed());
				
			}
			if(game.getBallDirectionX() == "downX" && game.getBallDirectionY() == "downY")
			{
				game.getBall().setX(game.getBall().getX() - game.getBallSpeed());
				
				game.getBall().setY(game.getBall().getY() - game.getBallSpeed());
				
			}
		   
		
		       
		       if(game.getBall2DirectionX() == "upX" && game.getBall2DirectionY() == "upY")
			{
				game.getBall2().setX(game.getBall2().getX() + game.getBallSpeed());
				
				game.getBall2().setY(game.getBall2().getY() + game.getBallSpeed());
		
			}
			if(game.getBall2DirectionX() == "downX" && game.getBall2DirectionY() == "upY")
			{
				game.getBall2().setX(game.getBall2().getX() - game.getBallSpeed());
				
				game.getBall2().setY(game.getBall2().getY() + game.getBallSpeed());
				
			}
			if(game.getBall2DirectionX() == "upX" && game.getBall2DirectionY() == "downY")
			{
				game.getBall2().setX(game.getBall2().getX() + game.getBallSpeed());
				
				game.getBall2().setY(game.getBall2().getY() - game.getBallSpeed());
				
			}
			if(game.getBall2DirectionX() == "downX" && game.getBall2DirectionY() == "downY")
			{
				game.getBall2().setX(game.getBall2().getX() - game.getBallSpeed());
				
				game.getBall2().setY(game.getBall2().getY() - game.getBallSpeed());
				
			}
			
			
			
			 if(game.getBall3DirectionX() == "upX" && game.getBall3DirectionY() == "upY")
			{
				game.getBall3().setX(game.getBall3().getX() + game.getBallSpeed());
				
				game.getBall3().setY(game.getBall3().getY() + game.getBallSpeed());
		
			}
			if(game.getBall3DirectionX() == "downX" && game.getBall3DirectionY() == "upY")
			{
				game.getBall3().setX(game.getBall3().getX() - game.getBallSpeed());
				
				game.getBall3().setY(game.getBall3().getY() + game.getBallSpeed());
				
			}
			if(game.getBall3DirectionX() == "upX" && game.getBall3DirectionY() == "downY")
			{
				game.getBall3().setX(game.getBall3().getX() + game.getBallSpeed());
				
				game.getBall3().setY(game.getBall3().getY() - game.getBallSpeed());
				
			}
			if(game.getBall3DirectionX() == "downX" && game.getBall3DirectionY() == "downY")
			{
				game.getBall3().setX(game.getBall3().getX() - game.getBallSpeed());
				
				game.getBall3().setY(game.getBall3().getY() - game.getBallSpeed());
				
			}
		

		
		}
		
		//checking for borders
		if (game.getBall().getX() + 10 > 1020) 
		{
		    game.setBallDirectionX("downX");
		}
		if (game.getBall().getX() - 10 < 0)   
		{
		    game.setBallDirectionX("upX");
		}
		if (game.getBall().getY() + 10 > 840) 
		{
		    game.setBallDirectionY("downY");
		    if(game.getLevel() == 3)
		    {
		          game.setTotalLives(game.getTotalLives() - 1);
		   
			   game.getBall().setX((1020/2) + 10);
			   game.getBall().setY(840/2);
			   game.getBall2().setShow(0); 
			   game.getBall3().setShow(0);
			   game.setBallReset(1);
			   game.setBallResetTime(300);
			   game.setBallDirectionY("upY");
			   game.setBallDirectionX("upX");
			   game.setPaddleLength(50);
			   game.setBallPowerActive3(0);
			   game.setBallPowerActive4(0);
			   game.setBallPowerActive5(0);
		    }
		    
		}
		if (game.getBall().getY() - 10 < 0) 
		{  
		   game.setTotalLives(game.getTotalLives() - 1);
		   
		   game.getBall().setX((1020/2) + 10);
		   game.getBall().setY(840/2);
		   game.getBall2().setShow(0); 
		   game.getBall3().setShow(0);
		   game.setBallReset(1);
		   game.setBallResetTime(300);
		   game.setBallDirectionY("upY");
		   game.setBallDirectionX("upX");
		   game.setPaddleLength(50);
		   game.setBallPowerActive3(0);
		   game.setBallPowerActive4(0);
		   game.setBallPowerActive5(0);
		}
		
		//checking for paddle collision
		if( game.getBall().getY() - 10 == game.getPaddle().getY() && ((game.getBall().getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall().getX() - 10 <= game.getPaddle().getX() + game.getPaddleLength()) || (game.getBall().getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall().getX() + 10 <= game.getPaddle().getX() + game.getPaddleLength())) )
		{
		   game.setBallDirectionY("upY");     
		   game.getPaddle().setColor(game.getBall().getColor());
		   game.getPaddle2().setColor(game.getBall().getColor());  
		}
		
		
		if( (game.getBall().getY() + 10 == game.getPaddle2().getY() && ((game.getBall().getX() - 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall().getX() - 10 <= game.getPaddle2().getX() + game.getPaddleLength()) || (game.getBall().getX() + 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall().getX() + 10 <= game.getPaddle2().getX() + game.getPaddleLength()))) && game.getLevel() == 3 )
		{
		   game.setBallDirectionY("downY");  
		   game.getPaddle().setColor(game.getBall().getColor());
		   game.getPaddle2().setColor(game.getBall().getColor());     
		}
		
		
		if(game.getBall2().Show())
		{
			if (game.getBall2().getX() + 10 > 1020) 
			{
			    game.setBall2DirectionX("downX");
			}
			if (game.getBall2().getX() - 10 < 0)   
			{
			    game.setBall2DirectionX("upX");
			}
			if (game.getBall2().getY() + 10 > 840) 
			{
			    game.setBall2DirectionY("downY");
			     if(game.getLevel() == 3)
			    {
				 game.getBall2().setShow(0);
			    }
			}
			if (game.getBall2().getY() - 10 < 0) 
			{
			   game.setBall2DirectionY("upY");
			   game.getBall2().setShow(0);
			}
			if( game.getBall2().getY() - 10 == game.getPaddle().getY() && ((game.getBall2().getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall2().getX() - 10 <= game.getPaddle().getX() + game.getPaddleLength()) || (game.getBall2().getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall2().getX() + 10 <= game.getPaddle().getX() + game.getPaddleLength())) )
			{
			   game.setBall2DirectionY("upY");       
			}
			
			if( (game.getBall2().getY() + 10 == game.getPaddle2().getY() && ((game.getBall2().getX() - 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall2().getX() - 10 <= game.getPaddle2().getX() + game.getPaddleLength()) || (game.getBall2().getX() + 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall2().getX() + 10 <= game.getPaddle2().getX() + game.getPaddleLength()))) && game.getLevel() == 3 )
			{
			   game.setBall2DirectionY("upY");       
			}
			
			
		}	
			
		
		if(game.getBall3().Show())	
		{	
			if (game.getBall3().getX() + 10 > 1020) 
			{
			    game.setBall3DirectionX("downX");
			}
			if (game.getBall3().getX() - 10 < 0)   
			{
			    game.setBall3DirectionX("upX");
			}
			if (game.getBall3().getY() + 10 > 840) 
			{
			    game.setBall3DirectionY("downY");
			    if(game.getLevel() == 3)
			    {
				 game.getBall2().setShow(0);
			    }
			}
			if (game.getBall3().getY() - 10 < 0) 
			{
			   game.setBall3DirectionY("upY");
			   game.getBall3().setShow(0);
			}
			if( game.getBall3().getY() - 10 == game.getPaddle().getY() && ((game.getBall3().getX() - 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall3().getX() - 10 <= game.getPaddle().getX() + game.getPaddleLength()) || (game.getBall3().getX() + 10 >= game.getPaddle().getX() - game.getPaddleLength() && game.getBall3().getX() + 10 <= game.getPaddle().getX() + game.getPaddleLength())) )
			{
			   game.setBall3DirectionY("upY");       
			}
			
			
			if( (game.getBall3().getY() + 10 == game.getPaddle2().getY() && ((game.getBall3().getX() - 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall3().getX() - 10 <= game.getPaddle2().getX() + game.getPaddleLength()) || (game.getBall3().getX() + 10 >= game.getPaddle2().getX() - game.getPaddleLength() && game.getBall3().getX() + 10 <= game.getPaddle2().getX() + game.getPaddleLength()))) && game.getLevel() == 3 )
			{
			   game.setBall3DirectionY("upY");       
			}
		
		
		}
          
                glutSwapBuffers();
        }
 	
	glutPostRedisplay();
	//glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if((game.getPaddle().getX() - 5) - 50 >= -10)
		game.getPaddle().setX(game.getPaddle().getX() - 20);

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	 
	if((game.getPaddle().getX() + 5) + 50 < 1050)
	 game.getPaddle().setX(game.getPaddle().getX() + 20);
	
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'p' || key == 'P') 
	{
		game.setPaused(1);

	}
	if (key == 'b' || key == 'B') 
	{
	       if(game.Paused())
		game.setPaused(0);
		
		if(game.SeeScore())
		{
		   game.setSeeScore(0);
		   game.setPaused(1);
		}
		
		if(game.SeeHighScore())
		{
		  game.setSeeHighScore(0);
		  game.setPaused(1);
		}

	}
	if (key == 'a' || key == 'A') 
	{
	        if(game.getLevel() == 3)
	        {
		  if((game.getPaddle2().getX() - 5) - 50 >= -10)
		  game.getPaddle2().setX(game.getPaddle2().getX() - 20);
                }
	}
	if (key == 'd' || key == 'D') 
		
	{
	        if(game.getLevel() == 3)
	        {
		  if((game.getPaddle2().getX() + 5) + 50 < 1050)
	          game.getPaddle2().setX(game.getPaddle2().getX() + 20);
                }
	}
	
	
	if ((key == 's' || key == 'S') && (game.getTotalLives() == 0 || game.Paused() || game.End()))	
	{
	         game.setSeeScore(1);
	}
	
	if ((key == 'h' || key == 'H') && (game.getTotalLives() == 0 || game.Paused() || game.End()))	
	{
	         game.setSeeHighScore(1);
	}
	
	
	if ((key == 'r' || key == 'R') && (game.getTotalLives() == 0 || game.Paused() || game.End()))
		
	{
	         game.setRestart(1);
	}
	
	
	
	
	 
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
        glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	game.getPaddle().setX(x);
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(500, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Arkadriod Brick Breaker"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
