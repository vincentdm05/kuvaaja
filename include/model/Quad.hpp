#ifndef QUAD_HPP
#define QUAD_HPP

#include "PrimitiveModel.hpp"

namespace model {

class Quad : public PrimitiveModel
{
public:
  Quad();
  virtual ~Quad();

protected:
  const std::string &modelName() const override { return cClassName; }
  Quad *makeBlueprint() const override;

private:
  Quad(unsigned int vertexCount, unsigned int indexCount); // Blueprint ctr

  static const std::string cClassName;
};

} // namespace model

#endif // QUAD_HPP
