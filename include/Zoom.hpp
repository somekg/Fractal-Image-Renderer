/**
 * @file Zoom.h
 * @brief Defines zoom struct for holding zoom within image information.
 * @author Alex
 */

#pragma once

/**
 * @brief Represents a single zoom action or position on the fractal image.
 */
struct Zoom {
    double x{0.0};
    double y{0.0};
    double scale{ 0.0 };

	/**
     * @brief Construct a new Zoom object.
     * @param x The x-coordinate of the zoom center.
     * @param y The y-coordinate of the zoom center.
     * @param scale The zoom scale factor.
     */
    Zoom(double x, double y, double scale) : x(x), y(y), scale(scale) {};
};

