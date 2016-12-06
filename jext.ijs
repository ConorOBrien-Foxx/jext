NB. enter the special locale for defining things
18 !: 4 <'z'
SP =: ' '
tabulate =: [: ([:<;._1 SP&,);._1 LF&,

([:(}:([:".[,' =: ',])&.>{:)]#~(<i.0)&~:)"1 tabulate ]raw_names =: }: noun define
equal self_classify =
less_than less lt box <
larger_than more gt open >
lesser_of floor <.
larger_of ceil >.
decrement less_or_equal dec lte <:
increment larger_or_equal inc gte >:
conj conjugate add plus +
real_imaginary or real_imag gcd +.
double not_or +:
times mul multiply sign sgn *
angle length lcm and *.
square not_and *:
neg negate negative minus sub -
not less w_out without -.
halve match same -:
reciprocal recip div divide %
m_inv m_div m_inverse m_divide %.
sqrt square_root root %:
exp exponential exponentiate power pow ^
nat_log ln ^.
rep repeat ^:
shape shape_of $
sparse $.
self self_reference $.
reflex passive evoke ~
nub ~.
nub_sieve not_equal neq ~:
magnitude residue divides |
reverse rotate shift |.
transpose |:
det determinant dot_product dot_prod .
even ..
odd .:
explicit monad_dyad :
obverse :.
adverse ::
ravel append ,
ravel_items stitch ,.
itemize laminate ,:
raze link ;
cut ;.
words sequential sequential_machine ;:
tally copy #
base2 base #.
antibase2 antibase #:
abase abase2 from_base from_base2 #.inv
fac factorial out_of !
fit custom customize !.
foreign !:
insert table /
oblique key /.
grade_up sort /:
prefix infix \
suffix outfix \.
grade_down sort_down \:
left [
right ]
catalogue from get {
first head take {.
last tail {:
map fetch {::
item_amend amend }
notfirst behead drop }.
notlast betail curtail }:
rank "
do numbers ".
default_format format ":
tie gerund `
atop @
agenda @.
at @:
bond compose &
under &.
dual &.:
appose &:
roll deal ?
f_roll fixed_roll f_deal fixed_deal ?.
alphabet alpha a.
ace a:
anagram_index anagram A.
boolean basic b.
cycle_direct permute C.
level_derivative d.
derivative D.
secant secant_slope D:
raze_in member in e.
member_of_interval E.
fix f.
hypergeometric H.
integers ints index_of index i.
steps index_of_last last_index_of i:
indices interval_index I.
imaginary complex j.
level_of L.
level_at L:
memo M.
pi_times circle circle_func o.
roots polynomial p.
poly_derive poly_integrate p..
primes p:
prime_factors prime_exponents q:
angle polar r.
symbol s:
spread S:
taylor taylor_coeff t.
weighted_taylor t:
taylor_approximation taylor_apx T.
unicode chr u:
extended_precision extended x:
zero 0:
one 1:
two 2:
three 3:
four 4:
five 5:
six 6:
seven 7:
eight 8:
nine 9:
)

MONAD =: adverb def 'u : ([: err ''no dyadic case''"_)'
DYAD =: adverb def '([: err ''no monadic case''"_) : u'

min =: <./
max =: >./
t =: 0 bond neq
f =: not atop t
repr =: 5!:
atomic =: 1 [ boxed =: 2 [ tree =: 4 [ linear =: 5 [ paren =: 6 [ explicit =: 7
monadic =: 1 [ dyadic =: 2
adv_of =: adverb define
  up =. linear repr <'u'
  adverb def ('[: ' , up , ' u')
)
T =: t adv_of
F =: f adv_of
any =: max T
all =: min T
none =: max F
ANY =: any adv_of
ALL =: all adv_of
TRUTHY =: monad define
  if. y do. 1
  else.     0
  end.
)
truthy =: t @ {.

ab =: #.inv
unbox =: >@

NB. N pad fill ; str
NB. fills the right of str with `fill` until of length `N`
pad =: [ $ >@last@] , [ # >@first@]
lpad =: -@[ {. >@last@] ,~ [ # >@first@]
snumpad =: [ lpad '0'&;

enbox =: <@(>^:_)
exec =: 0!:0@enbox
reload =: monad define
  if. 0=#y do. y =. 'jext.ijs' end.
  exec y
)

err =: [: 0 0&$@(1!:2&5) ,&LF
out =: 0 0&$@(1!:2&4)

printable =: (126 >: ord) *. 32 <: ord

ord =: 3&u:
comp =: ((] ; 32 u:@+ 95 ab #.~) 1x + max) :. (first unbox ab 95 #. 32x -~ 3 u: last unbox)
decomp =: comp inv
DECOMP =: [ ab 95 #. 32x -~ 3 u: ]
rle =: monad define
  text =. y
  i =. 0
  res =. 0 ; 0
  while. i < #text do.
    c =. i { text
    len =. 0
    while. c -: (i + len) { text do.
      len =. >: len
      if. (i + len) >: #text do. break. end.
    end.
    res =. res ,. c ; len
    i =. i + len
  end.
  }. |: res
)
NB. only is bijective for non-digits
RLE =: [: ; ":&.>@|."1@rle

apply =: conjunction define
  i =. 0
  r =. ''
  for_j. y do.
    if. i e. u do.  r =. r , v j
    else.           r =. r , j
    end.
    i =. >: i
  end.
  r
)

invariant =: adverb def '(= u)'
accept =: adverb def '(#~ u T)'
reject =: adverb def '(#~ u F)'
keep =: [ #~ e.
isupper =: toupper invariant
islower =: tolower invariant
upalpha =: 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
downalpha =: tolower upalpha
ISUPPER =: e.&upalpha
ISLOWER =: e.&upalpha
ascii =: (#~ printable) alpha
then =: conjunction def '[: u v'
sum =: +/
freq =: ~. ;"0 [: sum ] ="0 1 ~.
coset =: 18!:4@enbox
box_draw_opt =: 9!:7
stn =: 95x #. 32 -~ ord
succ =: inc&.stn : ([: stn inv [ + stn@])
prev =: dec&.stn : ([: stn inv [ - stn@])

NB. test class
coclass 'Stack'
create =: monad def 'items =: '''''
push =: monad def '# items =: items , < y'
top =: monad def '> last items'
pop =: monad def '(items =: betail items) ] pop 0'
inspect =: monad def 'items'
destory = codestroy

coset 'z'

NB. from http://code.jsoftware.com/wiki/Essays/Huffman_Coding
NB. frequencies hc letters
hc =: dyad define
  if. 1=#x do. y
  else. ((i{x),+/j{x) hc (i{y),<j{y [ i=. (i.#x) -. j=. 2{./:x end.
)

hcodes =: dyad define
  assert. x -:&$ y            NB. weights and words have same shape
  assert. (0<:x) *. 1=#$x     NB. weights are non-negative
  assert. 1 >: L.y            NB. words are boxed not more than once
  w =. ,&.> y                 NB. standardized words
  assert. w -: ~.w            NB. words are unique
  t =. 0 {:: x hc w           NB. minimal weight binary tree
  ((< S: 0 t) i. w) { <@(1&=)@; S: 1 {:: t
)

coset 'base'
NB. end jext.ijs
