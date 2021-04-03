/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CDummy.cpp
 *  PURPOSE:     Dummy entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

CDummy::CDummy(CGroups* pGroups, CElement* pParent) : CElement(pParent)
{
    // Init
    m_iType = CElement::DUMMY;
    SetTypeName("dummy");
    m_pGroups = pGroups;

    // Add us to parent's list
    if (pGroups)
    {
        pGroups->AddToList(this);
    }
}

CDummy::~CDummy()
{
    // Unlink from manager
    Unlink();
}

CElement* CDummy::Clone(bool* bAddEntity, CResource* pResource)
{
    CElement* pNewElement = new CDummy(g_pGame->GetGroups(), GetParentEntity());
    pNewElement->SetName(GetName());
    pNewElement->SetTypeName(GetTypeName());
    return pNewElement;
}

void CDummy::Unlink()
{
    // Remove us from groupmanager's list
    if (m_pGroups)
    {
        m_pGroups->RemoveFromList(this);
    }
}

void CDummy::GetRotationDegrees(CVector& vecRotation)
{
    GetRotationRadians(vecRotation);
    ConvertRadiansToDegrees(vecRotation);
}

void CDummy::SetRotationDegrees(const CVector& vecRotation)
{
    CVector vecTemp = vecRotation;
    ConvertDegreesToRadians(vecTemp);
    SetRotationRadians(vecTemp);
}

void CDummy::GetMatrix(CMatrix& matrix)
{
    matrix = CMatrix(m_vecPosition, m_vecRotation);
}

void CDummy::SetMatrix(const CMatrix& matrix)
{
    m_vecRotation = matrix.GetRotation();
    m_vecPosition = matrix.GetPosition();
}

bool CDummy::ReadSpecialData(const int iLine)
{
    // Grab the position data
    GetCustomDataFloat("posX", m_vecPosition.fX, true);
    GetCustomDataFloat("posY", m_vecPosition.fY, true);
    GetCustomDataFloat("posZ", m_vecPosition.fZ, true);

    // Grab the rotation data
    GetCustomDataFloat("rotX", m_vecRotation.fX, true);
    GetCustomDataFloat("rotY", m_vecRotation.fY, true);
    GetCustomDataFloat("rotZ", m_vecRotation.fZ, true);
    return true;
}
