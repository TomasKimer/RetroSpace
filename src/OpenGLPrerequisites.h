// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLPrerequisites.h
  *  @brief  Prerekvizity pro praci s OpenGL.
  */

#pragma once

#ifdef _WIN32
    #define NOMINMAX    
    #include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>