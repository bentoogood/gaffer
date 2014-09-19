//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2013, Image Engine Design Inc. All rights reserved.
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

#ifndef GAFFERSCENE_PARENTCONSTRAINT_H
#define GAFFERSCENE_PARENTCONSTRAINT_H

#include "Gaffer/TransformPlug.h"

#include "GafferScene/Constraint.h"

namespace GafferScene
{

class ParentConstraint : public Constraint
{

	public :

		ParentConstraint( const std::string &name=defaultName<ParentConstraint>() );
		virtual ~ParentConstraint();

		IE_CORE_DECLARERUNTIMETYPEDEXTENSION( GafferScene::ParentConstraint, ParentConstraintTypeId, Constraint );

		Gaffer::TransformPlug *relativeTransformPlug();
		const Gaffer::TransformPlug *relativeTransformPlug() const;

	protected :

		virtual bool affectsConstraint( const Gaffer::Plug *input ) const;
		virtual void hashConstraint( const Gaffer::Context *context, IECore::MurmurHash &h ) const;
		virtual Imath::M44f computeConstraint( const Imath::M44f &fullTargetTransform, const Imath::M44f &fullInputTransform ) const;

	private :

		static size_t g_firstPlugIndex;

};

IE_CORE_DECLAREPTR( ParentConstraint )

} // namespace GafferScene

#endif // GAFFERSCENE_PARENTCONSTRAINT_H