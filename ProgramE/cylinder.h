int n_rec = 40;
int n_cir = 50;
void draw_pixel(int x,int y)
{
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(x,y);
    glEnd();
}

void plot_pixel(int h,int k,int x,int y)
{
    draw_pixel(h+x,k+y);
    draw_pixel(h-x,k+y);
    draw_pixel(h+x,k-y);
    draw_pixel(h-x,k-y);
    draw_pixel(h+y,k+x);
    draw_pixel(h+y,k-x);
    draw_pixel(h-y,k+x);
    draw_pixel(h-y,k-x);
}
void circle(int h,int k,int r)
{
    int x=0,y=r;
    int d = 1-r;
    while(y>x)
    {
        plot_pixel(h,k,x,y);
        if(d<0) d+=2*x+3;
        else{ d += 2*(x-y) +5;--y;}
        x++;
    }
    plot_pixel(h,k,x,y);
}

void draw_cylinder()
{
    int x=300,y=300,r=50;
    int i=0;
    for(i=0;i<n_cir;i++)
        circle(x+i,y+i,r);
}
void parallelopiped(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2, y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
    glFlush();
    
}

void parallelo()
{
    float x1=400.0,y1=400.0,x2=600.0,y2=400.0,x3=600.0,y3=600.0,x4=400.0,y4=600.0;
    int i=0;
    for(i=0;i<n_rec;i++)
        parallelopiped(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,x4+i,y4+i);
        
}

void init_program3()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,700);
    glMatrixMode(GL_MODELVIEW);
}
void display3()
{
    parallelo();
    draw_cylinder();
    glFlush();
}
