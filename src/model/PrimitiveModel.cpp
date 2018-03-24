#include "model/PrimitiveModel.hpp"

namespace model {

PrimitiveModel::Blueprints PrimitiveModel::cBlueprints;

PrimitiveModel::PrimitiveModel()
 : Model(false)
{
  mIsBlueprint = false;
}

PrimitiveModel::PrimitiveModel(unsigned int vertexCount, unsigned int indexCount)
  : Model(vertexCount, indexCount)
{
  mIsBlueprint = true;
}

PrimitiveModel::~PrimitiveModel()
{
  assert(!mBlueprintAcquired && "Warning! A model blueprint was acquired but not released.");

  if (!mIsBlueprint)
  {
    mIndices = nullptr;
    mVertices = nullptr;
    mNormals = nullptr;
    mVertexColors = nullptr;
    mUVs = nullptr;
  }
}

void PrimitiveModel::acquireBlueprint()
{
  if (mBlueprintAcquired)
    return;

  const std::string &name = modelName();
  Blueprints::iterator it = cBlueprints.find(name);
  if (it == cBlueprints.end())
    cBlueprints[name].model = makeBlueprint();

  Blueprint &blueprint = cBlueprints[name];
  PrimitiveModel *blueprintModel = blueprint.model;

  mIndices = blueprintModel->mIndices;
  mVertices = blueprintModel->mVertices;
  mNormals = blueprintModel->mNormals;
  mVertexColors = blueprintModel->mVertexColors;
  mUVs = blueprintModel->mUVs;

  blueprint.instanceCount++;
  mBlueprintAcquired = true;
}

void PrimitiveModel::releaseBlueprint()
{
  if (!mBlueprintAcquired || mIsBlueprint)
    return;

  Blueprints::iterator pair = cBlueprints.find(modelName());
  assert(pair != cBlueprints.end() && "Could not find blueprint for release!");
  if (pair == cBlueprints.end())
    return;

  Blueprint &blueprint = pair->second;
  blueprint.instanceCount--;

  if (blueprint.instanceCount == 0)
  {
    PrimitiveModel *blueprintModel = blueprint.model;
    cBlueprints.erase(pair);
    delete blueprintModel;
  }

  mBlueprintAcquired = false;
}

} // namespace model
