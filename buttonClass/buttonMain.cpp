/**
 * @file main.cpp
 * @author Ekaterina Miller
 * @brief  This program testing class buton
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * @aknolegment https://code.markrichards.ninja/sfml/how-to-create-simple-buttons-for-your-sfml-game
 * 
 * 
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 500), "MyButton!");
   Button yes("Rules",sf::Vector2f(200.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color::Green);
   //changed color of first button
   yes.setColorTextHover(sf::Color::Green);
   yes.setColorTextNormal(sf::Color(95,25,10));
   Button no;
   no.setText("Play");
   no.setPosition({600, 300});
   no.setSize({200, 71});
   no.setColor(sf::Color::Red);
   no.setColorTextHover(sf::Color(95,25,10));
   no.setColorTextNormal(sf::Color::Green);
   //extra button
   Button header("Squirrels Tower Defense", sf::Vector2f(400,50), sf::Vector2f(200,100), sf::Color::Black);
   header.setColorTextHover(sf::Color::Green);

   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
           yes.update(event, window);
           no.update(event, window);
           header.update(event, window);
       }

       window.clear();
       window.draw(yes);
       window.draw(no);
       window.draw(header);
       window.display();
   }

   return 0;
}

//int main()
// {
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
            
//             //get position of the mouse
//             //sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//             sf::Vector2i mPos = sf::Mouse::getPosition(window);
//             sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);
//             bool mouseInButton =    mousePosition.x >= button.getPosition().x - button.getGlobalBounds().width/2
//                                     && mousePosition.x <= button.getPosition().x + button.getGlobalBounds().width/2
//                                     && mousePosition.y >= button.getPosition().y - button.getGlobalBounds().height/2
//                                     && mousePosition.y <= button.getPosition().y + button.getGlobalBounds().height/2;
//             if(event.type == sf::Event::MouseMoved)
//             {
//                 if(mouseInButton)
//                 {
//                     text.setFillColor(textHover);
//                 }
//                 else
//                 {
//                     text.setFillColor(textNormal);
//                 }
//             }
//             if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 if(event.mouseButton.button==sf::Mouse::Left)
//                 {
//                     if(mouseInButton)
//                     {
//                         button.setRotation(180);
//                     }
//                     else
//                     {
//                         button.setRotation(0);
//                     }
//                 }
//             }
//             if (event.type == sf::Event::MouseButtonReleased)
//             {
//                 if (event.mouseButton.button==sf::Mouse::Left)
//                 {
//                     if(mouseInButton)
//                     {
//                         text.setFillColor(textHover);
//                         button.setRotation(0);
//                     }
//                     else
//                     {
//                         text.setFillColor(textNormal);
//                         button.setRotation(0);
//                     }
//                 }
//             }
//         }
//         window.clear();
//         window.draw(button);
//         window.draw(text);
//         window.display();
//     }
//     return 0;
// }