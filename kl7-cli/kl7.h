//
///  \file KL7.h
///  \package kl7
//
///  \author Joseph Dunn on 9/5/19.
///  \copyright © 2019 Joseph Dunn..
//

/*
 Dirk Rijmenants's original simulator copyright © 2006-2013
 
 Copyright Information
 This program is provided as freeware and can be used and distributed under the
 following conditions: it is strictly forbidden to use this software or copies
 or parts of it for commercial purposes or to sell or lease this software, or
 to make profit from this program by any means. You are allowed to use this
 software only if you agree to these conditions.
 
 Disclaimer of Warranties
 This software and the accompanying files are supplied “as is” and without
 warranties of any kind, either expressed or implied, with respect to this
 product, its quality, performance, or fitness for any particular purpose.
 The entire risk as to its quality and performance is with the user. In no
 event will the author of this software be liable for any direct, indirect
 or consequential damages, resulting out of the use or inability to use this
 software.
 */

#ifndef KL7_h
#define KL7_h

#include <array>
using std::array;
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <fstream>
using std::ifstream;
#include <iomanip>
using std::setw;
#include <string>
using std::string;
#include <vector>
#include <boost/tokenizer.hpp>
using boost::tokenizer;
using boost::char_separator;

/// Wrap lines at word or punctuation boundaries
inline string line_wrap(string str,  ///< [in] Input string
                        size_t n        ///< [in] Line length
                       )
{
  tokenizer<> tok(str);
  string ret;
  size_t cur_line_length=0;
  for (auto it=tok.begin(); it != tok.end(); ++it) {
    if (cur_line_length+(*it).size()+1 < n) {
      ret += *it + " ";
      cur_line_length += (*it).size()+1;
    } else {
      ret += "\n" + (*it) + " ";
      cur_line_length = (*it).size()+1;
    }
  }
  return ret;
}

/// Structure containing the elements of the usually daily key settings
/// All of these elements would have been supplied on key sheets
struct KL7SystemIndicator {
  string indicator;                 ///< the system indicator
  array<char, 8> rotor_core;        ///< the 8 rotor cores lettered A-M
  array<int, 8> alphabet_ring_set;  ///< the position of each alphbet ring on its core
  array<int, 7> notch_ring_num;     ///< the 7 notch rings number 1 to 11
  array<string, 7> notch_ring_set;  ///< the position of each notch ring
  string letter_check;              ///< the letter check used to verify that
                                    ///< machine is properly configured
};


/// simulates cryptological core of KL7
class KL7 {
public:
  
  /// Construct KL7 given rotors and notches
  KL7 (KL7SystemIndicator si  ///< [in] struct with setup information
  )
  {
    for (size_t i=0; i<8; ++i) {
      rotor_core.at(i) = si.rotor_core.at(i) - 'A';
    }
    for (size_t i=0; i<8; ++i) {
      alphabet_ring_set.at(i) = si.alphabet_ring_set.at(i)-1;
    }
    for (size_t i= 0; i<7; ++i ) {
      notch_ring_num.at((i<=2) ? i : i+1) = si.notch_ring_num.at(i)-1;
    }
    for (size_t i=0; i<7; ++i) {
      char c0 = si.notch_ring_set.at(i)[0];
      int j = static_cast<int>(std::find(ring.begin(), ring.end(), c0) - ring.begin());
      j = (si.notch_ring_set.at(i).size()>1 && si.notch_ring_set.at(i)[1]=='+') ? j+1 : j;
      notch_ring_set.at((i<=2) ? i : i+1) = j;
    }
    set_position(array<char,7>{'A','A','A','A','A','A','A'});
    string calc_letter_check = encrypt("LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL").substr(42,11);
    cout << "System Indicator:    " << si.indicator << endl;
    cout << "Target letter check: " << si.letter_check << endl;
    cout << "Actual letter check: " << calc_letter_check << endl;
  }
  
