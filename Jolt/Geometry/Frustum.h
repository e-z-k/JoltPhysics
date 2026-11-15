#pragma once
#include <Jolt/Math/Math.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Geometry/Plane.h>

JPH_NAMESPACE_BEGIN

class Frustum
{
public:
	JPH_OVERRIDE_NEW_DELETE

	Frustum(Vec3 position, Vec3 direction, float near, float far, float FOV)
	{
		auto direction_right  = direction.Cross(Vec3(0.f, 1.f, 0.f));
		auto direction_up     = direction_right.Cross(direction);
		auto near_point       = position + direction * near;
		auto far_point        = position + direction * far;
		auto top_near_point   = near_point + direction_up * 10.f;
		auto top_far_point    = far_point + direction_up * 1.f * far;
		auto bottom_near_point = near_point + -direction_up * 10.f;
		auto bottom_far_point = far_point + -direction_up * 1.f * far;

		auto bottom_dir = (bottom_far_point - bottom_near_point).Normalized();
		auto bottom_normal_right = bottom_dir.Cross(Vec3(0.f, 1.f, 0.f));
		auto bottom_normal = bottom_normal_right.Cross(bottom_dir);

		auto top_dir = (top_far_point - top_near_point).Normalized();
		auto top_normal_right = top_dir.Cross(Vec3(0.f, 1.f, 0.f));
		auto top_normal = top_dir.Cross(top_normal_right);

		Near   = Plane::sFromPointAndNormal(near_point, direction);
		Far    = Plane::sFromPointAndNormal(far_point, -direction);
		Bottom = Plane::sFromPointAndNormal((bottom_far_point + bottom_near_point) / 2.f, bottom_normal);
		Top    = Plane::sFromPointAndNormal(top_near_point, top_normal);

		auto right_point = position + direction_right * 4.f;
		auto left_point = position + direction_right * -4.f;

		Quat quat = Quat::sRotation({0.f, 1.f, 0.f}, DegreesToRadians(90.f - FOV/2.f));

		auto right_dir = quat * direction;
		auto left_dir = quat.InverseRotate(direction);

		Right = Plane::sFromPointAndNormal(right_point, right_dir);
		Left = Plane::sFromPointAndNormal(left_point, left_dir);
	}

	Plane Near, Far, Bottom, Top, Left, Right;
};

JPH_NAMESPACE_END
