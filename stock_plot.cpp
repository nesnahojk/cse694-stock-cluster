#include <iostream>
#include <stdlib.h>
#include <vector>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <float.h>

using namespace std;



int max_time_steps=35;
int which_cluster_size=0;
int which_time_period=0;

vector<vector<float> > col;
vector<float> blue;
vector<float> red;
vector<float> green;
vector<float> orange;
vector<float> purple;
vector<float> yellow;
vector<float> black;
vector<float> brown;


vector<vector<float> > pc1;
vector<vector<float> > pc2;
vector<vector<int> > c5;
vector<vector<int> > c6;
vector<vector<int> > c7;
vector<vector<int> > c8;
vector<vector<float> > returns;


vector<vector<float> > stab5;
vector<vector<float> > stab6;
vector<vector<float> > stab7;
vector<vector<float> > stab8;

float zoom_fac=1;
float offsetx=0;
float offsety=0;

const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	// Define the portion of the window used for OpenGL rendering.
	glViewport( 0, 0, w, h );	// View port uses whole window

	// Set up the projection view matrix: orthographic projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {
		scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
		center = (Xmax+Xmin)/2;
		windowXmin = center - (center-Xmin)*scale;
		windowXmax = center + (Xmax-center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
		center = (Ymax+Ymin)/2;
		windowYmin = center - (center-Ymin)*scale;
		windowYmax = center + (Ymax-center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}
	
	// Now that we know the max & min values for x & y that should be visible in the window,
	//		we set up the orthographic projection.
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, -1, 1 );
}


void Tokenize(string& str, vector<string>& tokens, const string& delimiters)
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

int user_select=1;

void KeyboardFunc(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(1);
    }
    else if(key=='z')
      {
	zoom_fac+=.1;
      }
    else if(key=='v')
      {
	if(user_select>1)
	  {
	    user_select--;
	  }
      }
    else if(key=='c')
      {
	    user_select++;
      }
    else if(key=='x')
      {
	if(zoom_fac>.1)
	  {
	zoom_fac-=.1;
	  }
      }

      glutPostRedisplay();
      glutSwapBuffers();

}



void processSpecialKeys(int key, int x, int y) {



    switch (key) {
    case GLUT_KEY_F2:
      if(which_time_period<max_time_steps-1)
	{
	  which_time_period++;
	}
      break;
    case GLUT_KEY_F1:
      if(which_time_period>0)
	{
	  which_time_period--;
	}
      break;
    case GLUT_KEY_HOME:
      which_cluster_size++;
      which_cluster_size=which_cluster_size%4;
      break;
    case GLUT_KEY_RIGHT:
      offsetx+=.1;
      break;
    case GLUT_KEY_LEFT:
      offsetx-=.1;
      break;
    case GLUT_KEY_UP:
      offsety+=.1;
      break;
    case GLUT_KEY_DOWN:
      offsety-=.1;
      break;
    }
	  glutPostRedisplay();
	  glutSwapBuffers();
}






void drawStab()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(which_time_period>0)
      {
    float total=0.0f;
    float user=0.0f;


    //get stab for each stock upto a point
    for(int k=0;k<400;k++)
      {
	for(int i=0;i<which_time_period;i++)
	  {
	    switch(which_cluster_size)
	      {
	      case 0:
		total+=stab5[k][i];
		break;
	      case 1:
		total+=stab6[k][i];
		break;
	      case 2:
		total+=stab7[k][i];
		break;
	      case 3:
		total+=stab8[k][i];
		break;
	      }
	  }
      }

    for(int k=0;k<400;k++)
      {
	for(int i=which_time_period-user_select;i<which_time_period;i++)
	  {
	    switch(which_cluster_size)
	      {
	      case 0:
		user+=stab5[k][i];
		break;
	      case 1:
		user+=stab6[k][i];
		break;
	      case 2:
		user+=stab7[k][i];
		break;
	      case 3:
		user+=stab8[k][i];
		break;
	      }
	  }
      }

	glBegin(GL_QUADS);	

	glColor4f(1,0,0,0);
	glVertex3f(-1,total/which_time_period/400, 0.0f);
	glVertex3f(0, total/which_time_period/400, 0.0f);
	glVertex3f(0, -1, 0.0f);
	glVertex3f(-1, -1, 0);

	glColor4f(0,1,0,0);
	glVertex3f(0,user/(user_select)/400, 0.0f);
	glVertex3f(1, user/(user_select)/400, 0.0f);
	glVertex3f(1, -1, 0.0f);
	glVertex3f(0, -1, 0);

	glEnd();
	
      }


    glutSwapBuffers();		
    glutPostRedisplay();
}

