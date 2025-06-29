#pragma once

#include "Ellipse.hpp"

#include "ModelList.hpp"


class Pixel
{
   public:
    Pixel()
    : m_position{Vec3{0.0f, 0.0f, 0.0f}}
    {

    }
    Pixel(const char* name, Vec3 position)
    : m_name{name},
      m_position{position},
      m_worldPosition{position}
    {

    }
    ~Pixel()
    {

    }

    void setPosition(Vec3 position)
    {
    m_position = position;
    }

    String name() const
    {
    return m_name;
    }

    Vec3 position() const
    {
    return m_position;
    }

    Vec3 worldPosition() const
    {
    return m_worldPosition;
    }

   private:
    String m_name;
    Vec3 m_position;
    Vec3 m_worldPosition;
};

inline Array<Pixel, 8> createEightVertexCube(Array<Pixel, 8> cube, float amount)
{
    Array<Pixel, 8> cubeModel = cube;

    cubeModel[0] = Pixel{"VertexPixel0", Vec3{-amount, amount, -amount}};
    cubeModel[1] = Pixel{"VertexPixel1", Vec3{amount, amount, -amount}};
    cubeModel[2] = Pixel{"VertexPixel2", Vec3{-amount, amount, amount}};
    cubeModel[3] = Pixel{"VertexPixel3", Vec3{amount, amount, amount}};
    cubeModel[4] = Pixel{"VertexPixel4", Vec3{-amount, -amount, -amount}};
    cubeModel[5] = Pixel{"VertexPixel5", Vec3{amount, -amount, -amount}};
    cubeModel[6] = Pixel{"VertexPixel6", Vec3{-amount, -amount, amount}};
    cubeModel[7] = Pixel{"VertexPixel7", Vec3{amount, -amount, amount}};

    return cubeModel;
}

inline Vector<Vec3> findVerticies(Vec3 point0, Vec3 point1, float amountValue)
{
    Vector<Vec3> verticies;

    Vec3 delta = point0 - point1;
    Vec3 addDelta = delta / amountValue;
    Vec3 addAmount{0.0f};
    while(Ellipse::EllipseMath::length(addAmount) < Ellipse::EllipseMath::length(delta))
    {
    addAmount = addAmount + addDelta;

    Vec3 position = point1 + addAmount;

    verticies.push_back(position);
    }

    return verticies;
}

class CubeMadeCube
{
   public:
    CubeMadeCube(ModelList& modelList, Ellipse::Engine& engine, Light& light)
    : m_cubeScale{0.5f},
      m_modelList{modelList},
      m_camera{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule")).camera()},
      m_light{light}
    {

    }
    ~CubeMadeCube()
    {

    }

    void init()
    {
    m_modelVertex = createEightVertexCube(m_modelVertex, 5.0f);

    for(u64_t i=0;i<m_modelVertex.size();i++)
    {
    m_modelList.addModel(m_modelVertex[i].name().c_str(), "Cube", m_camera, m_light);
    m_modelList.model(m_modelVertex[i].name().c_str()).setTranslateAmount(m_modelVertex[i].position());
    m_modelList.model(m_modelVertex[i].name().c_str()).setScaleAmount(Vec3{m_cubeScale});
    }

    Vector<Pair<u64_t, u64_t>> vertexLocations{Pair<u64_t, u64_t>{0,1},
                                               Pair<u64_t, u64_t>{0,2},
                                               Pair<u64_t, u64_t>{0,4},
                                               Pair<u64_t, u64_t>{7,6},
                                               Pair<u64_t, u64_t>{7,5},
                                               Pair<u64_t, u64_t>{7,3},

                                               Pair<u64_t, u64_t>{1,3},
                                               Pair<u64_t, u64_t>{2,3},
                                               Pair<u64_t, u64_t>{1,5},
                                               Pair<u64_t, u64_t>{4,6},
                                               Pair<u64_t, u64_t>{2,6},
                                               Pair<u64_t, u64_t>{4,5}
                                              };

    for(u64_t i=0;i<vertexLocations.size();i++)
    {
    Vector<Vec3> verticies = findVerticies(m_modelVertex[vertexLocations[i].first].position(), m_modelVertex[vertexLocations[i].second].position(), 5.0f);
    for(u64_t j=0;j<verticies.size();j++)
    {
    m_vertexBetweenVertex.push_back(Pixel{Ellipse::format("Pixel{}", m_vertexBetweenVertex.size()).c_str(), verticies[j]});

    m_modelList.addModel(m_vertexBetweenVertex[m_vertexBetweenVertex.size() - 1].name().c_str(), "Cube", m_camera, m_light);
    m_modelList.model(m_vertexBetweenVertex[m_vertexBetweenVertex.size() - 1].name().c_str()).setTranslateAmount(verticies[j]);
    m_modelList.model(m_vertexBetweenVertex[m_vertexBetweenVertex.size() - 1].name().c_str()).setScaleAmount(Vec3{m_cubeScale});
    }
    }

    }

    template<typename Func>
    void linearFunc(Func func)
    {
    for(u64_t i=0;i<m_modelVertex.size();i++)
    {
    func(m_modelVertex[i]);
    m_modelList.model(m_modelVertex[i].name().c_str()).setTranslateAmount(m_modelVertex[i].position());
    }
    for(u64_t i=0;i<m_vertexBetweenVertex.size();i++)
    {
    func(m_vertexBetweenVertex[i]);
    m_modelList.model(m_vertexBetweenVertex[i].name().c_str()).setTranslateAmount(m_vertexBetweenVertex[i].position());
    }

    }

   private:
    Array<Pixel, 8> m_modelVertex;
    Vector<Pixel> m_vertexBetweenVertex;

    float m_cubeScale;

    ModelList& m_modelList;

		Ellipse::Camera m_camera;
    Light& m_light;
};

