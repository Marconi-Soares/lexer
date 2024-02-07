#include "lexer.h"
#include <cctype>
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::stringstream;

Lexer::Lexer() {
  /*
    Keywords go here...
    example -> id_table["true"] = Id(Tag::TRUE, "true");
  */
}

Token Lexer::Scan() {
  while (std::isspace(peek)) {
    if (peek == '\n') {
      line += 1;
      // Once we're not working with a Parser yet, breaklines are EOF
      std::cout << "<END>";
      return Token{int('\n')};
    }
    peek = cin.get();
  }

  if (isdigit(peek)) {
    int v = 0;

    do {
      int n = peek - '0'; // cast char to int
      // explanation of the next statement in the following link
      // https://chat.openai.com/share/41db0118-77ea-43ec-9aa3-d75e6fc4b8a3
      v = 10 * v + n;
      peek = cin.get();
    } while (isdigit(peek));
    cout << "<NUM," << v << "> ";
    return Num{v};
  }

  if (isalpha(peek)) {
    stringstream ss;
    do {
      ss << peek;
      peek = cin.get();
    } while (isalpha(peek));
    string s = ss.str();
    auto pos = id_table.find(s);

    // id_table will return table.end() if s were not found
    if (pos != id_table.end()) {
      switch (pos->second.tag) {
      default:
        cout << "<ID," << pos->second.name << "> ";
        break;
      }
      return pos->second;
    }

    Id new_id{Tag::ID, s};
    id_table[s] = new_id;
    cout << "<ID," << new_id.name << "> ";
    return new_id;
  }

  Token t{peek};
  peek = ' ';
  cout << "<" << char(t.tag) << "> ";
  return t;
}

void Lexer::Start() {
  while (peek != '\n') {
    Scan();
  }
}
