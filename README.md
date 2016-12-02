# jext 

compile `jext` as:

    g++ jext.cpp -o jext

Then, run as:

    jext <name> [<arguments>]

Currently, the file must be located in the same location as `jext`.

## What is jext?

Well, jext is a simple derivative of J. First and foremost, it wraps the program in an explicit functions, so you can use controls straight from the program. For example:

```j
NB. controls.jext
for_j. i. 10 do.
  echo j
end.
```

The output of the file:

```
λ jext controls.jext
0
1
2
3
4
5
6
7
8
9
```

Here's how the file is currently compiled to, in J:

```j
load 'jext.ijs'
final =: monad : 'exit 0'
main =: monad define
  argv =: y
  try. arge =: >@(".&.>) argv
  catch. arge =: i.0 0
  end.
  open_arg =: ".@>
  arg =: monad : 'open_arg y { argv'
  for_j. i. 10 do.
    echo j
  end.
)
main <''
final ''
```

Note that the arguments are compiled into the program, as passed to main in `main <''`.