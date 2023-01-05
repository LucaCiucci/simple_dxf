#pragma once

#include <simple_dxf/utils.hpp>

// derived from https://github.com/FreeCAD/FreeCAD/blob/b44d70f6460b8175cc1c554d68b86b432845563b/src/Base/Vector3D.h

namespace simple_dxf
{
	class Vector3d {
	public:

		Vector3d() = default;
		Vector3d(const Vector3d&) = default;
		Vector3d(Vector3d&&) = default;
		Vector3d(double x, double y, double z) : m_data{ x, y, z } {}
		Vector3d(double x, double y) : m_data{ x, y, 0.0 } {}

		explicit Vector3d(const double* data) : m_data{ data[0], data[1], data[2] } {}

		Vector3d& operator=(const Vector3d&) = default;
		Vector3d& operator=(Vector3d&&) = default;

		double* data() { return m_data; }
		const double* data() const { return m_data; }

		explicit operator double* () { return m_data; }
		explicit operator const double* () const { return m_data; }

		double& operator[](int i) { return m_data[i]; }
		const double& operator[](int i) const { return m_data[i]; }


		double& x() { return m_data[0]; }; const double& x() const { return m_data[0]; };
		double& y() { return m_data[1]; }; const double& y() const { return m_data[1]; };
		double& z() { return m_data[2]; }; const double& z() const { return m_data[2]; };

		Vector3d& normalize();

		Vector3d distanceToLineSegment(const Vector3d& rclP1, const Vector3d& rclP2) const;

		double getAngle(const Vector3d& rcVect);

		double length() const;

	private:
		double m_data[3] = {};
	};

	inline Vector3d operator+(const Vector3d& a, const Vector3d& b) {
		return Vector3d(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
	}

	inline Vector3d operator-(const Vector3d& a, const Vector3d& b) {
		return Vector3d(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
	}

	inline Vector3d operator*(const Vector3d& a, double b) {
		return Vector3d(a.x() * b, a.y() * b, a.z() * b);
	}

	inline Vector3d operator*(double a, const Vector3d& b) {
		return Vector3d(a * b.x(), a * b.y(), a * b.z());
	}

	inline Vector3d operator/(const Vector3d& a, double b) {
		return Vector3d(a.x() / b, a.y() / b, a.z() / b);
	}

	inline double dot(const Vector3d& a, const Vector3d& b) {
		return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
	}

	inline double length(const Vector3d& a) { return a.length(); }

	inline double distance(const Vector3d& a, const Vector3d& b) { return length(a - b); }


	inline Vector3d& Vector3d::normalize()
	{
		double len = std::sqrt(dot(*this, *this));
		if (len > 0.0) {
			m_data[0] /= len;
			m_data[1] /= len;
			m_data[2] /= len;
		}

		return *this;
	}

	inline Vector3d Vector3d::distanceToLineSegment(const Vector3d& rclP1, const Vector3d& rclP2) const
	{
		double len2 = distance(rclP1, rclP2);
		if (len2 == 0)
			return rclP1;

		Vector3d p2p1 = rclP2 - rclP1;
		Vector3d pXp1 = *this - rclP1;
		double _dot = dot(pXp1, p2p1);
		double t = clamp<double>(_dot / len2, 0, 1);
		Vector3d dist = t * p2p1 - pXp1;
		return dist;
	}

	inline double Vector3d::getAngle(const Vector3d& rcVect)
	{
		double len1 = this->length();
		double len2 = rcVect.length();
		if (len1 <= std::numeric_limits<double>::epsilon() || len2 <= std::numeric_limits<double>::epsilon())
			return std::numeric_limits<double>::quiet_NaN(); // division by zero

		double _dot = dot(*this, rcVect);
		_dot /= len1;
		_dot /= len2;

		if (_dot <= -1.0)
			return acos(-1.0); // pi
		else if (_dot >= 1.0)
			return 0.0;

		return double(acos(_dot));
	}

	inline double Vector3d::length() const
	{
		return std::sqrt(dot(*this, *this));
	}
}