
    float rotate_theta = -180.0;
    void drawHouse()
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0, 0);
        glVertex2f(230, 0);
        glVertex2f(230, 220);
        glVertex2f(0, 220);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(0, 220);
        glVertex2f(230, 220);
        glVertex2f(120, 290);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(100, 0);
        glVertex2f(150, 0);
        glVertex2f(150, 150);
        glVertex2f(100, 150);
        glEnd();
    }

    void init_program1()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-500, 500, -300, 400);
        glMatrixMode(GL_MODELVIEW);
    }

    void display1()
    {
        drawHouse();
        glFlush();
        glRotatef(rotate_theta, 0.0, 0.0, 1.0);
        drawHouse();
        glFlush();
    }
