#pragma once

#include <memory>

#include <dlib-glib/widgets.h>

GDLIBWidgets *gdlib_widgets_new_raw(std::shared_ptr<dlib::image_window> *image_window);