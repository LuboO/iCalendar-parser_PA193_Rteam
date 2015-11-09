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
#include "parameters/calusertype.h"
#include "parameters/delegatedto.h"
#include "parameters/delegatedfrom.h"
#include "parameters/commonname.h"
#include "parameters/direntryref.h"

namespace ical {
namespace properties {

class Attendee
{
private:
    std::string value;
    std::vector<parameters::CalUserType> calUserTypeParam;
    std::vector<parameters::Member> memberParam;
    std::vector<parameters::Role> roleParam;
    std::vector<parameters::PartStat> partStatParam;
    std::vector<parameters::Rsvp> rsvpParam;
    std::vector<parameters::DelegatedTo> delegatedToParam;
    std::vector<parameters::DelegatedFrom> delegatedFromParam;
    std::vector<parameters::SentBy> sentByParam;
    std::vector<parameters::CommonName> commonNameParam;
    std::vector<parameters::DirEntryRef> dirEntryRefParam;
    std::vector<parameters::Language> languageParam;
public:
    static const std::string NAME;

    Attendee() {}

    void print(std::ostream &out) const;

    static Attendee parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    const std::vector<parameters::CalUserType> getCalUserTypeParam() const noexcept { return calUserTypeParam; }
    const std::vector<parameters::Member> &getMemberParam() const noexcept { return memberParam; }
    const std::vector<parameters::Role> &getRoleParam() const noexcept { return roleParam; }
    const std::vector<parameters::PartStat> &getPartStatParam() const noexcept { return partStatParam; }
    const std::vector<parameters::Rsvp> &getRsvpParam() const noexcept { return rsvpParam; }
    const std::vector<parameters::DelegatedTo> getDelegatedToParam() const noexcept { return delegatedToParam; }
    const std::vector<parameters::DelegatedFrom> getDelegatedFromParam() const noexcept { return delegatedFromParam; }
    const std::vector<parameters::SentBy> &getSentByParam() const noexcept { return sentByParam; }
    const std::vector<parameters::CommonName> getCommonNameParam() const noexcept { return commonNameParam; }
    const std::vector<parameters::DirEntryRef> getDirEntryRefParam() const noexcept { return dirEntryRefParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTENDEE_H

