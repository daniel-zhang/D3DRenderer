#ifndef _MESH_DATA_H
#define _MESH_DATA_H

#include "VertexLayout.h"

Vertex cube[] = 
{
	//pos------------------------------color(RGBA)-------------------------normal-----------------------texcoord(optional for now)------
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },

	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
};

WORD cubeIndex[] = 
{
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

#endif