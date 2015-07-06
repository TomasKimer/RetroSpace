// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ControlsSettings.cpp
  *  @brief  Nacitani a ukladani ovladani hracu.
  */

#include "ControlsSettings.h"

namespace RetroSpace
{

ControlsSettings::ControlsSettings(void)
{
    m_settingsName = "Controls"; 

    // player 1
    m_defaultValues.ctrls[0].ctrl = Controls::CTRL_MOUSE;
    
    m_defaultValues.ctrls[0].mouse.accel = BC_RIGHT;
    m_defaultValues.ctrls[0].mouse.shoot = BC_LEFT;
    m_defaultValues.ctrls[0].mouse.transfer = BC_MIDDLE;

    m_defaultValues.ctrls[0].keyb.accel = KC_W;
    m_defaultValues.ctrls[0].keyb.shoot = KC_LSHIFT;
    m_defaultValues.ctrls[0].keyb.turnLeft = KC_A;
    m_defaultValues.ctrls[0].keyb.turnRight = KC_D;
    m_defaultValues.ctrls[0].keyb.transfer = KC_Q;


    // player 2
    m_defaultValues.ctrls[1].ctrl = Controls::CTRL_KEYBOARD;

    m_defaultValues.ctrls[1].mouse.accel = BC_RIGHT;
    m_defaultValues.ctrls[1].mouse.shoot = BC_LEFT;
    m_defaultValues.ctrls[1].mouse.transfer = BC_MIDDLE;

    m_defaultValues.ctrls[1].keyb.accel = KC_UP;
    m_defaultValues.ctrls[1].keyb.shoot = KC_RETURN;
    m_defaultValues.ctrls[1].keyb.turnLeft = KC_LEFT;
    m_defaultValues.ctrls[1].keyb.turnRight = KC_RIGHT;
    m_defaultValues.ctrls[1].keyb.transfer = KC_RSHIFT;
}


ControlsSettings::~ControlsSettings(void)
{
}

void ControlsSettings::LoadDefaultValues()
{
    m_values = m_defaultValues;
}

void ControlsSettings::LoadValues(const KeyValueDeserializer & kvd)
{
    int tmp;

    kvd.Load("Player1Controller", tmp, static_cast<int>(m_defaultValues.ctrls[0].ctrl));
    m_values.ctrls[0].ctrl = static_cast<Controls::Controller>(tmp);

    LoadPlayerControls(0, kvd);

    // player 2
    kvd.Load("Player2Controller", tmp, static_cast<int>(m_defaultValues.ctrls[0].ctrl));
    m_values.ctrls[1].ctrl = static_cast<Controls::Controller>(tmp);

    if (m_values.ctrls[0].ctrl == Controls::CTRL_MOUSE && m_values.ctrls[1].ctrl == Controls::CTRL_MOUSE)
    {
        Log::Msg(m_settingsName + "Settings: Both players are mouse-controlled, forcing second to keyboard");
        m_values.ctrls[1].ctrl = Controls::CTRL_KEYBOARD;
    }

    LoadPlayerControls(1, kvd);
}

void ControlsSettings::SaveValues(KeyValueSerializer & kvs)
{
    // player 1
    kvs.Save("Player1Controller", static_cast<int>(m_values.ctrls[0].ctrl));

    kvs.SaveBlankLine();

    SavePlayerControls(0, kvs);

    kvs.SaveBlankLine();
    kvs.SaveBlankLine();

    // player 2
    kvs.Save("Player2Controller", static_cast<int>(m_values.ctrls[1].ctrl));

    kvs.SaveBlankLine();

    SavePlayerControls(1, kvs);
}

void ControlsSettings::LoadPlayerControls(int num, const KeyValueDeserializer & kvd)
{
    std::stringstream ss;
    ss << num + 1;

    kvd.Load("Player" + ss.str() + "MouseAccel"   , m_values.ctrls[num].mouse.accel   , m_defaultValues.ctrls[num].mouse.accel   );
    kvd.Load("Player" + ss.str() + "MouseShoot"   , m_values.ctrls[num].mouse.shoot   , m_defaultValues.ctrls[num].mouse.shoot   );
    kvd.Load("Player" + ss.str() + "MouseTransfer", m_values.ctrls[num].mouse.transfer, m_defaultValues.ctrls[num].mouse.transfer);
                    
    kvd.Load("Player" + ss.str() + "KeybAccel"    , m_values.ctrls[num].keyb.accel    , m_defaultValues.ctrls[num].keyb.accel    );
    kvd.Load("Player" + ss.str() + "KeybShoot"    , m_values.ctrls[num].keyb.shoot    , m_defaultValues.ctrls[num].keyb.shoot    );
    kvd.Load("Player" + ss.str() + "KeybTurnLeft" , m_values.ctrls[num].keyb.turnLeft , m_defaultValues.ctrls[num].keyb.turnLeft );
    kvd.Load("Player" + ss.str() + "KeybTurnRight", m_values.ctrls[num].keyb.turnRight, m_defaultValues.ctrls[num].keyb.turnRight);    
    kvd.Load("Player" + ss.str() + "KeybTransfer" , m_values.ctrls[num].keyb.transfer , m_defaultValues.ctrls[num].keyb.transfer );
}

void ControlsSettings::SavePlayerControls(int num, KeyValueSerializer & kvs)
{
    std::stringstream ss;
    ss << num + 1;

    kvs.Save("Player" + ss.str() + "MouseAccel"   , m_values.ctrls[num].mouse.accel   );
    kvs.Save("Player" + ss.str() + "MouseShoot"   , m_values.ctrls[num].mouse.shoot   );
    kvs.Save("Player" + ss.str() + "MouseTransfer", m_values.ctrls[num].mouse.transfer);

    kvs.SaveBlankLine();

    kvs.Save("Player" + ss.str() + "KeybAccel"    , m_values.ctrls[num].keyb.accel    );
    kvs.Save("Player" + ss.str() + "KeybShoot"    , m_values.ctrls[num].keyb.shoot    );
    kvs.Save("Player" + ss.str() + "KeybTurnLeft" , m_values.ctrls[num].keyb.turnLeft );
    kvs.Save("Player" + ss.str() + "KeybTurnRight", m_values.ctrls[num].keyb.turnRight);    
    kvs.Save("Player" + ss.str() + "KeybTransfer" , m_values.ctrls[num].keyb.transfer );
}

}