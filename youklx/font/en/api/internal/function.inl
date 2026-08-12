bool bake(char32_t ch, float scale);
void rebuildAll(float scale);
void createAtlasImage();   // 按 atlasW/H 创建图像+视图+内存(绑定/重建共用)
void recreateTexture();    // 图集尺寸变化时重建贴图并更新描述符
