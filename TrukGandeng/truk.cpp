// Nama File : truk.cpp
// Deskripsi : modul truk
// Tanggal : Senin, 23 Mei 2022
// Lab : GKV A2

#include <math.h>
#ifdef __APPLE__ // untuk program yang dijalankan di MacOS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else // untuk program yang dijalankan di Windows
#include <GL/glut.h>
#endif

void pembuatSegiEmpat(
                      float x1,float y1, float z1,
                      float x2,float y2, float z2,
                      float x3,float y3, float z3,
                      float x4,float y4, float z4 )
{
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glEnd();
}


void trukGandeng()
{
        GLUquadricObj * quadr;
        quadr = gluNewQuadric();
        
        //==============CHASSIS==============
        glPushMatrix();
        //frame utama
            glScalef(1.15,1.15,1.15);
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
	            glPushMatrix();
	                glTranslatef(0.0,1.0,0.0);
	                glScalef(1.5, 0.25, 5.0);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        
	            glPushMatrix();
	                glTranslatef(0.0,0.75,2.5);
	                glScalef(1.5, 0.25, 2.0);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        
	        // roda depan kiri
	            glPushMatrix();
	                glTranslatef(0.9, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	        // roda depan kanan
	            glPushMatrix();
	                glTranslatef(-1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	        
	            glPushMatrix();
	                glTranslatef(-1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	        
	        // roda belakang kiri
	            glPushMatrix();
	                glTranslatef(0.75, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	        
	            glPushMatrix();
	                glTranslatef(1.00, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	        // roda belakang kanan
	            glPushMatrix();
	                glTranslatef(-1.05, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	        
	            glPushMatrix();
	                glTranslatef(-1.0, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	        glPopMatrix();
        
        	glPushMatrix();
        		glColor3f(1.0,1.0,1.0);
	        //wheelcover belakang kanan
		        glPushMatrix();
		            glTranslatef(-0.9, 1.0, -1.5);
		            glPushMatrix();
		                glScalef(0.35, 0.1, 0.8);
		                glutSolidCube(1.0);
		            glPopMatrix();
		                    
		            glPushMatrix();
		                glTranslatef(0.0, -0.1, 0.5);
		                glRotatef(30,1,0,0);
		                glScalef(0.35, 0.1, 0.4);
		                glutSolidCube(1.0);
		            glPopMatrix();
		                
		            glPushMatrix();
		                glTranslatef(0.0, -0.1, -0.5);
		                glRotatef(-30,1,0,0);
		                glScalef(0.35, 0.1, 0.4);
		                glutSolidCube(1.0);
		            glPopMatrix();
		        glPopMatrix();
		     
	        //wheelcover belakang kiri
	            glPushMatrix();
	            glTranslatef(0.9, 1.0, -1.5);
	                glPushMatrix();
	                    glScalef(0.35, 0.1, 0.8);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, 0.5);
	                    glRotatef(30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, -0.5);
	                    glRotatef(-30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	            glPopMatrix();
	        glPopMatrix();
   
        //Gardan dan sumbu roda belakang
            glPushMatrix();
                glTranslatef(-1.0, 0.5, -1.5);
                glRotatef(90,0,1,0);
                gluCylinder(quadr, 0.1, 0.1, 2.0, 32, 32);
            glPopMatrix();
        
            glPushMatrix();
                glTranslatef(0, 0.5, -1.5);
                glRotatef(90,0,1,0);
                gluSphere(quadr, 0.3, 32, 32);
            glPopMatrix();
        
        
        //Powertrain
        	glPushMatrix();
        		glColor3f(0.0,0.0,0.0);
	            glPushMatrix();
	                glTranslatef(0.0, 0.75, 1.0);
	                glScalef(0.6, 0.5, 1.0);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        
	            glPushMatrix();
	                glTranslatef(0.0, 0.75, 1.6);
	                glutSolidCube(0.75);
	            glPopMatrix();
	        glPopMatrix();
        
        
        //Gardan dan sumbu roda depan
            glPushMatrix();
                glTranslatef(-1.0, 0.5, 2.25);
                glRotatef(90,0,1,0);
                gluCylinder(quadr, 0.1, 0.1, 2.0, 32, 32);
            glPopMatrix();
        
            glPushMatrix();
                glTranslatef(0, 0.5, 2.25);
                glRotatef(90,0,1,0);
                gluSphere(quadr, 0.3, 32, 32);
            glPopMatrix();
		glPopMatrix();

        //==============BODY==============
        glPushMatrix();
            glTranslatef(0.0, 1.25, 3.85);
        //base
        //glScalef(5.0,5.0,5.0);
            glPushMatrix();
            	glColor3f(1.0,0.0,0.0);
                glTranslatef(0,-0.15,0);
                glScalef(2.5, 0.75, 2.0);
                glutSolidCube(1.0);
            glPopMatrix();
        //half cabin
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
                glTranslatef(0, 0.6, -1.0);
                glScalef(2.5, 2.25, 0.5);
                glutSolidCube(1.0);
            glPopMatrix();
        //roof
            glPushMatrix();
            	glColor3f(1.0,0.0,0.0);
                glTranslatef(0, 1.55, 0);
                glScalef(2.8, 0.25, 1.8);
                glutSolidCube(1.0);
            glPopMatrix();
        //a pillar kanan
            glPushMatrix();
            	glColor3f(0.5,0.5,0.5);
                glRotatef(-10, 1,0,0);
                glTranslatef(-1.1, 0.8, 0.75);
                glScalef(0.25, 1.5, 0.25);
                glutSolidCube(1.0);
            glPopMatrix();
        //a pillar kiri
            glPushMatrix();
            	glColor3f(0.5,0.5,0.5);
                glRotatef(-10, 1,0,0);
                glTranslatef(1.1, 0.8, 0.75);
                glScalef(0.25, 1.5, 0.25);
                glutSolidCube(1.0);
            glPopMatrix();
        
		//Wheelcover
			glPushMatrix();
				glColor3f(1.0,1.0,1.0);
	        //wheelcover kanan
	        //atas
	            glPushMatrix();
	                glTranslatef(1.3, 0.1, -0.85);
	                glScalef(0.25, 0.25, 0.75);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //samping
	            glPushMatrix();
	                glTranslatef(1.3, -0.2, -0.39);
	                glRotatef(60,1,0,0);
	                glScalef(0.25, 0.25, 0.75);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //wheelcover kiri
	        //atas
	            glPushMatrix();
	                glTranslatef(-1.3, 0.1, -0.85);
	                glScalef(0.25, 0.25, 0.75);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //samping
	            glPushMatrix();
	                glTranslatef(-1.3, -0.2, -0.39);
	                glRotatef(60,1,0,0);
	                glScalef(0.25, 0.25, 0.75);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        glPopMatrix();
	        
		//Footstep
			glPushMatrix();
				glColor3f(0.0,0.0,0.0);
	        //footstep kanan
	            glPushMatrix();
	                glTranslatef(-1.3, -0.55, -0.1);
	                glScalef(0.25, 0.25, 0.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //footstep kiri
	            glPushMatrix();
	                glTranslatef(1.3, -0.55, -0.1);
	                glScalef(0.25, 0.25, 0.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        glPopMatrix();
	        
        //bumper
            glPushMatrix();
            	glColor3f(0.5,0.5,1.0);
                glTranslatef(0.0, -0.5, 1.00);
                glScalef(2.5, 0.2, 0.25);
                glutSolidCube(1.0);
            glPopMatrix();
        //grill
            glPushMatrix();
            	glColor3f(0.5,0.5,0.5);
                glTranslatef(0.0, -0.15, 1.0);
                glScalef(1.0, 0.5, 0.25);
                glutSolidCube(1.0);
            glPopMatrix();
		
		//Headlight frame
			glPushMatrix();
				glColor3f(0.5,0.5,0.5);    
	        //headlight frame kanan
	            glPushMatrix();
	                glTranslatef(-1.0, -0.15, 1.0);
	                glScalef(0.5, 0.25, 0.25);
	                glutSolidCube(1.0);
	            glPopMatrix();
			//headlight frame kiri
	            glPushMatrix();
	                glTranslatef(1.0, -0.15, 1.0);
	                glScalef(0.5, 0.25, 0.25);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        glPopMatrix();
	    
	    //Headlight
	    	glPushMatrix();
	    		glColor3f(1.0,1.0,1.0);
	        //headlight kanan
	            glPushMatrix();
	                glTranslatef(1.125, -0.15, 1.1);
	                gluCylinder(quadr, 0.125, 0.125, 0.08, 32, 32);
	            glPopMatrix();
	            glPushMatrix();
	                glTranslatef(-0.875, -0.15, 1.1);
	                gluCylinder(quadr, 0.125, 0.125, 0.08, 32, 32);
	            glPopMatrix();
	            glPushMatrix();
	                //((disk kanan))
	                glTranslatef(-1.125, -0.15, 1.175);
	                gluDisk(quadr, 0, 0.125, 32,32);
	                glPopMatrix();
	                glPushMatrix();
	                glTranslatef(-0.875, -0.15, 1.175);
	                gluDisk(quadr, 0, 0.125, 32,32);
	            glPopMatrix();
	
	        //headlight kiri
	            glPushMatrix();
	                glTranslatef(1.125, -0.15, 1.1);
	                gluCylinder(quadr, 0.125, 0.125, 0.08, 32, 32);
	                glPopMatrix();
	                glPushMatrix();
	                glTranslatef(0.875, -0.15, 1.1);
	                gluCylinder(quadr, 0.125, 0.125, 0.08, 32, 32);
	            glPopMatrix();
	            glPushMatrix();
	                //((disk kiri))
	                glTranslatef(1.125, -0.15, 1.175);
	                gluDisk(quadr, 0, 0.125, 32,32);
	                glPopMatrix();
	                glPushMatrix();
	                glTranslatef(0.875, -0.15, 1.175);
	                gluDisk(quadr, 0, 0.125, 32,32);
	            glPopMatrix();
	        glPopMatrix();
            
        //kaca
            glPushMatrix();
            	glColor3f(0.7,0.7,1.0);
                glRotatef(-10,1,0,0);
                glTranslatef(0,0.75,0);
                glScalef(2.0, 1.6, 1.50);
                glutSolidCube(1.0);
            glPopMatrix();
        
		//Sidepod
			glPushMatrix();
				glColor3f(0.5,0.5,0.5);    
	        //sidepod kiri
	            glPushMatrix();
	                glTranslatef(1.25,0.75,-1.0);
	                glScalef(0.25, 0.75, 0.25);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //sidepod kanan
	            glPushMatrix();
	                glTranslatef(-1.25,0.75,-1.0);
	                glScalef(0.25, 0.75, 0.25);
	                glutSolidCube(1.0);
	            glPopMatrix();
			glPopMatrix();
		
		//Spion
			glPushMatrix();
				glColor3f(0.0,0.0,0.0);	
	        //spion kiri
	            glPushMatrix();
	                glTranslatef(1.35,0.95,1.0);
	                glScalef(0.5, 0.75, 0.05);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //spion kanan
	            glPushMatrix();
	                glTranslatef(-1.35,0.95,1.0);
	                glScalef(0.5, 0.75, 0.05);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //bar spion kiri
	            glPushMatrix();
	                glTranslatef(1.35,1.45,0.850);
	                glRotatef(30,1,0,0);
	                glScalef(0.05, 0.05, 0.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        //bar spion kanan
	            glPushMatrix();
	                glTranslatef(-1.35,1.45,0.850);
	                glRotatef(30,1,0,0);
	                glScalef(0.05, 0.05, 0.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        glPopMatrix();
	        
        //Kontainer
			glPushMatrix();
				glColor3f(0.7,0.5,0.5);
                glTranslatef(0.0,1.15,-3.75);
                glScalef(2.75, 2.25, 4.80);
                glutSolidCube(1.0);
            glPopMatrix();
		glPopMatrix();

    //============== CHASSIS TRAILER==============
        glPushMatrix();
            glTranslatef(0,0,-7.5);
            glScalef(1.15,1.15,1.15);
            
			//Gandengan
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
				//gandengan kanan
	            glPushMatrix();
	                glTranslatef(-0.25,1.0,3.50);
	                glRotatef(15,0,1,0);
	                glScalef(0.25, 0.25, 1.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	            //gandengan kiri
	            glPushMatrix();
	                glTranslatef(0.25,1.0,3.5);
	                glRotatef(-15,0,1,0);
	                glScalef(0.25, 0.25, 1.5);
	                glutSolidCube(1.0);
	            glPopMatrix();
	        glPopMatrix();
	        
            //frame utama
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
                glTranslatef(0.0,1.0,0.0);
                glScalef(1.5, 0.25, 5.0);
                glutSolidCube(1.0);
            glPopMatrix();
            
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
                glTranslatef(0.0,0.75,2.5);
                glScalef(1.5, 0.25, 2.0);
                glutSolidCube(1.0);
            glPopMatrix();
            
            //Roda
            glPushMatrix();
            	glColor3f(0.0,0.0,0.0);
	            // roda depan kiri
	            glPushMatrix();
	                glTranslatef(0.9, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	            // roda depan kanan
	            glPushMatrix();
	                glTranslatef(-1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(-1.15, 0.5, 2.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	            
	            // roda belakang kiri
	            glPushMatrix();
	                glTranslatef(0.75, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(1.00, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	            // roda belakang kanan
	            glPushMatrix();
	                glTranslatef(-1.05, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.5, 0.5, 0.3, 32, 32);
	            glPopMatrix();
            
	            glPushMatrix();
	                glTranslatef(-1.0, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluDisk(quadr, 0, 0.5, 32, 32);
	            glPopMatrix();
	        glPopMatrix();
	        
            //Wheelcover
            glPushMatrix();
            	glColor3f(1.0,1.0,1.0);
	            //wheelcover belakang kanan
	            glPushMatrix();
	            glTranslatef(-0.9, 1.0, -1.5);
	                glPushMatrix();
	                    glScalef(0.35, 0.1, 0.8);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, 0.5);
	                    glRotatef(30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, -0.5);
	                    glRotatef(-30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	            glPopMatrix();
            
	            //wheelcover belakang kiri
	            glPushMatrix();
	            glTranslatef(0.9, 1.0, -1.5);
	                glPushMatrix();
	                    glScalef(0.35, 0.1, 0.8);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, 0.5);
	                    glRotatef(30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, -0.5);
	                    glRotatef(-30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	            glPopMatrix();
            
	            //wheelcover depan kanan
	            glPushMatrix();
	            	glTranslatef(-0.9, 1.0, 2.5);
	                glPushMatrix();
	                    glScalef(0.35, 0.1, 0.8);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, 0.5);
	                    glRotatef(30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, -0.5);
	                    glRotatef(-30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	            glPopMatrix();
	            //wheelcover depan kiri
	            glPushMatrix();
	                glTranslatef(0.9, 1.0, 2.5);
	                glPushMatrix();
	                    glScalef(0.35, 0.1, 0.8);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, 0.5);
	                    glRotatef(30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	                
	                glPushMatrix();
	                    glTranslatef(0.0, -0.1, -0.5);
	                    glRotatef(-30,1,0,0);
	                    glScalef(0.35, 0.1, 0.4);
	                    glutSolidCube(1.0);
	                glPopMatrix();
	            glPopMatrix();
	        glPopMatrix();
	        
	        //Gardan dan sumbu roda
	        glPushMatrix();
	        	glColor3f(0.0,0.0,0.0);
	            //Gardan dan sumbu roda belakang
	            glPushMatrix();
	                glTranslatef(-1.0, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.1, 0.1, 2.0, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(0, 0.5, -1.5);
	                glRotatef(90,0,1,0);
	                gluSphere(quadr, 0.3, 32, 32);
	            glPopMatrix();
	            
	            
	            //Gardan dan sumbu roda depan
	            glPushMatrix();
	                glTranslatef(-1.0, 0.5, 3.0);
	                glRotatef(90,0,1,0);
	                gluCylinder(quadr, 0.1, 0.1, 2.0, 32, 32);
	            glPopMatrix();
	            
	            glPushMatrix();
	                glTranslatef(0, 0.5, 3.0);
	                glRotatef(90,0,1,0);
	                gluSphere(quadr, 0.3, 32, 32);
	            glPopMatrix();
	        glPopMatrix();
	        
            //Kontainer
            glPushMatrix();
            	glColor3f(1.0,0.5,0.5);
                glTranslatef(0.0,2.15,0.5);
                glScalef(2.5, 2.0, 5.8);
                glutSolidCube(1.0);
            glPopMatrix();
		
        glPopMatrix();
}


