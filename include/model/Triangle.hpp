#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Model.hpp"

namespace model {

class Triangle : public Model
{
public:
  Triangle();
  virtual ~Triangle();

protected:
  const std::string &modelName() const override { return cClassName; }
  Triangle *makeBlueprint() override;

private:
  Triangle(unsigned int vertexCount); // Blueprint ctr

  static const std::string cClassName;
  static unsigned int cNumInstances;
};

} // namespace model

#endif // TRIANGLE_HPP
