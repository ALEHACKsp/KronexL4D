//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef EHANDLE_H
#define EHANDLE_H
#ifdef _WIN32
#pragma once
#endif

#if defined( _DEBUG ) && defined( GAME_DLL )
#include "tier0/dbg.h"
#include "cbase.h"
#endif


#include "const.h"
#include "basehandle.h"
#include "entitylist_base.h"


class IHandleEntity;


// -------------------------------------------------------------------------------------------------- //
// Game-code CBaseHandle implementation.
// -------------------------------------------------------------------------------------------------- //

inline IHandleEntity* CBaseHandle::Get() const
{
	extern CBaseEntityList *g_pEntityList;
	return g_pEntityList->LookupEntity( *this );
}


// -------------------------------------------------------------------------------------------------- //
// CHandle.
// -------------------------------------------------------------------------------------------------- //
template< class T >
class CHandleV : public CBaseHandle
{
public:

			CHandleV();
			CHandleV( int iEntry, int iSerialNumber );
			CHandleV( const CBaseHandle &handle );
			CHandleV( T *pVal );

	// The index should have come from a call to ToInt(). If it hasn't, you're in trouble.
	static CHandleV<T> FromIndex( int index );

	T*		Get() const;
	void	Set( const T* pVal );

			operator T*();
			operator T*() const;

	bool	operator !() const;
	bool	operator==( T *val ) const;
	bool	operator!=( T *val ) const;
	const CBaseHandle& operator=( const T *val );

	T*		operator->() const;
};

typedef CHandleV<CBaseEntity> EHANDLE;

// ----------------------------------------------------------------------- //
// Inlines.
// ----------------------------------------------------------------------- //

template<class T>
CHandleV<T>::CHandleV()
{
}


template<class T>
CHandleV<T>::CHandleV( int iEntry, int iSerialNumber )
{
	Init( iEntry, iSerialNumber );
}


template<class T>
CHandleV<T>::CHandleV( const CBaseHandle &handle )
	: CBaseHandle( handle )
{
}


template<class T>
CHandleV<T>::CHandleV( T *pObj )
{
	Term();
	Set( pObj );
}


template<class T>
inline CHandleV<T> CHandleV<T>::FromIndex( int index )
{
	CHandleV<T> ret;
	ret.m_Index = index;
	return ret;
}


template<class T>
inline T* CHandleV<T>::Get() const
{
	return (T*)CBaseHandle::Get();
}


template<class T>
inline CHandleV<T>::operator T *() 
{ 
	return Get( ); 
}

template<class T>
inline CHandleV<T>::operator T *() const
{ 
	return Get( ); 
}


template<class T>
inline bool CHandleV<T>::operator !() const
{
	return !Get();
}

template<class T>
inline bool CHandleV<T>::operator==( T *val ) const
{
	return Get() == val;
}

template<class T>
inline bool CHandleV<T>::operator!=( T *val ) const
{
	return Get() != val;
}

template<class T>
void CHandleV<T>::Set( const T* pVal )
{
	CBaseHandle::Set( reinterpret_cast<const IHandleEntity*>(pVal) );
}

template<class T>
inline const CBaseHandle& CHandleV<T>::operator=( const T *val )
{
	Set( val );
	return *this;
}

template<class T>
T* CHandleV<T>::operator -> () const
{
	return Get();
}


#endif // EHANDLE_H
