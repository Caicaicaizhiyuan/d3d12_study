#include "shape.h"



using namespace DirectX;

GeoCreator::MeshData GeoCreator::createflower(
    float a, float b, float c,
    int k, int m, int N)
{
    MeshData mesh;

    constexpr float PI = XM_PI;
    const float dTheta = 2.0f * PI / N;
    const float rMax = a + b;

    // 中心点
    mesh.Vertices.emplace_back(
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 1.0f),
        XMFLOAT4(1.0f, 0.2f, 0.3f, 1.0f)
    );

    // 周围点
    for (int i = 0; i <= N; ++i)
    {
        float theta = i * dTheta;
        float r = a + b * std::cos(k * theta) *
            (1.0f + c * std::sin(m * theta));

        float x = r * std::cos(theta);
        float y = r * std::sin(theta);

        // 颜色：从中心到边缘渐变
        float t = saturate(r / rMax);
        XMFLOAT4 color(
            1.0f - 0.5f * t,
            0.2f + 0.6f * t,
            0.3f + 0.5f * t,
            1.0f
        );

        mesh.Vertices.emplace_back(
            XMFLOAT3(x, y, 0.0f),
            XMFLOAT3(0.0f, 0.0f, 1.0f),
            color
        );
    }

    // Triangle Fan 索引
    for (int i = 1; i <= N; ++i)
    {
        mesh.Indices32.push_back(0);
        mesh.Indices32.push_back(i);
        mesh.Indices32.push_back(i + 1);
    }

    return mesh;
}

GeoCreator::MeshData GeoCreator::createWaves()
{
    return MeshData();
}
