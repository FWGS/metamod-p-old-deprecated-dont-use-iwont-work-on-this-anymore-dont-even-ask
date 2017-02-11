/*
 * Copyright (c) 2017 Alibek Omarov
 *
 *    This file is part of "Metamod All-Mod-Support"-patch for Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */
 
#include <extdll.h>		// always

#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <dlfcn.h>
#include "osdep.h"
#include "osdep_p.h"
#include "physint.h"

static void * gamedll_module_handle = 0;
static void * metamod_module_handle = 0;

//
// Xash3D physics interface
//

typedef void (*LINK_ENTITY_FN)( entvars_t *pev );

//
// attempt to create custom entity when default method is failed
// 0 - attempt to create, -1 - reject to create
//
int DispatchCreateEntity( edict_t *pent, const char *szName )
{
	LINK_ENTITY_FN	SpawnEdict = (LINK_ENTITY_FN)dlsym( gamedll_module_handle , szName );

	if( SpawnEdict )	// found the valid spawn
	{
		SpawnEdict( &pent->v );
		return 0;	// handled
	}

	return -1; // failed
}
//
//
// run custom physics for each entity
// return 0 to use built-in engine physic
//

int DispatchPhysicsEntity( edict_t *pEdict )
{
	return 0;
}


static physics_interface_t gPhysicsInterface =
{
	SV_PHYSICS_INTERFACE_VERSION,
	DispatchCreateEntity,
	DispatchPhysicsEntity,
};

extern "C" int Server_GetPhysicsInterface( int iVersion, server_physics_api_t *pfuncsFromEngine, physics_interface_t *pFunctionTable )
{
	if( !pFunctionTable || !pfuncsFromEngine || iVersion != SV_PHYSICS_INTERFACE_VERSION )
	{
		return FALSE;
	}

	memcpy( pFunctionTable, &gPhysicsInterface, sizeof(physics_interface_t) );

	return TRUE;
}

int DLLINTERNAL init_linkent_replacement(DLHANDLE MetamodHandle, DLHANDLE GameDllHandle)
{
	metamod_module_handle = MetamodHandle;
	gamedll_module_handle = GameDllHandle;

	return 1;
}
