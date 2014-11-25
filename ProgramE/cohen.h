#define outcode int

double xmin,ymin,xmax,ymax;// Windows boundaries
double xvmin,yvmin,xvmax,yvmax; // Viewport boundaries
double x60=170,y60=100,x61=200,y61=300;
const int RIGHT= 8; // bit codes for the right
const int LEFT =2;  //bit codes for the left
const int TOP=4;    // bit codes for the top
const int BOTTOM=1; //bit codes for the bottom

outcode ComputeOutCode(double x,double y); // used to compute bit codes of a point

// Cohen -Sutherland clipping algorithm clips a line from
// p0=(x0,y0)  to p1 =(x1,y1) against a rectangle with.
// diagonal from (xmin,ymin)to (xmax,ymax)

void CohenSutherlandLineClipAnddraw(double x0,double y0,double x1,double y1)
{
    // OutCodes for P0 ,P1 and Whatever point(among P0 & P1) lies outside the
    // clip rectangle
    
    outcode outcode0,outcode1,outcodeOut;
    
    int accept =0,done =0;// These are two bits to indicate trivial accept and/or
    // done with clipping
    //compute outcodes
    outcode0= ComputeOutCode(x0,y0);
    outcode1= ComputeOutCode(x1,y1);
    
    do
    {
        if(!(outcode0|outcode1)) // logical or is 0 trivially accept and exit
        { accept=1;
            done=1;
        }
        
        else
            if(outcode0 & outcode1)  // logical and is 0 trivially reject and exit
                done=1;
            else
            {
                //failed both tests , so calculate the line segment clip;
                // from an outside point to an intersection with clip edge
                double x,y;
                // at least one endpoint is outside the clip rectangle ; pick it.
                outcodeOut= outcode0?outcode0:outcode1;
                
                //now find the intersection point ; slope m= (y1-y0)/(x1-x0)
                // use formula
                /// y=y0+slope*(x-x0), //either x is xmin or xmax
                /// x=x0+(1/slope)*(y-y0) // y is ymin or ymax
                if(outcodeOut & TOP) //point is above the clip rectangle
                {
                    x= x0+(x1-x0)*(ymax-y0)/(y1-y0);
                    y=ymax;
                }
                else
                    if(outcodeOut & BOTTOM) //point is below the clip rectangle
                    {
                        x= x0+(x1-x0)*(ymin-y0)/(y1-y0);
                        y=ymin;
                    }
                    else
                        if(outcodeOut & RIGHT) //point is to the right of clip rectangle
                        {
                            y= y0+(y1-y0)*(xmax-x0)/(x1-x0);
                            x=xmax;
                        }
                        else                   //point is to the left of the clip rectangle
                        {
                            y= y0+(y1-y0)*(xmin-x0)/(x1-x0);
                            x=xmin;
                        }
                // now we move outside point to intersection point to clip
                // and get ready for next pass.
                if(outcodeOut == outcode0) // If the outside point was p0 update x0,y0 to x,y
                { x0=x;                           // so x,y become the new x0,y0
                    y0=y;
                    outcode0 = ComputeOutCode(x0,y0);
                    //compute outcode of new endpoint
                }
                else                            // If the outside point was p1 update x1,y1 to x,y
                {                           // so x,y becomes the new x1,y1
                    x1=x;
                    y1=y;
                    outcode1 = ComputeOutCode(x1,y1);
                    // compute outcode of new endpoint
                }
            }
    }while(!done);
    if(accept) //If line was trivial reject no need to draw viewport
    {
        // window to viewport mapping
        double sx=(xvmax-xvmin)/(xmax-xmin);// scale parameter in x direction
        double sy=(yvmax-yvmin)/(ymax-ymin);// scale parameter in y direction
        double vx0 = xvmin+(x0-xmin)*sx;
        double vy0 = yvmin+(y0-ymin)*sy;
        double vx1 = xvmin+(x1-xmin)*sx;
        double vy1 = yvmin+(y1-ymin)*sy;
        //draw a red color viewport
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}
// compute the bit code for a point (x,y) using the clip rectangle
// bounded diagonally by (xmin,ymin) and (xmax,ymax)
outcode ComputeOutCode(double x,double y)
{
    outcode code =0;
    if(y>ymax)   //above the clip window
        code |=TOP;
    if(y<ymin)   //below the clip window
        code |=BOTTOM;
    if(x>xmax)        //to the right of the clip window
        code |=RIGHT;
    if(x<xmin)  //to the left of the clip window
        code |=TOP;
    return code;
}
void display6()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0); // draw red color lines
    glBegin(GL_LINES);
    glVertex2d(x60,y60);
    glVertex2d(x61,y61);
    //glVertex2d(60,20);
    //glVertex2d(80,120);
    glEnd();
    glColor3f(0.0,0.0,1.0); // draw a blue colored window
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    CohenSutherlandLineClipAnddraw(x60,y60,x61,y61);
    //CohenSutherlandLineClipAnddraw(170,100,280,200);
    glFlush();
}
void init_program6()
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