#include "glpch.h"
#include "Cubemap.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/texture/Cubemap_OpenGL.h"

API::Texture::Cubemap::Cubemap(const std::string& dirPath, const std::string& fileFormat)
    :DirPath(dirPath), FileFormat(fileFormat)
{
}

API::Texture::Cubemap* API::Texture::Cubemap::Create(const std::string& dirPath, const std::string& fileFormat, bool calcEnvironmentLight)
{
    switch (Core::DefaultRendererContext::GetAPI())
    {
    case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Texture::Cubemap_OpenGL(dirPath, fileFormat, calcEnvironmentLight);
    }

    API_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

glm::vec3 API::Texture::Cubemap::GetCubemapAverageColor() const
{
    glm::vec3 averageColor(0.0f);
    for (const auto& [face, faceColor] : FaceColors)
    {
        averageColor += faceColor.AverageColor;
    }

    constexpr float conversionFac = 1.f / 6.0f;
    return averageColor * conversionFac;
}

glm::vec3 API::Texture::Cubemap::GetCubemapAverageColorExceptFaces(std::vector<Face>&& face) const
{
    glm::vec3 averageColor(0.0f);
    for (const auto& [currentFace, faceColor] : FaceColors)
    {
        if (std::find(face.begin(), face.end(), currentFace) != face.end())
            continue;
        averageColor += faceColor.AverageColor;
    }

    constexpr float conversionFac = 1.f / 6.0f;
    return averageColor * conversionFac;
}

glm::vec3 API::Texture::Cubemap::GetFaceAverageColor(const Face face) const
{
    return FaceColors.at(face).AverageColor;
}

glm::vec2 API::Texture::Cubemap::GetFaceBrightestPoint(const Face face) const
{
    return FaceColors.at(face).BrightestPoint;
}

float API::Texture::Cubemap::GetFaceBrightness(const Face face) const
{
    return FaceColors.at(face).Brightness;
}

glm::vec3 API::Texture::Cubemap::CalculateAverageColor(const unsigned char* data, const int width, const int height, const int channels, const unsigned int sampleCount, const float lowerCutoffPercent)
{
    const size_t pixelCount = width * height;
    const size_t strideInPixel = std::floor(((float)pixelCount * (1.f - lowerCutoffPercent)) / (float)sampleCount);
    const size_t strideInBytes = strideInPixel * channels;
    glm::vec3 averageColor(0.0f);

    constexpr float conversionFac = 1.f / 255.0f;

    for (int i = 0; i < sampleCount; i++)
    {
        const size_t offset = i * strideInBytes;
        const glm::vec3 color(
            static_cast<float>(data[offset]) * conversionFac,
            static_cast<float>(data[offset + 1]) * conversionFac,
            static_cast<float>(data[offset + 2]) * conversionFac
        );

        averageColor += color;
    }

    return averageColor / static_cast<float>(sampleCount);
}

glm::vec2 API::Texture::Cubemap::FindBrightestPoint(const unsigned char* data, const int width, const int height, const int channels, const unsigned int sampleCount, const float lowerCutoffPercent)
{
    const size_t pixelCount = width * height;
    const size_t strideInPixel = std::floor(((float)pixelCount * (1.f - lowerCutoffPercent)) / (float)sampleCount);
    const size_t strideInBytes = strideInPixel * channels;

    const float normFacX = 1.f / (float)width;
    const float normFacY = 1.f / (float)height;

    glm::vec2 brightestPointCoord(0.0f);
    float maxBrightness = -1.0f;

    for (int i = 0; i < sampleCount; i++)
    {
        const size_t offset = i * strideInBytes;
        const float brightness = CalculateBrightness(
            static_cast<float>(data[offset]),
            static_cast<float>(data[offset + 1]),
            static_cast<float>(data[offset + 2])
        );

        if (brightness > maxBrightness)
        {
            maxBrightness = brightness;
            const int offsetInPixel = i * (int)strideInPixel;
            brightestPointCoord.x = (float)(offsetInPixel % width) * normFacX;
            brightestPointCoord.y = (float)(offsetInPixel / width) * normFacY;
        }
    }

    return brightestPointCoord;
}

float API::Texture::Cubemap::CalculateBrightness(const float r, const float g, const float b)
{
    return r +g +b;
}

API::Texture::Cubemap::Face API::Texture::Cubemap::StringToFace(const std::string& faceStr)
{
    static const std::map<std::string, Face> faceMap = {
        {"px", Face::PX}, {"nx", Face::NX},
        {"py", Face::PY}, {"ny", Face::NY},
        {"pz", Face::PZ}, {"nz", Face::NZ}
    };

    auto it = faceMap.find(faceStr);
    if (it != faceMap.end())
        return it->second;

    throw std::invalid_argument("Invalid cubemap face string: " + faceStr);
}
