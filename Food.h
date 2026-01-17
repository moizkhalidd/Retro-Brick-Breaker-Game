class Food
{
  
  int type;
  bool active;
  int x;
  int y;
  bool show;
  bool timer;
  int initialx;
  int initialy;
  public:
  
  Food()
  {}
  
  Food(int t, int posx, int posy)
  {
   type = t;
   active = 0;
   x = posx;
   y = posy;
   show = 1;
   timer = 0;
   initialx = posx;
   initialy = posy;
  }
  
  int getType()
  {
   return type;
  }
  
  bool isActive()
  {
   return active;
  }
  
  bool Show()
  {
   return show;
  }
  
  bool getTimer()
  {
   return timer;
  }
  
  void setShow(bool s)
  {
    show = s;
  }
  
  void setTimer(bool t)
  {
    timer = t;
  }
  
  void setActive(bool act)
  {
    active = act;
  }
  
  int getX()
  {
   return x;
  }
  
  int getY()
  {
    return y;
  }
  
  void setX(int posx)
  {
    x = posx;
  }
  
  void setY(int posy)
  {
    y = posy;
  }
  
  void reset()
  {
    active = 0;
    show = 1;
    timer = 0;
    x = initialx;
    y = initialy;
  }
  


};
