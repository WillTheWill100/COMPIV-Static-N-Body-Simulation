# PS3: N-Body Simulation

## Contact
Name: William King
Section: 202
Time to Complete: A very very long time ( > 5 hrs )


## Description
This program will read from planets.txt which contains all the require info
such as velocity, mass, position, and the image. The radius which is also found in the file
is passed to the Universe class and the rest of the info is used to construct a vector smart pointer
of celestial bodies. This will be drawn into a sfml window and create a static N-Body.

### Features
I used smart pointers because it made holding the bodies easier (explained in memory section).
The code reads from a file and use them to make the celestial bodies.
The features were the ones asked for, for the assignment. I made a few helper fucntions such as
getters and setters, along with a fucntion for Universe to add celestil bodies to the vector.

### Memory
I used smart pointers because it made holding the bodies easier. std::shared_ptr will 
automatically manage the memory of the vector so I don't have too. It would've been a pain
in the but to manually manage the memory, probally would've been a memory leak.


### Issues
Everything should be working correctly (almost a week late so it better be working).
There were alot of issues withg this project. White squares and the planets were drawn in the corner (0, 0). 
I had no idea for the longest on why that was the case. I still don't really know what the problem was but I believe for
the white square, it was cause i wasn't loadiung the pictures correctly as only one white square and not the whole thing.
It got fixed I think when I used smart pointers, though it didn;t work right away as there were more trial and error before all planets
were drawn. The next problem was positioning. I fixed after I went through the pong code from class and realized I could add an update funtion
to update the coordinates of the bodies. 

### Extra Credit
I added a background image so it looks like a real solar system

## Acknowledgements
For help with smart pointers:
https://stackoverflow.com/questions/28733385/c11-vector-of-smart-pointer

Pong code from class
