#pragma once

#include "../../Common/d3dUtil.h"

class RenderItem {
public:
	RenderItem() = default;
	DirectX::XMFLOAT4X4 world = MathHelper::Identity4x4();

	int resourceChangeCount = 0;

	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	UINT ObjCBIndex = -1;

	Material* mat = nullptr;
	MeshGeometry* geo = nullptr;

	UINT indexCount = 0;
	UINT startLocation = 0;
	int baseVertexLocation = 0;

};

class GeoCreator {
public:
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	
	struct Vertex
	{
		Vertex();
		Vertex(
			const DirectX::XMFLOAT3& p,
			const DirectX::XMFLOAT3& n,
			const DirectX::XMFLOAT4& c
			):pos(p), normal(n), color(c) {
		}
		Vertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u) :
			pos(px, py, pz),
			normal(nx, ny, nz),
			color(tx, ty, tz,u){
		}

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 color;
	};

	struct MeshData
	{
		std::vector<Vertex> Vertices;
		std::vector<uint32> Indices32;

		std::vector<uint16>& GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices32.size());
				for (size_t i = 0; i < Indices32.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices32[i]);
			}

			return mIndices16;
		}

	private:
		std::vector<uint16> mIndices16;
	};
	inline float saturate(float x)
	{
		return x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x);
	}

	MeshData createflower(float a,float b,float c,int k, int m,int N);
	MeshData createWaves();

};



