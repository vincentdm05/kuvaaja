#ifndef QUAD_HPP
#define QUAD_HPP

#include "Model.hpp"

namespace model {

class Quad : public Model
{
public:
  Quad();
  virtual ~Quad();

protected:
  const std::string &modelName() const override { return cClassName; }
  Quad *makeBlueprint() override;

private:
  Quad(unsigned int vertexCount); // Blueprint ctr

  static const std::string cClassName;
  static unsigned int cNumInstances;
};

} // namespace model

#endif // QUAD_HPP
