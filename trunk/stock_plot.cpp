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


vector<vector<float> > stab5;
vector<vector<float> > stab6;
vector<vector<float> > stab7;
vector<vector<float> > stab8;

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

void KeyboardFunc(unsigned char key, int x, int y) {
    if (key == ' ') {
      which_time_period++;
      which_time_period=which_time_period%max_time_steps;
      cout<<which_time_period<<endl;
      glutPostRedisplay();
      glutSwapBuffers();
    } else if (key == 27) {
        exit(1);
    }
}



void processSpecialKeys(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_HOME:
	  which_cluster_size++;
	  which_cluster_size=which_cluster_size%4;
	  glutPostRedisplay();
	  glutSwapBuffers();

    }
}

void initRendering() 
{
    glEnable(GL_DEPTH_TEST);

    glPointSize(8);
    glLineWidth(5);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




void draw3()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glBegin(GL_QUADS);					       
	for(int i=0;i<400;i++)
	  {
	    float posx=pc1[i][which_time_period];
	    float posy=pc2[i][which_time_period];
	    float diff=.01;
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
	  }
	glEnd();		

    glutSwapBuffers();		
    glutPostRedisplay();
}

void draw2()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glBegin(GL_QUADS);					       
	for(int i=0;i<400;i++)
	  {
	    float posx=pc1[i][which_time_period];
	    float posy=pc2[i][which_time_period];
	    float diff=.01;
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
	  }
	glEnd();		

    glutSwapBuffers();		
    glutPostRedisplay();
}

void draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glBegin(GL_QUADS);					       
	for(int i=0;i<400;i++)
	  {
	    float posx=pc1[i][which_time_period];
	    float posy=pc2[i][which_time_period];
	    float diff=.01;
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
	  }
	glEnd();		

    glutSwapBuffers();		
    glutPostRedisplay();
}


void idle_both()
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

 float total_max1=FLT_MIN;
 float total_min1=FLT_MAX;

 float total_max2=FLT_MIN;
 float total_min2=FLT_MAX;

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
	
	for(int i=0;i<sv.size();i+=6)
	  {
            
	    if(atof(sv[i].c_str())>total_max1)
	      {
		total_max1=atof(sv[i].c_str());
	      }

	    if(atof(sv[i].c_str())<total_min1)
	      {
		total_min1=atof(sv[i].c_str());
	      }


	    if(atof(sv[i+1].c_str())>total_max2)
	      {
		total_max2=atof(sv[i+1].c_str());
	      }

	    if(atof(sv[i+1].c_str())<total_min2)
	      {
		total_min2=atof(sv[i+1].c_str());
	      }

	    pc1_temp.push_back(atof(sv[i].c_str()));
	    pc2_temp.push_back(atof(sv[i+1].c_str()));
	    c5_temp.push_back(atoi(sv[i+2].c_str()));
	    c6_temp.push_back(atoi(sv[i+3].c_str()));
	    c7_temp.push_back(atoi(sv[i+4].c_str()));
	    c8_temp.push_back(atoi(sv[i+5].c_str()));
	  }
		
	pc1.push_back(pc1_temp);
	pc2.push_back(pc2_temp);
	c5.push_back(c5_temp);
	c6.push_back(c6_temp);
	c7.push_back(c7_temp);
	c8.push_back(c8_temp);
      }

	float posx=pc1[0][0];
	float posy=pc2[0][0];

	cout<<pc1.size()<<endl;


    // Init OpenGL stuff
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    //Window 1 ---------------------
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(720, 720);
    int wind1=glutCreateWindow("1");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(draw);

    //End Window 1 -----------------

    //Window 2 ---------------------
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(300, 50);
    int wind2=glutCreateWindow("2");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(draw2);


    //End Window 2 -----------------

    //Window 3 ---------------------
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(300, 50);

    int wind3=glutCreateWindow("2");

    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(processSpecialKeys);

    glutDisplayFunc(draw3);

    //End Window 3 -----------------
    initRendering();


    glutIdleFunc(idle_both);
    glutMainLoop();

    return (0);
}
