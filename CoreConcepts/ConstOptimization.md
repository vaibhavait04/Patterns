## Compiler provides const optimization 

Read: http://www.gotw.ca/gotw/081.htm for more details 

const is mainly a compile-time thing, however, declaring something as const sometimes allows for certain optimizations. 
If the code in question isn't a performance bottleneck, I wouldn't worry about it and just use const as intended: to produce clearer code and prevent yourself from doing stupid things.

