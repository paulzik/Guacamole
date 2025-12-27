#include "AudioClipImporter.h"
#include "Assets/Texture2D.h"
#include <iostream>
#include <memory>
#include <Audio/AudioClip.h>

std::shared_ptr<Asset> AudioClipImporter::Load(const std::string& path)
{
    auto clip = std::make_shared<AudioClip>(path);

    return clip;
}
