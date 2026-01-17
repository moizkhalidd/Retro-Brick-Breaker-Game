class Ball
{
   int x;
   int y;
   int radius;
   bool show;
   int color;
   
   public:
   
   Ball()
   {}
   
   Ball(int posX , int posY, int r, bool s)
   {
     x = posX;
     y = posY;
     radius = r;
     show = s;
     color = 3;
   } 
     
   
    int getX() const 
    { 
      return x; 
    }
    
    int getY() const 
    {
      return y; 
    }
    int getRadius() const 
    { 
      return radius; 
    }
    
    int getColor()
    {
     return color;
    }
    
    bool Show()
    {
      return show;
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
    
    void setR(int r)
    {
      radius = r;
    }
    
    void setShow(bool s)
    {
      show = s;
    }
   
};
