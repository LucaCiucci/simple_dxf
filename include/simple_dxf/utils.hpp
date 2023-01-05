#pragma once

namespace simple_dxf
{
	template <class T>
	const T& clamp(const T& v, const T& lo, const T& hi) {
		return std::max(lo, std::min(v, hi));
	}
}