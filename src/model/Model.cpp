#include "model/Model.hpp"

#include <stdio.h>
#include <string>

namespace model
{

Model::Model()
  : Model(true)
{}

Model::Model(const std::string &path)
  : Model(true)
{
  loadObj(path);
}

Model::~Model()
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

  delete mIndices;
  delete mVertices;
  delete mNormals;
  delete mVertexColors;
  delete mUVs;
}

bool Model::loadObj(const std::string &path)
{
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> tempVertices;
  std::vector<glm::vec2> tempUvs;
  std::vector<glm::vec3> tempNormals;

  FILE *file = fopen(path.c_str(), "r");
  if (file == NULL)
  {
    printf("Impossible to open the file.\n");
    getchar();
    return false;
  }

  while(1)
  {
    char lineHeader[128];
    // Read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break;

    if (strcmp(lineHeader, "v") == 0)
    {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      tempVertices.push_back(vertex);
    }
    else if (strcmp(lineHeader, "vt") == 0)
    {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      uv.y = -uv.y;
      tempUvs.push_back(uv);
    }
    else if (strcmp(lineHeader, "vn") == 0)
    {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      tempNormals.push_back(normal);
    }
    else if (strcmp(lineHeader, "f") == 0)
    {
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9){
        printf("File can't be read.\n");
        fclose(file);
        return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices.push_back(uvIndex[0]);
      uvIndices.push_back(uvIndex[1]);
      uvIndices.push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
    else
    {
      // Probably a comment, eat up the rest of the line
      char stupidBuffer[1000];
      fgets(stupidBuffer, 1000, file);
    }
  }

  // For each vertex of each triangle
  for (unsigned int i=0; i<vertexIndices.size(); i++)
  {
    // Get the indices of its attributes
    unsigned int vertexIndex = vertexIndices[i];
    unsigned int uvIndex = uvIndices[i];
    unsigned int normalIndex = normalIndices[i];

    // Get the attributes thanks to the index
    glm::vec3 vertex = tempVertices[vertexIndex-1];
    glm::vec2 uv = tempUvs[uvIndex-1];
    glm::vec3 normal = tempNormals[normalIndex-1];

    // Put the attributes in buffers
    mVertices->push_back(vertex);
    mUVs->push_back(uv);
    mNormals->push_back(normal);
  }
  fclose(file);

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

} // namespace model
