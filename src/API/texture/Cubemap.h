#pragma once
#include <string>

#include "API/core/Shader.h"

namespace API::Texture
{
    class Cubemap
    {
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

        static Cubemap* Create(const std::string& dirPath, const std::string& fileFormat);

    protected:
        const std::string DirPath;
        const std::string FileFormat;
        Core::Shader* Shader = nullptr;
    };
}
