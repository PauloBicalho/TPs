#include "Word.h"

Word Word::And("&&", Tag::AND);
Word Word::Or("||", Tag::OR);
Word Word::eq("==", Tag::EQ);
Word Word::ne("!=", Tag::NE);
Word Word::le("<=", Tag::LE);
Word Word::ge(">=", Tag::GE);
Word Word::minus("minus", Tag::MINUS);
Word Word::True("true", Tag::TRUE);
Word Word::False("false", Tag::FALSE);
Word Word::temp("t", Tag::TEMP);
