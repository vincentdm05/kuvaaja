#include "model/Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <map>
#include <stdio.h>
#include <string>
#include <vector>

namespace model
{

Model::Model()
  : Model(true)
{}

Model::Model(const std::string &path)
  : Model(true)
{
  loadFromFile(path);
}

Model::~Model()
{
  reset();
  delete mIndices;
  delete mVertices;
  delete mNormals;
  delete mVertexColors;
  delete mUVs;
}

bool Model::loadFromFile(const std::string &path)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), nullptr) || !err.empty())
  {
    fprintf(stderr, "%s\n", err.c_str());
    return false;
  }

  struct TupleKey
  {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 uv;
    TupleKey()
      : vertex(glm::vec3(0, 0, 0))
      , normal(glm::vec3(0, 0, 0))
      , uv(glm::vec2(0, 0))
    {}
    TupleKey(const glm::vec3 &v, const glm::vec3 &n, const glm::vec2 &c)
      : vertex(v)
      , normal(n)
      , uv(c)
    {}
    bool operator<(const TupleKey &o) const
    {
      return vertex[0] < o.vertex[0] || vertex[1] < o.vertex[1] || vertex[2] < o.vertex[2]
        || normal[0] < o.normal[0] || normal[1] < o.normal[1] || normal[2] < o.normal[2]
        || uv[0] < o.uv[0] || uv[1] < o.uv[1];
    }
  };
  struct TupleValue
  {
    int i;
    TupleValue()
      : i(-1)
    {}
  };
  std::map<TupleKey, TupleValue> primitiveTuples;
  int lastIndex = 0;

  // Shapes
  for (const tinyobj::shape_t &shape : shapes)
  {
    const tinyobj::mesh_t &mesh = shape.mesh;

    unsigned int maxIndices = mVertices->size() + mesh.indices.size();
    mVertices->reserve(maxIndices);
    mNormals->reserve(maxIndices);
    mVertexColors->reserve(maxIndices);
    mUVs->reserve(maxIndices);

    // Indices index
    unsigned int ii = 0;

    // Faces
    for (unsigned int fi = 0; fi < mesh.num_face_vertices.size(); fi++)
    {
      unsigned int nFaceVertices = mesh.num_face_vertices[fi];

      // Ignore non-triangles
      if (nFaceVertices != 3)
      {
        ii += nFaceVertices;
        continue;
      }

      glm::vec3 vertices[nFaceVertices];
      int normalIndices[nFaceVertices];
      bool normalsMissing = false;
      int uvIndices[nFaceVertices];
      for (unsigned int fvi = 0; fvi < nFaceVertices; fvi++)
      {
        const tinyobj::index_t &indices = mesh.indices[ii + fvi];
        int vi = indices.vertex_index;
        vertices[fvi] = glm::vec3(attrib.vertices[3 * vi], attrib.vertices[3 * vi + 1], attrib.vertices[3 * vi + 2]);
        int ni = indices.normal_index;
        if (ni == -1)
          normalsMissing = true;
        normalIndices[fvi] = ni;
        uvIndices[fvi] = indices.texcoord_index;
      }

      glm::vec3 faceNormal;
      if (normalsMissing)
        faceNormal = computeNormal(vertices[0], vertices[1], vertices[2]);

      // Add the data
      for (unsigned int fvi = 0; fvi < nFaceVertices; fvi++)
      {
        const glm::vec3 &vertex = vertices[fvi];

        glm::vec3 normal;
        int ni = normalIndices[fvi];
        if (ni < 0)
          normal = faceNormal;
        else
          normal = glm::vec3(attrib.normals[3 * ni], attrib.normals[3 * ni + 1], attrib.normals[3 * ni + 2]);

        glm::vec2 uv;
        int uvi = uvIndices[fvi];
        if (uvi == -1)
          uv = glm::vec2(0, 0);
        else
          uv = glm::vec2(attrib.texcoords[2 * uvi], attrib.texcoords[2 * uvi + 1]);

        TupleValue &tupleIndex = primitiveTuples[TupleKey(vertex, normal, uv)];
        if (tupleIndex.i == -1)
        {
          mVertices->push_back(vertex);
          mNormals->push_back(normal);
          mUVs->push_back(uv);
          mVertexColors->push_back(normal * 0.5f + 0.5f);

          int index = lastIndex++;
          tupleIndex.i = index;
        }
        mIndices->push_back(tupleIndex.i);
      }

      ii += nFaceVertices;
    }
  }

  return true;
}

Model::Model(bool initialise)
{
  if (initialise)
    init();
}

Model::Model(unsigned int vertexCount, unsigned int indexCount)
{
  init();
  mIndices->reserve(indexCount);
  mVertices->reserve(vertexCount);
  mNormals->reserve(vertexCount);
  mVertexColors->reserve(vertexCount);
  mUVs->reserve(vertexCount);
}

void Model::init()
{
  mIndices = new std::vector<unsigned int>();
  mVertices = new std::vector<glm::vec3>();
  mNormals = new std::vector<glm::vec3>();
  mVertexColors = new std::vector<glm::vec3>();
  mUVs = new std::vector<glm::vec2>();
}

void Model::reset()
{
  if (mIndices)
    mIndices->clear();
  if (mVertices)
    mVertices->clear();
  if (mNormals)
    mNormals->clear();
  if (mVertexColors)
    mVertexColors->clear();
  if (mUVs)
    mUVs->clear();
}

glm::vec3 Model::computeNormal(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2) const
{
  glm::vec3 v01 = v1 - v0;
  glm::vec3 v02 = v2 - v0;
  glm::vec3 n = glm::cross(v01, v02);
  float length2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
  if (length2 > 0)
  {
    float length = sqrt(length2);
    n /= length;
  }
  return n;
}

} // namespace model
