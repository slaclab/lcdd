// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/id/IdSpec.hh"
#include "lcdd/schema/idspecElem.hh"
#include "lcdd/schema/idfieldElem.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/util/StringUtil.hh"

/**
 * @brief Creates IdSpec objects from idspec elements.
 * @note  Also creates IdField objects from idfield child elements.
 */
class idspecSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    idspecSubscriber() {
        Subscribe("idspec");
    }

    virtual ~idspecSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        //std::cout << "idspecSubscriber::Activate()" << std::endl;

        if (object) {
            const idspecElem* idspec_elem = dynamic_cast<const idspecElem*>(object);

            if (idspec_elem) {

                std::string name = idspec_elem->get_name();

                std::string length = idspec_elem->get_length();
                IdSpec::SizeType length_s = (IdSpec::SizeType) StringUtil::toInt(length);

                // @todo support lengths over 64
                if (length_s > 64) {
                    std::cerr << "Number of bits cannot be greater than 64 at this time." << std::endl;
                    assert(0);
                }

                IdSpec* idspec = new IdSpec;
                idspec->setName(name);
                idspec->setBitLength(length_s);

                IdManager::instance()->addIdSpec(name, idspec);

                // create fields
                ContentSequence* seq = const_cast<ContentSequence*>(idspec_elem->get_content());
                size_t count = seq->size();

                for (size_t i = 0; i < count; i++) {
                    const ContentGroup::ContentItem& segitem = seq->content(i);
                    if (segitem.tag == "idfield") {
                        idfieldElem* idfield_elem = dynamic_cast<idfieldElem*>(segitem.object);

                        if (idfield_elem) {

                            IdField* idfield = new IdField;

                            // label
                            std::string label = idfield_elem->get_label();

                            // start
                            std::string start = idfield_elem->get_start();
                            IdField::SizeType start_s = (IdField::SizeType) StringUtil::toInt(start);

                            // signed
                            std::string signed_str = idfield_elem->get_signed();
                            bool signed_bool = StringUtil::toBool(signed_str);

                            // length
                            std::string length = idfield_elem->get_length();
                            IdField::SizeType length_s = (IdField::SizeType) StringUtil::toInt(length);

                            // set in G4 object
                            idfield->setLabel(label);
                            idfield->setSigned(signed_bool);
                            idfield->setStart(start_s);
                            idfield->setLength(length_s);

                            // add to spec
                            idspec->addIdField(idfield);
                        } else {
                            G4Exception("", "", FatalException, "Failed cast to idfieldElem.");
                        }
                    } else {
                        std::cerr << "Ignoring unknown child - " << segitem.tag << std::endl;
                    }
                }
            } else {
                G4Exception("", "", FatalException, "Failed cast to idspecElem.");
            }
        } else {
            G4Exception("", "", FatalException, "SAXObject is null!");
        }

        //delete object;
    }
};

DECLARE_SUBSCRIBER_FACTORY(idspecSubscriber)
