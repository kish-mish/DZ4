#include <iostream>
#include "stdio.h"
#include <math.h>
#include "glut.h"

#define PI 3.14159

using namespace std;

int b;

class point
{
public:
	float x;
	float y;
};

struct line
{
	int index;
	int n;
};

point *p;
int **matrix;
int **matrix1;
void render(void)
{
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < b; i++)
	{
		for (int j = i + 1; j < b; j++)
		{
			if (matrix[i][j] == 1)
			{
				glBegin(GL_LINES);
					glVertex2f(p[i].x*0.75, p[i].y*0.75);
					glVertex2f(p[j].x*0.75, p[j].y*0.75);
				glEnd();
			}
		}
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(p[i].x*0.75,p[i].y*0.75);
			for (int j = 0; j <= 50; j++) 
			{
				float a = (float)j / 50.0 * PI * 2.0;
				glVertex2f(p[i].x*0.75+cos(a) * 0.01, p[i].y*0.75+ sin(a) * 0.01);
			}
		glEnd();
	}
	glFlush();
}

void render1(void)
{
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < b; i++)
	{
		for (int j = i + 1; j < b; j++)
		{
			if (matrix1[i][j] == 1)
			{
				glBegin(GL_LINES);
				glVertex2f(p[i].x*0.75, p[i].y*0.75);
				glVertex2f(p[j].x*0.75, p[j].y*0.75);
				glEnd();
			}
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(p[i].x*0.75, p[i].y*0.75);
		for (int j = 0; j <= 50; j++)
		{
			float a = (float)j / 50.0 * PI * 2.0;
			glVertex2f(p[i].x*0.75 + cos(a) * 0.01, p[i].y*0.75 + sin(a) * 0.01);
		}
		glEnd();
	}
	glFlush();
}

bool search(int *arr,int n)
{
	for (int i = 0; i < b; i++)
	{
		if (arr[i] == n)
			return true;
	}
	return false;
}

int main(int argc, char **argv)
{
	cout << "How many points?" << endl;
	int f,k;
	bool flag;
	cin>>b;
	p = new point[b];
	line *matr = new line[b];
	matrix = new int*[b];
	for (int i = 0; i < b; i++)
		matrix[i] = new int[b];
	matrix1 = new int*[b];
	for (int i = 0; i < b; i++)
		matrix1[i] = new int[b];
	float fi = (2 * PI) / b;
	float angel = 0.0;
	for (int i = 0; i < b; i++)
		for (int j = 0; j < b; j++)
		{
			matrix[i][j] = 0;
		}
	cout << "| |";
	for (int i = 1; i <= b; i++)
	{
		cout << i << '|';
	}
	cout << endl;
	for (int i = 0; i < b; i++)
	{
		p[i].x = cos(angel);
		p[i].y = sin(angel);
		while (true)
		{
			cout << "|" << i + 1 << "|";
			flag = false;
			for (int j = 0; j <= i; j++)
			{
				cout << " |";
			}
			for (int j = i + 1; j < b; j++)
			{
				cin >> f;
				if ((f < 0) || (f > 1))
				{
					cout << "INVALID NUMBER" << endl;
					flag = true;
					break;
				}
				else matrix[i][j] = f;
			}
			if (!flag)
				break;
		}
		angel += fi;
	}
	for (int i = 0; i < b; i++)
		for (int j = 0; j < i; j++)
			matrix[i][j] = matrix[j][i];
	for (int i = 0; i < b; i++)
		for (int j = 0; j < b; j++)
			matrix1[i][j] = matrix[i][j];
	cout << endl << "Enter the number point for which you want to remove adjacent edges" << endl;
	while (true)
	{
		cin >> f;
		if ((f > 0) && (f <= b))
			break;
		else cout << "Invalid number" << endl;
	}
	f--;
	for (int i = 0; i < b; i++)
	{
		matrix1[i][f] = 0;
		matrix1[f][i] = 0;
	}
	cout << endl << "| |";
	for (int i = 1; i <= b; i++)
		cout << i << "|";
	cout << endl;
	for (int i = 0; i < b; i++)
	{
		cout << "|" << i + 1 << "|";
		for (int j = 0; j < b; j++)
			cout << matrix[i][j] << "|";
		cout << endl;
	}
	cout << endl << "| |";
	for (int i = 1; i <= b; i++)
		cout << i << "|";
	cout << endl;
	for (int i = 0; i < b; i++)
	{
		matr[i].index = i;
		matr[i].n = 0;
		for (int j = 0; j < b; j++)
			if(matrix1[i][j]==1)
				matr[i].n++;
	}
	for (int i = 0; i < b; i++)
	{
		int min = matr[i].n,index=i;
		line t;
		for(int j=i+1;j<b;j++)
			if (matr[j].n < min)
			{
				min = matr[j].n;
				index = j;
			}
		t.index = matr[i].index;
		t.n = matr[i].n;
		matr[i].index = matr[index].index;
		matr[i].n = matr[index].n;
		matr[index].index = t.index;
		matr[index].n = t.n;
		cout << "|" << matr[i].index+1<< "|";
		for (int j = 0; j < b; j++)
		{
			cout << matrix1[matr[i].index][j] << "|";
		}
		cout << endl;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graph");
	glClearColor(1.0, 1.0, 1.0, 0.0);	
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(render);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(700, 100);
	glutCreateWindow("Modified Graph");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(render1);
	glutMainLoop();
	return 0;
}