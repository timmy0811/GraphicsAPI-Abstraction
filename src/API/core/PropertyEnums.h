#pragma once

// Default values for OpenGL, consider the version in usage
// Implement a mapper function for other APIs

namespace API::Core {
	enum class BlendFunction {
		Zero = 0,
		One = 1,
		SrcColor = 0x0300,
		OneMinusSrcColor = 0x0301,
		DstColor = 0x0306,
		OneMinusDstColor = 0x0307,
		SrcAlpha = 0x0302,
		OneMinusSrcAlpha = 0x0303,
		DstAlpha = 0x0304,
		OneMinusDstAlpha = 0x0305,
		ConstantColor = 0x8001,
		OneMinusConstantColor = 0x8002,
		ConstantAlpha = 0x8003,
		OneMinusConstantAlpha = 0x8004,
		SrcAlphaSaturate = 0x0308,
	};

	enum class Face {
		None = 0x0000,
		Front = 0x0404,
		Back = 0x0405,
		FrontAndBack = 0x0408
	};

	enum class DepthFunction {
		Never = 0x0200,
		Less = 0x0201,
		Equal = 0x0202,
		LEqual = 0x0203,
		Greater = 0x0204,
		NotEqual = 0x0205,
		GEqual = 0x0206,
		Always = 0x0207
	};

	enum class StencilFunction {
		Never = 0x0200,
		Less = 0x0201,
		Equal = 0x0202,
		LEqual = 0x0203,
		Greater = 0x0204,
		NotEqual = 0x0205,
		GEqual = 0x0206,
		Always = 0x0207
	};

	enum class StencilOperation {
		Keep = 0x1E00,
		Zero = 0,
		Replace = 0x1E01,
		Incr = 0x1E02,
		IncrWrap = 0x8507,
		Decr = 0x1E03,
		DecrWrap = 0x8508,
		Invert = 0x150A
	};

	enum class BufferUsage {
		Static = 0x88E4,
		Dynamic = 0x88E8,
		Stream = 0x88E0
	};

	enum class FrontFace {
		Clockwise = 0x0900,
		CounterClockwise = 0x0901
	};

	enum class AntiAliasingMethod {
		Multisample = 0x809D,
		SampleAlphaToCoverage = 0x809E,
		SampleAlphaToOne = 0x809F,
		SampleCoverage = 0x80A0,
		None = 0
	};
}