#pragma once

#include "API/core/PropertyEnums.h"
#include <GL/glew.h>

#include "Debug/Log.h"

namespace OpenGL::Core
{
	inline GLenum GLBlendFunction(const API::Core::BlendFunction function)
	{
		switch (function)
		{
		case API::Core::BlendFunction::Zero: return GL_ZERO;
		case API::Core::BlendFunction::One: return GL_ONE;
		case API::Core::BlendFunction::SrcColor: return GL_SRC_COLOR;
		case API::Core::BlendFunction::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
		case API::Core::BlendFunction::DstColor: return GL_DST_COLOR;
		case API::Core::BlendFunction::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
		case API::Core::BlendFunction::SrcAlpha: return GL_SRC_ALPHA;
		case API::Core::BlendFunction::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
		case API::Core::BlendFunction::DstAlpha: return GL_DST_ALPHA;
		case API::Core::BlendFunction::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
		case API::Core::BlendFunction::ConstantColor: return GL_CONSTANT_COLOR;
		case API::Core::BlendFunction::OneMinusConstantColor: return GL_ONE_MINUS_CONSTANT_COLOR;
		case API::Core::BlendFunction::ConstantAlpha: return GL_CONSTANT_ALPHA;
		case API::Core::BlendFunction::OneMinusConstantAlpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
		default:
			LOG_GL_WARN("Blend function not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLFaceCull(const API::Core::Face cull)
	{
		switch (cull)
		{
		case API::Core::Face::Front: return GL_FRONT;
		case API::Core::Face::Back: return GL_BACK;
		case API::Core::Face::FrontAndBack: return GL_FRONT_AND_BACK;
		default:
			LOG_GL_WARN("Face cull not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLDepthFunction(const API::Core::DepthFunction function)
	{
		switch (function)
		{
		case API::Core::DepthFunction::Never: return GL_NEVER;
		case API::Core::DepthFunction::Less: return GL_LESS;
		case API::Core::DepthFunction::Equal: return GL_EQUAL;
		case API::Core::DepthFunction::LEqual: return GL_LEQUAL;
		case API::Core::DepthFunction::Greater: return GL_GREATER;
		case API::Core::DepthFunction::NotEqual: return GL_NOTEQUAL;
		case API::Core::DepthFunction::GEqual: return GL_GEQUAL;
		case API::Core::DepthFunction::Always: return GL_ALWAYS;
		default:
			LOG_GL_WARN("Depth function not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLStencilFunction(const API::Core::StencilFunction function)
	{
		switch (function)
		{
		case API::Core::StencilFunction::Never: return GL_NEVER;
		case API::Core::StencilFunction::Less: return GL_LESS;
		case API::Core::StencilFunction::Equal: return GL_EQUAL;
		case API::Core::StencilFunction::LEqual: return GL_LEQUAL;
		case API::Core::StencilFunction::Greater: return GL_GREATER;
		case API::Core::StencilFunction::NotEqual: return GL_NOTEQUAL;
		case API::Core::StencilFunction::GEqual: return GL_GEQUAL;
		case API::Core::StencilFunction::Always: return GL_ALWAYS;
		default:
			LOG_GL_WARN("Stencil function not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLStencilOperation(const API::Core::StencilOperation operation)
	{
		switch (operation)
		{
		case API::Core::StencilOperation::Keep: return GL_KEEP;
		case API::Core::StencilOperation::Zero: return GL_ZERO;
		case API::Core::StencilOperation::Replace: return GL_REPLACE;
		case API::Core::StencilOperation::Incr: return GL_INCR;
		case API::Core::StencilOperation::IncrWrap: return GL_INCR_WRAP;
		case API::Core::StencilOperation::Decr: return GL_DECR;
		case API::Core::StencilOperation::DecrWrap: return GL_DECR_WRAP;
		default:
			LOG_GL_WARN("Stencil operation not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLBufferUsage(const API::Core::BufferUsage usage)
	{
		switch (usage)
		{
		case API::Core::BufferUsage::Static: return GL_STATIC_DRAW;
		case API::Core::BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
		case API::Core::BufferUsage::Stream: return GL_STREAM_DRAW;
		default:
			LOG_GL_WARN("Buffer usage not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLFrontFace(const API::Core::FrontFace face)
	{
		switch (face)
		{
		case API::Core::FrontFace::Clockwise: return GL_CW;
		case API::Core::FrontFace::CounterClockwise: return GL_CCW;
		default:
			LOG_GL_WARN("Front face not supported");
			return GL_INVALID_ENUM;
		}
	}

	inline GLenum GLAntiAliasingMethod(const API::Core::AntiAliasingMethod method)
	{
		switch (method)
		{
		case API::Core::AntiAliasingMethod::Multisample: return GL_MULTISAMPLE;
		case API::Core::AntiAliasingMethod::SampleAlphaToCoverage: return GL_SAMPLE_ALPHA_TO_COVERAGE;
		case API::Core::AntiAliasingMethod::SampleAlphaToOne: return GL_SAMPLE_ALPHA_TO_ONE;
		case API::Core::AntiAliasingMethod::SampleCoverage: return GL_SAMPLE_COVERAGE;
		case API::Core::AntiAliasingMethod::None: return GL_NONE;
		default:
			LOG_GL_WARN("Anti aliasing method not supported");
			return GL_INVALID_ENUM;
		}
	}
}
