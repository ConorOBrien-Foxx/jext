# Docs!

Always more to come.

## Defined keywords

These are commands which are usually defined explicitly and have special effects; they differ from functions in that functions can be described in terms of their tacit definitions, e.g. `max` is `>./`.

| Command | Arity   | Description |
| ------- | ------- | ----------- |
| `repl`  | monadic | Engages repl mode after program execution, if argument is truthy; exits afterwords otherwise. |

## Defined functions

| Command     | Type        | Description |
| ----------- | ----------- | ----------- |
| `MONAD`     | Adverb      | `u`, but when called dyadically, errors. |
| `DYAD`      | Adverb      | `u`, but when called monadically, errors. |
| `max`       | Verb        | Equiv. `>./`, or the maximum function reduced over `y`. |
| `min`       | Verb        | Equiv. `<./`; see `max`. |
| `t`         | Verb        | Yields `y ~: 0`, or inequality with `0`. |
| `f`         | Verb        | Negation of `t`. |
| `repr`      | Conjunction | Is `5!:`; see [here](http://www.jsoftware.com/help/dictionary/dx005.htm), and all the literal names (namely, `atomic`, `boxed`, `tree`, `linear`, `paren`, and `explicit`) all are set to their corresponding constants. So, for example, `tree repr` is a conjunction that yields the representation of the given named argument as a tree. |
| `adv_of`    | Adverb      | Given `u1`'s name, is an adverb that, given `u2`, is `[: u1 u2`. |
| `T`         | Adverb      | Equiv. `t adv_of`; given a function `u`, is whether or not the result of that function is not equal to `0`. |
| `F`         | Adverb      | Equiv. `f adv_of`; see `T`. |
| `any`       | Verb        | Equiv. `max T`; yields `1` if any member is not equal to `0`. |
| `all`       | Verb        | Equiv. `min T`; see `any`. |
| `none`      | Verb        | Equiv. `max F`; yields `0` if all members are equal to `0`. |
| `ANY`       | Adverb      | Equiv. `any adv_of`. |
| `ALL`       | Adverb      | Equiv. `all adv_of`. |
| `TRUTHY`    | Verb        | uses `if.`'s definition of truth. |
| `truthy`    | Verb        | tacit approximation of `TRUTHY`--if the first member is not equal to `0`. |
| `ab`        | Verb        | short for **a**nti**b**ase. Strictly equivalent to `#.inv`. |
| `unbox`     | Adverb      | Equiv. `>@`. Applies `u` to `y`, then unboxes the result. E.g., `5 = last unbox 3 ; 4 ; 5`. |
| `pad`       | Verb        | Takes a left argument `x` and right argument `y`, which looks like `y1 ; y2`. Pads `y2` to size `x` with `y1`s to the right. E.g., `5 2 0 = 3 pad 0 ; 5 2`. |
| `lpad`      | Verb        | Similar to `pad`, but pads to the left instead. |
| `snumpad`   | Verb        | `x snumpad y` &leftrightarrow; `x lpad '0' ; y`. |
| `enbox`     | Verb        | Fully unboxes `y`, then boxes. |
| `exec`      | Verb        | Like `0!:0`; takes an optionally boxed script name and executes it. |
| `reload`    | Verb        | Like `exec`, with default argument 'jext.ijs' (i.e. `exec ''` &leftrightarrow; `exec 'jext.ijs'`) |  
| `err`       | Verb        | Writes `y` and a LF to stderr. |
| `out`       | Verb        | `err`, but with stdout. |
| `printable` | Verb        | returns whether or not `y` is within the printable ASCII range, namely, between 0x20 and 0x7e (` ` and `~`). |
| `ord`       | Verb        | Equiv. `3&u:`; `y.charCodeAt()` in pseudo code. |
| `comp`      | Verb        | Given `y`, a list of numbers, yields `b ; s`, which represents a base-encoded version of `y`. The inverse is defiend to revert this process. |
| `decomp`    | Verb        | `decomp y` &leftrightarrow; `comp^:_1 y`. |
| `DECOMP`    | Verb        | Infix version of `decomp`. |
| `rle`       | Verb        | Given `y`, a string, run-length encodes `y` into a table, that is, yields a table of values whose left column represent the characters, and the right column their run frequency. |
| `RLE`       | Verb        | `rle`, but yields a string. |
| `apply`     | Conjunction | Applies `v` to the `u` indices of a flat list `y`. |
| `keep`      | Verb        | Remove from `x` that which isn't in `y`. |
| `upalpha`   | Noun        | `upalpha` &leftrightarrow; `'ABCDEFGHIJKLMNOPQRSTUVWXYZ'` |
| `downalpha` | Noun        | `downalpha` &leftrightarrow; `'abcdefghijklmnopqrstuvwxyz'` |

## Examples

```J
   sgn =: * MONAD
   sgn 3
1
   3 sgn 4
no dyadic case
   NB. printed to stderr

   is_one =: =&1
   any_are_one =: is_one ANY
   any_are_one 1 2 3 4
1
   any_are_one 5 2 3 4
0
   max 3 4 5 6 2 _2
6
   min 3 4 5 6 2 _2
_2
   t 3 4 2
1 1 1
   t 0 1 2 3
0 1 1 1
   f 0 1 2 3
1 0 0 0
   tree repr <'any_are_one'
  +- [:
--+- any
  +- is_one
```