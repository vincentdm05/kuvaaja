#ifndef BOX_HPP
#define BOX_HPP

#include "PrimitiveModel.hpp"

namespace model {

class Box : public PrimitiveModel
{
public:
  Box();
  virtual ~Box();

protected:
  const std::string &modelName() const override { return cClassName; }
  Box *makeBlueprint() const override;

private:
  Box(unsigned int vertexCount, unsigned int indexCount); // Blueprint ctr

  static const std::string cClassName;
};

} // namespace model

#endif // BOX_HPP
