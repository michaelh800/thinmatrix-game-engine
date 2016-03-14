/**
 * Original work Copyright (c) 2016 Tristan Brindle
 * License: MIT
 * Source: https://github.com/tcbrindle/thinmatrix-gl-tutorials
 */

#pragma once
#include <GL/glew.h>
#include <algorithm>
#include <array>

namespace gl {
namespace detail {

template <class Deleter>
class Handle {
public:
    Handle() = default;
    Handle(GLuint id) : id(id) {}

    Handle(Handle&& other)
        : id(other.id)
    {
        other.id = 0;
    }

    Handle& operator=(Handle&& other) {
        std::swap(id, other.id);
        return *this;
    }

    ~Handle() {
        if (id) Deleter{}(id);
    }

    GLuint get() const { return id; }

private:
    GLuint id = 0;
};

template <class Deleter, std::size_t N = 1>
class MultiHandle {
public:
    MultiHandle() = default;

    MultiHandle(MultiHandle&& other)
        : ids(std::move(other.ids))
    {
        std::fill(std::begin(other.ids), std::end(other.ids), 0);
    }

    MultiHandle& operator=(MultiHandle&& other) {
        std::swap(ids, other.ids);
        return *this;
    }

    ~MultiHandle() {
        Deleter()(N, ids.data());
    }

    GLuint* operator&() {
        return ids.data();
    }

    GLuint get(std::size_t n = 0) const {
        return ids[n];
    }

private:
    std::array<GLuint, N> ids = {};
};

struct GLBufferDeleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteBuffers(count, ptr);
    }
};

struct GLFramebufferDeleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteFramebuffers(count, ptr);
    }
};

struct GLProgramDeleter {
    void operator()(GLuint handle) const {
        glDeleteProgram(handle);
    }
};

struct GLRenderbufferDeleter {
    void operator() (GLsizei count, GLuint* ptr) const {
        glDeleteRenderbuffers(count, ptr);
    }
};

struct GLShaderDeleter {
    void operator()(GLuint handle) const {
        glDeleteShader(handle);
    }
};

struct GLTextureDeleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteTextures(count, ptr);
    }
};

struct GLVertexArrayDeleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteVertexArrays(count, ptr);
    }
};

} // end namespace detail

using BufferHandle = detail::MultiHandle<detail::GLBufferDeleter>;
using FramebufferHandle = detail::MultiHandle<detail::GLFramebufferDeleter>;
using ProgramHandle = detail::Handle<detail::GLProgramDeleter>;
using RenderbufferHandle = detail::MultiHandle<detail::GLRenderbufferDeleter>;
using ShaderHandle = detail::Handle<detail::GLShaderDeleter>;
using TextureHandle = detail::MultiHandle<detail::GLTextureDeleter>;
using VertexArrayHandle = detail::MultiHandle<detail::GLVertexArrayDeleter>;

} // end namespace gl
