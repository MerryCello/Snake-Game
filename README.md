# Snake Game
Based off of the classic [snake][wiki-snake] game, this project started to gain more knowledge about [Test-driven Development (TDD)][wiki-TDD] and was finished after 1 <sup>1</sup>/<sub>2</sub> weeks (planned on 2). The hands-on experience was a good demonstration of the benefits of TDD. The automated testing was done with the help of [Google's C++ test framework][wiki-google-tests]. The framework helped quickly discover what the issues were with the code while in development and after.
## Looks
|![][start]|![][long]|
|:--------:|:--------:|
|![][small]|![][game-over]|
## Installation
Requirements:
- JetBrain's Clion IDE
- [C++ 14][MinGW-download-page] (32-bit) or later compiler
- [Open GL][freeglut-3.0.0] (freeglut) libraries

Unfortunately, Google tests is on a x64bit C++ compiler and is not compatible with the project. Once I incorporated the graphics, I had to use a x32bit compiler until I figured out how to get OpenGL to work on x64bit. There's a open issue for it on [StackOverflow][stackoverflow-question]. Once I get back to it, I hope to be able to have it all run on x64bit so that the automated tests will work once again.

[wiki-google-tests]: https://developer.ibm.com/technologies/systems/articles/au-googletestingframework/
[wiki-TDD]: https://www.agilealliance.org/glossary/tdd/
[wiki-snake]: https://en.wikipedia.org/wiki/Snake_(video_game_genre)

[start]: ./Docs/Snake-start.jpg
[small]: ./Docs/Snake-small.jpg
[long]: ./Docs/Snake-long.jpg
[game-over]: ./Docs/Snake-game-over.jpg

[MinGW-download-page]: https://osdn.net/projects/mingw/releases/
[freeglut-3.0.0]: https://www.transmissionzero.co.uk/software/freeglut-devel/
[stackoverflow-question]: https://stackoverflow.com/questions/63458637/how-can-i-have-freeglut-3-2-1-and-glew-2-1-0-run-on-mingw-w64