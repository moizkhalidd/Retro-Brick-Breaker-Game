class Game
{
  //x variables change columns and y variables changes rows 
  int score = 0;
  int highScore = 0;
  int paddleX;
  int paddleY;
  int paddle2X;
  int paddle2Y;
  int ballx;
  int bally;
  int brickX;
  int brickY;
  string ballDirectionX, ballDirectionY, ball2DirectionX, ball2DirectionY, ball3DirectionX, ball3DirectionY;
  Paddle paddle;
  Paddle paddle2;
  Ball ball1, ball2, ball3 ;
  Brick bricks[8][5];
  Brick bricks2[20][5];
  Brick bricks3[12][11];
  int space = 0;
  int col = 0;
  int hits = 1;
  Food power[8][5];
  Food power2[20][5];
  Food power3[12][11];
  int powerType = 1;
  int paddleLength = 50;
  int ballSpeed = 5;
  int timeForPower3 = 0;
  int timeForPower4 = 0;
  int timeForPower5 = 0;
  bool ballPowerActive1 = 0;
  bool ballPowerActive2 = 0;
  bool ballPowerActive3 = 0;
  bool ballPowerActive4 = 0;
  bool ballPowerActive5 = 0;
  int totalLives = 2;
  bool ballReset = 1;
  int ballResetTime = 300;
  int prevMouseX = (1020/2);
  int level = 1;
  bool paused = 0;
  bool end = 0;
  bool stored = 0;
  bool seeScore = 0;
  bool seeHighScore = 0;
  bool Restart = 0;
  
  

  public: 
     
     Game()
     {
           paddleX=(1020/2);
	   paddleY = 50 ;
	   paddle2X=(1020/2);
	   paddle2Y = 830 ;
	   ballx=(1020/2) + 10;
	   bally=840/2;
	   brickX = 120;
	   brickY = 700;
	   ballDirectionX = "upX", ballDirectionY = "upY";
	   ball2DirectionX = "upX", ball2DirectionY = "downY";
	   ball3DirectionX = "downX", ball3DirectionY = "downY";
	   paddle = Paddle(paddleX, paddleY, 10, 10);
	   paddle2 = Paddle(paddle2X, paddle2Y, 10, 10);
	   ball1 = Ball(ballx, bally, 10, 1);
	   ball2 = Ball(ballx, bally, 10, 0);
	   ball3 = Ball(ballx, bally, 10, 0);
	   
  
	for(int j = 0; j <5 ; j++)
        {
         for(int i = 0; i< 8; i++)
         {
            bricks[i][j] = Brick(brickX + space, brickY, 15, 15, col, hits);
            if(space<700)
            space = space + 110;    
            
            col++;
            if(col >= 5)
            col = 0;
            
            if(col == 0)
            {
             hits = 1;
            }
            else
            if(col == 1)
            {
              hits = 2;
            }
            else
            if(col == 2)
            {
              hits = 3;
            }
            else
            if(col == 3)
            {
              hits = 3;
            }
            else
            if(col == 4)
            {
              hits = 2;
            }
                  
         }
         brickY = brickY - 10;
         space = 0;
        }
        
        for(int j = 0; j <5 ; j++)
        {
         for(int i = 0; i< 8; i++)
         {
             
             power[i][j] = Food(powerType, bricks[i][j].getX(), bricks[i][j].getY());
             
             powerType++;
             if(powerType == 6)
             {
              powerType = 1;
             }
               
         }
       
        }

        level2(0 , 0, 0, 0, 1, 0, 0, 60, 750);
        level2(0 , 0, 0, 0, 1, 4, 0, 60 + 320, 750 - 60);
        level2(0 , 0, 0, 0, 1, 8, 0, 60 + 320 + 320, 750 - 120);
        level2(0 , 0, 0, 0, 1, 12, 0, 60 +320, 750 - 180);
        level2(0 , 0, 0, 0, 1, 16, 0, 60 , 750 - 240);
        
        int powerType = 1;
        for(int i = 0; i <20 ; i++)
        {
         for(int j = 0; j< 5; j++)
         {
             
             power2[i][j] = Food(powerType, bricks2[i][j].getX(), bricks2[i][j].getY());
             
             powerType++;
             if(powerType == 6)
             {
              powerType = 1;
             }
               
         }
        }
        
        
        level3( 0, 0, 1, 0, 0, 150, 550, 0, 250);
        
        
        powerType = 1;
        for(int i = 0; i <12 ; i++)
        {
         for(int j = 0; j< 11; j++)
         {
             
             power3[i][j] = Food(powerType, bricks3[i][j].getX(), bricks3[i][j].getY());
             
             powerType++;
             if(powerType == 6)
             {
              powerType = 1;
             }
               
         }
         powerType = 1;
        }
        
        
     }
     
     
     
     
     void level2(int x , int y, int sp, int c, int hit, int i, int j, int Bx, int By)
     {
        
        if(y > 4 || x > 3)
        return;
       
        bricks2[i][j] = Brick(Bx + sp, By, 15, 15, c, hit);
        if(sp<700)
        sp = sp + 60;    
            
            c++;
            if(c >= 5)
            c = 0;
            
            if(c == 0)
            {
             hit = 1;
            }
            else
            if(c == 1)
            {
              hit = 2;
            }
            else
            if(c == 2)
            {
              hit = 3;
            }
            else
            if(c == 3)
            {
              hit = 3;
            }
            else
            if(c == 4)
            {
              hit = 2;
            }
                  
           
         level2(x , y + 1, sp, c, hit, i, j+1, Bx, By);       
         
         
         By = By - 10;
         
         level2(x+1 , y , 0, 0, 1, i + 1, j, Bx, By);
        
     
     }
     
     
     void level3( int sp, int c, int hit, int i, int j, int Bx, int By, int line, int diff)
     {
        if(line > 11/2) { //line 
         return; //line
         }
    
         printLine(11, (11 - ((line * 2) - 1)) /2, 0, 0, 1, line, 0, 170, By); //line

     
        level3( 0, 0, 1, line + 1, 0, 60, By - 25, line + 1, diff - 50); //line 
        
      
        printLine(11, (11 - ((line * 2) - 1)) /2, 0, 0, 1, 11 - line, 0, 170, By - (diff) ); //line

     
     }
     
     
     void printLine(int dimension, int stericCount, int sp, int c, int hit, int i, int j, int Bx, int By, int k=1) {

    if (k>dimension){
        return;
    }

    if (k <= stericCount || k > dimension - stericCount) 
    {
           bricks3[i][j] = Brick(Bx + sp, By, 15, 15, c, hit);
            if(sp<700)
            sp = sp + 60;    
            
            c++;
            if(c >= 5)
            c = 0;
            
            if(c == 0)
            {
             hit = 1;
            }
            else
            if(c == 1)
            {
              hit = 2;
            }
            else
            if(c == 2)
            {
              hit = 3;
            }
            else
            if(c == 3)
            {
              hit = 3;
            }
            else
            if(c == 4)
            {
              hit = 2;
            }

    }
    else 
    {
            if(sp<700)
            sp = sp + 60; 
  
            c++;
            if(c >= 5)
            c = 0;
            if(c == 0)
            {
             hit = 1;
            }
            else
            if(c == 1)
            {
              hit = 2;
            }
            else
            if(c == 2)
            {
              hit = 3;
            }
            else
            if(c == 3)
            {
              hit = 3;
            }
            else
            if(c == 4)
            {
              hit = 2;
            }
    }
    printLine(dimension,stericCount, sp,  c, hit,  i, j + 1, Bx, By, k+1);
}
     
    

    int getScore() { return score;}
    int getHighscore() { return highScore;} 
    int getPaddleX() { return paddleX; }
    int getPaddleY() { return paddleY; }
    int getPaddle2X() { return paddle2X; }
    int getPaddle2Y() { return paddle2Y; }
    int getBallX() { return ballx; }
    int getBallY()  { return bally; }
    int getBrickX()  { return brickX; }
    int getBrickY() { return brickY; }
    int getPaddleLength() { return paddleLength;}
    int getBallSpeed() { return ballSpeed;}
    int getTimeForPower3() { return  timeForPower3;}
    int getTimeForPower4() { return  timeForPower4;}
    int getTimeForPower5() { return  timeForPower5;}
    int getTotalLives() { return  totalLives;}
    int getBallResetTime() {  return ballResetTime; }
    int getPrevMouseX() { return prevMouseX; }
    int getLevel() { return level;}
    bool getBallPowerActive1() {  return ballPowerActive1; }
    bool getBallPowerActive2() {  return ballPowerActive2; }
    bool getBallPowerActive3() {  return ballPowerActive3; }
    bool getBallPowerActive4() {  return ballPowerActive4; }
    bool getBallPowerActive5() {  return ballPowerActive5; }
    bool getBallReset() {  return ballReset; }
    bool Paused() {  return paused; }
    bool End() {  return end; }
    bool Stored() {  return stored; }
    bool SeeScore() {  return seeScore; }
    bool SeeHighScore() {  return seeHighScore; }
    bool restart() {  return Restart; }
    string getBallDirectionX()  { return ballDirectionX; }
    string getBallDirectionY()  { return ballDirectionY; }
    string getBall2DirectionX()  { return ball2DirectionX; }
    string getBall2DirectionY()  { return ball2DirectionY; }
    string getBall3DirectionX()  { return ball3DirectionX; }
    string getBall3DirectionY()  { return ball3DirectionY; }
    Paddle& getPaddle() { return paddle; }
    Paddle& getPaddle2() { return paddle2; }
    Ball& getBall()  { return ball1; }
    Ball& getBall2()  { return ball2; }
    Ball& getBall3()  { return ball3; }
    Brick (&getBricks())[8][5] { return bricks; }
    Brick (&getBricks2())[20][5] { return bricks2; }
    Brick (&getBricks3())[12][11] { return bricks3; }
    Food (&getPower())[8][5]  { return power;}
    Food (&getPower2())[20][5]  { return power2;}
    Food (&getPower3())[12][11]  { return power3;}
    
    
    
    
    // Setters
    void setScore(int s) {score = s;}
    void setHighscore(int h) { highScore = h;} 
    void setRestart(bool  r) { Restart = r;}
    void setSeeScore(bool s) { seeScore = s; }
    void setSeeHighScore(bool s) { seeHighScore = s; }
    void setStored(int s) { stored = s;}
    void setEnd(bool e) { end = e;}
    void setPaddleX(int x) { paddleX = x; }
    void setPaddleY(int y) { paddleY = y; }
    void setPaddle2X(int x) { paddle2X = x; }
    void setPaddle2Y(int y) { paddle2Y = y; }
    void setBallX(int x) { ballx = x; }
    void setBallY(int y) { bally = y; }
    void setBrickX(int x) { brickX = x; }
    void setBrickY(int y) { brickY = y; }
    void setTimeForPower3(int t) { timeForPower3 = t;}
    void setTimeForPower4(int t) { timeForPower4 = t;}
    void setTimeForPower5(int t) { timeForPower5 = t;}
    void setPaddleLength(int len) { paddleLength = len;}
    void setBallSpeed(int sp) { ballSpeed = sp;}
    void setTotalLives(int live) { totalLives = live;}
    void setLevel(int l) { level = l;}
    void setPaused(bool p) {paused = p;}
    void setBallPowerActive1(bool act) { ballPowerActive1 = act;}
    void setBallPowerActive2(bool act) { ballPowerActive2 = act;}
    void setBallPowerActive3(bool act) { ballPowerActive3 = act;}
    void setBallPowerActive4(bool act) { ballPowerActive4 = act;}
    void setBallPowerActive5(bool act) { ballPowerActive5 = act;}
    void setBallReset(bool b) { ballReset = b;}
    void setBallResetTime(int t) { ballResetTime = t; }
    void setPrevMouseX(int x) { prevMouseX = x; }
    void setBallDirectionX(const string& direction) { ballDirectionX = direction; }
    void setBallDirectionY(const string& direction) { ballDirectionY = direction; }
    void setBall2DirectionX(const string& direction) { ball2DirectionX = direction; }
    void setBall2DirectionY(const string& direction) { ball2DirectionY = direction; }
    void setBall3DirectionX(const string& direction) { ball3DirectionX = direction; }
    void setBall3DirectionY(const string& direction) { ball3DirectionY = direction; }
};

