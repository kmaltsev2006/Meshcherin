/**
 * @brief Table of casts
 *
 *  pub    implicit static
 * D -> B     V       V
 * D&-> B&    V       V
 * B -> D     X       V (UB possible)
 * B&-> D     X       V (UB possible)
 *
 *  priv  implicit static
 * D -> B     X       X
 * D&-> B&    X       X
 * B -> D     X       X
 * B&-> D     X       X
 */

#include "common.hpp"

class Mom {};
class Son : public Mom {};
class Daughter : private Mom {};

void publicUpper() {
    static const auto lambdaCopy = [](Mom){};
    static const auto lambdaRef = [](Mom&){};

    Son s;
    
    // imiplicit
    lambdaCopy(s);
    lambdaRef(s);

    // static
    static_cast<Mom>(s);
    static_cast<Mom&>(s);
}

void pulicDown() {
    static const auto lambdaCopy = [](Son){};
    static const auto lambdaRef = [](Son&){};

    Son s; Mom& m {s}; // NOLINT

    // imiplicit
    // lambdaCopy(m); // error: no known conversion for argument 1 from ‘Mom’ to ‘Son’
    // lambdaRef(m); // error: no known conversion for argument 1 from ‘Mom’ to ‘Son&’
    
    // static
    static_cast<Son>(m); // possible UB if underlying object type is not Son
    static_cast<Son&>(m); // possuble UB if underlying object type is not Son
}

void privateUpper() {
    static const auto lambdaCopy = [](Mom){};
    static const auto lambdaRef = [](Mom&){};

    Daughter d;
    
    // imiplicit
    // lambdaCopy(d); // error: ‘Mom’ is an inaccessible base of ‘Daughter’
    // lambdaRef(d); // error: ‘Mom’ is an inaccessible base of ‘Daughter’

    // static
    // static_cast<Mom>(d); // error: ‘Mom’ is an inaccessible base of ‘Daughter’
    // static_cast<Mom&>(d); // error: ‘Mom’ is an inaccessible base of ‘Daughter’
}


void privateDown() {
    static const auto lambdaCopy = [](Daughter){};
    static const auto lambdaRef = [](Daughter&){};

    Mom m; // NOLINT

    // imiplicit
    // lambdaCopy(m); // error: no known conversion for argument 1 from ‘Mom’ to ‘Daughter’
    // lambdaRef(m); // error: no known conversion for argument 1 from ‘Mom’ to ‘Daughter&’
    
    // static
    // static_cast<Daughter>(m); // error: no matching function for call to ‘Daughter::Daughter(Mom&)’
    // static_cast<Daughter&>(m); // error: ‘Mom’ is an inaccessible base of ‘Daughter’
}

int main() {
    
}