//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2015, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "Gaffer/ArrayPlug.h"
#include "Gaffer/SubGraph.h"
#include "Gaffer/Dot.h"

#include "GafferScene/FilterProcessor.h"

using namespace IECore;
using namespace Gaffer;
using namespace GafferScene;

IE_CORE_DEFINERUNTIMETYPED( FilterProcessor );

size_t FilterProcessor::g_firstPlugIndex = 0;

FilterProcessor::FilterProcessor( const std::string &name )
	:	Filter( name )
{
	storeIndexOfNextChild( g_firstPlugIndex );
	addChild( outPlug()->createCounterpart( "in", Plug::In ) );
}

FilterProcessor::FilterProcessor( const std::string &name, size_t minInputs, size_t maxInputs )
	:	Filter( name )
{
	storeIndexOfNextChild( g_firstPlugIndex );
	addChild(
		new ArrayPlug( "in", Gaffer::Plug::In, outPlug()->createCounterpart( "in0", Plug::In ), minInputs, maxInputs )
	);
}

FilterProcessor::~FilterProcessor()
{
}

Gaffer::IntPlug *FilterProcessor::inPlug()
{
	GraphComponent *p = getChild<GraphComponent>( g_firstPlugIndex );
	if( IntPlug *s = IECore::runTimeCast<IntPlug>( p ) )
	{
		return s;
	}
	else
	{
		return static_cast<ArrayPlug *>( p )->getChild<IntPlug>( 0 );
	}
}

const Gaffer::IntPlug *FilterProcessor::inPlug() const
{
	const GraphComponent *p = getChild<GraphComponent>( g_firstPlugIndex );
	if( const IntPlug *s = IECore::runTimeCast<const IntPlug>( p ) )
	{
		return s;
	}
	else
	{
		return static_cast<const ArrayPlug *>( p )->getChild<IntPlug>( 0 );
	}
}

Gaffer::ArrayPlug *FilterProcessor::inPlugs()
{
	return getChild<Gaffer::ArrayPlug>( g_firstPlugIndex );
}

const Gaffer::ArrayPlug *FilterProcessor::inPlugs() const
{
	return getChild<Gaffer::ArrayPlug>( g_firstPlugIndex );
}

bool FilterProcessor::sceneAffectsMatch( const ScenePlug *scene, const Gaffer::ValuePlug *child ) const
{
	for( InputIntPlugIterator it( inPlugs() ); it != it.end(); ++it )
	{
		const Filter *filter = IECore::runTimeCast<const Filter>( (*it)->source<Plug>()->node() );
		if( filter && filter != this && filter->sceneAffectsMatch( scene, child ) )
		{
			return true;
		}
	}
	return false;
}

bool FilterProcessor::acceptsInput( const Gaffer::Plug *plug, const Gaffer::Plug *inputPlug ) const
{
	if( !Filter::acceptsInput( plug, inputPlug ) )
	{
		return false;
	}

	if( !inputPlug )
	{
		return true;
	}

	if( plug->parent<ArrayPlug>() == inPlugs() || plug == inPlug() )
	{
		const Node *n = inputPlug->source<Plug>()->node();
		return runTimeCast<const Filter>( n ) || runTimeCast<const SubGraph>( n ) || runTimeCast<const Dot>( n );
	}

	return true;
}
