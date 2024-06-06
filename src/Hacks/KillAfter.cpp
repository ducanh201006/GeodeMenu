#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../Client/Client.h"

Module* killAt = nullptr;
InputModule* pc = nullptr;
InputModule* tm = nullptr;

class $modify (PlayLayer)
{
    struct Fields {
        CCLabelBMFont* time;
    };

    virtual void postUpdate(float p0)
    {
        PlayLayer::postUpdate(p0);

        if (!killAt)
        {
            killAt = Client::GetModule("kill-after");
            pc = as<InputModule*>(killAt->options[0]);
            tm = as<InputModule*>(killAt->options[1]);
        }

        if (killAt->enabled)
        {
            auto v = (m_player1->m_isPlatformer ? tm : pc)->getFloatValue();

            if (m_player1->m_isPlatformer)
            {
                if (!m_fields->time)
                    m_fields->time = getChildOfType<CCLabelBMFont>(this, 1);

                auto x = utils::numFromString<float>(m_fields->time->getString());

                if (x.isOk() && x.value() > v)
                {
                    this->PlayLayer::destroyPlayer(m_player1, nullptr);
                }
            }
            else
            {
                if (this->getCurrentPercent() > v)
                {
                    this->PlayLayer::destroyPlayer(m_player1, nullptr);
                }
            }
        }
    }
};