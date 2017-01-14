/*!
  \file
  @author Eric Bailey
  @date 2016-12-11
  @brief Egyptian Multiplication
*/

/*! Add instances of `a` together `n` times.

  Efficiency: \f$\mathcal{O}(n)\f$

  @param n the number of instances of `a` to add.
  @param a the number to add `n` times.
  @return \f$n \times a\f$
*/
int multiply0(int n, int a)
{
  /// \f{equation}{1a = a \tag{2.1}\f}
  if (n == 1) return a;
  /// \f{equation}{(n + 1)a = na + a \tag{2.2}\f}
  return multiply0(n - 1, a) + a;
}

/*! Determine whether a number is odd.

  \f[
    n = \frac{n - 1}{2} + \frac{n - 1}{2} + 1 \Longrightarrow \text{odd}(n)
  \f]

  \f[
    \text{odd}(n) \Longrightarrow \text{half}(n) = \text{half}(n - 1)
  \f]
 */
bool odd(int n)
{
  return n & 0x1;
}

/*! Return half of a given number.

  \f[
    \text{half}(n) = \frac{n}{2}
  \f]
 */
int half(int n)
{
  return n >> 1;
}

/*! "Egyptian multiplication" aka the "Russian Peasant Algorithm"

  \f{eqnarray*}{
    4a &=& ((a + a) + a) + a \\
       &=& (a + a) + (a + a)
  \f}

  The law of associativity of addition:
  \f[
    a + (b + c) = (a + b) + c
  \f]

  | Power of 2 |      1-bits      | Doublings |
  | ---------: | :--------------: | --------: |
  |          1 | \f$\checkmark\f$ |        59 |
  |          2 |                  |       118 |
  |          4 |                  |       236 |
  |          8 | \f$\checkmark\f$ |       472 |
  |         16 |                  |       944 |
  |         32 | \f$\checkmark\f$ |      1888 |

  \f[
    41 \times 59 = (1 \times 59) + (8 \times 59) + (32 \times 59)
  \f]

  Efficiency: \f$\mathcal{O}(\log_2 n)\f$

  \f{eqnarray*}{
    \#_+(n) &=& \lfloor \log_2 n \rfloor + (v(n) - 1) \\
       v(n) &=& \text{the number of 1s in the binary representation of $n$,
                      i.e. the }\textit{population count}
  \f}
 */
int multiply1(int n, int a)
{
  if (n == 1) return a;
  int result = multiply1(half(n), a + a);
  if (odd(n)) result = result + a;
  return result;
}
