namespace youklx {
    // 图集尺寸变化时重建贴图并更新描述符(旧的随 raii 析构释放)
    void Font::recreateTexture() {
        createAtlasImage();
        uploadedW = atlasW;
        uploadedH = atlasH;

        vk::DescriptorImageInfo imageInfo;
        imageInfo.setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
        imageInfo.setImageView(*atlasView);
        imageInfo.setSampler(sampler);
        vk::WriteDescriptorSet write;
        write.setDstSet(descSet);
        write.setDstBinding(0);
        write.setDstArrayElement(0);
        write.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        write.setDescriptorCount(1);
        write.setPImageInfo(&imageInfo);
        device->updateDescriptorSets({write}, {});
    }
}
