# crafting-interpreters

This is my implementation of [Crafting Interpreters](https://craftinginterpreters.com/).
I followed the book's implementation almost exactly.

Check out the [Pull Request](https://github.com/tmastny/crafting-intrepreters/pulls)
section for my attempt at the `clox` exercises.

As I worked through the book, I occasionally found it
useful to refer to the author's implementations,
which can be found on his Github [here](https://github.com/munificent/craftinginterpreters).

## Bonus

[My blog post on Lox garbage collection.](https://timmastny.com/blog/garbage-collection-crafting-interpreters/)

## Exercises

I worked through most exercises in the book.
Take a look if you if you need some ideas.
(No promises my solutions are easy to understand
or even correct. I also got stuck on some and skipped others).

### jlox

My `jlox` exercises are a mess. For each one,
I copy/pasted the implementation up to that chapter
and made a new (vaguely named) folder in `jlox`.

### clox

For `clox` I was more systematic. I got the
idea from [Chelsea Troy](https://chelseatroy.com/2022/02/10/adding-error-productions-to-the-lox-compiler/)
to have each chapter and exercise a PR of this repo.
This makes it easy to organize and see the changes
I made against the chapter implementation.

Check out the PR section if you are curious! So the diffs make
sense:
* Pull request `chapter-{n}` is against `chapter-{n-1}`
* Pull request `chapter-{n}_{x}` is against `chapter-{n}`.
