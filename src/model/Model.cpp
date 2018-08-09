#include "model/Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

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

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), nullptr))
  {
    fprintf(stderr, "%s\n", err.c_str());
    return false;
  }

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

      // Vertices
      for (unsigned int fvi = 0; fvi < nFaceVertices; fvi++, ii++)
      {
        const tinyobj::index_t &indices = mesh.indices[ii];
        int vi = indices.vertex_index;
        int ni = indices.normal_index;
        int tci = indices.texcoord_index;

        if (vi < 0)
        {
          // TODO
        }
        else
        {
          mVertices->push_back(glm::vec3(attrib.vertices[3 * vi], attrib.vertices[3 * vi + 1], attrib.vertices[3 * vi + 2]));
        }

        if (ni < 0)
        {
          // TODO
        }
        else
        {
          mNormals->push_back(glm::vec3(attrib.normals[3 * ni], attrib.normals[3 * ni + 1], attrib.normals[3 * ni + 2]));
        }

        if (tci < 0)
        {
          // TODO
        }
        else
        {
          mUVs->push_back(glm::vec2(attrib.texcoords[2 * tci], attrib.texcoords[2 * tci + 1]));
        }

        mVertexColors->push_back(glm::vec3(1, 0, 0));

        // TODO: use a set to uniquely store tuples
        mIndices->push_back(ii);
      }
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

} // namespace model
