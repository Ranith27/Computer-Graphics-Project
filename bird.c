#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#define FPS 48
#define MFLY 1
#define MSTAY 0
#define INCF 1
#define DECF 0.1
float wingval=0;
float yaxis=3;
float val=3;
float min=0;
float temp=2,temp2=2,temp3;
short int mode;
int score=0,i,j,k;
const char *s="Score:";
const char *e="GAME OVER";
const char *msg="Press F1 to Restart";
char stack[10];
short int h,w,dis,pos,wait,error,wingmode;
void display();
void keybord(int key,int x,int y);
void drawBird();
void restart();
void helper(int);
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutCreateWindow("The Bird Game");
	glutSpecialFunc(keybord);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
void display()
{
	int l=0,m;
	if(!error){
	glClearColor(0.8,0.8,0.8,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,10,0,10);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.59765625,0.59765625,0.3984375);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(10,0);
	glVertex2f(10,2);
	glVertex2f(0,2);
	glEnd();
	if(wait==0)
	{
		min=0;
		dis=FPS+rand()%120;
		h=2+rand()%3;
		w=1+rand()%2;
		pos=rand()%2;
		wait=rand()%60;
		temp=0;
		temp2=0;
		wait=1;
		
	}else if(temp<1)
	{
			temp2=temp2+8.5;
		glColor3f(0.3,0.3,0.3);
		temp=temp2/dis;
		
		if(!pos)
		{
			if(dis){
			glBegin(GL_POLYGON);
			glVertex2f(10,10);
			glVertex2f(10,10-h);
			glVertex2f(10-temp*w,10-h);
			glVertex2f(10-temp*w,10);
			glEnd();
		}
		}else{
			if(dis){
			glBegin(GL_POLYGON);
			glVertex2f(10,2);
			glVertex2f(10,h+2);
			glVertex2f(10-temp*w,h+2);
			glVertex2f(10-temp*w,2);
			glEnd();
		}
		}
		if(temp2>=dis)
		temp2=0;
		
	}else if(temp2==0)
	{
		temp3+=1;
		glColor3f(0.3,0.3,0.3);
		if(!pos)
		{
		if(dis){
			glBegin(GL_POLYGON);
			glVertex2f((10-(temp3/dis)*10),10);
			glVertex2f((10-(temp3/dis)*10),10-h);
			glVertex2f((10-(temp3/dis)*10-w),10-h);
			glVertex2f((10-(temp3/dis)*10-w),10);
			glEnd();
			if(yaxis>=(10-h)&&yaxis<=10&&((10-((temp3/dis)*10)-w)<=5)&&(10-((temp3/dis)*10))>=5)
				error=1;
			else if(yaxis+0.7>=(10-h)&&yaxis+0.7<=10&&((10-((temp3/dis)*10)-w)<=4.7)&&(10-((temp3/dis)*10))>=3.3)
				error=1;
				if((10-(temp3/dis)*10)<3.1)
				{if(min<(10-(temp3/dis)*10))
					{
						min=(10-(temp3/dis)*10);
						k++;
						score+=k;
					}
			    }		
			
		}}else{
			if(dis){
					glBegin(GL_POLYGON);
			glVertex2f((10-(temp3/dis)*10),2);
			glVertex2f((10-(temp3/dis)*10),h+2);
			glVertex2f((10-(temp3/dis)*10)-w,h+2);
			glVertex2f((10-(temp3/dis)*10)-w,2);
			glEnd();
				if(yaxis>=2&&yaxis<=h+2&&((10-((temp3/dis)*10)-w)<=5)&&(10-((temp3/dis)*10))>=5)
				error=1;
				else if(yaxis-1.1>=(2)&&yaxis-1.1<=h+2&&((10-((temp3/dis)*10)-w)>=3.55)&&(10-((temp3/dis)*10))<=3.8)
				error=1;
				if((10-(temp3/dis)*10)<3.1)
				{if(min<(10-(temp3/dis)*10))
					{
						min=(10-(temp3/dis)*10);
						k++;
						score+=k;
					}
			    }		
		
		
	}
	}
	if(temp3==dis){
		temp2=1;
		temp3=0;
	}
	}
	else{
		wait--;
	}
	if(mode==MFLY)
	{
		if(yaxis<val)
		{
			yaxis+=0.2;
		}else {
			mode=MSTAY;
		}
	}else if(yaxis-DECF<3){
		yaxis=3;
    }
	else if(yaxis>=3+DECF)
	yaxis-=DECF;
	
	drawBird();
	glColor3f(0,0,0);
	//setting score position
	glRasterPos2f(7.5,1);
	for(i=0;i<6;i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,s[i]);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,'\n');
	i=score;
	do{
		stack[l++]=i%10+'0';
		i=i/10;
	}while(i!=0);
	for(m=l-1;m>=0;m--)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stack[m]);
	glutSwapBuffers();
	glFlush();
}else{
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_POLYGON);
	glVertex2f(3.8,4.0);
	glVertex2f(7.8,4.0);
	glVertex2f(7.8,6.0);
	glVertex2f(3.8,6.0);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(4,5.5);
	for(i=0;i<9;i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,e[i]);
	glRasterPos2f(4,5);
	for(i=0;i<6;i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,s[i]);
	i=score;
	do{
		stack[l++]=i%10+'0';
		i=i/10;
	}while(i!=0);
	for(m=l-1;m>=0;m--)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stack[m]);
	glRasterPos2f(4,4.5);
		for(i=0;i<19;i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,msg[i]);
	glutSwapBuffers();
	glFlush();
	}
}
void keybord(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:if(yaxis<=9-INCF)
							val=yaxis+INCF;
						 else val=9.3;
						 mode=MFLY;
							break;
		case GLUT_KEY_F1:restart();
							break;
		
	}
}
void drawBird(int n)
{
	int i;
	//body code
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
	for(i=0;i<360;i++)
	glVertex2f(4+0.7*cosf(i),yaxis+0.7*sinf(i));
	glEnd();
	//wing code
	glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	glVertex2f(3.5,yaxis);
	glVertex2f(4.3,yaxis-0.2);
	if(yaxis==3){
	glVertex2f(3.9,yaxis-0.5);
	wingval=0;
	wingmode=0;
	}
	else{
		//making wing flap while flying
		glVertex2f(3.9,yaxis+wingval);
		if(wingmode==0)
		wingval-=0.03;
		else wingval+=0.03;
		if(wingval<=-0.5)
		wingmode=1;
		else if(wingval>=0)
		wingmode=0;
		}
	glEnd();
	//eye code
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<360;i++)
	glVertex2f(4.4+0.2*cosf(i),yaxis+0.2+0.2*sinf(i));
	glEnd();
	//eye sparkle code
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<360;i++)
	glVertex2f(4.45+0.08*cosf(i),yaxis+0.25+0.08*sinf(i));
	glEnd();
	//beak code
	glColor3f(0.3984375,0,0.19921875);
	glBegin(GL_TRIANGLES);
	glVertex2f(4.68,yaxis);
	glVertex2f(4.68,yaxis+0.15);
	glVertex2f(5,yaxis);
	glEnd();
	glColor3f(0.19921875,0.19921875,0);
	glBegin(GL_TRIANGLES);
	glVertex2f(4.68,yaxis);
	glVertex2f(4.68,yaxis-0.15);
	glVertex2f(5,yaxis);
	glEnd();
	//legs code
	glColor3f(0.65,0.85,0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(3.7,yaxis-1);
	glVertex2f(3.65,yaxis-0.9);
	glVertex2f(3.9,yaxis-1);
	glEnd();
	glColor3f(0.75,0.85,0.4);
	glBegin(GL_POLYGON);
	glVertex2f(3.8,yaxis-0.6);
	glVertex2f(3.9,yaxis-0.65);
	glVertex2f(3.7,yaxis-1);
	glVertex2f(3.65,yaxis-0.9);
	glEnd();
	//hidden leg
	glColor3f(0.65,0.85,0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(3.6,yaxis-1.1);
	glVertex2f(3.55,yaxis-1);
	glVertex2f(3.8,yaxis-1.1);
	glEnd();
	glColor3f(0.7,0.8,0.35);
	glBegin(GL_POLYGON);
	glVertex2f(3.7,yaxis-0.5);
	glVertex2f(3.8,yaxis-0.55);
	glVertex2f(3.6,yaxis-1.1);
	glVertex2f(3.55,yaxis-1);
	glEnd();
	//tail feather code
	glColor3f(1,1,0.796875);
	glBegin(GL_TRIANGLES);
	glVertex2f(3.3,yaxis);
	glVertex2f(3.32,yaxis+0.15);
	glVertex2f(3.3,yaxis+0.35);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(3.3,yaxis);
	glVertex2f(3.3,yaxis+0.15);
	glVertex2f(3,yaxis+0.07);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(3.35,yaxis+0.1);
	glVertex2f(3.3,yaxis-0.05);
	glVertex2f(3.1,yaxis-0.25);
	glEnd();
	glutTimerFunc(1000/FPS,helper,1);
}
void helper(int i)
{
	glutPostRedisplay();
}
void restart()
{
	error=0;
	yaxis=3;
	val=3;
	min=0;
	temp=2;
	temp2=2;
	temp3=0;
	mode=0;
	i=0;
	j=0;
	k=0;
	score=0;
	h=0;
	w=0;
	dis=0;
	pos=0;
	wait=0;
	glutPostRedisplay();
}

//compile gcc prog.c -lm -lGL -lGLU -lglut 
// run ./a.out

