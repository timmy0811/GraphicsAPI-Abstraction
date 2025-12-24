#include "glpch.h"
#include "CascadedShadowMap_OpenGL.h"

#include "Debug/Debug.h"

#include <GL/glew.h>
#include <array>
#include <iostream>
#include <sstream>

namespace OpenGL::Advanced
{
    static inline void LabelObject(const GLenum identifier, const GLuint name, const std::string& label)
    {
        if (GLEW_KHR_debug && glObjectLabel)
        {
            glObjectLabel(identifier, name, (GLsizei)label.size(), label.c_str());
        }
#ifdef GL_EXT_debug_label
        else if (GLEW_EXT_debug_label && glLabelObjectEXT)
        {
            glLabelObjectEXT(identifier, name, (GLsizei)label.size(), label.c_str());
        }
#endif
    }

    static void SetupDepthTexture(const GLuint texId, const int width, const int height)
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, texId));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

        // Default to nearest; apps can sample with PCF in shader
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        constexpr float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

        // If hardware compare sampling is desired, caller can set compare mode in its sampler
        // GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
        // GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    }

    CascadedShadowMap_OpenGL::~CascadedShadowMap_OpenGL()
    {
        for (int i = 0; i < CascadeCount; ++i)
            DestroyCascade(i);
    }

    bool CascadedShadowMap_OpenGL::Init(const std::array<glm::ivec2, CascadeCount>& sizes)
    {
        m_Sizes = sizes;
        for (int i = 0; i < CascadeCount; ++i)
        {
            if (!CreateCascade(i, sizes[i]))
                return false;
        }

        return true;
    }

    bool CascadedShadowMap_OpenGL::CreateCascade(const int i, const glm::ivec2& size)
    {
        // Clean previous
        DestroyCascade(i);

        GLCall(glGenFramebuffers(1, &m_Cascades[i].fbo));
        GLCall(glGenTextures(1, &m_Cascades[i].depthTex));
        SetupDepthTexture(m_Cascades[i].depthTex, size.x, size.y);
        // Unbind texture to avoid accidental state leakage
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));

        {
            std::stringstream ssFbo; ssFbo << "CSM Cascade " << i << " FBO";
            LabelObject(GL_FRAMEBUFFER, m_Cascades[i].fbo, ssFbo.str());
            std::stringstream ssTex; ssTex << "CSM Cascade " << i << " Depth";
            LabelObject(GL_TEXTURE, m_Cascades[i].depthTex, ssTex.str());
        }

        GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Cascades[i].fbo));
        GLCall(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Cascades[i].depthTex, 0));
        GLCall(glDrawBuffer(GL_NONE));
        GLCall(glReadBuffer(GL_NONE));

        const GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_GL_ERROR("Error while creating CSM cascade FBO");
            GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
            return false;
        }

        GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

        return true;
    }

    void CascadedShadowMap_OpenGL::DestroyCascade(const int i)
    {
        if (m_Cascades[i].depthTex)
        {
            GLCall(glDeleteTextures(1, &m_Cascades[i].depthTex));
            m_Cascades[i].depthTex = 0;
        }
        if (m_Cascades[i].fbo)
        {
            GLCall(glDeleteFramebuffers(1, &m_Cascades[i].fbo));
            m_Cascades[i].fbo = 0;
        }
        m_Cascades[i].boundSlot = -1;
    }

    void CascadedShadowMap_OpenGL::BindAndClear(const int cascadeIndex)
    {
        if (cascadeIndex < 0 || cascadeIndex >= CascadeCount) return;
        GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Cascades[cascadeIndex].fbo));
        GLCall(glViewport(0, 0, m_Sizes[cascadeIndex].x, m_Sizes[cascadeIndex].y));
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    }

    unsigned int CascadedShadowMap_OpenGL::BindDepthTexture(const int cascadeIndex, unsigned int slot)
    {
        if (cascadeIndex < 0 || cascadeIndex >= CascadeCount) return 0u;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_Cascades[cascadeIndex].depthTex));
        m_Cascades[cascadeIndex].boundSlot = static_cast<int>(slot);

        return slot;
    }

    void CascadedShadowMap_OpenGL::UnbindDepthTexture(const int cascadeIndex)
    {
        if (cascadeIndex < 0 || cascadeIndex >= CascadeCount) return;
        const int bound = m_Cascades[cascadeIndex].boundSlot;
        if (bound >= 0)
        {
            GLCall(glActiveTexture(GL_TEXTURE0 + bound));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
            m_Cascades[cascadeIndex].boundSlot = -1;
        }
    }

    void CascadedShadowMap_OpenGL::Resize(const int cascadeIndex, const glm::ivec2& newSize)
    {
        if (cascadeIndex < 0 || cascadeIndex >= CascadeCount) return;
        m_Sizes[cascadeIndex] = newSize;
        CreateCascade(cascadeIndex, newSize);
    }
}
