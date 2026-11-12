#pragma once
#include <Jolt/Math/Vec3.h>
#include <Jolt/Geometry/Plane.h>

JPH_NAMESPACE_BEGIN

class Frustum
{
public:
	JPH_OVERRIDE_NEW_DELETE

	Frustum(Vec3 position, Vec3 direction, float near, float far, float FOV)
	{
		//auto direction_right  = direction.Cross(Vec3(0.f, 1.f, 0.f));
		//auto direction_up     = direction.Cross(direction_right);
		auto near_point       = position + direction * near;
		auto far_point        = position + direction * far;
		//auto top_near_point   = near_point + direction_up * 10.f;
		//auto top_far_point    = far_point + direction_up * 5.f * far;
		//auto bottom_near_point = near_point + -direction_up * 10.f;
		//auto bottom_far_point = far_point + -direction_up * 5.f * far;

		//auto bottom_dir = (bottom_far_point - bottom_near_point).Normalized();
		//auto bottom_normal_right = bottom_dir.Cross(Vec3(0.f, 1.f, 0.f));
		//auto bottom_normal = bottom_dir.Cross(bottom_normal_right);

		//auto top_dir = (top_far_point - top_near_point).Normalized();
		//auto top_normal_right = top_dir.Cross(Vec3(0.f, 1.f, 0.f));
		//auto top_normal = top_normal_right.Cross(top_dir);

		Near   = Plane::sFromPointAndNormal(near_point, direction);
		Far    = Plane::sFromPointAndNormal(far_point, -direction);
		//Bottom = Plane::sFromPointAndNormal((bottom_far_point + bottom_near_point) / 2.f, bottom_normal);
		//Top    = Plane::sFromPointAndNormal((bottom_far_point + bottom_near_point) / 2.f, top_normal);



	}

	Plane Near, Far;// Bottom, Top, Left, Right;
};

JPH_NAMESPACE_END
