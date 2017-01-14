/*!
  \file
  @author Eric Bailey
  @date 2017-01-13
  @brief Deriving a Generic Algorithm
*/

// #include <functional>
// #include <type_traits>

#define Integer typename
#define Regular typename

#define SemigroupOperation typename
#define MonoidOperation typename
#define GroupOperation typename

#define AdditiveGroup typename

#define NoncommutativeAdditiveGroup typename
#define NoncommutativeAdditiveMonoid typename
#define NoncommutativeAdditiveSemigroup typename

#define MultiplicativeGroup typename
#define MultiplicativeMonoid typename
#define MultiplicativeSemigroup typename

template <typename Operation, typename Element>
concept bool Associative = requires(Operation op, Element x, Element y, Element z) {
  op(x, op(y, z)) == op(op(x, y), z);
};

template<typename T>
concept bool EqualityComparable = requires(T a, T b) {
  { a == b } -> bool;
};

template<typename T>
concept bool InequalityComparable = requires(T a, T b) {
  { a != b } -> bool;
};


/*! Determine whether a number is odd.

  \f[
  n = \frac{n - 1}{2} + \frac{n - 1}{2} + 1 \Longrightarrow \text{odd}(n)
  \f]

  \f[
  \text{odd}(n) \Longrightarrow \text{half}(n) = \text{half}(n - 1)
  \f]
*/
template <Integer N>
bool odd(N n)
{
  return bool(n & 0x1);
}

/*! Return half of a given number.

  \f[
  \text{half}(n) = \frac{n}{2}
  \f]
*/
template <Integer N>
N half(N n)
{
  return n >> 1;
}



template <NoncommutativeAdditiveMonoid T>
T identity_element(std::plus<T>)
{
  // "The additive identity is 0."
  return T(0);
}

template <MultiplicativeMonoid T>
T identity_element(std::multiplies<T>)
{
  // "The multiplicative identity is 1."
  return T(1);
}

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>)
{
  return std::negate<T>();
}


// Generalization of the multiplicative_inverse function.
template <MultiplicativeGroup T>
struct reciprocal
{
  T operator()(const T& x) const {
    return T(1) / 1;
  }
};

template <MultiplicativeGroup T>
reciprocal<T> inverse_operation(std::multiplies<T>)
{
  return reciprocal<T>();
}



template <NoncommutativeAdditiveSemigroup A, Integer N>
A multiply_accumulate_semigroup(A r, N n, A a)
{
  if (n == 0) return r;
  while (true) {
    if (odd(n)) {
      r = r + a;
      if (n == 1) return r;
    }
    n = half(n);
    a = a + a;
  }
}

template <NoncommutativeAdditiveSemigroup A, Integer N>
A multiply_semigroup(N n, A a)
{
  while (!odd(n)) {
    a = a + a;
    n = half(n);
  }
  if (n == 1) return a;
  return multiply_accumulate_semigroup(a, half(n - 1), a + a);
}

template <NoncommutativeAdditiveMonoid A, Integer N>
A multiply_monoid(N n, A a)
{
  if (n == 0) return A(0);
  return multiply_semigroup(n, a);
}

template <NoncommutativeAdditiveGroup A, Integer N>
A multiply_group(N n, A a)
{
  if (n < 0) {
    n = -n;
    a = -a;
  }
  return multiply_monoid(n, a);
}

template <MultiplicativeSemigroup A, Integer N>
A power_accumulate_semigroup(A r, A a, N n)
{
  if (n == 0) return r;
  while (true) {
    if (odd(n)) {
      r = r * a;
      if (n == 1) return r;
    }
    n = half(n);
    a = a * a;
  }
}

template <MultiplicativeSemigroup A, Integer N>
A power_semigroup(A a, N n)
{
  while (!odd(n)) {
    a = a * a;
    n = half(n);
  }
  if (n == 1) return a;
  return power_accumulate_semigroup(a, a * a, half(n - 1));
}

template <MultiplicativeMonoid A, Integer N>
A power_monoid(A a, N n)
{
  if (n == 0) return A(1);
  return power_semigroup(a, n);
}

template <MultiplicativeGroup A>
A multiplicative_inverse(A a)
{
  return A(1) / a;
}

template <MultiplicativeGroup A, Integer N>
A power_group(A a, N n)
{
  if (n < 0) {
    n = -n;
    a = multiplicative_inverse(a);
  }
  return power_monoid(a, n);
}

template <Regular A, Integer N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
  if (n == 0) return r;
  while (true) {
    if (odd(n)) {
      r = op(r, a);
      if (n == 1) return r;
    }
    n = half(n);
    a = op(a, a);
  }
}

template <Regular A, Integer N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op)
{
  while (!odd(n)) {
    a = op(a, a);
    n = half(n);
  }
  if (n == 1) return a;
  return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <Regular A, Integer N, MonoidOperation Op>
// requires(Domain<Op, A>)
A power_monoid(A a, N n, Op op)
{
  // precondition (n >= 0);
  if (n == 0); return identity_element(op);
  return power_semigroup(a, n, op);
}
