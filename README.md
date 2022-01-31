# Cheem Scheme
A interpreter for a dialect of the functional programming language Scheme written from scratch in C++. Currently implements integers, cons lists, booleans, characters, strings, scoped environments and lambdas, all put together in a simple REPL.

## Build Instructions
Run `make` to build cheem-scheme and `make run` to run it. You should see this repl pop up.

```
(master) λ make
 g++ -g -Wall -I include -c -o build/cheem.o src/cheem.cpp
 Linking...
 g++ build/cheem.o build/environment.o build/eval.o build/object.o build/parser.o build/print.o build/scanner.o build/token.o -o bin/cheem
(master) λ make run
 Running...
./bin/cheem
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMNNNNWWWMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMWXxlllloooodkKWMMMMMMMMMMMMMM
MMMMMMMMMMMKoc:;;;;;;;,,;xNMMMMMMMMMMMMM
MMMMMMMMMMNd;;:ccll::;,,,;dXMMMMMMMMMMMM
MMMMMMMMW0c',:ccldxolc:;;;;lONMMMMMMMMMM
MMMMMMMMW0lcc:;:codolc;;,,;;:xXWMMMMMMMM
MMMMMMMMWMMWOoodddl:;;;,;;;;;;cxXMMMMMMM
MMMMMMMMMMMMKddddolccccccc:;,,',lKMMMMMM
MMMMMMMMMMMMKxdxxddoooolcc:;,'',;oXMMMMM
MMMMMMMMMMMW0dddddddddoooc:,',,,';OMMMMM
MMMMMMMMMMMMKoloddooooooc:,,,,;;cOWMMMMM
MMMMMMMMMMMWKoloollollc:;;,',,,oXMMMMMMM
MMMMMMMMMMMW0oooc;:cccc:;,'.'',xWMMMMMMM
MMMMMMMWX0kxdool;;cllllc:,'..':0MMMMMMMM
MMMMMMMNK00KOdlclxxdoolc;,''cxKWMMMMMMMM
MMMMMMWKkkkkO00KXXXK0ko:;lOKNMMMMMMMMMMM
MMMMMMMKxxkKNWWMMMWWWNx:lKWWMMMMMMMMMMMM
MMMMMMMMWNNWMMMMMMMWWWX0KWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
============cheem-scheme v.1============
1] cheem>
```
