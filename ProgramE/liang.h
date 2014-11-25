
double xmin,ymin,xmax,ymax;
double xvmin,xvmax,yvmin,yvmax;
int x1,y11,x2,y2;
double x40=170,y40=100,x41=200,y41=300;
int cliptest(double p,double q,double *t1,double *t2)
{      // p is denominator in division and q is numerator
    // t1 is t entering and t2 is t leaving
    double t=q/p;
    if(p<0.0)        //potentially entry point ,update te
    {    if(t>*t1) *t1=t;
        if(t>*t2) return(0); //line portion is outside as in line no 2 where t(entering)
        // has become more than t(leaving)
    }
    else if(p>0.0) //potentially leaving point ,update tl
    {
        if(t<*t2) *t2=t;
        if(t<*t1) return(0); //line portion is outside
    }
    else if(p==0.0)
    { if(q<0.0)
        return(0);//line parallel to edge but outside
    }
    return(1);
}
void liangbaraskylineclipanddraw(double x0,double y0,double x1,double y1)
{
    double dx= x1-x0,dy=y1-y0, te=0.0,tl=1.0;
    if(cliptest(-dx,x0-xmin,&te,&tl))// inside test wrt left edge
        // t for the left edge is t=(xmin-x0) /dx .... order of numerator is reversed and you get -dx
        if(cliptest(dx,xmax-x0,&te,&tl))// inside test wrt right edge
            // t for the right edge is t=(xmax-x0)/dx.... first parameter becomes q and second p then t=q/p
            if(cliptest(-dy,y0-ymin,&te,&tl))// inside test wrt bottom edge
                // same story numerator by demoninator to find t
                if(cliptest(dy,ymax-y0,&te,&tl))// inside test wrt top edge
                    // in one way cohen sutherland and liang barasky are similar
                {
                    if(tl<1.0)
                    {
                        x1=x0+tl*dx;
                        y1=y0+tl*dy;
                    }
                    if(te>0.0)
                    {
                        x0=x0+te*dx;
                        y0=y0+te*dy;
                    }
                }
    //window to viewport mappings
    double sx= (xvmax-xvmin)/(xmax-xmin);// scale parameters
    double sy= (yvmax-yvmin)/(ymax-ymin);
    double vx0= xvmin+(x0-xmin)*sx;
    double vy0= yvmin+(y0-ymin)*sy;
    double vx1= xvmin+(x1-xmin)*sx;
    double vy1= yvmin+(y1-ymin)*sy;
    // draw a red colored viewport
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin,yvmin);
    glVertex2f(xvmax,yvmin);
    glVertex2f(xvmax,yvmax);
    glVertex2f(xvmin,yvmax);
    glEnd();
    glColor3f(0.0,0.0,1.0); //draw blue colored clip line
    glBegin(GL_LINES);
    glVertex2d(vx0,vy0);
    glVertex2f(vx1,vy1);
    glEnd();
    
}
void display4()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);          //draw a line with red color
    glBegin(GL_LINES);
    glVertex2d(x40,y40);
    glVertex2d(x41,y41);
    glEnd();
    glColor3f(0.0,0.0,1.0);     //draw a blue color window
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    liangbaraskylineclipanddraw(x40,y40,x41,y41);
    glFlush();
}
void init_program4()
{   
    xmin=150; ymin=150; xmax=250;ymax=250; //window boundaries
    xvmin=400;yvmin=400;xvmax=500; yvmax=500; //viewport boundaries
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1000.0,0.0,700.0);
}