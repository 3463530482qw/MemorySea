Fontcmd& sf(Font* fot) { this->fot=fot; dirty=true; return *this; }
Fontcmd& sc(std::string tex) { text=tex; dirty=true; return *this; }
Fontcmd& sp(float sx, float sy) { x=sx;y=sy; dirty=true; return *this; }
Fontcmd& ss(float fsize) { fontSize=fsize; dirty=true; return *this; }
Fontcmd& srot(float ro,float rx,float ry) { rotate=ro;rox=rx;roy=ry; dirty=true; return *this; }
Fontcmd& srgba(std::array<float, 4> srgba) { rgba=srgba; dirty=true; return *this; }
Fontcmd& so(int order) { this->order=order; return *this; }
Fontcmd& soutline(bool oon, float sw, std::array<float, 4> scol) { outline=oon; outlineW=sw; outlineColor=scol; dirty=true; return *this; }
Fontcmd& iload(const Fontmap& fmap, const INIReader& reader, const std::string& ivrtp);
