// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/subscribers/limitsetSubscriber.cc,v 1.5 2013-11-13 23:02:59 jeremy Exp $

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/schema/limit.hh"
#include "lcdd/schema/limitset.hh"
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/geant4/PhysicsLimitSet.hh"
#include "lcdd/util/StringUtil.hh"

#include <string>
#include <iostream>

using std::string;
using std::vector;

/**
 * @brief Creates PhysicsLimitSet objects from limitset elements.
 */
class limitsetSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:

    limitsetSubscriber() {
        Subscribe("limitset");
    }

    virtual void Activate(const SAXObject* object) {
        //std::cout << "limitsetSubscriber::Activate()" << std::endl;
        if (object != 0) {

            GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
            const limitset* lsobj = dynamic_cast<const limitset*>(object);

            if (lsobj != 0) {
                //std::cout << "got limitset: " << lsobj->get_name() << std::endl;

                PhysicsLimitSet* ls = new PhysicsLimitSet(lsobj->get_name());

                const ContentSequence* seq = lsobj->get_content();
                size_t count = seq->size();
                for (size_t i = 0; i < count; i++) {
                    if (seq->content(i).tag == "limit") {
                        limit* param = dynamic_cast<limit*>(seq->content(i).object);

                        if (param != 0) {
                            //std::cout << "got limit: " << param->get_name() << std::endl;

                            string unit = param->get_unit();
                            string particles = param->get_particles();
                            string limitName = param->get_name();

                            string sval = param->get_value();
                            sval += "*" + unit;
                            double value = calc->Eval(sval);

                            /* Process the comma-delimited list of particles. */
                            vector<string> particleList;
                            StringUtil::split(particles, ",", particleList);

                            /* No specific particles so make an entry for all particles. */
                            if (particleList.end() == particleList.begin()) {
                                //std::cout << "adding limit with name, particle, value: <" << limitName << "> <" << G4LimitSet::ANY_PARTICLE << "> <" << value << ">" << std::endl;
                                ls->setLimitForParticle(limitName, PhysicsLimitSet::ANY_PARTICLE, value);
                            }
                            /* Insert the limit once for each particle. */
                            else {
                                for (vector<string>::iterator iter = particleList.begin(); iter != particleList.end(); iter++) {
                                    string particle = (*iter);
                                    StringUtil::trim(particle);
                                    //std::cout << "adding limit with name, particle, value: <" << limitName << "> <" << particle << "> <" << value << ">" << std::endl;
                                    ls->setLimitForParticle(limitName, particle, value);
                                }
                            }
                        } else {
                            G4Exception("", "", FatalException, "Failed cast to limit.");
                        }
                    }
                }

                LCDDProcessor::instance()->addLimitSet(ls->getName(), ls);
            } else {
                G4Exception("", "", FatalException, "Failed cast to limitset.");
            }
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(limitsetSubscriber)
