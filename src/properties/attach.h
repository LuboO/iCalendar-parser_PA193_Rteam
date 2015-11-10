#ifndef ICAL_PROPERTIES_ATTACH_H
#define ICAL_PROPERTIES_ATTACH_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"
#include "parameters/fmttype.h"
#include "parameters/encoding.h"
#include "parameters/value.h"

namespace ical {
namespace properties {

class Attach
{
private:
    std::string value;
    std::vector<parameters::FmtType> fmttypeParam;
    std::vector<parameters::Encoding> encodingParam;
    std::vector<parameters::Value> valueParam;
public:
    static const std::string NAME;

    Attach() {}

    void print(std::ostream & out) const;

    static Attach parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    const std::vector<parameters::FmtType> &getFmtTypeParam() const noexcept { return fmttypeParam; }
    const std::vector<parameters::Encoding> &getEncodingParam() const noexcept { return encodingParam; }
    const std::vector<parameters::Value> &getValueParam() const noexcept { return valueParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTACH_H

