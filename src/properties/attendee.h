#ifndef ICAL_PROPERTIES_ATTENDEE_H
#define ICAL_PROPERTIES_ATTENDEE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/member.h"
#include "parameters/partstat.h"
#include "parameters/sentby.h"
#include "parameters/language.h"
#include "parameters/role.h"
#include "parameters/rsvp.h"

namespace ical {
namespace properties {

class Attendee
{
private:
    std::string value;
    //std::vector<parameters::CuType> cuTypeParam;
    std::vector<parameters::Member> memberParam;
    std::vector<parameters::Role> roleParam;
    std::vector<parameters::PartStat> partStatParam;
    std::vector<parameters::Rsvp> rsvpParam;
    //std::vector<parameters::DelegatedTo> delegatedToParam;
    //std::vector<parameters::DelegatedFrom> delegatedFromParam;
    std::vector<parameters::SentBy> sentByParam;
    //std::vector<parameters::CN> cnParam;
    //std::vector<parameters::Dir> dirParam;
    std::vector<parameters::Language> languageParam;
public:
    Attendee() {}

    void print(std::ostream &out) const;

    static Attendee parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    //const std::vector<parameters::CuType> getCuTypeParam() const noexcept { return cuTypeParam; }
    const std::vector<parameters::Member> &getMemberParam() const noexcept { return memberParam; }
    const std::vector<parameters::Role> &getRoleParam() const noexcept { return roleParam; }
    const std::vector<parameters::PartStat> &getPartStatParam() const noexcept { return partStatParam; }
    const std::vector<parameters::Rsvp> &getRsvpParam() const noexcept { return rsvpParam; }
    //const std::vector<parameters::DelegatedTo> getDelegatedToParam() const noexcept { return delegatedToParam; }
    //const std::vector<parameters::DelegatedFrom> getDelegatedFromParam() const noexcept { return delegatedFromParam; }
    const std::vector<parameters::SentBy> &getSentByParam() const noexcept { return sentByParam; }
    //const std::vector<parameters::CN> getCnParam() const noexcept { return cnParam; }
    //const std::vector<parameters::Dir> getDirParam() const noexcept { return dirParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTENDEE_H

