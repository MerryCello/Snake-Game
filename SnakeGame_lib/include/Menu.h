//
// Created by Kevin on 8/14/2020.
//

#ifndef UNIT_TESTING_ON_SNAKE_GAME_MENU_H
#define UNIT_TESTING_ON_SNAKE_GAME_MENU_H

#include <string>
#include "Point.h"
using namespace std;

class Menu {
private:
   string gameName;                       /// The name of the game that the menu is for
   string title;                          /// Title of the menu
   list<string> options;                  /// the list of options
   list<string>::iterator optionSelected; /// the option highlighted/selected
   Point center;                          /// the location of the menu (for drawing)

public:
   /// constructors
   Menu();
   Menu(string title, string gameName, Point center);

   /// destructor
   ~Menu() {}

   /// setters
   void setGameName(const string &gameName) { Menu::gameName = gameName; }
   void setTitle(const string &title) { Menu::title = title; }
   void setCenter(Point c) { center = c; }
   /// i.e. the option that is highlighted on the screen
   void setOptionSelected(_List_iterator<string> selection){ optionSelected = selection; }

   /// getters
   const string &getGameName() const { return gameName; }
   const string &getTitle() const { return title; }
   auto getOptionSelected() const { return optionSelected; }

   void draw();
   auto begin() { return options.begin();   }
   auto end()   { return --(options.end()); }

   /// operator overloads
   Menu& operator = (list<string> & newOptions); /// To the set the options of the menu
   friend Menu& operator ++ (Menu& menu);        /// to iterate through the options
   friend Menu& operator -- (Menu& menu);        /// to iterate through the options
};


#endif //UNIT_TESTING_ON_SNAKE_GAME_MENU_H