  /// output the current state of the machine to an ostream
  friend ostream& operator<< (ostream& os,     ///< [in,out] reference to output stream
                              const KL7& kl7   ///< [in] the KL7 machine
                              ) {
    os << "Rotor Core: ";
    for (int i=0; i<8; ++i)
      os << static_cast<char>(kl7.rotor_core.at(i)+'A') << " ";
    os << endl << endl << "Alphabet Ring Set: ";
    for (int i=0; i<8; ++i)
      os << kl7.alphabet_ring_set.at(i) + 1 << " ";
    os << endl << endl << "Notch Ring Number: ";
    for (int i=0; i<8; ++i) {
      if (i==3)
        continue;
      os << kl7.notch_ring_num.at(i)+1 << " ";
    }
    os << endl << endl << "Notch Ring Set: ";
    for (int i=0; i<8; ++i) {
      if (i==3)
        continue;
      char c0 = kl7.ring.at(kl7.notch_ring_set.at(i));
      if (c0==' ') {
        os << kl7.ring.at(kl7.notch_ring_set.at(i)-1) << '+' << " ";
      } else
        os << c0 << " ";
    }
    os << endl << endl << "Current Position: ";
    for (int i=0; i<8; ++i) {
      if (i==3)
        continue;
      char c0 = kl7.ring.at(kl7.position.at(i));
      if (c0==' ') {
        os << kl7.ring.at(kl7.position.at(i)-1) << '+' << " ";
      } else
        os << c0 << " ";
    }
    return os;
  }
  
  /// return the filtered and encrypted string
  string encrypt(string str        ///< [in] the plain text
                 ) {
    str = filter_encrypt_in(str);
    string ret;
    for (int i=0; i<str.size(); ++i) {
      step_rotors();
      int c = alpha_to_plate.at(str[i]-'A');
      while(true) {
        for (int j=0; j<8; ++j) {
          int offset = position.at(j)+alphabet_ring_set.at(j);
          c = mod(wiring.at(rotor_core.at(j)).at(mod(c+offset,36))-offset,36);
        }
        if (isupper(base_plate.at(c)))
          break;
        c = num_to_plate.at(base_plate.at(c));
      }
      ret.push_back(base_plate.at(c));
    }
    return filter_encrypt_out(ret);
  }
  
  /// filter and decrypt the input string
  string decrypt(string str        ///< [in] input cipher text
                 ) {
    str = filter_decrypt_in(str);
    string ret;
    for (int i=0; i<str.size(); ++i) {
      step_rotors();
      int c = alpha_to_plate.at(str[i]-'A');
      while(true) {
        for (int j=7; j>=0; --j) {
          int offset = position.at(j)+alphabet_ring_set.at(j);
          c = mod(inverse_wiring.at(rotor_core.at(j)).at(mod(c+offset,36))-offset,36);
        }
        if (isupper(base_plate.at(c)))
          break;
        c = num_to_plate.at(base_plate.at(c));
      }
      ret.push_back(base_plate.at(c));
    }
    ret = filter_decrypt_out(ret);
    return ret;
  }
  
  /// step the rotors
  void step_rotors() {
    
    array<bool, 8> s;
    for (int j=0; j<8; ++j) {
      if (j==3)
        continue;
      int offset = mod(position.at(j)+alphabet_ring_set.at(j) + notch_ring_set.at(j)+10,36);
      s.at(j) = notch_ring.at(notch_ring_num.at(j)).at(offset);
    }
    
    for (int i=0; i<8; ++i) {
      if (i==3)
        continue;
    }
    /*
     Stepping
     Rotor Notched Rings ( 0 = inactive & 1 = active )
     1   Ring 7 = 0 AND (Ring 2 = 0 OR Ring 3 = 0)
     2   Ring 5 = 0 OR Ring 6 = 0
     3   Ring 2 = 1 OR Ring 6 = 1
     4   Ring 2 = 0 OR Ring 3 = 0
     5   Ring 1 = 0 OR Ring 3 = 1
     6   Ring 1 = 1 OR Ring 5 = 1
     7   Ring 4 = 0 AND (Ring 2 = 0 OR Ring 3 = 0)
     
     Renumbered 1=>0, 2=>1, 3=>2, 4=>4, 5=>5, 6=>6, 7=>7
     */
    if (s.at(7)==0 && (s.at(1)==0 || s.at(2)==0))
      position.at(0) = mod(position.at(0)+1,36);
    if (s.at(5)==0 || s.at(6)==0)
      position.at(1) = mod(position.at(1)+1,36);
    if (s.at(1)== 1 || s.at(6)==1)
      position.at(2) = mod(position.at(2)+1,36);
    if (s.at(1)==0 || s.at(2)==0)
      position.at(4) = mod(position.at(4)+1,36);
    if (s.at(0)==0 || s.at(2)==1)
      position.at(5) = mod(position.at(5)+1,36);
    if (s.at(0)==1 || s.at(5)== 1)
      position.at(6) = mod(position.at(6)+1,36);
    if (s.at(4)==0 && (s.at(1)==0 || s.at(2)==0))
      position.at(7) = mod(position.at(7)+1,36);
  }
  
