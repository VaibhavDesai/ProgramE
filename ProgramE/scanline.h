#define BLACK 0
float x90=400,y90=400,x91=600,y91=600,x92=800,y92=400,x93=600,y93=200;
void edgedetect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                GLint *le,int *re)
{
    float mx,x,temp;
    int i;
    if((y2-y1)<0)
    {
        temp=y1;y1=y2;y2=temp;
        temp=x1;x1=x2;x2=temp;
    }
    if((y2-y1)!=0)
        mx=(x2-x1)/(y2-y1);
    else
        mx=x2-x1;
    x=x1;
    for(i=y1;i<=y2;i++)
    {
        if(x<(float)le[i])
            le[i]=(int)x;
        if(x>(float)re[i])
            re[i]=(int)x;
        x+=mx;
    }
}
void draw_pixel_9(GLint x, GLint y)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void scanfill(float x1,float y1, float x2, float y2,float x3, float y3,float x4, float y4)
{
    int le[1000],re[1000];
    int i,scanline;
    for(i=0;i<1000;i++)
    {
        le[i]=1000;
        re[i]=0;
    }
    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);
    for(scanline=0; scanline<1000; scanline++)
    {
        if(le[scanline]<=re[scanline])
            for(i=(int)le[scanline];i<(int)re[scanline];i++)
                draw_pixel_9(i,scanline);
    }
    
}
void display9()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x90,y90);
    glVertex2f(x91,y91);
    glVertex2f(x92,y92);
    glVertex2f(x93,y93);
    glEnd();
    scanfill(x90,y90,x91,y91,x92,y92,x93,y93);
    glFlush();
}
void init_program9()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1000.0,0.0,700.0);//
}