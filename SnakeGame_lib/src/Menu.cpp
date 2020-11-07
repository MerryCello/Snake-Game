//
// Created by Kevin on 8/14/2020.
//

#include <cassert>
#include <utility>
#include <iterator>
#include <list>
#include "include/Menu.h"
#include "include/uiDraw.h"


Menu::Menu() {
}

Menu::Menu(string title, string gameName, Point center)
         : center(center) {
   Menu menuSetup;
   *this = menuSetup;
   Menu::gameName = gameName;
   Menu::title = title;
}

void Menu::draw() {
   Color blue(BLUE("r"), BLUE("g"), BLUE("b"));
   Color green(GREEN("r"), GREEN("g"), GREEN("b"));
   Color black(0.0, 0.0, 0.0);
   Color white(1.0, 1.0, 1.0);
   Color brown(BROWN("r"), BROWN("g"), BROWN("b"));
   float lineSpacing = 20;

   drawRectangle(center, WINDOW_WIDTH * 0.50, WINDOW_WIDTH * 0.50, white       );
   drawRectangle(center, WINDOW_WIDTH * 0.50, WINDOW_WIDTH * 0.50, black, false);

   drawTextCenter(Point(center.getX(), center.getY() + 3 * lineSpacing),
                  gameName.c_str(),
                  brown,
                  true);

   drawTextCenter(Point(center.getX(), center.getY() + 1 * lineSpacing),
                title.c_str(),
                blue,
                true);

   int i = 0;
   for (auto option = options.begin(); option != options.end(); option++, i++) {
      drawTextCenter(Point(center.getX(), center.getY() - i * lineSpacing),
                     (*option).c_str(),
                     (option == optionSelected ? green : black));
   }
}

Menu& Menu::operator = (list<string> & newOptions) {
   this->options = newOptions;
   optionSelected = begin();
   return *this;
}

Menu& operator ++ (Menu& menu) {
   if (menu.optionSelected == menu.end()) {
      menu.optionSelected = menu.begin();
   } else {
      ++(menu.optionSelected);
   }
   return menu;
}

Menu& operator -- (Menu& menu) {
   if (menu.optionSelected == menu.begin()) {
      menu.optionSelected = menu.end();
   } else {
      --(menu.optionSelected);
   }
   return menu;
}
