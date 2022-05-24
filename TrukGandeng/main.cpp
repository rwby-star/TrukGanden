/* Anggota kelompok:
 Afnan Fauz Djau (24060120140158)
 Dhanang Kurniawan Diyatama Putra (24060120140122)
 Najib Rifai Indrayanto (24060120140082)
 Wahyu Arif Maulana (24060120120018)
 Tanggal : Senin, 23 Mei 2022
 Lab : GKV A2 */

//Bagian Afnan
#include "truk.h" // modul truk
#include "mobil.h" // modul truk
#include "jalan.h" // modul jalan
#include "pohon.h" // modul phon

#include <math.h>
#include <iostream>
#ifdef __APPLE__ // untuk program yang dijalankan di MacOS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else // untuk program yang dijalankan di Windows
#include <GL/glut.h>
#include <stdlib.h>
#endif

using namespace std;

float angle=0.0, deltaAngle = 0.0, addX = 0.0, addZ = 0.0, rratio;
float x=0.0f,y=15.0f,z=50.0f;
float lx=.0f,ly=0.0f,lz=30.0f;
int h,w;

//SkyColor
float time = 0.1;

// nyawa
int nyawa = 3;

// skor
int skor = 0;
int jeda = 0;
float putaranTruk = 90.0; 

float radius = 40.0, phi = 3.1415, theta = 0.0;

// untuk kamera bergerak orbit pada truk
float eyeX = x + radius*cos(phi)*sin(theta);
float eyeZ = z + radius*cos(theta);

// posisi truk
float posisiXTrukKekiri = 0.0; // sekaligus jarak btas
float posisiXTrukKekanan = 0.0; // sekaligus jarak btas
float deltaXTruk = 0.0;
float perubahanXTruk = 0.0;
float trukSpeed = 0.3;
float posisiXTrukUntukCollision = 0;
int nabrak = 1;
int nabrak2 = 1;
int nabrak3 = 1;

//batas jalan yang tidak bisa dilewati truk
float batasTrukKanan = -15;
float batasTrukKiri = 15;

// mobil
Halangan halangan1;
Halangan halangan2;
Halangan halangan3;

// random warna mobil
float r = rand() % 2, g = rand() % 2, b = rand() % 2;
float r2 = rand() % 2, g2 = rand() % 2, b2 = rand() % 2;
float r3 = rand() % 2, g3 = rand() % 2, b3 = rand() % 2;
float carSpeed = 5.0;

//posisi jalan
float posisiXJalan1 = 0.0;
float posisiXJalan2 = 0.0;
float posisiXJalan3 = 0.0;
float posisiXJalan4 = 0.0;
float jalanSpeed = 15 ;

//posisi pohon
float posisiZpohon1 = -700;
float posisiXpohon1 = rand() % 40 + 20;
float posisiZpohon2 = -900;
float posisiXpohon2 = rand() % 10 - 60;
float posisiZpohon3 = -1000;
float posisiXpohon3 = rand() % 10 - 60;
float posisiZpohon4 = -900;
float posisiXpohon4 = rand() % 60 + 20;
float posisiZpohon5 = -900;
float posisiXpohon5 = rand() % 80 + 20;
float posisiZpohon6 = -1200;
float posisiXpohon6 = rand() % 40 - 60;
float posisiZpohon7 = -900;
float posisiXpohon7 = rand() % 40 + 50;
float posisiZpohon8 = -800;
float posisiXpohon8 = rand() % 40 + 20;

// posisi masjid
float posisiZmasjid = -1600;
float posisiXmasjid = rand() % 90 + 20;

//status gameover
int gameover = 0;

void Reshape(int w1, int h1)
{
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    rratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(50, rratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              eyeX, y, eyeZ, // posisi kamera
              lx, ly, lz, // target shoot
              0.0f, 1.0f, 0.0f); // up
}

void orientMe(float ang)
{
    theta = ang;
    
    // untuk kamera bergerak orbit pada truk
    eyeX = x + radius*cos(phi)*sin(theta);
    eyeZ = z + radius*cos(theta);
    
   
    glLoadIdentity();
    gluLookAt(eyeX, y , eyeZ, lx, ly, lz, 0.0f, 1.0f, 0.0f);

}

void trukKekananKekiri(float xTruk)
{
        perubahanXTruk = xTruk;
}

