#pragma once
#include <map>
#include <string>

#include "API/core/Shader.h"

namespace API::Texture
{
    class Cubemap
    {
    public:
        enum Face {PX, NX, PY, NY, PZ, NZ, NONE};

        struct FaceColorResult
        {
            glm::vec3 AverageColor{0.0f, 0.0f, 0.0f};
            glm::vec2 BrightestPoint{0.0f, 0.0f};
            float Brightness = 0.0f;
        };

    public:
        Cubemap(const std::string& dirPath, const std::string& fileFormat);
        virtual ~Cubemap() = default;

        virtual void Unbind() = 0;
        virtual unsigned int Bind(unsigned int slot) = 0;

        virtual void Render() = 0;

        inline void SetCacheShader(Core::Shader* shader) { Shader = shader; }
        inline void SetViewProjectionMatrix(const glm::mat4& view, const glm::mat4& projection) const
        {
            if (Shader)
            {
                Shader->Bind();
                Shader->SetUniformMat4f("u_Projection", projection);
                Shader->SetUniformMat4f("u_View", glm::mat4(glm::mat3(view)));
            }
        }

        [[nodiscard]] inline virtual Core::Shader* GetShader() const { return Shader; }
        [[nodiscard]] inline virtual const std::string& GetPath() const {return DirPath;};
        [[nodiscard]] inline virtual const std::string& GetFileFormat() const {return FileFormat;};

        [[nodiscard]] virtual glm::vec3 GetCubemapAverageColor() const;
        [[nodiscard]] virtual glm::vec3 GetCubemapAverageColorExceptFaces(std::vector<Face>&& face) const;
        [[nodiscard]] virtual glm::vec3 GetFaceAverageColor(Face face) const;
        [[nodiscard]] virtual glm::vec2 GetFaceBrightestPoint(Face face) const;
        [[nodiscard]] virtual float GetFaceBrightness(Face face) const;

        inline Face GetBrightestFace() const { return BrightestFace; }

        [[nodiscard]] inline int GetWidth() const { return Width; }
        [[nodiscard]] inline int GetHeight() const { return Height; }
        [[nodiscard]] inline int GetChannels() const { return Channels; }

        static glm::vec3 CalculateAverageColor(const unsigned char* data, int width, int height, int channels, unsigned int sampleCount = 128, float lowerCutoffPercent = 0.f);
        static glm::vec2 FindBrightestPoint(const unsigned char* data, int width, int height, int channels, unsigned int sampleCount = 128, float lowerCutoffPercent = 0.f);

        static inline float CalculateBrightness(float r, float g, float b);

        static Face StringToFace(const std::string& faceStr);

        static Cubemap* Create(const std::string& dirPath, const std::string& fileFormat, bool calcEnvironmentLight = true);

    protected:
        const std::string DirPath;
        const std::string FileFormat;
        Core::Shader* Shader = nullptr;

        Face BrightestFace = Face::NONE;
        std::unordered_map<Face, FaceColorResult> FaceColors;

        int Width = 0;
        int Height = 0;
        int Channels = 0;
    };
}

// namespace std {
//     template <>
//     struct hash<API::Texture::Cubemap::Face> {
//         std::size_t operator()(const API::Texture::Cubemap::Face& f) const noexcept {
//             return std::hash<int>()(static_cast<int>(f));
//         }
//     };
// }