  /// set postion given seven uppercase letters
  void set_position(array<char,7> pos     ///< [in] position
                    ) {
    for (size_t i=0; i<7; ++i) {
      position.at((i<=2) ? i : i+1) = alpha_to_ring.at(pos.at(i)-'A');
    }
    position.at(3) = 0;
  }
  
  /// return an array of strings of form X or X+ with position
  array<string, 7> get_position() {
    array<string, 7> ret;
    for (size_t i=0; i<8; ++i) {
      if (i==3)
        continue;
      char c0 = ring.at(position.at(i));
      size_t j = (i<=2) ? i : i-1;
      if (c0==' ') {
        ret.at(j).push_back(ring.at(position.at(i)-1));
        ret.at(j).push_back('+');
      } else {
        ret.at(j).push_back(ring.at(position.at(i)));
        ret.at(j).push_back(' ');
      }
    }
    return ret;
  }
  
  /// calculate mod using mathematical convention
  static int mod(int a,    ///< [in] number
                 int b     ///< [in] modulus
                 ) {
    int c = a % b;
    return (c>=0) ? c : c+b;
  }
  
  /// return the encryption of the plain text in a file
  string encrypt_file(string file_name,  ///< [in] the file name
                      string& preface    ///< [out] reference to line with indicators
                      ) {
    return process_file(ENCRYPT,file_name, preface);
  }
  
  /// return the decryption of the cipher text in a file
  string decrypt_file(string file_name,  ///< [in] the file name
                      string& preface    ///< [out] reference to line with indicators
                      ) {
    return process_file(DECRYPT,file_name, preface);
  }
  
  
  /// Initialize the static elements
  static void initialize_static(const array< array<char, 36>, 13>& wiring_in,  ///< [in] rotor wiring 1 based
                                const array< array<bool, 36>, 11>& notch_ring_in, ///< [in] notch bumps
                                const array<char, 36>& base_plate_in ///< [in] 26 letters & 10 digita
  ) {
    for (size_t i=0; i<36; ++i){
      if (isupper(ring.at(i)))
        alpha_to_ring.at(ring.at(i)-'A') = static_cast<char>(i);
      else
        plus_letters.push_back(ring.at(i-1));
    }
    for (size_t i=0; i<13; ++i) {
      for (size_t j=0; j<36; ++j) {
        wiring.at(i).at(j) = wiring_in.at(i).at(j)-1;
        inverse_wiring.at(i).at(wiring_in.at(i).at(j)-1) = j;
      }
    }
    notch_ring = notch_ring_in;
    base_plate = base_plate_in;
    for (size_t i=0; i<36; ++i) {
      if (isupper(base_plate.at(i)))
        alpha_to_plate.at(base_plate.at(i)-'A') = static_cast<char>(i);
      else
        num_to_plate.at(base_plate.at(i)) = static_cast<char>(i);
    }
    
  }
  
  /// print the static elements
  static void print_static(ostream& os   ///< [in,out] the ostream to use
                           ) {
    os << "Ring: ";
    for (auto a : ring)
      os << a;
    os << endl << endl << "Alpha to Ring" << endl;
    for (auto a : alpha_to_ring)
      os << static_cast<int>(a) << " ";
    os << endl << endl << "Wiring: " << endl;
    for (int i=0; i<static_cast<int>(wiring.size()); ++i) {
      os << static_cast<char> ('A'+i) << ": ";
      for (auto a : wiring[i])
        os << static_cast<int>(a) << " ";
      os << endl;
    }
    os << endl << "Inverse Wiring: " << endl;
    for (int i=0; i<static_cast<int>(inverse_wiring.size()); ++i) {
      os << static_cast<char> ('A'+i) << ": ";
      for (auto a : inverse_wiring[i])
        os << static_cast<int>(a) << " ";
      os << endl;
    }
    os << endl << "Base Plate" << endl;
    for (auto a : base_plate)
      if (isupper(a))
        os << a;
      else
        os << static_cast<int>(a);
    os << endl << endl << "Alpha to Plate" << endl;
    for (auto a : alpha_to_plate)
      os << static_cast<int>(a) << " ";
    os << endl << endl << "Num to Plate" << endl;
    for (auto a : num_to_plate)
      os << static_cast<int>(a) << " ";
    os << endl << endl << "Notch ring: " << endl;
    for (int i=0; i<static_cast<int>(notch_ring.size()); ++i){
      os << setw(2) << (i+1) << ": ";
      for (auto b : notch_ring[i])
        os << (b ? '1' : '0') << " ";
      os << endl;
    }
  }
  
