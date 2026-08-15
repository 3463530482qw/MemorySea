namespace youklx {
    Fontcmd& Fontcmd::iload(const Fontmap& fmap, const INIReader& reader, const std::string& ivrtp) {
        // font 键按名字从字体仓库取字体对象;缺省或为空则保留当前绑定的字体
        std::string fontName = reader.Get(ivrtp, "font", "");
        if (!fontName.empty()) fot = fmap.get(fontName);

        // 其余参数的缺省值 = 当前值:ini 没写的键保持原样,只覆盖写了的键
        text     = reader.Get(ivrtp, "text", text);
        x        = static_cast<float>(reader.GetReal(ivrtp, "x", x));
        y        = static_cast<float>(reader.GetReal(ivrtp, "y", y));
        fontSize = static_cast<float>(reader.GetReal(ivrtp, "fontSize", fontSize));
        rotate   = static_cast<float>(reader.GetReal(ivrtp, "rotate", rotate));
        rox      = static_cast<float>(reader.GetReal(ivrtp, "rox", rox));
        roy      = static_cast<float>(reader.GetReal(ivrtp, "roy", roy));
        rgba[0]  = static_cast<float>(reader.GetReal(ivrtp, "r", rgba[0]));
        rgba[1]  = static_cast<float>(reader.GetReal(ivrtp, "g", rgba[1]));
        rgba[2]  = static_cast<float>(reader.GetReal(ivrtp, "b", rgba[2]));
        rgba[3]  = static_cast<float>(reader.GetReal(ivrtp, "a", rgba[3]));
        order    = static_cast<int>(reader.GetInteger(ivrtp, "order", order));

        // 描边:显式开关(缺省保留当前值);outlineW 是 em,须 ≤ 所绑字体的 pad,否则被裁剪
        outline        = reader.GetBoolean(ivrtp, "outline", outline);
        outlineW       = static_cast<float>(reader.GetReal(ivrtp, "outlineW", outlineW));
        outlineColor[0] = static_cast<float>(reader.GetReal(ivrtp, "outlineR", outlineColor[0]));
        outlineColor[1] = static_cast<float>(reader.GetReal(ivrtp, "outlineG", outlineColor[1]));
        outlineColor[2] = static_cast<float>(reader.GetReal(ivrtp, "outlineB", outlineColor[2]));
        outlineColor[3] = static_cast<float>(reader.GetReal(ivrtp, "outlineA", outlineColor[3]));

        dirty = true;   // 批量覆盖后下次绘制重算顶点缓冲
        return *this;
    }
}
