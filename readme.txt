2014 Neil Edelman.
neil dot edelman each mail dot mcgill dot ca

Orcish words are gathered off the Internet, SMAUG1.8, made up myself,
etc. They originate or are inspired by JRR Tolkien's Orcish; this
file has had many incarnations and was ported from Java. Random
words are super-useful in testing and character generation;
\url{http://en.wikipedia.org/wiki/Languages_constructed_by_J._R._R._Tolkien}.

ANSI C89; provides one function, {void Orcish(char *const name,
const size_t name_size)}, which takes {name}, a string, and
replaces it, to a maximum of {name_size} characters, with a
{rand()} Orcish name.
