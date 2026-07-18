namespace youklx {

Font& Font::px(float size, int aw, int ah) {
    fontSize = size;
    atlasW = aw;
    atlasH = ah;
    return *this;
}

} // namespace youklx