  /// the letters on the alphabet ring that may be followed by plus
  static string plus_letters;
  
private:
  array<int, 8> rotor_core;
  array<int, 8> alphabet_ring_set;
  array<int, 8> notch_ring_num;
  array<int, 8> notch_ring_set;
  array<int, 8> position;
  bool let = true;
  static array<char, 36> ring;
  static array<char, 26> alpha_to_ring;
  static array<array<char, 36>, 13> wiring;
  static array<array<char, 36>, 13> inverse_wiring;
  static array<char, 36> base_plate;
  static array<char, 26> alpha_to_plate;
  static array<char, 10> num_to_plate;
  static array< array<bool,36> , 11> notch_ring;
  
  /// process text for encryption, setting let/fig state, & mapping space
  string filter_encrypt_in(string str      ///< [in] input text
  ) {
    static string let_fig{"PQWERTYUIO"};
    string ret;
    for (auto c : str) {
      c=toupper(c);
      if (c=='Z')
        ret.push_back('X');
      else if (c==' ')
        ret.push_back('Z');
      else if (c=='J')
        ret.push_back('Y');
      else if (isdigit(c)) {
        if (let) {
          ret.push_back('J');
          let = false;
        }
        ret.push_back(let_fig[c-'0']);
      } else if (isupper(c)) {
        if (!let) {
          ret.push_back('V');
          let = true;
        }
        ret.push_back(c);
      }
    }
    return ret;
  }
  
  /// add a space every five letters
  string filter_encrypt_out (string str   ///< [in] text from encryption engile
  ) {
    string ret;
    for (size_t i=0; i<str.size(); i+=5)
      ret += str.substr(i,5)+" ";
    return ret;
  }
  
  /// filter the input to the decryption process.  Removes white space
  string filter_decrypt_in(string str     ///< [in] raw output of decryption
  ) {
    string ret;
    for (size_t i=0; i<str.size(); ++i){
      char c=str[i];
      if (isupper(c))
        ret.push_back(c);
    }
    return ret;
  }
  
  /// Reverse the filter_ecrypt_in processing let/fig and spaces
  string filter_decrypt_out(string str     ///< t[in] he output of decryption engine
  ) {
    static string let_fig = "PQWERTYUIO";
    string ret;
    for (auto c : str) {
      if (c == 'Z') {
        ret.push_back(' ');
      } else if (c == 'J'){
        let=false;
      } else if (!let && let_fig.find(c) != string::npos) {
        ret.push_back("0123456789"[let_fig.find(c)]);
      } else if (!let && c == 'V'){
        ret.push_back(' ');
        let = true;
      } else {
        ret.push_back(c);
      }
    }
    return ret;
  }
  
  enum Direction {ENCRYPT, DECRYPT};
  
  /// return an encryption/decription of a file
  string process_file(Direction direction,  ///< [in] direction ENCRYPT/DECRYPT
                      string file_name,     ///< [in] the file name
                      string& preface       ///< [out] line with indicators
  )
  {
    ifstream file_in(file_name);
    if (!file_in)
      throw std::runtime_error("Unable to opern file: " + file_name);
    getline(file_in, preface);
    char_separator<char> sep(" ");
    tokenizer<char_separator<char> > tok(preface, sep);
    auto it = tok.begin();
    string system_indicator = (*it);
    it++;
    int i=0;
    string message_indicator;
    for (; it != tok.end(); ++i,++it) {
      message_indicator.push_back((*it)[0]);
    }
    if (i !=5)
      throw std::runtime_error("Message indicator is not 5 characters");
    set_position(array<char,7>{'A','A','A','A','A','A','A'});
    string m = encrypt(message_indicator);
    array<char,7> message_pos{m[0],m[1],m[2],m[3],m[4],m[0],m[1]};
    set_position(message_pos);
    string message_text;
    while (file_in) {
      string line;
      getline(file_in, line);
      message_text += line;
    }
    // This leaves the trailing system indicator in the cipher text
    // but it should be ignored by the decryption process
    if (direction==ENCRYPT)
      return line_wrap(encrypt(message_text),70);
    else
      return line_wrap(decrypt(message_text), 70);
  }
  

};





#endif /* KL7_h */
