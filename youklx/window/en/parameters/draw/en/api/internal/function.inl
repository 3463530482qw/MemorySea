static char32_t utf8next(const char*& p);
void fontblocks(const Fontcmd& cmd, float scale, std::vector<fontblock>& blocks);
void fontemit(const Fontcmd& cmd, const fontblock& b, float ow, float aa, float cosr, float sinr);
