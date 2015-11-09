#ifndef ICAL_PROPERTIES_REQUESTSTATUS_H
#define ICAL_PROPERTIES_REQUESTSTATUS_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"

namespace ical {
namespace properties {

class RequestStatus
{
private:
    std::string statCode;
    std::string statDesc;
    std::string data;

    std::vector<parameters::Language> languageParam;

public:
    static const std::string NAME;

    RequestStatus() {}

    void print(std::ostream &out) const;

    static RequestStatus parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getStatusCode() const noexcept { return statCode; }
    const std::string &getStatusDescription() const noexcept { return statDesc; }
    const std::string &getExtraData() const noexcept { return data; }

    const std::vector<parameters::Language> &getLanguageParam() const noexcept
    {
        return languageParam;
    }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_REQUESTSTATUS_H

