#include "options/camera_options.h"
#include "options/render_options.h"
#include "raytracer.h"
#include "util.h"

int main() {
    CameraOptions camera_opts{.screen_width = 800,
                              .screen_height = 600,
                              .look_from = {2., 1.5, -.1},
                              .look_to = {1., 1.2, -2.8}};
    RenderOptions render_opts{4};
    static const auto kTestsDir = GetRelativeDir(__FILE__, "prob");
    auto image = Render(kTestsDir / "scene.obj", camera_opts, render_opts);
    image.Write(kTestsDir / "result.png");
}