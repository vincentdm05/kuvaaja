#ifndef PRIMITIVE_MODEL_HPP
#define PRIMITIVE_MODEL_HPP

#include "Model.hpp"

#include <map>
#include <string>
#include <vector>

namespace model {

class PrimitiveModel : public Model
{
protected:
  PrimitiveModel();
  PrimitiveModel(unsigned int vertexCount, unsigned int indexCount = 0); // Blueprint ctr
  virtual ~PrimitiveModel();

  // These need to be called in constructor and destructor of inheriting classes
  void acquireBlueprint();
  void releaseBlueprint();

  virtual const std::string &modelName() const = 0;
  virtual PrimitiveModel *makeBlueprint() const = 0;
  void deleteBlueprint();

private:
  struct Blueprint
  {
    unsigned int instanceCount = 0;
    PrimitiveModel *model = nullptr;
  };
  typedef std::map<std::string, Blueprint> Blueprints;
  static Blueprints cBlueprints;

  // Being a blueprint or a unique model class is similar
  bool mIsBlueprint = true;
  bool mBlueprintAcquired = false;
};

} // namespace model

#endif // PRIMITIVE_MODEL_HPP
