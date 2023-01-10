# BigInt
### Create BigInt
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a;
    return 0;
}
```
### Get data to BigInt
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a("981259601"), b(18916563), c = 1294612489;
    BigInt d = a, e = '1', f = 1;
    return 0;
}
```
### Converting to string
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt c = 1294612489;
    std::string str = string(c);
    return 0;
}
```
### Show BigInt
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt c = 1294612489;
    cout << c;
    return 0;
}
```
### Arithmetic operations
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt c = 21, d = 5;
    cout << c+d << endl; // >>> 26
    cout << c-d << endl; // >>> 16
    cout << c*d << endl; // >>> 105
    cout << c/d << endl; // >>> 4
    cout << c%d << endl; // >>> 1
    return 0;
}
```
### Arithmetic operations v2
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt c = 21, d = 5;
    c += d;
    c -= d;
    c *= d;
    c /= d;
    c %= d;
    return 0;
}
```
### Boolean
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a = 5, b = 3, c = 7;
    if (a > b) cout << 1;
    else cout << 0; // >>> 1
    if(b < c) cout << 1;
    else cout << 0; // >>> 1
    return 0;
}
```
### Change signe
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a = 5;
    cout << -a; // >>> -5
    return 0;
}
```
### ++ and --
```c++
#include <iostream>
#include "BigInt.h"

int main() {
    BigInt a = 5;
    cout << ++a; // >> 6
    cout << --a; // >> 5
    cout << a--; // >> 5;
    cout << a; // >> 4;
    return 0;
}
```