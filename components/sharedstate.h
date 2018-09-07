#pragma once

namespace GameComponent
{
    struct SharedState
    {
        bool isHolding = false; // did we start a holding operation
        int e_link = -1; // holds handle to the last unlinked portal entity
    };
};