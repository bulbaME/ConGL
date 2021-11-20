#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <iostream>
#include <tuple>
#include <stdio.h>
#include "congl.h"

namespace py = pybind11;


// COORD type conversion
namespace pybind11 { namespace detail {
    template <> struct type_caster<COORD> {
        PYBIND11_TYPE_CASTER(COORD, _("COORD"));

        bool load(handle src, bool) {
            // get object
            PyObject *source = src.ptr();
            if (PyTuple_Size(source) != 2) return false;

            // parse tuple
            PyObject *x = PyTuple_GetItem(source, 0);
            PyObject *y = PyTuple_GetItem(source, 1);

            if (PyNumber_Check(x) && PyNumber_Check(y)) {
                value.X = (short) PyLong_AsLong(x);
                value.Y = (short) PyLong_AsLong(y);
            }

            Py_DECREF(x);
            Py_DECREF(y);
            return true;
        }

        static handle cast(COORD src, return_value_policy, handle) {
            return PyTuple_Pack(2, PyLong_FromLong(src.X), PyLong_FromLong(src.Y));
        }
    };
}}

PYBIND11_MODULE(congl, m) { 
    m.doc() = "\
    //--------------------- (c) BULBA 2021 -------------------------// \n\
    //                                                              // \n\
    //        /$$$$$$                       /$$$$$$  /$$            // \n\
    //       /$$__  $$                     /$$__  $$| $$            // \n\
    //      | $$  \\__/  /$$$$$$  /$$$$$$$ | $$  \\__/| $$            // \n\
    //      | $$       /$$__  $$| $$__  $$| $$ /$$$$| $$            // \n\
    //      | $$      | $$  \\ $$| $$  \\ $$| $$|_  $$| $$            // \n\
    //      | $$    $$| $$  | $$| $$  | $$| $$  \\ $$| $$            // \n\
    //      |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$$      // \n\
    //       \\______/  \\______/ |__/  |__/ \\______/ |________/      // \n\
    //                                                              // \n\
    //--------------------- Now on Python. -------------------------// \
    ";
    
    m.attr("W_FF_BLOCK") = &ConGL::W_FF_BLOCK;
    m.attr("W_HF_BLOCK") = &ConGL::W_HF_BLOCK;
    m.attr("W_QF_BLOCK") = &ConGL::W_QF_BLOCK;

    // COORD CLASS
    py::class_<COORD>(m, "COORD")
        .def_readwrite("X", &COORD::X)
        .def_readwrite("Y", &COORD::Y);

    // PIXEL CLASS
    py::class_<ConGL::PIXEL>(m, "PIXEL", "pixel object")
        .def(py::init<>())
        .def(py::init<wchar_t>())
        .def(py::init<ConGL::COLOR>())
        .def(py::init<wchar_t, ConGL::COLOR>())
        .def(py::init<COORD, wchar_t, ConGL::COLOR>())
        .def(py::init<COORD>())
        
        .def_readwrite("pos", &ConGL::PIXEL::pos)
        .def_readwrite("ch", &ConGL::PIXEL::ch)
        .def_readwrite("col", &ConGL::PIXEL::col);


    // KEYS SUB MODULE
    py::module_ m_keys = m.def_submodule("keys");
    
    m_keys.attr("CAPS_ON") = ConGL::keys::CAPS_ON;
    m_keys.attr("ALT_LEFT") = ConGL::keys::ALT_LEFT;
    m_keys.attr("ALT_RIGHT") = ConGL::keys::ALT_RIGHT;
    m_keys.attr("CTRL_LEFT") = ConGL::keys::CTRL_LEFT;
    m_keys.attr("CTRL_RIGHT") = ConGL::keys::CTRL_RIGHT;
    m_keys.attr("SHIFT") = ConGL::keys::SHIFT;

    m_keys.def("down", &ConGL::keys::down, "if key is down");
    m_keys.def("released", &ConGL::keys::released, "if key was released");


    // COLORS SUB MODULE
    py::module_ m_colors = m.def_submodule("colors");
    
    // foreground colors
    m_colors.attr("FG_RED") = &ConGL::colors::FG_RED;
    m_colors.attr("FG_GREEN") = &ConGL::colors::FG_GREEN;
    m_colors.attr("FG_BLUE") = &ConGL::colors::FG_BLUE;
    m_colors.attr("FG_BLACK") = &ConGL::colors::FG_BLACK;
    m_colors.attr("FG_WHITE") = &ConGL::colors::FG_WHITE;
    m_colors.attr("FG_INTENSE") = &ConGL::colors::FG_INTENSE;

    // background colors
    m_colors.attr("BG_RED") = &ConGL::colors::BG_RED;
    m_colors.attr("BG_GREEN") = &ConGL::colors::BG_GREEN;
    m_colors.attr("BG_BLUE") = &ConGL::colors::BG_BLUE;
    m_colors.attr("BG_BLACK") = &ConGL::colors::BG_BLACK;
    m_colors.attr("BG_WHITE") = &ConGL::colors::BG_WHITE;
    m_colors.attr("BG_INTENSE") = &ConGL::colors::BG_INTENSE;   

    m_colors.attr("UNDERSCORE") = &ConGL::colors::UNDERSCORE;


    // SCREEN CLASS
    py::class_<ConGL::Screen>(m, "Screen", "Screen class")
        .def(py::init<>())
        .def("setPX", &ConGL::Screen::setPX, "set pixel to a specific position")
        .def("getPX", &ConGL::Screen::getPX, "get pixel from a specific position")
        .def("getScrSize", &ConGL::Screen::getScrSize, "returns screen size")
        .def("setSurfaceSize", &ConGL::Screen::setSurfaceSize, "set surface size")
        .def("getSurfaceSize", &ConGL::Screen::getSurfaceSize, "get surface size")
        .def("render", &ConGL::Screen::render, "returns surface size")
        .def("flush", &ConGL::Screen::flush, "clears screen")
        .def("toggleAutosize", &ConGL::Screen::toggleAutosize, "toggle auto screen resizing")
        .def("toggleMeta", &ConGL::Screen::toggleMeta, "toggle meta data")
        .def("setFont", &ConGL::Screen::setFont, "set font size")
        .def("_setFpsLimit", &ConGL::Screen::_setFpsLimit, "returns current fps")
        .def("getFps", &ConGL::Screen::getFps, "");

    
    // 2D ENGINE
    py::module_ m_eng2D = m.def_submodule("eng2D", "2D engine module");

    // LAYOUT CLASS
    py::class_<ConGL::eng2D::Layout>(m_eng2D, "Layout")
        .def(py::init<ConGL::Screen*>())
        .def("setCamera", &ConGL::eng2D::Layout::setCamera, "camera interface")
        .def("getCamera", &ConGL::eng2D::Layout::getCamera, "camera interface")
        .def("addFigure", &ConGL::eng2D::Layout::addFigure, "adds figure to the layout ; returns figure's ID")
        .def("getFigure", &ConGL::eng2D::Layout::getFigure, "returns pointer to the figure")
        .def("disableFigure", &ConGL::eng2D::Layout::disableFigure, "disables figure on the layout")
        .def("enableFigure", &ConGL::eng2D::Layout::enableFigure, "enables figure on the layout")
        .def("collides", static_cast<bool (ConGL::eng2D::Layout::*)(int, int)>(&ConGL::eng2D::Layout::collides), "checks collisions between two figures on the layout")
        .def_static("collides_S", static_cast<bool (*)(ConGL::eng2D::shapes::Figure*, ConGL::eng2D::shapes::Figure*)>(&ConGL::eng2D::Layout::collides), "checks collisions between two figures")
        .def("onCollision", static_cast<bool (ConGL::eng2D::Layout::*)(int, int)>(&ConGL::eng2D::Layout::onCollision), "checks if two figures on the layout are touching each other")
        .def_static("onCollision_S", static_cast<bool (*)(ConGL::eng2D::shapes::Figure*, ConGL::eng2D::shapes::Figure*)>(&ConGL::eng2D::Layout::onCollision), "checks if two figures are touching each other")
        .def("draw", &ConGL::eng2D::Layout::draw, "draw frame on to the screen");
    
    // TEXTURES
    py::module_ m_txr = m_eng2D.def_submodule("txr");

    py::class_<ConGL::eng2D::txr::Texture>(m_txr, "Texture")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def_readonly("size", &ConGL::eng2D::txr::Texture::size);

    // SHAPES
    py::module_ m_shapes = m_eng2D.def_submodule("shapes");

    py::class_<ConGL::eng2D::shapes::Figure>(m_shapes, "Figure")
        .def("setPos", &ConGL::eng2D::shapes::Figure::setPos)
        .def("getPos", &ConGL::eng2D::shapes::Figure::getPos)
        .def("movePos", &ConGL::eng2D::shapes::Figure::movePos)
        .def("setSize", &ConGL::eng2D::shapes::Figure::setSize)
        .def("getSize", &ConGL::eng2D::shapes::Figure::getSize);

    // ELLIPSE
    py::class_<ConGL::eng2D::shapes::Ellipse, ConGL::eng2D::shapes::Figure>(m_shapes, "Ellipse")
        .def(py::init<>())
        .def(py::init<COORD>())
        .def("setFilling", &ConGL::eng2D::shapes::Ellipse::setFilling);

    // RECTANGLE
    py::class_<ConGL::eng2D::shapes::Rectangle, ConGL::eng2D::shapes::Figure>(m_shapes, "Rectangle")
        .def(py::init<>())
        .def(py::init<COORD>())
        .def("setFilling", &ConGL::eng2D::shapes::Rectangle::setFilling);

    // SPRITE
    py::class_<ConGL::eng2D::shapes::Sprite, ConGL::eng2D::shapes::Figure>(m_shapes, "Sprite")
        .def(py::init<>())
        .def(py::init<COORD>())
        .def(py::init<ConGL::eng2D::txr::Texture*>())
        .def(py::init<std::string>())
        .def("setTexture", &ConGL::eng2D::shapes::Sprite::setTexture);

    // TEXT
    py::class_<ConGL::eng2D::shapes::Text, ConGL::eng2D::shapes::Figure>(m_shapes, "Text")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("setText", &ConGL::eng2D::shapes::Text::setText)
        .def("setFilling", &ConGL::eng2D::shapes::Text::setFilling);
}