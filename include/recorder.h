#pragma once

#include <string>

#include "renderer.h"

struct Recorder {
    int frame_;
    Renderer* renderer_;
    Recorder(Renderer& r);

    void capture_bmp();
    void load_bmp(const std::string& f) const;
    void play();
    void reset();
};

