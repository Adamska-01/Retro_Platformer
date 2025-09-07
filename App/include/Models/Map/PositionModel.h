#pragma once
#include <Core/Math/Vector2.h>
#include <nlohmann/json.hpp>


/** @brief 2D position for entities/tiles. */
struct PositionModel
{
	int x = 0;

	int y = 0;


	inline Vector2F ToVector2F(float positionScaler) const
	{
		auto scaledPos = Vector2F(x, y) * positionScaler;

		// Shift by half tile for rendering at the center
		scaledPos.x += positionScaler / 2.0f;
		scaledPos.y += positionScaler / 2.0f;

		return scaledPos;
	}


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PositionModel, x, y)
};