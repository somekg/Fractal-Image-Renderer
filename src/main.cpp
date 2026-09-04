/**
 * @file main.cpp
 * @brief SFML 3.0 GUI entry point for the Fractal Engine.
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <future>

#include <iomanip>
#include <sstream>

#include "FractalCreator.hpp"

using namespace std;

enum class AppState { Idle, Animating, Rendering4K };

int main() {
    // Remove const so the window can be resized/fullscreened
    unsigned int winW = 800;
    unsigned int winH = 450; 
    
    FractalCreator lowResEngine(800, 450); // Keep internal engine fixed at 16:9
    lowResEngine.setSSAA(false); 
    
    FractalCreator highResEngine(3840, 2160);
    
    cout << "Rendering initial preview..." << endl;
    lowResEngine.render();
    highResEngine.render(); 

    // Enable Resizing (Maximize for Fullscreen)
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(winW, winH)), "4K Fractal Explorer");
    window.setFramerateLimit(60);

    sf::Texture lowResTex; lowResTex.resize(sf::Vector2u(800, 450));
    sf::Texture highResTex; highResTex.resize(sf::Vector2u(3840, 2160));
    
    // THIS FIXES THE "FUNKY" ALIASING!
    lowResTex.setSmooth(true);
    highResTex.setSmooth(true); 
    
    highResTex.update(highResEngine.getPixels());
    sf::Sprite displaySprite(highResTex);
    
    sf::RectangleShape zoomBox;
    zoomBox.setFillColor(sf::Color::Transparent);
    zoomBox.setOutlineColor(sf::Color::White);
    zoomBox.setOutlineThickness(2.0f);
    float boxWidth = 160.0f; 
    float boxHeight = 90.0f;  
    zoomBox.setSize(sf::Vector2f(boxWidth, boxHeight));

    AppState state = AppState::Idle;
    std::future<void> backgroundRender;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // Handle Fullscreen / Resizing dynamically
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                winW = resized->size.x;
                winH = resized->size.y;
                // Prevent the view from stretching
                window.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(winW, winH))));
            }

            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                
                // Add a static variable to track the palette state
                static int currentPalette = 0;

                // --- CHANGE COLOR PALETTE EVENT ---
                if (keyPress->code == sf::Keyboard::Key::C && state == AppState::Idle) {
                    currentPalette++;
                    lowResEngine.setPalette(currentPalette);
                    highResEngine.setPalette(currentPalette);

                    // Re-render instantly
                    lowResEngine.render();
                    lowResTex.update(lowResEngine.getPixels());
                    displaySprite.setTexture(lowResTex, true);

                    // Kick off 4K background render
                    state = AppState::Rendering4K;
                    backgroundRender = std::async(std::launch::async, [&highResEngine]() {
                        highResEngine.render();
                    });
                }

                // SAVE IMAGE EVENT
                if (keyPress->code == sf::Keyboard::Key::S) {
                    cout << "Saving 4K Image..." << endl;
                    highResEngine.saveImage("output/fractal_4k.png");
                    cout << "Saved!" << endl;
                }
                // UNZOOM EVENT
                if ((keyPress->code == sf::Keyboard::Key::Z || keyPress->code == sf::Keyboard::Key::Backspace) && state == AppState::Idle) {
                    lowResEngine.unZoom();
                    highResEngine.unZoom();

                    // Instantly show the unzoomed low-res frame
                    lowResEngine.render();
                    lowResTex.update(lowResEngine.getPixels());
                    displaySprite.setTexture(lowResTex, true);

                    state = AppState::Rendering4K;
                    backgroundRender = std::async(std::launch::async, [&highResEngine]() {
                        highResEngine.render();
                    });
                }
            }

            if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
                zoomBox.setPosition(sf::Vector2f(
                    mouseMove->position.x - boxWidth/2, 
                    mouseMove->position.y - boxHeight/2
                ));
            }

            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (state == AppState::Idle) {
                    float factor = (scroll->delta > 0) ? 0.9f : 1.1f;
                    boxWidth *= factor;
                    boxHeight *= factor;
                    zoomBox.setSize(sf::Vector2f(boxWidth, boxHeight));
                }
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (click->button == sf::Mouse::Button::Left && state == AppState::Idle) {
                    
                    // Map the click based on the dynamic window size back to the 800x450 base scale
                    double normalizedX = (zoomBox.getPosition().x + (boxWidth / 2.0)) / winW;
                    double normalizedY = (zoomBox.getPosition().y + (boxHeight / 2.0)) / winH;
                    
                    double boxCenterX = normalizedX * 800.0;
                    double boxCenterY = normalizedY * 450.0;
                    double scaleFactor = (boxWidth / winW); 
                    
                    lowResEngine.addZoom(Zoom(boxCenterX, boxCenterY, scaleFactor));
                    highResEngine.addZoom(Zoom(boxCenterX * 4.8, boxCenterY * 4.8, scaleFactor));

                    lowResEngine.render();
                    lowResTex.update(lowResEngine.getPixels());
                    displaySprite.setTexture(lowResTex, true);

                    state = AppState::Rendering4K;
                    backgroundRender = std::async(std::launch::async, [&highResEngine]() {
                        highResEngine.render();
                    });
                }
            }
        }

        if (state == AppState::Rendering4K) {
            if (backgroundRender.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                highResTex.update(highResEngine.getPixels());
                displaySprite.setTexture(highResTex, true);
                state = AppState::Idle;
            }
        }

        // Dynamically scale the sprite to fit the window exactly
        if (state == AppState::Idle) {
            displaySprite.setScale(sf::Vector2f(winW / 3840.0f, winH / 2160.0f));
        } else {
            displaySprite.setScale(sf::Vector2f(winW / 800.0f, winH / 450.0f));
        }

        window.clear();
        window.draw(displaySprite);
        if (state == AppState::Idle) window.draw(zoomBox);
        window.display();
    }
    return 0;
}