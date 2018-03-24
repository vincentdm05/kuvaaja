#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "PrimitiveModel.hpp"

namespace model {

class Triangle : public PrimitiveModel
{
public:
  Triangle();
  virtual ~Triangle();

protected:
  const std::string &modelName() const override { return cClassName; }
  Triangle *makeBlueprint() const override;

private:
  Triangle(unsigned int vertexCount); // Blueprint ctr

  static const std::string cClassName;
};

} // namespace model

#endif // TRIANGLE_HPP