void drawHist()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    

    glLoadIdentity();
			       
    for(int t=0;t<=which_time_period-1;t++)
      {
	for(int i=0;i<400;i++)
	  {
	    glBegin(GL_QUADS);		

	    float posx=(pc1[i][t]/zoom_fac)-offsetx;
	    float posy=(pc2[i][t]/zoom_fac)-offsety;
	    float diff=.01*(1.0+2*returns[i][t]);
	    switch(which_cluster_size)
	      {
		
	      case 0:
		glColor4f(col[c5[i][t]-1][0], col[c5[i][t]-1][1], col[c5[i][t]-1][2],(float)(t+1)/(float)(which_time_period+1)/10);
		break;
	      case 1:
		glColor4f(col[c6[i][t]-1][0], col[c6[i][t]-1][1], col[c6[i][t]-1][2],(float)(t+1)/(float)(which_time_period+1)/10);
		break;
	      case 2:
		glColor4f(col[c7[i][t]-1][0], col[c7[i][t]-1][1], col[c7[i][t]-1][2],(float)(t+1)/(float)(which_time_period+1)/10);
		break;
	      case 3:
		glColor4f(col[c8[i][t]-1][0], col[c8[i][t]-1][1], col[c8[i][t]-1][2],(float)(t+1)/(float)(which_time_period+1)/10);
		break;
	      }

            glVertex3f(posx - diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy + diff, 0.0f);
            glVertex3f(posx - diff, posy + diff, 0.0f);
	glEnd();		
	  }
      }

	for(int i=0;i<400;i++)
	  {
	    	    if(returns[i][which_time_period]>0)
	    {
		glBegin(GL_QUADS);		
		}
			    else
			      {
				glBegin(GL_LINE_LOOP);
	  }
	    float posx=(pc1[i][which_time_period]/zoom_fac)-offsetx;
	    float posy=(pc2[i][which_time_period]/zoom_fac)-offsety;
	    float diff=.01*(1.0+2*returns[i][which_time_period]);
	    switch(which_cluster_size)
	      {
		
	      case 0:
		glColor4f(col[c5[i][which_time_period]-1][0], col[c5[i][which_time_period]-1][1], col[c5[i][which_time_period]-1][2],1);
		break;
	      case 1:
		glColor4f(col[c6[i][which_time_period]-1][0], col[c6[i][which_time_period]-1][1], col[c6[i][which_time_period]-1][2],1);
		break;
	      case 2:
		glColor4f(col[c7[i][which_time_period]-1][0], col[c7[i][which_time_period]-1][1], col[c7[i][which_time_period]-1][2],1);
		break;
	      case 3:
		glColor4f(col[c8[i][which_time_period]-1][0], col[c8[i][which_time_period]-1][1], col[c8[i][which_time_period]-1][2],1);
		break;
	      }

            glVertex3f(posx - diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy + diff, 0.0f);
            glVertex3f(posx - diff, posy + diff, 0.0f);
	glEnd();		
	  }

    glutSwapBuffers();		
    glutPostRedisplay();
}

void draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
			       
	for(int i=0;i<400;i++)
	  {
	    if(returns[i][which_time_period]>0)
	      {
		glBegin(GL_QUADS);		
	      }
	    else
	      {
		glBegin(GL_LINE_LOOP);
	      }
	    float posx=(pc1[i][which_time_period]/zoom_fac)-offsetx;
	    float posy=(pc2[i][which_time_period]/zoom_fac)-offsety;
	    float diff=.01*(1.0+2*returns[i][which_time_period]);
	    switch(which_cluster_size)
	      {
	      case 0:
		glColor3f(col[c5[i][which_time_period]-1][0], col[c5[i][which_time_period]-1][1], col[c5[i][which_time_period]-1][2]);
		break;
	      case 1:
		glColor3f(col[c6[i][which_time_period]-1][0], col[c6[i][which_time_period]-1][1], col[c6[i][which_time_period]-1][2]);
		break;
	      case 2:
		glColor3f(col[c7[i][which_time_period]-1][0], col[c7[i][which_time_period]-1][1], col[c7[i][which_time_period]-1][2]);
		break;
	      case 3:
		glColor3f(col[c8[i][which_time_period]-1][0], col[c8[i][which_time_period]-1][1], col[c8[i][which_time_period]-1][2]);
		break;
	      }

            glVertex3f(posx - diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy - diff, 0.0f);
            glVertex3f(posx + diff, posy + diff, 0.0f);
            glVertex3f(posx - diff, posy + diff, 0.0f);
            glEnd();		
	  }


    glutSwapBuffers();		
    glutPostRedisplay();
}








