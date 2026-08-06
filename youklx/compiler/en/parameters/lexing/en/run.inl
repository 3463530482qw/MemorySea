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
            } else if (inlinechar.find(token->back().back()) != inlinechar.end()) {
                token->push_back(line->substr(rptr, lptr));
            } else if (cptr == ':' || cptr == '+' || cptr == '-') {
                if(!token->empty() && cptr == token->back().back()) {
                    token->back() += line->substr(rptr, lptr);
                } else {
                    token->push_back(line->substr(rptr, lptr));
                }
            } else if (keyword.find(line->substr(rptr, lptr)) != keyword.end()) {
                token->push_back(line->substr(rptr, lptr));
            } else if (inlinechar.find((*line)[rptr]) != inlinechar.end()) {
                token->push_back(line->substr(rptr, lptr));
            } else {
                token->back() += line->substr(rptr, lptr);
            }
            rptr += lptr;
            std::println("token: {}", token->back());
        }
    }
}