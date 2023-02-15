#pragma once

#include <glad/glad.h>

#include "poggles/gltypes.h"
#include "poggles/poggles_export.hpp"

namespace poggles::gl
{
void POGGLES_EXPORT bindBuffer(GLenum target, buffer_id buffer);

void POGGLES_EXPORT bindVertexArray(vertex_array_id array);

}  // namespace poggles::gl