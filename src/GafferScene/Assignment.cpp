//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2012, John Haddon. All rights reserved.
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

#include "GafferScene/Assignment.h"
#include "GafferScene/Shader.h"

using namespace IECore;
using namespace Gaffer;
using namespace GafferScene;

IE_CORE_DEFINERUNTIMETYPED( Assignment );

Assignment::Assignment( const std::string &name )
	:	SceneElementProcessor( name )
{
	addChild( new Plug( "shader" ) );
}

Assignment::~Assignment()
{
}

Gaffer::Plug *Assignment::shaderPlug()
{
	return getChild<Plug>( "shader" );
}

const Gaffer::Plug *Assignment::shaderPlug() const
{
	return getChild<Plug>( "shader" );
}

bool Assignment::acceptsInput( const Gaffer::Plug *plug, const Gaffer::Plug *inputPlug ) const
{
	if( plug == shaderPlug() )
	{
		return inputPlug->ancestor<Shader>();
	}
	return true;
}

IECore::ObjectVectorPtr Assignment::processState( const ScenePath &path, const Gaffer::Context *context, IECore::ConstObjectVectorPtr inputState ) const
{
	ObjectVectorPtr result = inputState ? inputState->copy() : ObjectVectorPtr( new ObjectVector );
	
	const Plug *in = shaderPlug()->getInput<Plug>();
	const Shader *shader = in ? in->ancestor<Shader>() : 0;
	if( shader )
	{
		IECore::ObjectVectorPtr state = shader->state();
		for( IECore::ObjectVector::MemberContainer::const_iterator it = state->members().begin(), eIt = state->members().end(); it != eIt; it++ )
		{
			result->members().push_back( *it );
		}
	}
	
	return result;
}
