class Paddle
{
    int x, y; // Position
    int width, height; // Size
    int color;
    
    public: 
    
    Paddle()
    {}
    
    Paddle(int posX , int posY, int w, int h)
    {
      x = posX;
      y = posY;
      width = w;
      height = h;
      color = 1;
    }
    
    int getX() const 
    { 
      return x; 
    }
    
    int getY() const 
    {
      return y; 
    }
    
    int getColor()
    {
      return color;
    }
    
    int getW() const 
    { 
      return width; 
    }
    
    int getH()
    {
      return height;
    }
    
    void setColor(int c)
    {
      color = c;
    }
    
    void setX(int posx)
    {
      x = posx;
    }
    
    void setY(int posy)
    {
      y = posy;
    }
    
    
    
};
