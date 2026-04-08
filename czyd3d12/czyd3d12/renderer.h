#pragma once

#include "../../Common/d3dUtil.h"

enum class LightClass {
	BLINN_PHONG,
	PBR,
	TOON_CEL,
	TOON_ANIME,
	TOON_UNLIT
};

struct LightConfig
{
	LightClass model = LightClass::BLINN_PHONG;

	struct toonParams
	{
		uint32_t colorBand = 3;
		float edgeThreshold = 0.1f;
		float outlineWidth = 0.015f;
		float specularThreshold = 0.8f;
		float rimLightPower = 2.0f;
	};

	float ambientIntensity = 0.1f;
	float diffuseIntensity = 1.0f;
	float specularIntensity = 0.5f;
	float shininess = 32.0f;
};

class ShaderManager {
public:
	void Initialize(ID3D12Device* device);
	void CompileShaderVariants(const std::wstring& baseShaderPath);
	ID3D12PipelineState* GetPOS(LightClass model, bool normalMap, bool outline = false);

private:
	std::unordered_map<uint64_t, Microsoft::WRL::ComPtr<ID3D12PipelineState>> m_posMap;

	uint64_t GeneratePSOKey(LightClass model, bool normalMap, bool outline) {
		return (static_cast<uint64_t>(model) << 32) | (static_cast<uint64_t>(normalMap) << 16 )| (static_cast<uint64_t>(outline));
	}
};