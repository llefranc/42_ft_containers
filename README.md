# ft_containers (@42Paris)

"C++ containers, easy mode"

![Alt text](https://github.com/lucaslefrancq/42_philosophers/blob/main/philo_example.png)

## About

Ft_containers is a project of the mandatory part of the cursus.
It's only made in C++ and was about recoding some containers from the STL.
In order to suceed, a good comprehension of how templates, iterators, containers and 
algorithms work was necessary. Here are the specificities of the five containers:

- Vector: a dynamic array.
- List: a circular linked list (with a neutral node linking beginning and end of the list).
- Stack: a container adaptator (LIFO, last in first out).
- Queue: a container adaptator (FIFO, first in first out).
- Map: a sorted container using an AVL binary tree to store the datas.


* Here is the [subject][1]

`This project was code for MACOS`

### Building and running the project

1. Download/Clone this repo

        git clone https://github.com/lucaslefrancq/42_philosophers.git
2. `cd` into the root directory, then `cd` into philo_x (one, two or three) and run `make`

        cd 42_philosophers/philo_one
        make

3.  run `./philo_x arg1 arg2 arg3 arg4 (arg5)` from the directory philo_x.
    - arg1 is the number of philosopher
    - arg2 is the time to die in ms
    - arg3 is the time to eat in ms
    - arg4 is the time to sleep in ms
    - arg5 (optional) is the number of time each philosopher needs to eat to end the simulation


## Sources

- 
- [Difference of keywords 'typename' and 'class' in templates][2]
- [Lvalus and rvalues][3]
- [Dependant names in C++][4]
- [What's explicit keyword][5]
- [Explicit call to a constructor][15]
- [Implemtenting iterators][6]
- [Writing your own STL style container][7]
- [Writing operator++ for iterator][8]
- [Writing operator== for iterator][9]
- [When use typename keyword][10]
- [Cours sur les templates][11]
- [Understanding SFINAE (used in enable_if)][12]
- [How to use the allocator][13]
- [Difference between explicit and implicit copy constructor][14]

[1]: https://github.com/lucaslefrancq/42_CPP_piscine/blob/main/CPP08/cpp08.en.subject.pdf
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