//Usman Zahid
//uzahid@ucsc.edu
//
#include <typeinfo>
#include <math.h>
#include <unordered_map>
using namespace std;

#include "shape.h"
#include "util.h"
#include "graphics.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices): vertices(vertices) {
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat width, GLfloat height):
   polygon({{0, 0}, {width, 0}, {width, height}, {0, height}}) {
   DEBUGF ('c', this);
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

diamond::diamond(const GLfloat width, const GLfloat height):
   polygon({{0, 0}, {-width / 2, height / 2}, {0, height},
      {width / 2, height / 2}}) {
   DEBUGF ('c', this);
}

triangle::triangle (const vertex_list& vertices): polygon(vertices) {
   DEBUGF ('c', this);
}

equilateral::equilateral(const GLfloat width):
  triangle({{-width/2, 0}, {width/2, 0}, 
     {0,  GLfloat{sqrt(3)} * width/2}}) {
   DEBUGF ('c', this);
}

void text::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv((window::is_selected ? window::selected_color.ubvec : 
   color.ubvec));

   glRasterPos2f(center.xpos, center.ypos);
    //glRasterPos2f(center.ypos,center.xpos)
      glutBitmapString(glut_bitmap_font, 
   reinterpret_cast<const unsigned char*>(textdata.c_str()));
}

void ellipse::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glBegin (GL_POLYGON);
   //glEnable(GL_LINE_SMOOTH); 
   glEnable (GL_LINE_SMOOTH);
   glColor3ubv (color.ubvec);
   const float delta = 2 * M_PI / 32;
   for (float theta = 0; theta < 2 * M_PI; theta += delta) {
      float xpos = dimension.xpos/2 * cos(theta) + center.xpos;
      float ypos = dimension.ypos * sin (theta) 
      + center.ypos;
      glVertex2f (xpos, ypos);
   }
   glEnd(); 
   if(window::is_selected) {
      glLineWidth(window::selected_border);
      glBegin(GL_LINE_LOOP);
      glColor3ubv(window::selected_color.ubvec);
      const float delta = 2 * M_PI / 32;
      for (float theta = 0; theta < 2*M_PI; theta += delta) {
         float xpos = dimension.xpos/2 * cos(theta) + center.xpos;
         float ypos = dimension.ypos/2 * sin (theta) + center.ypos;
         glVertex2f (xpos, ypos);
      }
      glEnd(); 
   }
}

void polygon::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   GLfloat yaverage;
   GLfloat xaverage; 
   for(const vertex v: vertices) {
          xaverage += v.xpos;

      yaverage += v.ypos;
   }
   xaverage /= vertices.size();
   //float  vertavg = xaverage + yaverage; 
   yaverage /= vertices.size();
   glBegin(GL_POLYGON);
   glColor3ubv(color.ubvec);
   for(const vertex v: vertices) {
      GLfloat x = center.xpos + v.xpos - xaverage;
      GLfloat y = center.ypos + v.ypos - yaverage;
      glVertex2f(x, y);
   }
   glEnd();
   if(window::is_selected) {
      glLineWidth(window::selected_border);
      glBegin(GL_LINE_LOOP);
      glColor3ubv(window::selected_color.ubvec);
      for(const vertex v: vertices) {
         GLfloat x = center.xpos + v.xpos - xaverage;
         GLfloat y = center.ypos + v.ypos - yaverage;
         glVertex2f(x, y);
      }
      glEnd();
   }
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

