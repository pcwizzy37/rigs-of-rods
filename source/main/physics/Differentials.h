/*
    This source file is part of Rigs of Rods
    Copyright 2005-2012 Pierre-Michel Ricordel
    Copyright 2007-2012 Thomas Fischer

    For more information, see http://www.rigsofrods.org/

    Rigs of Rods is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3, as
    published by the Free Software Foundation.

    Rigs of Rods is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <OgreUTFString.h>
#include <vector>

struct DifferentialData
{
    float speed[2];
    float delta_rotation; // sign is first relative to the second
    float out_torque[2];
    float in_torque;
    float dt;
};

enum DiffType
{
    SPLIT_DIFF = 0,
    OPEN_DIFF,
    LOCKED_DIFF
};

class Axle
{
public:
    Axle();

    int       ax_wheel_1; //!< array location of wheel 1
    int       ax_wheel_2; //!< array location of wheel 2
    float     ax_delta_rotation; //!< difference of rotational position between two axles... a kludge at best

    void             AddDifferentialType(DiffType diff);
    void             ToggleDifferentialMode();
    void             CalcAxleTorque(DifferentialData& diff_data );
    Ogre::UTFString  GetDifferentialTypeName();
    
    static void      CalcSeparateDiff(DifferentialData& diff_data);  //!< a differential that always splits the torque evenly, this is the original method
    static void      CalcOpenDiff(DifferentialData& diff_data );     //!< more power goes to the faster spining wheel
    static void      CalcLockedDiff(DifferentialData& diff_data );   //!< ensures both wheels rotate at the the same speed

private:

    float     m_torsion_rate; //! torsion spring rate binding wheels together.
    float     m_torsion_damp;    
    int       m_which_diff;
    std::vector<DiffType> m_available_diffs;
};

