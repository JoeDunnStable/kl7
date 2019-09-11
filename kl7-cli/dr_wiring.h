//
//  dr_wiring.hpp
//  kl7
//
//  Created by Joseph Dunn on 9/9/19.
//  Copyright © 2019 Joseph Dunn. All rights reserved.
//

#ifndef dr_wiring_h
#define dr_wiring_h

#include <array>
using std::array;

/*
 The government wiring, base_plate and notch_ring are still classified
 The items below are from Dirk Rijmenants's help file for his simulator
 */

/// The Dirk Rijmenants wiring for rotors, base_plate the bumps for notch ring
struct DR_wiring {
  static array< array<char, 36>, 13> wiring;     ///< rotor wiring for 13 rotors
  static array<char,36> base_plate;              ///< mapping of keys and reencyper
                                                 ///< numbers to plate
  static array< array<bool,36> , 11> notch_ring; ///< the bumps on the eleven
                                                 ///< notch rings
};

#endif /* dr_wiring_h */
