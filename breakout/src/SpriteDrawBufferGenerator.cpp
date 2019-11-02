#include "SpriteDrawBufferGenerator.hpp"


#include <graphics/SpriteDrawBufferSingleton.hpp>

#include <iostream>

void SpriteDrawBufferGenerator::operator()(const fug::EntityId& eId, PhysicsComponent& phys,
                                           const fug::SpriteDrawComponent &draw)
{
    // NOTE: buffers should be cleared before each frame
    auto *buffers = &_ecs.getSingleton<fug::SpriteDrawBufferSingleton>()->buffers;
    if (buffers->find(draw.sheet->textureID) == buffers->end()) {
        glsprite_draw_buffer buffer;
        glsprite_draw_buffer_init(&buffer, &draw.sheet->sheet);
        buffers->insert({draw.sheet->textureID, buffer});
    }
    auto elem = buffers->find(draw.sheet->textureID);
    glsprite_draw_buffer_push_grid(&elem->second, &draw.sheet->grid,
                                   draw.index,
                                   phys.pos,
                                   draw.origin,
                                   0.f);
}
