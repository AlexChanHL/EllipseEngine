#pragma once

#include "Core/Base.hpp"
#include "Shape.hpp"

namespace Ellipse
{

class Draw2D
{
   public:
    Draw2D()
    {
    addQuadShape();
    }
     
    void addQuadShape()
    {
    Shape shape;
    Vector<float> verticies = 
    {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    };
      
    shape.m_verticies = VerticiesData{3, verticies.size() ,verticies};
    shape.m_name = "Quad";
    // [ Confusing name, should use basic shader ]
    shape.m_vShader = "Assets/Shader/Triangle.vert.glsl";
    shape.m_fShader = "Assets/Shader/Triangle.frag.glsl";
    m_shapes.push_back(shape);
    }

    Shape getShape(const char* name)
    {
        for(const Shape& s : m_shapes)
        {
        if(strcmp(s.m_name.c_str(), name) == 0)
        {
        return s;
        }
        }
        return Shape{"Null Shape", VerticiesData{}, "Null", "Null"};
    }

   private:
    // [ Maybe have the renderer create the shape and store it in
    //   a vector for later use so that don't create same shape
    //   over and again ]
    Vector<Shape> m_shapes;
};

}   //   namespace Ellipse