// sumber cahaya
float l[] = { 100.0, 80.0, 0.0 }; // koordinat sumber cahaya
float n[] = { 0.0, -2.0, 0.0 };
float e[] = { 0.0, 0.2, 0.0 };

//membuat proyeksi bayangan
void glShadowProjection(float * l, float * e, float * n)
{
    float d, c;
    float mat[16];
    d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
    c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;
    mat[0] = l[0]*n[0]+c;
    // membuat matrik. OpenGL menggunakan kolom matrik
    mat[4] = n[1]*l[0];
    mat[8] = n[2]*l[0];
    mat[12] = -l[0]*c-l[0]*d;
    mat[1] = n[0]*l[1];
    mat[5] = l[1]*n[1]+c;
    mat[9] = n[2]*l[1];
    mat[13] = -l[1]*c-l[1]*d;
    mat[2] = n[0]*l[2];
    mat[6] = n[1]*l[2];
    mat[10] = l[2]*n[2]+c;
    mat[14] = -l[2]*c-l[2]*d;
    mat[3] = n[0];
    mat[7] = n[1];
    mat[11] = n[2];
    mat[15] = -d;
    glMultMatrixf(mat); // kalikan matrik
}

void ulangGame()
{
    nyawa = 5;
    skor = 0;
}

void renderBitmapString(float x,float y,float z,char *string) {
  char *c;

  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void RenderScore() {
    // nyawa
    char s[100];
    glPushMatrix();
    sprintf(s,"Nyawa: %d", nyawa);
    glColor3f(1,1,1);
    renderBitmapString(5, 30, 0,s); //y axis inverted
    glPopMatrix();
    
    // skor
    char s2[100];
    glPushMatrix();
    sprintf(s2,"Skor: %d", skor);
    glColor3f(1,1,1);
    renderBitmapString(150, 30, 0,s2); //y axis inverted
    glPopMatrix();
    
    
    //gameover
    if(gameover){
        char s3[100];
        glPushMatrix();
        sprintf(s3,"Game Over");
        glColor3f(1,0,0);
        renderBitmapString(1100/2, 900/2, 0,s3); //y axis inverted
        glPopMatrix();
        char s4[100];
        glPushMatrix();
        sprintf(s4,"Tekan 'spasi' untuk mengulang");
        glColor3f(1,0,0);
        renderBitmapString(900/2, (900/2)+30, 0,s4); //y axis inverted
        glPopMatrix();
    }
}

//Bagian Dhanang

void setOrthographicProjection() {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // set a 2D orthographic projection
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Display()
{
    if(time <= 90){
    	glClearColor(0.937, 0.631, 0.403, 0);//pagi
    	time = time + 0.5;
    }
    else if(time > 90 && time <=180){
    	glClearColor(0.552, 0.956, 0.984, 0); //siang
    	time = time + 0.5;
    }
    else if(time > 180 && time < 270){
    	glClearColor(0.937, 0.631, 0.403, 0);//sore
    	time = time + 0.5;
    }
    else if(time >= 270 && time < 360){
    	glClearColor(0.047, 0.074, 0.0254, 0);//malem
    	time = time + 0.5;
    	if(time >= 360){
    		time = 0.0;
    	}
    }

    
    if(deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle);
        
    }
    
    if(deltaXTruk == -trukSpeed) // enabler ke kanan
    {
        if(posisiXTrukKekanan >= batasTrukKanan) // mentok jalan kanan kanan
        {
            //collision nyawa
            posisiXTrukUntukCollision += 0.2;
            
            // collision jalan
            posisiXTrukKekanan += deltaXTruk;
            posisiXTrukKekiri += deltaXTruk; // agar bisa bergerak ke kiri walaupun mentok kanan
            trukKekananKekiri(posisiXTrukKekanan);
        }
    }
    else if (deltaXTruk == trukSpeed) // enabler ke kiri
    {
        if(posisiXTrukKekiri <= batasTrukKiri) // mentok jalan kanan kiri
        {
            //collision nyawa
            posisiXTrukUntukCollision -= 0.2;
            
            // collision jalan
            posisiXTrukKekanan += deltaXTruk ; // agar bisa bergerak ke kanan walaupun mentok kiri
            posisiXTrukKekiri += deltaXTruk;
            trukKekananKekiri(posisiXTrukKekiri);
        }
        
    }
        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_POSITION, l);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    
    // pergerakan truk kanan kiri
    glPushMatrix();
    glTranslatef(0, 0, 40);
    glRotatef(-180, 0.0, 1.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(perubahanXTruk, 0, 0);
    trukGandeng();
    glPopMatrix();
    
    if (posisiZpohon1 > 150)
    {
        posisiZpohon1 = -700;
        posisiXpohon1 = rand() % 40 + 30;
    }
    else{
        posisiZpohon1 += jalanSpeed * 0.8;
        
    }
    
    // pohon
    glPushMatrix();
    glTranslatef(posisiXpohon1, 0, posisiZpohon1);
    glScalef(2, 3, 2);
    pohon1();
    glPopMatrix();
    
    
    if (posisiZpohon2 > 300)
    {
        posisiZpohon2 = -700;
        posisiXpohon2 = rand() % 20 - 80;
    }
    else{
        posisiZpohon2 += jalanSpeed * 0.8; 
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon2, 0, posisiZpohon2);
    glScalef(2, 3, 2);
    pohon2();
    glPopMatrix();
    
    if (posisiZpohon3 > 300)
    {
        posisiZpohon3 = -900;
        posisiXpohon3 = rand() % 20 - 100;
    }
    else{
        posisiZpohon3 += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon3, 0, posisiZpohon3);
    glScalef(2, 3, 2);
    pohon1();
    glPopMatrix();
    
    if (posisiZpohon4 > 300)
    {
        posisiZpohon4 = -1000;
        posisiXpohon4 = rand() % 60 + 30;
    }
    else{
        posisiZpohon4 += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon4, 0, posisiZpohon4);
    glScalef(2, 3, 2);
    pohon2();
    glPopMatrix();
    
    
    if (posisiZpohon5 > 300)
    {
        posisiZpohon5 = -1200;
        posisiXpohon5 = rand() % 80 + 30;
    }
    else{
        posisiZpohon5 += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon5, 0, posisiZpohon5);
    glScalef(2, 3, 2);
    pohon1();
    glPopMatrix();
    
    
    if (posisiZpohon6 > 300)
    {
        posisiZpohon6 = -1200;
        posisiXpohon6  = rand() % 20 - 70;
    }
    else{
        posisiZpohon6 += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon6, 0, posisiZpohon6);
    glScalef(2, 3, 2);
    pohon1();
    glPopMatrix();
    
    
    if (posisiZpohon7 > 300)
    {
        posisiZpohon7 = -1400;
        posisiXpohon7 = rand() % 80 + 30;
    }
    else{
        posisiZpohon7 += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXpohon7, 0, posisiZpohon7);
    glScalef(2, 3, 2);
    pohon2();
    glPopMatrix();
    
    
//Bagian Najib
    
    // masjid
    if (posisiZmasjid > 500)
    {
        posisiZmasjid = -1600;
        posisiZmasjid = rand() % 100 + 100;
    }
    else{
        posisiZmasjid += jalanSpeed * 0.8;
        
    }
    glPushMatrix();
    glTranslatef(posisiXmasjid, 0, posisiZmasjid);
    glRotatef(-90, 0, 1, 0);
    glScalef(2, 2, 2);
    masjid();
    glPopMatrix();
    
    
    // jalan raya bergerak
    
    Jalan jalan2[3];
    Jalan jalan3[3];
    Jalan jalan4[3];
    
    Jalan jalan5[3];
    Jalan jalan6[3];
    Jalan jalan7[3];
    
    Jalan jalan8[3];
    Jalan jalan9[3];
    Jalan jalan10[3];
   
    
    
    if(posisiXJalan1 > 300.0 )
    {
        posisiXJalan1 = -300;
    }
    else
    {
        
        posisiXJalan1 += jalanSpeed * 0.9;
    }
    
    if(posisiXJalan2 > 300.0 )
    {
        posisiXJalan2 = -300;
    }
    else
    {
        posisiXJalan2 += jalanSpeed * 0.9 ;
    }
    
    if(posisiXJalan3 > 300.0 )
    {
        posisiXJalan3 = -300;
    }
    else
    {
        posisiXJalan3 += jalanSpeed * 0.9;
    }
    if(posisiXJalan4 > 300.0){
    	posisiXJalan4 = -300;
    }
    else{
    	posisiXJalan4 += jalanSpeed *0.9;
    }
    
    //dasar
    glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    pembuatSegiEmpat(25, -0.2, -100,
                     25, -0.2, 100,
                     -25, -0.2, 100,
                     -25, -0.2, -100);
    glPopMatrix();
    
    
    // muslti-jalan raya 1
    glPushMatrix();
    glTranslatef(0 , 0, posisiXJalan1);
    // jalan raya 3
    glPushMatrix();
       glTranslatef(0, 0, -200);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan2[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan2[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan2[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 2
    glPushMatrix();
       glTranslatef(0, 0, 0);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan3[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan3[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan3[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 1
    glPushMatrix();
        glTranslatef(0, 0, 200);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan4[0].jalan();
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan4[1].jalan();
        glPopMatrix();
            
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan4[2].jalan();
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
   
    // muslti-jalan raya 2
    glPushMatrix();
    glTranslatef(0 , 0, posisiXJalan2);
    // jalan raya 3
    glPushMatrix();
       glTranslatef(0, 0, -800);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan5[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan5[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan5[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 2
    glPushMatrix();
       glTranslatef(0, 0, -600);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan6[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan6[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan6[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 1
    glPushMatrix();
        glTranslatef(0, 0, -400);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan7[0].jalan();
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan7[1].jalan();
        glPopMatrix();
            
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan7[2].jalan();
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    // multi-jalan raya 3
    glPushMatrix();
    glTranslatef(0 , 0, posisiXJalan3);
    // jalan raya 3
    glPushMatrix();
       glTranslatef(0, 0, -1400);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan8[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan8[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan8[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 2
    glPushMatrix();
       glTranslatef(0, 0, -1200);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan9[0].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan9[1].jalan();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan9[2].jalan();
        glPopMatrix();
    glPopMatrix();
    
    // jalan raya 1
    glPushMatrix();
        glTranslatef(0, 0, -1000);
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        jalan10[0].jalan();
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, 15);
        jalan10[1].jalan();
        glPopMatrix();
            
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, -15);
        jalan10[2].jalan();
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //pinggiran jalan
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    jalan2[0].pinggiranJalan();
    glPopMatrix();
    
    // Halangan
    
    // mobil ke-1
        // posisi random mobil berkurang tiap iterasi, dan diatur ulang ketika > 150.0
        if(halangan1.posisiZMobil > 150.0 ) // 150
        {
            halangan1.posisiZMobil = -700.0 ;
            halangan1.posisiXMobil = rand() % 40 - 20 ; // atur ulang posisi di sumbu x
            // warna mobil juga diubah
            r = (rand() % 11) * 0.1;
            g = (rand() % 11) * 0.1;
            b = (rand() % 11) * 0.1; // agar hasilnya 0.0 -- 1.0
        }
        else
        {
            halangan1.posisiZMobil += carSpeed;
        }
        
        // mobil bergerak dan posisi random
        glPushMatrix();
        // cukup bergerak di sumbu x dan z
        glTranslatef(halangan1.posisiXMobil, 1.7, halangan1.posisiZMobil);
        glScalef(0.15, 0.15, 0.15);
        glRotatef(90, 0.0, 1.0, 0.0);
        halangan1.Mobil(r,g,b);
        glPopMatrix();
        
        // ketika mobil berada dalam area truk maka nyawa berkurang
        
        if ( (halangan1.posisiZMobil >= 30 && halangan1.posisiZMobil <= 50) && (halangan1.posisiXMobil-5 <= posisiXTrukUntukCollision && halangan1.posisiXMobil+2 >= posisiXTrukUntukCollision) && (nabrak) )
        {
            // agar nyawa tidak terus menerus habis
            nabrak = 0;
            if(!gameover){
                nyawa--;
            }
        }
        //  agar nyawa tidak terus menerus habis
        if(halangan1.posisiZMobil > 50)
        {
            nabrak = 1;
        }

    
    // mobil ke-2
    if(halangan2.posisiZMobil > 150.0 ) // 150
    {
        halangan2.posisiZMobil = -1000.0 ;
        halangan2.posisiXMobil = rand() % 40 - 20 ; // atur ulang posisi di sumbu x
        // warna mobil juga diubah
        r2 = (rand() % 11) * 0.1;
        g2 = (rand() % 11) * 0.1;
        b2 = (rand() % 11) * 0.1; // agar hasilnya 0.0 -- 1.0
    }
    else
    {
        halangan2.posisiZMobil += carSpeed;
    }
    
    // mobil bergerak dan posisi random
    glPushMatrix();
        // cukup bergerak di sumbu x dan z
        glTranslatef(halangan2.posisiXMobil, 1.7, halangan2.posisiZMobil);
        glScalef(0.15, 0.15, 0.15);
        glRotatef(90, 0.0, 1.0, 0.0);
        halangan1.Mobil(r2,g2,b2);
    glPopMatrix();
    
    if ( (halangan2.posisiZMobil >= 0 && halangan2.posisiZMobil <= 60) && (halangan2.posisiXMobil-5 <= posisiXTrukUntukCollision && halangan2.posisiXMobil+8 >= posisiXTrukUntukCollision) && (nabrak2) )
    {
        // agar nyawa tidak terus menerus habis
        nabrak2 = 0;
        if(!gameover){
            nyawa--;
        }
    }
    // agar nyawa tidak terus menerus habis
    if(halangan2.posisiZMobil > 100)
    {
        nabrak2 = 1;
    }
    
    // scoring
    if(jeda < 100)
    {
        jeda++;
    }
    else
    {
        jeda = 0;
        if(!gameover){
            skor++;
        }
        
    }
    
    //nyawa dan score
        setOrthographicProjection();
        glPushMatrix();
        glLoadIdentity();
        RenderScore();
        glPopMatrix();
        restorePerspectiveProjection();
    
    if (nyawa <= 0){
        gameover = 1;
    }
    
    // akhiran
    glutSwapBuffers();
    glFlush();
}

//Bagian Wahyu

void keyboardKontrolPress(unsigned char key, int x , int y)
{
    switch (key) {
            // karena truk dirotate sehingga yang berubah sebenarnya adalah sumbu z
        case 'a':
            deltaXTruk = trukSpeed; // truk bergerak ke kiri
            break;
        case 'd':
            deltaXTruk = -trukSpeed; // truk bergerak ke kanan
            break;
        case 32:
            if(gameover){
                skor = 0;
                nyawa = 5;
                gameover = 0;
            }
            break;
        default:
            break;
    }
}

void keyboardKontrolRelease(unsigned char key, int x , int y)
{
    switch (key) {
            // karena truk dirotate sehingga yang berubah sebenarnya adalah sumbu z
        case 'a':
            deltaXTruk = 0.0; // truk bergerak ke kiri
            break;
        case 'd':
            deltaXTruk = 0.0; // truk bergerak ke kanan
            break;
        
        default:
            break;
    }
}


void pressKey(int k,int x, int y)
{
    switch (k) {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.03f;
            break;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.03f;
            break;
        default:
            break;
    }
}

void releaseKey(int k,int x, int y)
{
    switch (k) {
        case GLUT_KEY_LEFT:
            if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;
        case GLUT_KEY_RIGHT:
            if (deltaAngle > 0.0f )
                deltaAngle = 0.0f;
            break;
        default:
            break;
    }
}

const GLfloat light_ambient[] = {0.5f,0.5f,0.5f,0.0f};
const GLfloat light_diffuse[] = {1.0f,0.8f,0.2f,1.0f};
const GLfloat light_specular[] = {1.0f,1.0f,1.0f,1.0f};
const GLfloat light_position[] = {0.0f,20.0f,10.0f,1.0f};
const GLfloat mat_ambient[] = {0.831f,0.368f,0.086f,0.5f};
const GLfloat mat_diffuse[] = {0.8f,0.8f,0.8f,1.0f};
const GLfloat mat_specular[] = {1.f,1.f,1.f,1.0f};
const GLfloat high_shininess[] = {100.f};

void lighting()
{
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_FOG_HINT);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 400.0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // mobil
    halangan1.posisiXMobil = rand() % 30 - 15, halangan1.posisiZMobil = -700.0;
    halangan2.posisiXMobil = rand() % 30 - 15, halangan2.posisiZMobil = -1000.0;
    halangan3.posisiXMobil = rand() % 30 - 15, halangan3.posisiZMobil = -700.0;
}

int main(int argc,char **argv)
{
    glutInit(&argc, argv);
    //aktifkan depth
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Truk Gandeng");
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardKontrolPress);
    glutKeyboardUpFunc(keyboardKontrolRelease);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutReshapeFunc(Reshape);
    
    // Cahaya
    lighting();
    // setup awal
    init();
    
    // Mereset koordinat sebelum dimodifikasi/diubah
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -150.0);
    
    glutMainLoop();
    return 0;
}
