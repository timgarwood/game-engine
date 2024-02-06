#include "quad3d.h"

using namespace std;

Quad3d::Quad3d(btCollisionShape *collisionShape, Vector3f center, float faceLength, float height, float depth, Vector3f color) : GameObject(collisionShape)
{
    m_center = center;
    m_color = color;
    SetStartPosition(center);

    float cx = m_center.x;
    float cy = m_center.y;
    float cz = m_center.z;
    float halfFace = faceLength / 2.0;
    float halfDepth = depth / 2.0;
    float halfHeight = height / 2.0;

    m_vertices.push_back(Vector3f(Vector3f(cx + halfFace, cy + halfHeight, cz + halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx - halfFace, cy + halfHeight, cz - halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx - halfFace, cy + halfHeight, cz + halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx + halfFace, cy - halfHeight, cz - halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx - halfFace, cy - halfHeight, cz - halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx + halfFace, cy + halfHeight, cz - halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx + halfFace, cy - halfHeight, cz + halfDepth)));
    m_vertices.push_back(Vector3f(Vector3f(cx - halfFace, cy - halfHeight, cz + halfDepth)));

    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);

    m_indices.push_back(1);
    m_indices.push_back(3);
    m_indices.push_back(4);

    m_indices.push_back(5);
    m_indices.push_back(6);
    m_indices.push_back(3);

    m_indices.push_back(7);
    m_indices.push_back(3);
    m_indices.push_back(6);

    m_indices.push_back(2);
    m_indices.push_back(4);
    m_indices.push_back(7);

    m_indices.push_back(0);
    m_indices.push_back(7);
    m_indices.push_back(6);

    m_indices.push_back(0);
    m_indices.push_back(5);
    m_indices.push_back(1);

    m_indices.push_back(1);
    m_indices.push_back(5);
    m_indices.push_back(3);

    m_indices.push_back(5);
    m_indices.push_back(0);
    m_indices.push_back(6);

    m_indices.push_back(7);
    m_indices.push_back(4);
    m_indices.push_back(3);

    m_indices.push_back(2);
    m_indices.push_back(1);
    m_indices.push_back(4);

    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(7);
}

Quad3d::Quad3d(btCollisionShape *collisionShape, Vector3f center, float faceLength, float height, float depth) : Quad3d(collisionShape, center, faceLength, height, depth, Vector3f(1, 1, 1))
{
}

Vector3f Quad3d::GetCenter()
{
    return m_center;
}

Vector3f Quad3d::GetColor()
{
    return m_color;
}