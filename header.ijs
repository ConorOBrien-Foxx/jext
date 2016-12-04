final =: exit@0:
repl =: monad define
  if. y do. final =: 0:
  else.     final =: exit@0:  end.
  y
)
main =: monad define
  argv =: y
  try. arge =: >@(".&.>) argv
  catch. arge =: i.0 0
  end.
  open_arg =: ".@>
  arg =: monad def 'open_arg y { argv'
