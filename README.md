# ft_containers (@42Paris)

> This project was code for MACOS. Here is the [subject][1].
>
*"C++ containers, easy mode"*

![Alt text](https://github.com/llefranc/42_ft_containers/blob/main/containers_example.png)

## About

Ft_containers is a project of the mandatory part of the cursus.
It's only made in C++ and was about recoding some containers from the STL.

In order to succeed, a good comprehension of how **templates**, **iterators**, **containers** and 
**algorithms** work was necessary. Of course, STL is not allowed. That means 
you cannot use \<iterator\> or even \<utility\>. 

Here are the specificities of the five containers:

- :arrow_right: **Vector:** a dynamic array that allows insertion at the end of the container. Elements can be easily access thanks with the corresponding index, but it's not the most optimal container if a lot of insertion / deletion are needed.
- :arrow_right: **List:** a circular linked list (with a neutral node linking beginning and end of the list). Better than vector for inserting or deleting elements.
- :arrow_right: **Stack:** a container adaptator (LIFO, last in first out).
- :arrow_right: **Queue:** a container adaptator (FIFO, first in first out).
- :arrow_right: **Map:** a sorted container using an AVL binary tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store the datas like in a dictionnary (a key associated to its value).

All my containers use an allocator to manage properly their memory, iterators to access their datas, and handle the same constructors / methods than the containers from the STL in C++98.

## Tester

I created a tester with [Hélène Herin][16], doing several tests on each of the five mandatory containers. It handles over **10000 tests for some containers !**

It will test all the constructors, methods and iterators, by comparating your containers with the STL containers, and making a diff if some errors occured.
Also, you can choose which tests you want to execute, in the case you're checking specific containers / methods.

:white_check_mark:  If you want to see more, go check it at this repo : https://github.com/llefranc/42_Containator 

## Sources

- [Best website for learning about C++ (including C++98)][17]
- [Difference of keywords 'typename' and 'class' in templates][2]
- [Lvalus and rvalues][3]
- [Dependant names in C++][4]
- [What's explicit keyword][5]
- [Explicit call to a constructor][15]
- [Implementing iterators][6]
- [Writing your own STL style container][7]
- [Writing operator++ for iterator][8]
- [Writing operator== for iterator][9]
- [When use typename keyword][10]
- [Cours sur les templates][11]
- [Understanding SFINAE (used in enable_if)][12]
- [How to use the allocator][13]
- [Difference between explicit and implicit copy constructor][14]

[1]: https://github.com/llefranc/42_ft_containers/blob/main/ft_containers.en.subject.pdf
[2]: https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
[3]: https://www.tutorialspoint.com/What-are-Lvalues-and-Rvalues-in-Cplusplus#:~:text=An%20lvalue%20(locator%20value)%20represents,some%20identifiable%20location%20in%20memory.
[4]: https://stackoverflow.com/questions/1527849/how-do-you-understand-dependent-names-in-c#:~:text=A%20dependent%20name%20is%20essentially,depends%20on%20a%20template%20argument.&text=Names%20that%20depend%20on%20a,at%20the%20point%20of%20definition.
[5]: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
[6]: https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls
[7]: https://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622
[8]: https://stackoverflow.com/questions/4329677/increment-operator-iterator-implementation
[9]: https://stackoverflow.com/questions/12806657/writing-an-operator-function-for-an-iterator-in-c
[10]: https://stackoverflow.com/questions/7923369/when-is-the-typename-keyword-necessary
[11]: https://cpp.developpez.com/cours/cpp/?page=page_14
[12]: https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
[13]: https://stackoverflow.com/questions/59539057/c-does-it-lead-to-double-free-when-destroy-element-in-allocatorstring
[14]: https://stackoverflow.com/questions/1051379/is-there-a-difference-between-copy-initialization-and-direct-initialization
[15]: https://stackoverflow.com/questions/12036037/explicit-call-to-a-constructor
[16]: https://github.com/hherin
[17]: http://www.cplusplus.com/
