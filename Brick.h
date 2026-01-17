class Brick
{
    int x, y; // Position
    int width, height; // Size
    bool destroyed = 1; // Indicates whether the brick is destroyed or not
    int hitsToBreak;
    int color =-1;
    int hits;
    public:
    // Constructor
    
    Brick()
    {}
    
    Brick(int startX, int startY, int brickWidth, int brickHeight, int c, int h) {
        x = startX;
        y = startY;
        width = brickWidth;
        height = brickHeight;
        destroyed = false;
        hitsToBreak = h;
        hits = 0;
        color = c; 
    }
    
    
    int getX() const 
    { 
      return x; 
    }
    
    int getY() const 
    {
      return y; 
    }
    
    int getW() const 
    { 
      return width; 
    }
    
    int getH()
    {
      return height;
    }
    
    int getC() const 
    { 
      return color; 
    }
    
    bool getStatus()
    {
      return destroyed;
    }
    
    int getHits()
    {
      return hits; 
    }
    
    void setHits()
    {
      hits++;
      if(hits == hitsToBreak)
      {
        destroyed = 1;
      }
    }
    
    void setHit(int h)
    {
      hits = h;
    }
    
    void setStatus(bool s)
    {
      destroyed = s;
    }
    
    void reset()
    {
      hits = 0;
      destroyed  = 0;
    }
    
 
};
