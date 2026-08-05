namespace youklx {
    void Lexing::run() {
        token->clear();
        rptr = 0;
        for (;rptr < line->size();) {
            cptr = static_cast<unsigned char>((*line)[rptr]);
            switch (cptr >> 4) {
                case 12: case 13: lptr = 2; break;
                case 14: lptr = 3; break;
                case 15: lptr = 4; break;
                default: lptr = 1; break;
            }
            if (token->empty()) {
                token->push_back(line->substr(rptr, lptr));
            } else if (lptr == 1 && cptr == ' ') {
                rptr += lptr;
                continue;
            } else if (ichar->find(token->back().back()) != ichar->end()) {
                token->push_back(line->substr(rptr, lptr));
            } else if (cptr == ':' || cptr == '+' || cptr == '-') {
                if(!token->empty() && cptr == token->back().back()) {
                    token->back() += line->substr(rptr, lptr);
                } else {
                    token->push_back(line->substr(rptr, lptr));
                }
            } else if (kw->find(line->substr(rptr, lptr)) != kw->end()) {
                token->push_back(line->substr(rptr, lptr));
            } else if (ichar->find((*line)[rptr]) != ichar->end()) {
                token->push_back(line->substr(rptr, lptr));
            } else {
                token->back() += line->substr(rptr, lptr);
            }
            rptr += lptr;
        }
    }
}