void idle_all()
{
    glutSwapBuffers();		
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

blue.push_back(0);
blue.push_back(0);
blue.push_back(1);
red.push_back(1);
red.push_back(0);
red.push_back(0);
green.push_back(0);
green.push_back(1);
green.push_back(0);
orange.push_back(1);
orange.push_back(.64);
orange.push_back(0);
purple.push_back(.62);
purple.push_back(.12);
purple.push_back(.94);
black.push_back(0);
black.push_back(0);
black.push_back(0);
yellow.push_back(1);
yellow.push_back(1);
yellow.push_back(0);
brown.push_back(.54);
brown.push_back(.27);
brown.push_back(.07);

 col.push_back(blue);
 col.push_back(red);
 col.push_back(green);
 col.push_back(black);
 col.push_back(yellow);
 col.push_back(brown);
 col.push_back(orange);
 col.push_back(purple);



  //Read in the data from stdin


    string s;
    while(getline(cin, s) != NULL)
      {
	vector<string> sv;
	Tokenize(s,sv,",");
	vector<float> pc1_temp;
	vector<float> pc2_temp;
	vector<int> c5_temp;
	vector<int> c6_temp;
	vector<int> c7_temp;
	vector<int> c8_temp;
	vector<float> ret_temp;
        vector<float> stab5_temp;
        vector<float> stab6_temp;
        vector<float> stab7_temp;
        vector<float> stab8_temp;
	
	for(int i=0;i<sv.size();i+=11)
	  {
	    pc1_temp.push_back(atof(sv[i].c_str()));
	    pc2_temp.push_back(atof(sv[i+1].c_str()));
	    c5_temp.push_back(atoi(sv[i+2].c_str()));
	    c6_temp.push_back(atoi(sv[i+3].c_str()));
	    c7_temp.push_back(atoi(sv[i+4].c_str()));
	    c8_temp.push_back(atoi(sv[i+5].c_str()));
	    ret_temp.push_back(atof(sv[i+6].c_str()));
	    stab5_temp.push_back(atof(sv[i+7].c_str()));
	    stab6_temp.push_back(atof(sv[i+8].c_str()));
	    stab7_temp.push_back(atof(sv[i+9].c_str()));
	    stab8_temp.push_back(atof(sv[i+10].c_str()));
	  }
		
	pc1.push_back(pc1_temp);
	pc2.push_back(pc2_temp);
	c5.push_back(c5_temp);
	c6.push_back(c6_temp);
	c7.push_back(c7_temp);
	c8.push_back(c8_temp);
	returns.push_back(ret_temp);
	stab5.push_back(stab5_temp);
	stab6.push_back(stab6_temp);
	stab7.push_back(stab7_temp);
	stab8.push_back(stab8_temp);
      }



    // Init OpenGL stuff
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    //Window 2 ---------------------
    glutInitWindowPosition(800, 625);
    glutInitWindowSize(300, 300);
    int wind2=glutCreateWindow("Stability");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(drawStab);
    glutReshapeFunc( resizeWindow );

    //End Window 2 -----------------

    //Window Hist ---------------------
    glutInitWindowPosition(800, 300);
    glutInitWindowSize(300, 300);
    int wind4=glutCreateWindow("History Window");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(drawHist);
    glutReshapeFunc( resizeWindow );
    //End Window Hist -----------------


    //Window 1 ---------------------
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(720, 720);
    int wind1=glutCreateWindow("Plotting Window");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(draw);
    glutReshapeFunc( resizeWindow );
    //End Window 1 -----------------




    //    initRendering();


    glutIdleFunc(idle_all);
    glutMainLoop();

    return (0);
}
