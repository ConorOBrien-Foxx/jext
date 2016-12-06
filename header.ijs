final =: exit@0:
repl =: monad define
  if. y do. final =: 0:
  else.     final =: exit@0:  end.
  y
)
main =: monad define
  argv =: y
  try.   arge =: >@(".&.>) argv
  catch. arge =: i.0 0
  end.
  arg =: monad define
    try.   > y { argv
    catch. 
    end.
  )
