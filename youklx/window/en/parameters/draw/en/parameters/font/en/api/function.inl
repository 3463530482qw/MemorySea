Fontcmd& sf(Font* fot) { this->fot=fot;return *this; }
Fontcmd& sc(std::string tex) { text=tex;return *this; }
Fontcmd& sp(float sx, float sy) { x=sx;y=sy;return *this; }
Fontcmd& ss(float fsize) { fontSize=fsize;return *this; }
Fontcmd& srot(float ro,float rx,float ry) { rotate=ro;rox=rx;roy=ry;return *this; }
Fontcmd& srgba(std::array<float, 4> srgba) { rgba=srgba;return *this;}
