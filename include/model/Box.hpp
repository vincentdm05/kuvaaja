#ifndef BOX_HPP
#define BOX_HPP

#include "Model.hpp"

namespace model {

class Box : public Model
{
public:
  Box();
  virtual ~Box();

protected:
  const std::string &modelName() const override { return cClassName; }
  Box *makeBlueprint() override;

private:
  Box(unsigned int vertexCount); // Blueprint ctr

  static const std::string cClassName;
  static unsigned int cNumInstances;
};

} // namespace model

#endif // BOX_HPP
